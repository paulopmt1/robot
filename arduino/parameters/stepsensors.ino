
int rightSensorMinValue = 70;
int rightSensorMaxValue = 125;

int leftSensorMinValue = 200;
int leftSensorMaxValue = 450;

int getRightSensorMiddleValue(){
  return (rightSensorMinValue + rightSensorMaxValue) / 2;
}

int getLeftSensorMiddleValue(){
  return (leftSensorMinValue + leftSensorMaxValue) / 2;
}

void readStepSensors(){
  proccessRightMotor();
  proccessLeftMotor();
  delay(10);
}

void proccessRightMotor(){
  
  int sensorRightValue = analogRead(sensorRightPin);
  
  if (sensorRightValue < 100){
    //MYSERIAL.println("Parece que o sensor da roda da direita esta com problemas");
  }

  if (sensorRightValue < rightSensorMinValue){
    MYSERIAL.print("Alterando valor minimo do sensor right para: ");
    MYSERIAL.println(sensorRightValue);
    rightSensorMinValue = sensorRightValue;
  }
  
  if (sensorRightValue > rightSensorMaxValue){
    MYSERIAL.print("Alterando valor maximo do sensor right para: ");
    MYSERIAL.println(sensorRightValue);
    rightSensorMaxValue = sensorRightValue;
  }

  #ifdef DEBUG_SENSOR_WHEEL_RAW_RIGHT
    MYSERIAL.print("SENSOR_RIGHT_RAW_VALUE: ");
    MYSERIAL.println(sensorRightValue);
  #endif
  
  boolean changed = 0;
  
  if (sensorRightValue <= getRightSensorMiddleValue()){
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

  if (sensorLeftValue < leftSensorMinValue){
    MYSERIAL.print("Alterando valor minimo do sensor left para: ");
    MYSERIAL.println(sensorLeftValue);
    leftSensorMinValue = sensorLeftValue;
  }
  
  if (sensorLeftValue > leftSensorMaxValue){
    MYSERIAL.print("Alterando valor maximo do sensor left para: ");
    MYSERIAL.println(sensorLeftValue);
    leftSensorMaxValue = sensorLeftValue;
  }
  
  #ifdef DEBUG_SENSOR_WHEEL_RAW_LEFT
    MYSERIAL.print("SENSOR_LEFT_RAW_VALUE: ");
    MYSERIAL.println(sensorLeftValue);
  #endif
  
  boolean changed = 0;
  
  if (sensorLeftValue <= getLeftSensorMiddleValue()){
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
