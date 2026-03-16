//=====[Libraries]=============================================================

#include "turn_signal.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"
#include "led_driver.h" // Cần file này

//=====[Declaration of private defines]========================================
#define DEBOUNCE_TIME 30
#define BLINK_TIME 100 // Thời gian nháy đèn (ms)
#define TIME_ELAP_RESET 0 


//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of public global objects]===============

// Đây là 2 nút bấm cho xi-nhan. Bạn có thể đổi pin nếu muốn.
// Tôi giữ nguyên 2 pin này từ code gốc của bạn.
DigitalIn leftTurnSignalButton(PG_1); 
DigitalIn rightTurnSignalButton(PF_9);

buttonState_t buttonStateLeft = BUTTON_UP;
buttonState_t buttonStateRight = BUTTON_UP;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//only one should be true at any time
bool leftBlinkerActive = OFF; // Trạng thái hệ thống (đang bật xi-nhan trái)
bool rightBlinkerActive = OFF; // Trạng thái hệ thống (đang bật xi-nhan phải)

//=====[Declarations (prototypes) of private functions]========================

static bool debounceLeftInput();
static bool debounceRightInput();
static int toggleLeftBlinker(int timeElap);
static int toggleRightBlinker(int timeElap);



//=====[Implementations of public functions]===================================

void turnSignalInit(){
    leftTurnSignalButton.mode(PullUp); // ĐỔI THÀNH PullUp
    rightTurnSignalButton.mode(PullUp); // ĐỔI THÀNH PullUp
}

// updates the variables that track the state of the blinkers and runs the functions that trigger the blinker leds
void turnSignalUpdate() {
    static int timeElap = 0;
    
    if (debounceLeftInput()) {
        leftBlinkerActive = !leftBlinkerActive;
        if (leftBlinkerActive == ON) {
            rightBlinkerActive = OFF; // Tắt xi-nhan phải nếu bật trái
        }
    }
    if (debounceRightInput()) {
        rightBlinkerActive = !rightBlinkerActive;
        if (rightBlinkerActive == ON) {
            leftBlinkerActive = OFF; // Tắt xi-nhan trái nếu bật phải
        }
    }
    
    if (leftBlinkerActive) {
        timeElap = toggleLeftBlinker(timeElap);
    }
    else if (rightBlinkerActive) {
        timeElap = toggleRightBlinker(timeElap);
    }
    else {
        // Không có xi-nhan nào bật
        ledDriverSetLeftSignal(OFF);
        ledDriverSetRightSignal(OFF);
        timeElap = 0;
    }
    timeElap += TIME_INCREMENT_MS;
}

//=====[Implementations of private functions]==================================

//fsm to debounce left turn signal button
static bool debounceLeftInput(){
    bool leftButtonReleasedEvent = false;
    static int timeElap = 0;
    switch( buttonStateLeft ) {

    case BUTTON_UP:
        if( leftTurnSignalButton ) {
            buttonStateLeft = BUTTON_FALLING;
            timeElap = 0; // Reset time
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( leftTurnSignalButton ) {
                buttonStateLeft = BUTTON_DOWN;
            } else {
                buttonStateLeft = BUTTON_UP;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !leftTurnSignalButton ) {
            buttonStateLeft = BUTTON_RISING;
            timeElap = 0;
        }
        break;

    case BUTTON_RISING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( !leftTurnSignalButton ) {
                buttonStateLeft = BUTTON_UP;
                leftButtonReleasedEvent = true;
            } else {
                buttonStateLeft = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return leftButtonReleasedEvent;
}

//fsm to debounce right turn signal button
static bool debounceRightInput(){
    bool rightButtonReleasedEvent = false;
    static int timeElap = 0;
    switch( buttonStateRight ) {

    case BUTTON_UP:
        if( rightTurnSignalButton ) {
            buttonStateRight = BUTTON_FALLING;
            timeElap = 0;
        }
        break;

    case BUTTON_FALLING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( rightTurnSignalButton ) {
                buttonStateRight = BUTTON_DOWN;
            } else {
                buttonStateRight = BUTTON_UP;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;

    case BUTTON_DOWN:
        if( !rightTurnSignalButton ) { // Sửa lỗi logic (dùng right, không phải left)
            buttonStateRight = BUTTON_RISING;
            timeElap = 0;
        }
        break;

    case BUTTON_RISING:
        if( timeElap >= DEBOUNCE_TIME ) {
            if( !rightTurnSignalButton ) {
                buttonStateRight = BUTTON_UP;
                rightButtonReleasedEvent = true;
            } else {
                buttonStateRight = BUTTON_DOWN;
            }
        }
        timeElap = timeElap + TIME_INCREMENT_MS;
        break;
    }
    return rightButtonReleasedEvent;
}

//makes the left turn signal led blink on and off
static int toggleLeftBlinker(int timeElap) {
    static bool blinkState = OFF; // Trạng thái đèn (đang bật hay tắt)
    if (blinkState == ON) {//the blinker is on and needs to be toggled off
            if (timeElap>=BLINK_TIME) {
                ledDriverSetLeftSignal(OFF); // Tắt đèn
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    } 
    else { // the blinker is off and needs to be toggled on
            if (timeElap>=BLINK_TIME) {
                ledDriverSetLeftSignal(ON); // Bật đèn
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    }
}

//makes the right turn signal led blink on and off
static int toggleRightBlinker(int timeElap) {
    static bool blinkState = OFF;
    if (blinkState == ON) {//the blinker is on and needs to be toggled off
            if (timeElap>=BLINK_TIME) {
                ledDriverSetRightSignal(OFF); // Tắt đèn
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    } 
    else { // the blinker is off and needs to be toggled on
            if (timeElap>=BLINK_TIME) {
                ledDriverSetRightSignal(ON); // Bật đèn
                blinkState = !blinkState;
                return TIME_ELAP_RESET;
            } else {//time is not up
                return timeElap;
            }
    }
}