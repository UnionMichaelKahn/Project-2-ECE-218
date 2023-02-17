#include "Night_Light.h"
#include "mbed.h"
#include "arm_book_lib.h"

DigitalOut light(LED2);
AnalogIn LDR(A2);

void updateLight(){
    if(LDR.read()<=ACTIVATION_VALUE){
        light = ON;
    }
    else {
        light = OFF;
    }
}
