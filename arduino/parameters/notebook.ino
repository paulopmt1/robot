



void powerUpNotebook(){
  
  #ifdef DEBUG_SENSOR_WHEEL_STEP_RIGHT
    MYSERIAL.println("Vou ligar o notebook");
  #endif
  
  digitalWrite(powerUpNotebookPin, LOW);
  delay(1000);
  digitalWrite(powerUpNotebookPin, HIGH);
}

