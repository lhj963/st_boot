#include "boot_check.h"

/* Packed layout is fixed-width. A 4-byte enum cannot fit in 140 bytes. */
typedef char boot_update_info_size_ok[(sizeof(UpdateInfo) == 140u) ? 1 : -1];
typedef char boot_update_status_is_byte[(sizeof(((UpdateInfo *)0)->eUpdateStatus) == 1u) ? 1 : -1];

static int boot_status_known(unsigned int status)
{
	return (status == UPDATE_STATUS_NO) ||
		(status == UPDATE_STATUS_START) ||
		(status == UPDATE_STATUS_FILE_OK) ||
		(status == UPDATE_STATUS_UPDATE_OK) ||
		(status == UPDATE_STATUS_UPDATE_FALSE);
}

int boot_vector_is_valid(unsigned int sp, unsigned int reset,
	unsigned int ram_lo, unsigned int ram_hi,
	unsigned int image_lo, unsigned int image_hi)
{
	unsigned int pc;

	if ((sp == 0xFFFFFFFFu) || (reset == 0xFFFFFFFFu))
	{
		return 0;
	}
	if ((ram_lo >= ram_hi) || (image_lo >= image_hi))
	{
		return 0;
	}
	/* Initial MSP is the first address above the stack, so it may equal ram_hi. */
	if ((sp <= ram_lo) || (sp > ram_hi) || ((sp & 7u) != 0u))
	{
		return 0;
	}
	if ((reset & 1u) == 0u)
	{
		return 0;
	}
	pc = reset & ~1u;
	if ((pc < image_lo) || (pc >= image_hi))
	{
		return 0;
	}
	return 1;
}

int boot_update_header_ok(const UpdateInfo *info, unsigned int computed_crc)
{
	if (info == 0)
	{
		return 0;
	}
	if (info->magic != UPDATE_INFO_MAGIC)
	{
		return 0;
	}
	if (info->usLayoutBytes != (unsigned short)sizeof(UpdateInfo))
	{
		return 0;
	}
	if (info->ucLayoutVersion != (uint8_t)UPDATE_INFO_LAYOUT_VER)
	{
		return 0;
	}
	if (!boot_status_known(info->eUpdateStatus))
	{
		return 0;
	}
	if (info->ulHeaderCrc != computed_crc)
	{
		return 0;
	}
	return 1;
}

int boot_update_bounds_ok(unsigned int start, unsigned int total,
	unsigned int staging_lo, unsigned int staging_hi)
{
	if (staging_lo >= staging_hi)
	{
		return 0;
	}
	if ((start < staging_lo) || (start >= staging_hi))
	{
		return 0;
	}
	if ((start & 3u) != 0u)
	{
		return 0;
	}
	if (total <= 4u)
	{
		return 0;
	}
	if (total > (staging_hi - start))
	{
		return 0;
	}
	if ((start + total) < start)
	{
		return 0;
	}
	return 1;
}

int boot_image_fits_partition(unsigned int total, unsigned int dest,
	unsigned int dest_end)
{
	if (total <= 4u)
	{
		return 0;
	}
	if (dest >= dest_end)
	{
		return 0;
	}
	if ((dest_end - dest) < total)
	{
		return 0;
	}
	return 1;
}

int boot_classify_image(const char *version, const char *driver_name,
	unsigned int flag_word, unsigned int expect_magic, int *is_driver)
{
	unsigned int n = 0;
	unsigned int i = 0;
	int match = 1;

	if (is_driver)
	{
		*is_driver = 0;
	}
	if ((version == 0) || (driver_name == 0) || (is_driver == 0))
	{
		return 0;
	}

	while (driver_name[n] != 0)
	{
		n++;
	}
	if (n == 0)
	{
		return 0;
	}

	for (i = 0; i < n; i++)
	{
		if ((version[i] == 0) || (version[i] != driver_name[i]))
		{
			match = 0;
			break;
		}
	}
	if (match)
	{
		if (flag_word == expect_magic)
		{
			*is_driver = 1;
			return 1;
		}
		/* Named BYSD_DRIVER but the flag word is wrong. Do not install it as an app. */
		return 0;
	}
	return 1;
}

int boot_slot_header_state(const unsigned char *text, unsigned int len,
	const char *manufacturer)
{
	unsigned int i = 0;
	unsigned int all_ff = 1;
	unsigned int lt = 0;
	unsigned int gt = 0;
	unsigned int mlen = 0;
	unsigned int nman = 0;

	if ((text == 0) || (len == 0) || (manufacturer == 0))
	{
		return BOOT_SLOT_MISMATCH;
	}

	for (i = 0; i < len; i++)
	{
		if (text[i] != 0xFFu)
		{
			all_ff = 0;
			break;
		}
	}
	if (all_ff || (text[0] == 0xFFu))
	{
		return BOOT_SLOT_EMPTY;
	}

	lt = len;
	for (i = 0; i < len; i++)
	{
		if (text[i] == '<')
		{
			lt = i;
			break;
		}
	}
	if (lt >= len)
	{
		return BOOT_SLOT_UNPARSED;
	}

	gt = len;
	for (i = lt + 1u; i < len; i++)
	{
		if (text[i] == '>')
		{
			gt = i;
			break;
		}
	}
	if ((gt >= len) || (gt <= (lt + 1u)))
	{
		return BOOT_SLOT_UNPARSED;
	}

	mlen = gt - (lt + 1u);
	while (manufacturer[nman] != 0)
	{
		nman++;
	}
	if (mlen != nman)
	{
		return BOOT_SLOT_MISMATCH;
	}
	for (i = 0; i < mlen; i++)
	{
		if (text[lt + 1u + i] != (unsigned char)manufacturer[i])
		{
			return BOOT_SLOT_MISMATCH;
		}
	}
	return BOOT_SLOT_OK;
}

int boot_slot_allows_install(int state)
{
	return state != BOOT_SLOT_MISMATCH;
}

int boot_commit_status(int program_ok, int image_crc_ok)
{
	if (program_ok && image_crc_ok)
	{
		return (int)UPDATE_STATUS_UPDATE_OK;
	}
	return (int)UPDATE_STATUS_UPDATE_FALSE;
}

void boot_pad_page(unsigned char *page, unsigned int page_size,
	const unsigned char *src, unsigned int src_len)
{
	unsigned int i = 0;
	unsigned int n = 0;

	if ((page == 0) || (page_size == 0))
	{
		return;
	}
	for (i = 0; i < page_size; i++)
	{
		page[i] = 0xFFu;
	}
	if ((src == 0) || (src_len == 0))
	{
		return;
	}
	n = src_len;
	if (n > page_size)
	{
		n = page_size;
	}
	for (i = 0; i < n; i++)
	{
		page[i] = src[i];
	}
}
