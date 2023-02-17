
#define DUTY_MIN 0.070
#define DUTY_MAX 0.1


#define PERIOD 0.02

bool returnBoolGateCode();
bool returnOpeningState();
bool test(char* codeToCompare);
void servoUpdate();
void openServorMotor();
void closeServorMotor();