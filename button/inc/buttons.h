/*
 * buttons.h
 *
 *  Created on: 6 мар. 2019 г.
 *      Author: tugay
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "stm32f10x.h"
#include <stdbool.h>
#include <string.h>

#define DELAY_CLICK							175
#define TIME_LONG_CLICK 				1100

typedef enum {DEFAULT, CLICK, LONG_CLICK, DOUBLE_CLICK} ButtonsMode;
typedef enum {NO_EVENT, PRESSED, RELEASED} ButtonStatus;

typedef struct {
	uint32_t timer_1;
	uint16_t timer_2;
	uint16_t cnt;
	ButtonStatus status;
	ButtonsMode mode;
} Buttons;

void buttons_init(void);
void buttons_struct_init(Buttons);

#endif /* BUTTONS_H_ */
