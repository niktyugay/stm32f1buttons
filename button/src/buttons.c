/*
 * buttons.c
 *
 *  Created on: 6 мар. 2019 г.
 *      Author: tugay
 */

#include "buttons.h"

GPIO_InitTypeDef GPIO_Buttons;

void buttons_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_Buttons.GPIO_Pin =  GPIO_Pin_0;
	GPIO_Buttons.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Buttons.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_Buttons);
}

void buttons_struct_init(Buttons button) {
	button.mode = DEFAULT;
	button.status = NO_EVENT;
	button.timer_1 = 0;
	button.timer_2 = 0;
	button.cnt = 0;
}

