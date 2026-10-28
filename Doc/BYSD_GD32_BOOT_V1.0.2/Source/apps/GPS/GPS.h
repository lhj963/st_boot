#ifndef __GPS_H__
#define __GPS_H__

#ifdef __cplusplus
extern "C" {
#endif



extern int GPS_Init(int bps,int iParity);


extern int GPS_Analyze(void *buf);

extern void DispGpsInfo(void);


//是否定位
extern char IsPosition(void);


//获取GPS速度
extern INT16U GetGpsSpeed(void);

extern INT16U GetAngle(void);
extern INT8U GetEW(void);
extern INT8U GetNS(void);

//获取经度
extern INT32U GetLong(void);
//获取纬度
extern INT32U GetLat(void);


#ifdef __cplusplus
}
#endif
#endif

