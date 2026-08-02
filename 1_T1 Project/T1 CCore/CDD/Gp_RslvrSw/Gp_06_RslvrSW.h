
#ifndef GP_06_RSLVRSW_H_
#define GP_06_RSLVRSW_H_


extern void Gp_06_RslvrSW_Init(void);
extern void Gp_06_RslvrSw_GetPos(sint16 *SinValue_s16, sint16 *CosValue_s16);
extern void Gp_06_RslvrSw_CddIo(void);

extern void Gp_06_RslvrSw_GetTimeStampSig(uint32 *TimeStamp_pu32);
extern void Gp_06_RslvrSw_GetCurTimeStampSig(uint32 *TimeStamp_pu32);


#endif /* GP_06_PWM3PH_H_ */
