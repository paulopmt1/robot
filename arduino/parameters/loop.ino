
void loop(){
  readBatteryLevel();
  checkIfNeedsToShutdown();
  readStepSensors();
  processSerialCommand();
  checkChargingBase();
  checkIfNeedsToRebootWifiAdapter();
  //sendBatteryStatus();

  if (needsToStopNow() && serialLastCommandTimeout()){
    disableLeftBridge();
    disableRightBridge();
    stopNowSolicited = false;
    MYSERIAL.println("Parei de verdade");
  }
  
}

