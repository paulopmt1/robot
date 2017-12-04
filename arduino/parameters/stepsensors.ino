

void readStepSensors(){
  proccessRightMotor();
  proccessLeftMotor();
  delay(10);
}

void proccessRightMotor(){
  
  int sensorRightValue = analogRead(sensorRightPin);
  
  if (sensorRightValue < 100){
    MYSERIAL.println("Parece que o sensor da roda da direita esta com problemas");
  }
  
  //debugPrintln(sensorRightValue);
  boolean changed = 0;
  
  if (sensorRightValue <= sensorDirMiddleValue){
    if (sensorRightLastState != 0){
      sensorRightLastState = 0;
      changed = 1;
    }
  }else{
    if (sensorRightLastState != 1){
      sensorRightLastState = 1;
      changed = 1;
    }
  }
  
  if (changed){
    sensorRightStepCount++;
    
    #ifdef DEBUG_SENSOR_WHEEL
      MYSERIAL.print("SENSOR_RIGHT: ");
      MYSERIAL.println(sensorRightStepCount);
      
      if (sensorRightStepCount == entireRoundStep){
        MYSERIAL.println("Volta completa");
        sensorRightStepCount = 0;
      }
    #endif
    
  }
  
}


void proccessLeftMotor(){
  
  int sensorLeftValue = analogRead(sensorLeftPin);
  
  if (sensorLeftValue < 100){
    MYSERIAL.println("Parece que o sensor da roda da esquerd esta com problemas");
  }
  
  //debugPrintln(sensorRightValue);
  boolean changed = 0;
  
  if (sensorLeftValue <= sensorLeftMiddleValue){
    if (sensorLeftLastState != 0){
      sensorLeftLastState = 0;
      changed = 1;
    }
  }else{
    if (sensorLeftLastState != 1){
      sensorLeftLastState = 1;
      changed = 1;
    }
  }
  
  if (changed){
    sensorLeftStepCount++;
    
    #ifdef DEBUG_SENSOR_WHEEL
      MYSERIAL.print("SENSOR_LEFT: ");
      MYSERIAL.println(sensorLeftStepCount);
       
      if (sensorLeftStepCount == entireRoundStep){
        MYSERIAL.println("Volta completa");
        sensorLeftStepCount = 0;
      }
    #endif

  }
  
}
