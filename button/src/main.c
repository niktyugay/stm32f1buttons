/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "buttons.h"
			
uint32_t delay = 0;
Buttons button1;

void SysTick_Handler(void){
	if (delay > 0){
		delay--;
	}

	/*-------------------------BUTTON 1----------------------------*/
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET) {
		button1.status = PRESSED;
	}
	else if ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET) && (button1.status == PRESSED)) {
		button1.status = RELEASED;
		button1.cnt++;
	}
	if (button1.status == PRESSED) {
		button1.timer_1++;
		if (button1.timer_1 >= TIME_LONG_CLICK) {
			button1.mode = LONG_CLICK;
		}
	}
	else if (button1.status == RELEASED) {
		if (button1.timer_1 >= TIME_LONG_CLICK) {
			button1.timer_1 = 0;
			button1.mode = DEFAULT;
			button1.status = NO_EVENT;
			button1.cnt = 0;
		}
		else {
			button1.timer_2++;
			if(button1.timer_2 >= DELAY_CLICK && button1.timer_1 < TIME_LONG_CLICK) {
				switch(button1.cnt) {
					case 1:
						button1.mode = CLICK;
						break;
					case 2:
						button1.mode = DOUBLE_CLICK;
						break;
					default:
						button1.mode = DEFAULT;
						break;
				}
				button1.status = NO_EVENT;
				button1.timer_1 = 0;
				button1.timer_2 = 0;
				button1.cnt = 0;
			}
		}
	}
	/*-------------------------------------------------------------*/
}

void delay_ms(uint32_t value){
	delay = value;
	while(delay){}
}

int main(void)
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);

	buttons_init();
	buttons_struct_init(button1);

	while (1) {
		if (button1.mode == LONG_CLICK) {
			button1.mode = DEFAULT;
		}
		if (button1.mode == CLICK) {
			button1.mode = DEFAULT;
		}
		if (button1.mode == DOUBLE_CLICK) {
			button1.mode = DEFAULT;
		}
	}
}
