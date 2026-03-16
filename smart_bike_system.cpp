//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "smart_bike_system.h"
#include "brake_light.h"
#include "turn_signal.h"
#include "led_driver.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================


//=====[Implementations of public functions]===================================

//calls all necessary init functions
void smartbikesystemInit(){
    turnSignalInit();
    ledDriverInit();
    brakeLightInit();
}

//calls all update functions
void smartbikesystemUpdate(){
    turnSignalUpdate();
    brakeLightUpdate(); // Phải update trạng thái phanh
    ledDriverUpdate();  // ledDriverUpdate sẽ quyết định đèn nào sáng dựa trên logic
 }

//=====[Implementations of private functions]==================================