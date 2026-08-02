#ifndef _TESTER_EDMA_H_
#define _TESTER_EDMA_H_
#include "eDma.h"

typedef void (*Edmafunc)(void);
typedef struct _EdmafuncMachine
{
    char *name;
    Edmafunc edmafunc;
}EdmafuncMachine;

FUNC(void, EDMA_CODE) EDMA_HW_IrqInstall(VAR(uint32, AUTOMATIC) mappedChannel);
void EDMA_0001();

#endif
