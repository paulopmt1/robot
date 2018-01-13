
#define MYSERIAL Serial

//#define DEBUG_SENSOR_WHEEL_RAW_RIGHT 1
//#define DEBUG_SENSOR_WHEEL_STEP_RIGHT 1

//#define DEBUG_SENSOR_WHEEL_RAW_LEFT 1
//#define DEBUG_SENSOR_WHEEL_STEP_LEFT 1

#define DEBUG_BALANCING 1
#define DEBUG_MOTORS 1
#define DEBUG_SERIAL 1
#define DEBUG_BATTERY 1
//#define DEBUG_NOTEBOOK 1

int entireRoundStep = 125;
int enginePower = 80;
int stepsPerActionOnRun = 2;
int stepsPerActionOnTurn = 1;
// Timeout para aguardar proximo comando da serial antes de parar os motores
int serialReceiveTimeoutInMs = 200;

const int powerOnPin = 12;
const int powerInVoltage = A7;
const int powerUpNotebookPin = 24;
int batteryLevel = 0;
int sameResultsOnBatteryStatusCount = 0;

// Controle de carga com a base de conexao esterna
const int externalPowerPin = 23;
const int externalBatteryChargerPin = 22;
const int timeInSecondsToStartCharging = 3;
const int batteryPercentageToStartCharging = 80;

// Garante que o sistema desligue se a bateria chegar a 13.3V
int batteryMinimumLevelInStep = 680;
int batteryMaximumLevelInStep = 860;

const int sensorRightPin = A0;
//const int sensorDirMiddleValue = 115;
int sensorRightLastState = 0;
int sensorRightStepCount = 0;

const int sensorLeftPin = A1;
//const int sensorLeftMiddleValue = 350;
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
void goFrontLeftBridge();
void disableRightBridge();
void goFrontRightBridge();
void disableLeftBridge();
void readStepSensors();
void stopNow();
void goBackLeftBridge();
void goBackRightBridge();
boolean executionCommandTimeout();
void serialFlush();

