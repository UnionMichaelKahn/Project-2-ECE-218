#include "mbed.h"
#include "arm_book_lib.h"
#include "servo.h"
#include "code.h"
PwmOut servo(PF_9);
bool opening;
bool test( char* codeToCompare );
extern char gateCode[4];
extern char gateCodeSequence[4];
void servoUpdate(){
    static int timeAccumulated = 0;
    servo.period(PERIOD);
    if(test(gateCode)){
        openServorMotor();
        timeAccumulated = timeAccumulated+10;
        if(timeAccumulated==7000){
            closeServorMotor();
            gateCode[0]='0';
            gateCode[1]='0';
            gateCode[2]='0';
            gateCode[3]='0';
            timeAccumulated=0;
        }
    }
    
}
void openServorMotor()
{
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
    opening = true;
}
bool returnOpeningState(){
    return opening;
}
bool returnBoolGateCode(){
    if(test(gateCode)){
        return true;
    }
    else{
        return false;
    }
}
bool test( char* codeToCompare )
{
    int i;
    for (i = 0; i < CODE_NUMBER_OF_KEYS; i++) {
        if ( gateCodeSequence[i] != codeToCompare[i] ) {
 
            return false;
        }
    }
    return true;
}

void closeServorMotor()
{
    servo.period(PERIOD);
    servo.write(DUTY_MAX);
    opening = false;
}
