

void goFrontWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount <= stepsPerActionOnRun && sensorLeftStepCount <= stepsPerActionOnRun && ! executionCommandTimeout()){
   #ifdef DEBUG_BALANCING 
      MYSERIAL.print("GO_FRONT: ");
      MYSERIAL.print(" - stepsPerActionOnRun: ");
      MYSERIAL.print(stepsPerActionOnRun);
      
      MYSERIAL.print(" - sensorLeftStepCount: ");
      MYSERIAL.print(sensorLeftStepCount);
      MYSERIAL.print(" - sensorRightStepCount: ");
      MYSERIAL.print(sensorRightStepCount);
      MYSERIAL.println();
    #endif

   
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
    
    readStepSensors();
  }
  
  stopNow();
}


void goBackWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerActionOnRun && ! executionCommandTimeout()){
   #ifdef DEBUG_BALANCING 
      MYSERIAL.print("GO_BACK: ");
      MYSERIAL.print(" - stepsPerActionOnTurn: ");
      MYSERIAL.print(stepsPerActionOnTurn);
      
      MYSERIAL.print(" - sensorRightStepCount: ");
      MYSERIAL.print(sensorRightStepCount);
      MYSERIAL.print(" - sensorLeftStepCount: ");
      MYSERIAL.print(sensorLeftStepCount);
      MYSERIAL.println();
    #endif
    
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
    
    readStepSensors();
  }
  
  stopNow();
}


