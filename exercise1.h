#ifndef SRC_EXERCISE1_H_
#define SRC_EXERCISE1_H_
#include "main.h"

unsigned int setIni = 0;
unsigned int count = 0;
void exercise1(){
	if (setIni == 0){
		HAL_GPIO_WritePin(red_led_GPIO_Port, red_led_Pin, 0);
		HAL_GPIO_WritePin(yel_led_GPIO_Port, yel_led_Pin, 1); //set initial LED
		setIni ++;
	}
	if (count >= 3){
		count = 0;
		HAL_GPIO_TogglePin(red_led_GPIO_Port, red_led_Pin);
		HAL_GPIO_TogglePin(yel_led_GPIO_Port, yel_led_Pin);
	}
	else ++count;
}

#endif /* SRC_EXERCISE1_H_ */
