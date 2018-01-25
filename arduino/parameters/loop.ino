
void loop(){
  readBatteryLevel();
  checkIfNeedsToShutdown();
  readStepSensors();
  processSerialCommand();
  checkChargingBase();
  //sendBatteryStatus();

  if (needsToStopNow() && serialLastCommandTimeout()){
    disableLeftBridge();
    disableRightBridge();
    stopNowSolicited = false;
    MYSERIAL.println("Parei de verdade");
  }
  
}

