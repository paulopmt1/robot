
void loop(){
  readBatteryLevel();
  checkIfNeedsToShutdown();
  readStepSensors();
  processSerialCommand();

  if (needsToStopNow() && serialLastCommandTimeout()){
    disableLeftBridge();
    disableRightBridge();
    stopNowSolicited = false;
    MYSERIAL.println("Parei de verdade");
  }
  
}

