#ifndef __TESTER_GPT_H_
#define __TESTER_GPT_H_

#include "Gpt.h"

typedef void (*Gptfunc)(void);
typedef struct _GptfuncMachine
{
    char *name;
    Gptfunc gptfunc;
}GptfuncMachine;

void gpt_test_1ms(void);
void gpt_test_10ms(void);
void gpt_test_100ms(void);
void gpt_test_1000ms(void);
void gpt_test_stop(void);

FUNC(void, GPT_CODE) GPT_GTM_TOM_LLD_SetIRQ(void);
FUNC(Std_ReturnType, GPT_CODE) Gpt_Pit_SetIRQ(void);
FUNC(Std_ReturnType, GPT_CODE) Gpt_Stm_SetIRQ(void);

#endif
