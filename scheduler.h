/*
 * scheduler.h
 *
 *  Created on: Oct 26, 2025
 *      Author: tongh
 */

#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "stdint.h"
#include "stdbool.h" // Cần cho biến bool

// Định nghĩa các mã lỗi dựa trên code của bạn
#define SCH_SUCCESS 0
#define ERROR_SCH_INVALID_INDEX 1
#define ERROR_SCH_TOO_MANY_TASKS 2

// Số lượng tác vụ tối đa
#define SCH_MAX_TASKS 10

// Cấu trúc sTask (dựa trên các biến bạn đã dùng trong hàm)
typedef struct {
    void (*funcPtr)(void); // Con trỏ hàm
    uint32_t delay;        // Thời gian trễ (ticks)
    uint32_t period;       // Chu kỳ (ticks)
    uint8_t runme;         // Cờ báo chạy
} sTask;

// --- CÁC HÀM CỐT LÕI ---

/**
 * @brief Khởi tạo bộ lập lịch.
 */
void SCH_Init(void);

/**
 * @brief Thêm tác vụ vào cuối danh sách.
 * @return ID (chỉ số) của tác vụ, hoặc 0xFFFFFFFF nếu thất bại.
 */
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);

/**
 * @brief Cập nhật thời gian, gọi trong ISR Timer.
 */
void SCH_Update(void);

/**
 * @brief Chạy các tác vụ, gọi trong vòng lặp main.
 */
void SCH_Dispatch_Tasks(void);

// --- CÁC HÀM BẠN CUNG CẤP (ĐÃ CHỈNH SỬA) ---

/**
 * @brief Xóa một tác vụ và dồn mảng lại.
 * @param taskID Chỉ số của tác vụ cần xóa.
 * @return Mã lỗi (SCH_SUCCESS hoặc ERROR_SCH_INVALID_INDEX).
 */
uint32_t SCH_Delete_Task(uint32_t taskID);

/**
 * @brief Xóa tất cả các tác vụ khỏi bộ lập lịch.
 */
void deleteAllTasks(void);

#endif /* __SCHEDULER_H */
