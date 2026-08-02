#include "mcu.h"
#include "port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "PowerCtrl_cfg.h"
#include "PowerCtrl.h"
typedef void (*Powerfunc)(void);
typedef struct _PowerfuncMachine
{
	char *name;
	Powerfunc powerfunc;
}PowerfuncMachine;


void testpower0001();
void testpower0002();
void testpower0003();
void testpower0004();
void testpower0005();
void testpower0006();
void testpower0007();
void testpower0008();



