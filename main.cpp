#include "mbed.h"
#include "smart_bike_system.h"
#include "arm_book_lib.h" 

int main()
{
    smartbikesystemInit();
    while (true) {
        smartbikesystemUpdate();
        delay(TIME_INCREMENT_MS);
    }
}

