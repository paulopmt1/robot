
#define MYSERIAL Serial

#define DEBUG_SENSOR_WHEEL 1
#define DEBUG_BALANCING 1
#define DEBUG_MOTORS 1
//#define DEBUG_BATTERY 1

int entireRoundStep = 125;
int enginePower = 100;
int stepsPerActionOnRun = 2;
int stepsPerActionOnTurn = 1;
// Timeout para aguardar proximo comando da serial antes de parar os motores
int serialReceiveTimeoutInMs = 200;

const int powerOnPin = 12;
const int powerInVoltage = A7;
int batteryLevel = 0;
int sameResultsOnBatteryStatusCount = 0;

// Garante que o sistema desligue se a bateria chegar a 9.5V
int batteryMinimumLevelInStep = 480;
int batteryMaximumLevelInStep = 700;

const int sensorRightPin = A0;
const int sensorDirMiddleValue = 390;
int sensorRightLastState = 0;
int sensorRightStepCount = 0;

const int sensorLeftPin = A1;
const int sensorLeftMiddleValue = 350;
int sensorLeftLastState = 0;
int sensorLeftStepCount = 0;

unsigned long serialCommandStartedTimeInMs;
int executionCommandTimeoutInSeconds = 2;

int xAxisData;
int yAxisData;

int leftBridge_PNP_A = 4;
int leftBridge_NPN_A = 5;
int leftBridge_PNP_B = 7;
int leftBridge_NPN_B = 6;

int rightBridge_PNP_A = 8;
int rightBridge_NPN_A = 9;
int rightBridge_PNP_B = 11;
int rightBridge_NPN_B = 10;

int ledSerialPin = 14;

int xAxis = 2;
int yAxis = 3;

boolean serialCommandInitialized = false;
boolean stopNowSolicited = false;

void proccessLeftMotor();
void proccessRightMotor();
boolean executionCommandTimeout();


