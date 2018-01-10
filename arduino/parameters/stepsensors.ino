
int rightSensorMinValue = 150;
int rightSensorMaxValue = 350;

int leftSensorMinValue = 150;
int leftSensorMaxValue = 300;

const int sensorWrongValueMin = 50;

int getRightSensorMiddleValue(){
  return (rightSensorMinValue + rightSensorMaxValue) / 2;
}

int getLeftSensorMiddleValue(){
  return (leftSensorMinValue + leftSensorMaxValue) / 2;
}

int getLeftSensorOffset(){
  return (leftSensorMaxValue - leftSensorMinValue) / 3;
}

int getRightSensorOffset(){
  return (rightSensorMaxValue - rightSensorMinValue) / 2.8;
}


void readStepSensors(){
  proccessRightMotor();
  proccessLeftMotor();
}

void proccessRightMotor(){
  
  int sensorRightValue = analogRead(sensorRightPin);
  
  if (sensorRightValue < sensorWrongValueMin){
    MYSERIAL.println("Parece que o sensor da roda da direita esta com problemas");
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
  
  if (sensorRightValue > rightSensorMaxValue - getRightSensorOffset()){
    if (sensorRightLastState != 1){
      sensorRightLastState = 1;
      changed = 1;
    }
  }
  
  if (sensorRightValue < rightSensorMinValue + getRightSensorOffset()){
    if (sensorRightLastState != 0){
      sensorRightLastState = 0;
      changed = 1;
    }
  }
  
  if (changed){
    sensorRightStepCount++;
    
    #ifdef DEBUG_SENSOR_WHEEL_STEP_RIGHT
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
  
  if (sensorLeftValue < sensorWrongValueMin){
    MYSERIAL.println("Parece que o sensor da roda da esquerda esta com problemas");
  }

  if (sensorLeftValue < leftSensorMinValue){
    #ifdef DEBUG_SENSOR_WHEEL_STEP_LEFT
      MYSERIAL.print("Alterando valor minimo do sensor left para: ");
      MYSERIAL.println(sensorLeftValue);
    #endif
    
    leftSensorMinValue = sensorLeftValue;
  }
  
  if (sensorLeftValue > leftSensorMaxValue){
    #ifdef DEBUG_SENSOR_WHEEL_STEP_LEFT
      MYSERIAL.print("Alterando valor maximo do sensor left para: ");
      MYSERIAL.println(sensorLeftValue);
    #endif
    
    leftSensorMaxValue = sensorLeftValue;
  }
  
  #ifdef DEBUG_SENSOR_WHEEL_RAW_LEFT
    MYSERIAL.print("SENSOR_LEFT_RAW_VALUE: ");
    MYSERIAL.println(sensorLeftValue);
  #endif
  
  boolean changed = 0;
  
  if (sensorLeftValue > leftSensorMaxValue - getLeftSensorOffset()){
    if (sensorLeftLastState != 1){
      sensorLeftLastState = 1;
      changed = 1;
    }
  }
  
  if (sensorLeftValue < leftSensorMinValue + getLeftSensorOffset()){
    if (sensorLeftLastState != 0){
      sensorLeftLastState = 0;
      changed = 1;
    }
  }
  
  if (changed){
    sensorLeftStepCount++;
    
    #ifdef DEBUG_SENSOR_WHEEL_STEP_LEFT
      MYSERIAL.print("SENSOR_LEFT: ");
      MYSERIAL.println(sensorLeftStepCount);
       
      if (sensorLeftStepCount == entireRoundStep){
        MYSERIAL.println("Volta completa");
        sensorLeftStepCount = 0;
      }
    #endif

  }
  
}
