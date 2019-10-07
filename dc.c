/*
 * Module: dc.c
 * Description: Source file for Digital clock Driver
 *  Created on: Oct 6, 2019
 *      Author: Amr Ramadan
 */
#include "dc.h"

uint8 seconds_count = 0;
uint8 minutes_count = 0;
uint8 hours_count = 0;
//uint8 count_flag = 0;

void Display_init(void) {
	/*7447 7SEG Decoder configuration Pins */
	DC_PORTC_DIR_REG |= 0x0F; //
	DC_PORTC_REG &= 0xF0;
	/*7SEG Power configuration Pins*/
	DC_PORTA_CTRL_DIR_REG |= 0x3F;
	DC_PORTA_CTRL_REG |= 0x3F;
	/*Reset Pins*/
	DC_PORTD_RESET_DIR_REG &= (1 << PD2);
	DC_PORTD_RESET_REG |= (1 << PD2);
}
void Timer1_init_CTC_mode(void) {
	Display_init();
	sei();			   //Global Interrupt Enable
	TCNT1 = 0; 		   //Time1 counter Register
	OCR1A = 1000; 	   //Compare Value
	/*Non PWM mode FOC1=1*/
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	/*
	 * TIMER 1 Compare Register
	 * 		WGM12=1 : CTC mode
	 * 	 	CS12,10 : Clock = F_CPU/1024
	 */
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
	/* Timer Interrupt Mast
	 * 		OCIEA = 1 : Compare Match Interrupt Enable */
	TIMSK |= (1 << OCIE1A);
}

void clk_ticks(void) {
	seconds_count++;
	if (seconds_count == 60) {
		seconds_count = 0;
		minutes_count++;
	}
	if (minutes_count == 60) {
		minutes_count = 0;
		hours_count++;
	}
	if (hours_count == 12) {
		seconds_count = 0;
		minutes_count = 0;
		hours_count = 0;
	}
}
ISR(TIMER1_COMPA_vect) {
	clk_ticks();
}
ISR(INT0_vect)
{
	seconds_count = 0;
	minutes_count = 0;
	hours_count = 0;
}
void INT0_init(void)
{
	/*General Interrupt Control Register
	 * 		INT0 =1 : Enable Interrupt 0 Request Pin INT0
	 * */
	GICR  |= (1<<INT0);
	/* MCU Control Register
	 * ISC00:01 = 01 : Falling Edge Interrupt Request
	 * */
	MCUCR &= ~(1<<ISC00);
	MCUCR |= (1<<ISC01);
}
void Clock_generator(void) {
	Timer1_init_CTC_mode();
	INT0_init();
	while (1) {
		_delay_ms(2);
		//Out the number of seconds
		PORTA = (PORTA & 0xC0) | (0x01 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((seconds_count % 10) & 0x0F); // number
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | (0x02 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((seconds_count / 10) & 0x0F); // number
		_delay_ms(2);
		//Out Number Of minutes
		PORTA = (PORTA & 0xC0) | (0x04 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((minutes_count % 10) & 0x0F); // number
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | (0x08 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((minutes_count / 10) & 0x0F); // number
		_delay_ms(2);
		//Out Number Of hours
		PORTA = (PORTA & 0xC0) | (0x10 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((hours_count % 10) & 0x0F); // number
		_delay_ms(2);
		PORTA = (PORTA & 0xC0) | (0x20 & 0x3F);
		PORTC = (PORTC & 0xF0) | ((hours_count / 10) & 0x0F); // number
	}
}
