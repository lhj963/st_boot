
unsigned int crc32_table[256] = {0};


void init_crc32_tabel(void)
{
	unsigned int i = 0;
	unsigned int k = 0;
	unsigned int Val = 0;

	for (i = 0; i < 256; i++)
	{
	    Val = i;
	    for (k = 0; k < 8; k++)
	    {
	        if (Val & 1)
	        {
	            Val = 0xedb88320L ^ (Val >> 1);
	        }
	        else
			{
	            Val = Val >> 1;
			}
	    }
	    crc32_table[i] = Val;
	}
}


unsigned int calc_crc32(unsigned int PartialCrc,void *pbuf,unsigned int Length)
{
    unsigned int crc = 0xffffffffL;
    unsigned int i = 0;
    unsigned char *Buffer = (unsigned char *)pbuf;
	static unsigned char s_init_crc32_tab_flag = 0;

	if (s_init_crc32_tab_flag == 0)
	{
		init_crc32_tabel();
		s_init_crc32_tab_flag = 1;
	}

	if ((pbuf == 0) || (Length == 0))
	{
		return 0;
	}

    crc = PartialCrc ^ 0xffffffffL;

    for (i = 0; i < Length; i++)
    {
        //crc = Crc32Table[(crc ^ Buffer[i]) & 0xff] ^ (crc >> 8);
        crc = crc32_table[(crc ^ Buffer[i]) & 0xff] ^ (crc >> 8);
    }

    return (crc ^ 0xffffffffL);
}




