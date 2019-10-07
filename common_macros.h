/*
 * common_macros.h
 *  Module: common macros
 *  Created on: Oct 4, 2019
 *  Description: AVR most common macros
 *      Author: Amr Ramadan
 *
 */
#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT) (REG = REG | (1<<BIT)) // set bit in a specific register
#define CLEAR_BIT(REG,BIT) (REG = REG & (~(1<<BIT))) // clear bit from a specific register
#define TOGGLE_BIT(REG,BIT) (REG = REG ^ (1<<BIT)) // toggle bit in a specific register
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))  // check if a bit is set or not
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT))) // check if a bit is cleared or not
#define ROL(REG,num) ((REG<<num) | (REG>>8-num)) // rotate a specific bit left with a defined number of rotates
#define ROR(REG,num) ((REG>>num) | (REG<<8-num)) // rotate a specific bit right with a defined number of rotates
#endif /* COMMON_MACROS_H_ */
