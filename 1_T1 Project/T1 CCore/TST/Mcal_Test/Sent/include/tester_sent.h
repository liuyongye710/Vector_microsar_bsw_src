/*
 * tester_sent.h
 *
 *  Created on: 2024Äê3ÔÂ12ÈÕ
 *      Author: pc
 */

#ifndef TESTER_SENT_TESTER_SENT_H_
#define TESTER_SENT_TESTER_SENT_H_

typedef void (*sentfunc)(void);
typedef struct _sentfuncMachine
{
    char *name;
    sentfunc sentfunc;
}SentfuncMachine;

void TEM00441_ReadIntFastMsg();
void TEM00441_ReadIntSlowMsg();
void Sensor0280B_ReadIntFastMsg();
void Sensor0280B_ReadIntSlowMsg();
void sent_test005(void);
void sent_test006(void);
void sent_test007(void);
void sent_test008(void);
void sent_test009(void);
void sent_test010(void);
void sent_test011(void);
void sent_test012(void);
void sent_test013(void);
void sent_test014(void);
void sent_test015(void);
void sent_test016(void);
void sent_test017(void);
void sent_test018(void);
void sent_test019(void);

#endif /* TESTER_SENT_TESTER_SENT_H_ */
