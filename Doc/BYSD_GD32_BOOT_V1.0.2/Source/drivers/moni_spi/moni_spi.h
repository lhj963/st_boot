#ifndef __MONI_SPI_H__
#define __MONI_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*SETFUNC)(void);
typedef unsigned char (*READFUNC)(void);
typedef void (*SETVALUEFUNC)(unsigned char);

#define MAX_SPI_CNT 		4


extern int moni_spi_init(int num,
	SETFUNC pSetCLKOutputMode,
	SETFUNC pSetMOSIOutputMode,
	SETFUNC pSetMISOIutputMode,

	SETVALUEFUNC pSetCLK,
	SETVALUEFUNC pSetMOSI,

	READFUNC pReadMISO,
	char CPOL,
	char CPHA,
	char IsMSBFirst
	);


extern void moni_spi_write_byte(int num,unsigned char dat);

extern unsigned char moni_spi_read_byte(int num);


#ifdef __cplusplus
}
#endif
#endif


