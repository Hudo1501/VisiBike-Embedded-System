//=====[Libraries]=============================================================
#include "arm_book_lib.h"
#include "brake_light.h"
#include "led_driver.h" // Cần file này

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

// Đây là 2 nút phanh. Bạn có thể đổi pin nếu muốn.
// Tôi giữ nguyên 2 pin này từ code gốc của bạn.
DigitalIn frontBrakeButton(PC_8); // Phanh trước
DigitalIn rearBrakeButton(PC_9);  // Phanh sau

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
// ... (các hàm khác giữ nguyên)

void brakeLightInit() { 
    frontBrakeButton.mode(PullUp); // ĐỔI THÀNH PullUp
    rearBrakeButton.mode(PullUp);  // ĐỔI THÀNH PullUp
}

void brakeLightUpdate() { 
    // KHÔI PHỤC LẠI HÀM NÀY
    // Logic mới: Bình thường chân sẽ là HIGH (1). Khi bấm nút (nối xuống GND), chân sẽ là LOW (0).
    // Chúng ta muốn 'true' khi bấm, tức là khi chân = 0 (LOW).
    
    bool brakePressed = !frontBrakeButton || !rearBrakeButton; // Thêm dấu ! (phủ định)
    
    ledDriverSetBrake(brakePressed);
}
//=====[Implementations of private functions]==================================