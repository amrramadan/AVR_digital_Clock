/*
 * std_types.h
 *  Module: Platform standard types
 *  Created on: Oct 4, 2019
 *  Description: AVR types
 *      Author: Amr Ramadan
 *
 */
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define HIGH 	(1u)
#define LOW 	(0u)


typedef unsigned char bool;
typedef unsigned char		uint8;  // 0...255
typedef signed char			sint8;  // -128...127
typedef unsigned short		uint16;	// 0...65535
typedef signed short		sint16;
typedef unsigned long		uint32;
typedef signed long			sint32;
typedef unsigned long long	uint64;
typedef signed long long	sint64;
typedef float				float32;
typedef double				double64;
#endif /* STD_TYPES_H_ */
