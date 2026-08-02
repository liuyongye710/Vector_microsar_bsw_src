#ifndef __TESTER_PORT_H_
#define __TESTER_PORT_H_

typedef void (*Portfunc)(void);
typedef struct _PortfuncMachine
{
    char *name;
    Portfunc portfunc;
}PortfuncMachine;


void port_test_0020(void);
void port_test_0021(void);
void port_test_0022(void);
void port_test_0023(void);
void port_test_0024(void);
void port_test_0025(void);
void port_test_0026(void);
void port_test_0027(void);
void port_test_0028(void);

#endif
