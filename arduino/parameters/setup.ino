

void setup(){
  Serial.begin(57600);
  Serial1.begin(57600);
  
  MYSERIAL.println("Inicio ok");
    
  pinMode(powerOnPin, OUTPUT);
  pinMode(ledSerialPin, OUTPUT);
  
  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);

  pinMode(leftBridge_PNP_A, OUTPUT);
  pinMode(leftBridge_NPN_A, OUTPUT);
  pinMode(leftBridge_PNP_B, OUTPUT);
  pinMode(leftBridge_NPN_B, OUTPUT);
  
  pinMode(rightBridge_PNP_A, OUTPUT);
  pinMode(rightBridge_NPN_A, OUTPUT);
  pinMode(rightBridge_PNP_B, OUTPUT);
  pinMode(rightBridge_NPN_B, OUTPUT);
  
  powerUp();
  
}


boolean needsToStopNow(){
  return stopNowSolicited;
}

boolean executionCommandTimeout(){
  if (millis() - serialCommandStartedTimeInMs > executionCommandTimeoutInSeconds * 1000){
    return true;
  }
  
  return false;
}


