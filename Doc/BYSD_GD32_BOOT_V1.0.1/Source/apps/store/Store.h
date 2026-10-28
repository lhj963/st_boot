#ifndef __STORE_H__
#define __STORE_H__
#ifdef __cplusplus
extern "C" {
#endif


#ifndef __USE_UCOS__
#define __USE_UCOS__  0
#endif

#ifndef __USE_LFOS__
#define __USE_LFOS__  0
#endif






#define MAX_STORE_BLOCK_CNT   	16

//typedef unsigned char INT8U;
//typedef unsigned short INT16U;
//typedef unsigned long INT32U;





typedef void (*StoreHWInitProc)(void);
typedef void (*StoreHWWriteProc)(unsigned long addr,void *buf,unsigned int len);
typedef void (*StoreHWReadProc)(unsigned long addr,unsigned int wantToReadBytes,void *buf,unsigned int bufsize);
typedef void (*StoreHWEraseProc)(unsigned long sector_id);


extern void store_acce_config(unsigned int usStartSectorID,unsigned int usSectorCnt);

extern void empty_acce_store_block(void);

extern int store_init(StoreHWInitProc pFuncInit,
					StoreHWWriteProc pFuncWrite,
					StoreHWReadProc pFuncRead,
					StoreHWEraseProc pFuncEraseSector,
					unsigned int ulOneSectorSize);

extern unsigned long store_view_history(unsigned int usStoreBlockNo,char IsForward,
					unsigned long max_cnt,
					void *buf,unsigned int buflen,
					void (*handler)(unsigned long index,void *buf,unsigned int buflen));


extern int CreateStoreBlock(unsigned int usStoreBlockNo,unsigned int usStartSectorID,
			unsigned int usSectorCnt,unsigned int usOneDataUnitSize,unsigned char ucAlign);

extern int ReadOneData_Reverse(unsigned int usStoreBlockNo,unsigned int index,void *buf,unsigned int buflen);

extern int StoreOneData(unsigned int usStoreBlockNo,void *pdat,unsigned int datlen);

extern int ReadOneData(unsigned int usStoreBlockNo,void *buf,unsigned int buflen);

extern void ReadOneDataOk(unsigned int usStoreBlockNo);



extern unsigned long GetStoreBlockCap(unsigned int usStoreBlockNo);
extern unsigned long GetStoreBlockUsed(unsigned int usStoreBlockNo);
extern unsigned long GetStoreBlockFree(unsigned int usStoreBlockNo);

extern unsigned int ReadStoreBlock(unsigned int usStoreBlockNo,unsigned int idx,void *buf,unsigned int buflen);

extern void EmptyStoreBlock(unsigned int usStoreBlockNo);

extern int store_fast_write(unsigned int usStoreBlockNo,unsigned long offset,
									void *pdat,unsigned int datlen);

extern int store_fast_write_int(unsigned int usStoreBlockNo,unsigned long offset,
									void *pdat,unsigned int datlen);

extern int store_fast_read(unsigned int usStoreBlockNo,unsigned long offset,
								  unsigned int WantToRead,void *pdat,unsigned int datlen);
							




#ifdef __cplusplus
}
#endif
#endif


