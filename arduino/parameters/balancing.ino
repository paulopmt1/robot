
void goFrontWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerActionOnRun && ! executionCommandTimeout()){
   
    if (sensorRightStepCount > sensorLeftStepCount){
      goFrontLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goFrontRightBridge();
      disableLeftBridge();
    }
      
    else{
      goFrontLeftBridge();
      goFrontRightBridge();
    }
    
    /*
    MYSERIAL.print(sensorLeftStepCount);
    MYSERIAL.print(" - ");
    MYSERIAL.println(sensorRightStepCount);
    */
    
    readStepSensors();
  }
  
  stopNow();
}


void goBackWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerActionOnRun && ! executionCommandTimeout()){
    
    if (sensorRightStepCount == sensorLeftStepCount){
      goBackLeftBridge();
      goBackRightBridge();
    }
    
    else if (sensorRightStepCount > sensorLeftStepCount){
      goBackLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorLeftStepCount > sensorRightStepCount){
      goBackRightBridge();
      disableLeftBridge();
    }
    
    /*
    MYSERIAL.print(sensorLeftStepCount);
    MYSERIAL.print(" - ");
    MYSERIAL.println(sensorRightStepCount);
    */
    
    readStepSensors();
  }
  
  stopNow();
}



void goLeftWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerActionOnTurn && ! executionCommandTimeout()){
   #ifdef DEBUG_BALANCING 
      MYSERIAL.print("GO_LEFT: ");
      MYSERIAL.print(" - stepsPerActionOnTurn: ");
      MYSERIAL.print(stepsPerActionOnTurn);
      
      MYSERIAL.print(" - sensorRightStepCount: ");
      MYSERIAL.print(sensorRightStepCount);
      MYSERIAL.print(" - sensorLeftStepCount: ");
      MYSERIAL.print(sensorLeftStepCount);
      MYSERIAL.println();
    #endif
    
    if (sensorRightStepCount > sensorLeftStepCount){
      goBackLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goFrontRightBridge();
      disableLeftBridge();
    } 
    
    else{
      goBackLeftBridge();
      goFrontRightBridge();
    }
    
    /*
    MYSERIAL.print(sensorLeftStepCount);
    MYSERIAL.print(" - ");
    MYSERIAL.println(sensorRightStepCount);
    */
    
    readStepSensors();
  }
  
  stopNow();
}



void goRightWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
 
  while(sensorRightStepCount < stepsPerActionOnTurn && ! executionCommandTimeout()){
    #ifdef DEBUG_BALANCING 
      MYSERIAL.print("GO_RIGHT: ");
      MYSERIAL.print(" - stepsPerActionOnTurn: ");
      MYSERIAL.print(stepsPerActionOnTurn);
      
      MYSERIAL.print(" - sensorRightStepCount: ");
      MYSERIAL.print(sensorRightStepCount);
      MYSERIAL.print(" - sensorLeftStepCount: ");
      MYSERIAL.print(sensorLeftStepCount);
      MYSERIAL.println();
    #endif
   
    if (sensorRightStepCount > sensorLeftStepCount){
      goFrontLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goBackRightBridge();
      disableLeftBridge();
    } 
    
    else{
      goBackRightBridge();
      goFrontLeftBridge();
    }
    
    /*
    MYSERIAL.print(sensorLeftStepCount);
    MYSERIAL.print(" - ");
    MYSERIAL.println(sensorRightStepCount);
    */
    
    readStepSensors();
  }
  
  stopNow();
}


