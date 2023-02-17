//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
bool userInterfaceCodeCompleteRead();
void userInterfaceCodeCompleteWrite( bool state );

bool incorrectCodeStateRead();
void incorrectCodeStateWrite( bool state );
char getGateCode();
bool systemBlockedStateRead();
void systemBlockedStateWrite( bool state );

//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_