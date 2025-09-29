#ifndef SRC_EXERCISE3_H_
#define SRC_EXERCISE3_H_
#include "main.h"
int init = 0;
int ver_stage = 0, hor_stage = 0;
int ver_timer = 0, hor_timer = 0;
void ver_setup_init(){
	ver_stage = 1;
	HAL_GPIO_WritePin(red_v_GPIO_Port, red_v_Pin, 0);
	HAL_GPIO_WritePin(yel_v_GPIO_Port, yel_v_Pin, 0);
	HAL_GPIO_WritePin(grn_v_GPIO_Port, grn_v_Pin, 1);
}
void hor_setup_init(){
	HAL_GPIO_WritePin(red_h_GPIO_Port, red_h_Pin, 1);
	HAL_GPIO_WritePin(yel_h_GPIO_Port, yel_h_Pin, 0);
	HAL_GPIO_WritePin(grn_h_GPIO_Port, grn_h_Pin, 0);
	hor_stage = 1;
}
void exercise_3(){
	if (init == 0){
		++init;
		ver_setup_init();
		hor_setup_init();
	}

	switch(ver_stage){
	case 1:
		if (ver_timer >= 3) {
			ver_stage = 2;
			HAL_GPIO_TogglePin(yel_v_GPIO_Port, yel_v_Pin);
			HAL_GPIO_TogglePin(grn_v_GPIO_Port, grn_v_Pin);
			ver_timer = 0;
		}
		break;
	case 2:
		if (ver_timer >= 2) {
			ver_stage = 3;
			HAL_GPIO_TogglePin(red_v_GPIO_Port, red_v_Pin);
			HAL_GPIO_TogglePin(yel_v_GPIO_Port, yel_v_Pin);
			ver_timer = 0;
		}
		break;
	case 3:
		if (ver_timer >= 5) {
			ver_stage = 1;
			HAL_GPIO_TogglePin(grn_v_GPIO_Port, grn_v_Pin);
			HAL_GPIO_TogglePin(red_v_GPIO_Port, red_v_Pin);
			ver_timer = 0;
		}
		break;
	}

	switch(hor_stage){
	case 1:
		if (hor_timer >= 5) {
			hor_stage = 2;
			HAL_GPIO_TogglePin(grn_h_GPIO_Port, grn_h_Pin);
			HAL_GPIO_TogglePin(red_h_GPIO_Port, red_h_Pin);
			hor_timer = 0;
		}
		break;
	case 2:
		if (hor_timer >= 3) {
			hor_stage = 3;
			HAL_GPIO_TogglePin(yel_h_GPIO_Port, yel_h_Pin);
			HAL_GPIO_TogglePin(grn_h_GPIO_Port, grn_h_Pin);
			hor_timer = 0;
		}
		break;
	case 3:
		if (hor_timer >= 2) {
			hor_stage = 1;
			HAL_GPIO_TogglePin(red_h_GPIO_Port, red_h_Pin);
			HAL_GPIO_TogglePin(yel_h_GPIO_Port, yel_h_Pin);
			hor_timer = 0;
		}
		break;
	}
	++ver_timer;
	++hor_timer;
}



#endif /* SRC_EXERCISE3_H_ */
