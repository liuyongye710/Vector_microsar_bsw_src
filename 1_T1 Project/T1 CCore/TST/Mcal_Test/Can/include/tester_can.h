#ifndef _TESTER_CAN_H_
#define _TESTER_CAN_H_
#include "Can.h"

typedef void (*Canfunc)(void);
typedef struct _CanfuncMachine
{
    char *name;
    Canfunc canfunc;
}CanfuncMachine;

void CAN_0001();
void CAN_0002();
void CAN_0003();
void CAN_0004();
void CAN_0005();
void CAN_0006();
void CAN_0007();
void CAN_0008();
void CAN_0009();
void CAN_0010();
void CAN_IRQ_Priority();
#endif
