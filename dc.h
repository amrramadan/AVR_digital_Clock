/*
 * Module: dc.h
 * Description: Header file for Digital clock Driver
 *  Created on: Oct 6, 2019
 *      Author: Amr Ramadan
 */

#ifndef DC_H_
#define DC_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*******************************Macros******************************/

#define DC_PORTC_DIR_REG DDRC //7SEG Data Direction Register
#define DC_PORTA_CTRL_DIR_REG DDRA //7SEG Control Direction Register

#define DC_PORTC_REG PORTC //7SEG Data Bus Register
#define DC_PORTA_CTRL_REG PORTA//7SEG Control Bus Register

#define DC_PORTD_RESET_DIR_REG DDRD //Reset Direction Register
#define DC_PORTD_RESET_REG PORTD     //Reset Data Bus Register

/**************************Functions Prototypes***********************/
void Display_init(void);
void Timer1_init_CTC_mode(void);
void clk_ticks(void);
void INT0_init(void);
void Clock_generator(void);
#endif /* DC_H_ */
