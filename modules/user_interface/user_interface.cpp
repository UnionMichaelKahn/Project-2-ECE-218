//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "code.h"
#include "siren.h"
#include "smart_home_system.h"
#include "fire_alarm.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "matrix_keypad.h"
#include "display.h"
#include "servo.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];
char gateCode[4]={};
extern char gateCodeSequence[4];
//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();
static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================


void userInterfaceInit()
{
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    incorrectCodeIndicatorUpdate();
    systemBlockedIndicatorUpdate();
    userInterfaceDisplayUpdate();
}

bool incorrectCodeStateRead()
{
    return incorrectCodeState;
}

void incorrectCodeStateWrite( bool state )
{
    incorrectCodeState = state;
}

bool systemBlockedStateRead()
{
    return systemBlockedState;
}

void systemBlockedStateWrite( bool state )
{
    systemBlockedState = state;
}

bool userInterfaceCodeCompleteRead()
{
    return codeComplete;
}

void userInterfaceCodeCompleteWrite( bool state )
{
    codeComplete = state;
}

//=====[Implementations of private functions]==================================


static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite("Enter Pass:");
}

static void userInterfaceDisplayUpdate()
{
    static int numberOfHashKeyReleased = 0;
    char keyReleased = matrixKeypadUpdate();
    static int incorrectAttempts = 0;
    char number[0]={};
    static int numKeysPressed = 0;
    static int accumulatedTime=0;
    if( keyReleased != '\0'&&incorrectAttempts<3) {
        gateCode[numKeysPressed]=keyReleased;
        if(numKeysPressed<3&&!returnOpeningState()){
            if( numKeysPressed ==0){
                displayCharPositionWrite(0, 1);
                displayStringWrite("          ");
            }
            number[0] = gateCode[numKeysPressed];
            displayCharPositionWrite (numKeysPressed, 1);
            displayStringWrite(number);
            numKeysPressed++;
        }
        
        else{
            displayCharPositionWrite (0, 1);
            userInterfaceCodeCompleteWrite(true);

                if(returnBoolGateCode()){
                    displayStringWrite("Welcome");
                    
                }
                else{
                    displayStringWrite("Wrong Pass");
                    incorrectAttempts++;
                }
           numKeysPressed=0;
        }
    }
     if(incorrectAttempts==3){
                displayCharPositionWrite(0, 0);
                displayStringWrite("          ");
                displayCharPositionWrite(0, 0);
                displayStringWrite("System Locked");
                displayCharPositionWrite(0, 1);
                displayStringWrite("          ");
            }
}

static void incorrectCodeIndicatorUpdate()
{
    incorrectCodeLed = incorrectCodeStateRead();
}

static void systemBlockedIndicatorUpdate()
{
    systemBlockedLed = systemBlockedState;
}