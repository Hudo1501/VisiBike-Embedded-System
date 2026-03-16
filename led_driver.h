//=====[#include guards - begin]===============================================

#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void ledDriverInit();
void ledDriverUpdate();

// Các hàm này được gọi bởi các module khác (turn_signal, brake_light)
// để báo cáo trạng thái mong muốn
void ledDriverSetBrake(bool state);
void ledDriverSetLeftSignal(bool state);
void ledDriverSetRightSignal(bool state);

//=====[#include guards - end]=================================================

#endif // _LED_DRIVER_H_