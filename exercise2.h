#ifndef SRC_EXERCISE2_H_
#define SRC_EXERCISE2_H_
#include "main.h"
unsigned int ini = 0;
unsigned int count = 0;
unsigned int stage = 0;
void exercise2(){
	if (ini == 0){
		HAL_GPIO_WritePin(red_led_GPIO_Port, red_led_Pin, 0);
	    HAL_GPIO_WritePin(yel_led_GPIO_Port, yel_led_Pin, 1);
	      HAL_GPIO_WritePin(grn_led_GPIO_Port, grn_led_Pin, 1);
		stage = 1;
		ini++;
	}
	switch (stage){
	case 1:
	{
		if (count ==5){
			stage = 2;
			HAL_GPIO_TogglePin(red_led_GPIO_Port, red_led_Pin);
	        HAL_GPIO_TogglePin(yel_led_GPIO_Port, yel_led_Pin);
			count = 0;
		}
		break;
	}
	case 2:
	{
		if (count == 3){
			stage = 3;
			HAL_GPIO_TogglePin(yel_led_GPIO_Port, yel_led_Pin);
	        HAL_GPIO_TogglePin(grn_led_GPIO_Port, grn_led_Pin);
			count = 0;
		}
		break;
	}
	case 3:
		{
		if (count == 2){
			stage = 1;
			HAL_GPIO_TogglePin(grn_led_GPIO_Port, grn_led_Pin);
	        HAL_GPIO_TogglePin(red_led_GPIO_Port, red_led_Pin);
			count = 0;
		}
		break;
	}
	}
	++count;
}


#endif /* SRC_EXERCISE2_H_ */
