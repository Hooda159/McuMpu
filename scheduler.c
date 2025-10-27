/*
 * scheduler.c
 *
 *  Created on: Oct 26, 2025
 *      Author: tongh
 */

#include "scheduler.h"
#include <stddef.h> // Để dùng NULL

sTask taskList[SCH_MAX_TASKS];

uint8_t ERROR_CODE_G = SCH_SUCCESS;

static uint32_t currentTasks = 0;

void SCH_Init(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        taskList[i].funcPtr = NULL;
        taskList[i].delay = 0;
        taskList[i].period = 0;
        taskList[i].runme = 0;
    }
    currentTasks = 0;
    ERROR_CODE_G = SCH_SUCCESS;
}

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    // Kiểm tra xem còn chỗ không
    if (currentTasks >= SCH_MAX_TASKS) {
        ERROR_CODE_G = ERROR_SCH_TOO_MANY_TASKS;
        return 0xFFFFFFFF; // Trả về ID không hợp lệ
    }

    // Thêm tác vụ vào cuối mảng nén
    taskList[currentTasks].funcPtr = pFunction;
    taskList[currentTasks].delay = DELAY;
    taskList[currentTasks].period = PERIOD;
    taskList[currentTasks].runme = 0;

    // Tăng biến đếm và trả về ID (là chỉ số hiện tại)
    uint32_t newID = currentTasks;
    currentTasks++;

    return newID;
}

void SCH_Update(void) {
    // Chỉ lặp qua các tác vụ đang chạy
    for (uint32_t i = 0; i < currentTasks; i++) {

        // Giảm delay trước (nếu > 0)
        if (taskList[i].delay > 0) {
            taskList[i].delay--;
        }

        // Kiểm tra xem đã đến lúc chạy chưa
        if (taskList[i].delay == 0) {
            taskList[i].runme += 1; // Tăng cờ báo chạy

            // Nếu có chu kỳ, nạp lại cho lần sau
            if (taskList[i].period > 0) {
                taskList[i].delay = taskList[i].period;
            }
        }
    }
}

void SCH_Dispatch_Tasks(void) {
    // Chỉ lặp qua các tác vụ đang chạy
    for (uint32_t i = 0; i < currentTasks; i++) {

        if (taskList[i].runme > 0) {
            // Chạy tác vụ
            (*taskList[i].funcPtr)();
            taskList[i].runme--; // Giảm cờ

            // Nếu là tác vụ chạy 1 lần (period == 0)
            if (taskList[i].period == 0) {
                // Xóa tác vụ này
                SCH_Delete_Task(i);
                i--;
            }
        }
    }
}

uint32_t SCH_Delete_Task(uint32_t taskID) {

    if (taskID >= currentTasks) {
        ERROR_CODE_G = ERROR_SCH_INVALID_INDEX;
        return ERROR_CODE_G;
    }

    currentTasks--;

    for (int i = taskID; i < currentTasks; i++) {
        taskList[i] = taskList[i + 1];
    }

    taskList[currentTasks].funcPtr = NULL;
    taskList[currentTasks].delay = 0;
    taskList[currentTasks].period = 0;
    taskList[currentTasks].runme = 0;

    ERROR_CODE_G = SCH_SUCCESS;
    return ERROR_CODE_G;
}

void deleteAllTasks(void) {
    currentTasks = 0;
}

