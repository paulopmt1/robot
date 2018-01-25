



void stopNow(){
  stopNowSolicited = true;
}

void goFront(){
  //goFrontWithBalancing();
  goFrontWithNoBalancing();
}

void goBack(){
  //goBackWithBalancing();
  goBackWithNoBalancing();
}

void goLeft(){
  //goLeftWithBalancing();
  goLeftWithNoBalancing();
}

void goRight(){
  //goRightWithBalancing();
  goRightWithNoBalancing();
}


void disableLeftBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando disableLeftBridge");
  #endif
  
  digitalWrite(leftBridge_PNP_A, LOW);
  digitalWrite(leftBridge_NPN_A, LOW);
  digitalWrite(leftBridge_PNP_B, LOW);
  digitalWrite(leftBridge_NPN_B, LOW);
}

void goFrontLeftBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goFrontLeftBridge");
  #endif
  
  digitalWrite(leftBridge_PNP_A, HIGH);
  digitalWrite(leftBridge_NPN_A, LOW);
  digitalWrite(leftBridge_PNP_B, LOW);
  analogWrite(leftBridge_NPN_B, enginePower);
}

void goBackLeftBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goBackLeftBridge");
  #endif
  
  digitalWrite(leftBridge_PNP_A, LOW);
  digitalWrite(leftBridge_NPN_A, HIGH);
  analogWrite(leftBridge_PNP_B, enginePower);
  digitalWrite(leftBridge_NPN_B, LOW);
}


void disableRightBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando disableRightBridge");
  #endif
  
  digitalWrite(rightBridge_PNP_A, LOW);
  digitalWrite(rightBridge_NPN_A, LOW);
  digitalWrite(rightBridge_PNP_B, LOW);
  digitalWrite(rightBridge_NPN_B, LOW);
}

void goFrontRightBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goFrontRightBridge");
  #endif
  
  digitalWrite(rightBridge_PNP_A, LOW);
  digitalWrite(rightBridge_NPN_A, HIGH);
  analogWrite(rightBridge_PNP_B, enginePower);
  digitalWrite(rightBridge_NPN_B, LOW);
}

void goBackRightBridge(){
  #ifdef DEBUG_MOTORS
    MYSERIAL.println("Executando goBackRightBridge");
  #endif
  
  digitalWrite(rightBridge_PNP_A, HIGH);
  digitalWrite(rightBridge_NPN_A, LOW);
  digitalWrite(rightBridge_PNP_B, LOW);
  analogWrite(rightBridge_NPN_B, enginePower);
}


