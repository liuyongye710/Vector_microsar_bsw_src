/*
 * SC2167.h
 *
 *  Created on: 2025Äê1ÔÂ3ÈÕ
 *      Author: liuziyu
 */

#ifndef IC_SC2167_H_
#define IC_SC2167_H_
#include"Platform_Types.h"
extern void SC2167_init();
extern uint16 SC2167_Angle();
extern uint16 SC2167_Speed();
extern void SC2167_Angle_Speed();
extern void SC2167_diag();
extern uint8 read_fault_data;
extern uint8 read_exc_f_ad;
extern uint8 read_control_ad;
extern uint8 read_exc_f_data;
extern uint8 read_control_data;
extern uint16 read_angle;
extern uint16 read_speed;
#endif /* IC_SC2167_H_ */
