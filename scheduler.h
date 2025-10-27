/*
 * scheduler.h
 *
 *  Created on: Oct 26, 2025
 *      Author: tongh
 */

#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "stdint.h"
#include "stdbool.h"

#define SCH_SUCCESS 0
#define ERROR_SCH_INVALID_INDEX 1
#define ERROR_SCH_TOO_MANY_TASKS 2

#define SCH_MAX_TASKS 10

typedef struct {
    void (*funcPtr)(void);
    uint32_t delay;
    uint32_t period;
    uint8_t runme;
} sTask;

void SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);


uint32_t SCH_Delete_Task(uint32_t taskID);

void deleteAllTasks(void);

#endif /* __SCHEDULER_H */
