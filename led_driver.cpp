//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h" 
#include "smart_bike_system.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================
// Định nghĩa chân điều khiển cho TB6612FNG
// Bạn có thể thay đổi các chân này
#define TB_AIN1_PIN     D2  // Channel A Input 1
#define TB_AIN2_PIN     D3  // Channel A Input 2
#define TB_PWMA_PIN     D4  // Channel A PWM (Speed)
#define TB_BIN1_PIN     D5  // Channel B Input 1
#define TB_BIN2_PIN     D6  // Channel B Input 2
#define TB_PWMB_PIN     D7  // Channel B PWM (Speed)
#define TB_STBY_PIN     D8  // Standby pin

// Định nghĩa chân cho LED C (đèn phanh) - Nối trực tiếp vào Nucleo
#define LED_C_PIN       D9

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
// Khai báo 7 chân điều khiển cho TB6612FNG
DigitalOut tb_ain1(TB_AIN1_PIN);
DigitalOut tb_ain2(TB_AIN2_PIN);
DigitalOut tb_pwma(TB_PWMA_PIN);
DigitalOut tb_bin1(TB_BIN1_PIN);
DigitalOut tb_bin2(TB_BIN2_PIN);
DigitalOut tb_pwmb(TB_PWMB_PIN);
DigitalOut tb_stby(TB_STBY_PIN);

// Khai báo chân cho LED C (đèn phanh)
DigitalOut ledC(LED_C_PIN);

//=====[Declaration and initialization of private global variables]============
// Các biến trạng thái để lưu yêu cầu từ các module khác
static bool brakeState = false;
static bool leftSignalState = false;
static bool rightSignalState = false;

//=====[Declarations (prototypes) of private functions]========================
// Hàm nội bộ để điều khiển Kênh A (LED A)
static void setChannelA(bool on);
// Hàm nội bộ để điều khiển Kênh B (LED B)
static void setChannelB(bool on);

//=====[Implementations of public functions]===================================
void ledDriverInit() {
    // Kích hoạt TB6612FNG
    tb_stby = 1;

    // Đặt "tốc độ" (độ sáng) của cả 2 kênh lên tối đa
    tb_pwma = 1;
    tb_pwmb = 1;

    // Tắt tất cả các đèn khi khởi động
    setChannelA(OFF);
    setChannelB(OFF);
    ledC = OFF;
}

// Hàm update này chứa logic ưu tiên
// Ưu tiên: Phanh > Xi-nhan
void ledDriverUpdate() {

    if (brakeState) {
        // YÊU CẦU MỚI: Khi phanh, CHỈ bật đèn C.
        // Tắt cả hai kênh xi-nhan A và B.
        setChannelA(OFF);
        setChannelB(OFF);
        ledC = ON;       // Bật LED C (trực tiếp)
    } 
    else {
        // Nếu KHÔNG phanh:
        // Đèn C (đèn phanh) luôn tắt
        ledC = OFF; 
        
        // Đèn A và B sẽ hoạt động bình thường theo trạng thái xi-nhan
        // (Biến leftSignalState và rightSignalState được bật/tắt 
        // liên tục bởi module turn_signal)
        setChannelA(leftSignalState);
        setChannelB(rightSignalState);
    }
}

// Các hàm này được gọi bởi brake_light và turn_signal
void ledDriverSetBrake(bool state) {
    brakeState = state;
}

void ledDriverSetLeftSignal(bool state) {
    leftSignalState = state;
}

void ledDriverSetRightSignal(bool state) {
    rightSignalState = state;
}

//=====[Implementations of private functions]==================================

// Điều khiển Kênh A (nối với LED A)
static void setChannelA(bool on) {
    if (on) {
        tb_ain1 = 1; // Quay thuận (HIGH)
        tb_ain2 = 0;
    } else {
        tb_ain1 = 0; // Dừng (LOW)
        tb_ain2 = 0;
    }
}

// Điều khiển Kênh B (nối với LED B)
static void setChannelB(bool on) {
    if (on) {
        tb_bin1 = 1; // Quay thuận (HIGH)
        tb_bin2 = 0;
    } else {
        tb_bin1 = 0; // Dừng (LOW)
        tb_bin2 = 0;
    }
}