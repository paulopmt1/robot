

int maxCommandDurationInMsForRun = 300;
int maxCommandDurationInMsForTun = 150;


void goFrontWithNoBalancing(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goFrontWithNoBalancing");
  #endif
  
  unsigned long commandDuration = 0;
  unsigned long commandLimitInMs = millis() + maxCommandDurationInMsForRun;

  while (commandDuration < commandLimitInMs){
    goFrontLeftBridge();
    goFrontRightBridge();
    commandDuration = millis();
  }

  stopNow();
}


void goBackWithNoBalancing(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goBackWithNoBalancing");
  #endif
  
  unsigned long commandDuration = 0;
  unsigned long commandLimitInMs = millis() + maxCommandDurationInMsForRun;

  while (commandDuration < commandLimitInMs){
    #ifdef DEBUG_MOTORS
      MYSERIAL.println("ESTOU NO LOOP");
    #endif
  
    goBackLeftBridge();
    goBackRightBridge();
    commandDuration = millis();
  }

  stopNow();
}


void goLeftWithNoBalancing(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goLeftWithNoBalancing");
  #endif
  
  unsigned long commandDuration = 0;
  unsigned long commandLimitInMs = millis() + maxCommandDurationInMsForTun;

  while (commandDuration < commandLimitInMs){
    goBackLeftBridge();
    goFrontRightBridge();
    commandDuration = millis();
  }

  stopNow();
}


void goRightWithNoBalancing(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goRightWithNoBalancing");
  #endif
  
  unsigned long commandDuration = 0;
  unsigned long commandLimitInMs = millis() + maxCommandDurationInMsForTun;

  while (commandDuration < commandLimitInMs){
    goBackRightBridge();
    goFrontLeftBridge();
    commandDuration = millis();
  }

  stopNow();
}

