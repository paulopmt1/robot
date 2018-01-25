
unsigned long msToReboot = 3 * 60 * 60 * 1000; // 3 horas
unsigned long lastReboot = millis();

void checkIfNeedsToRebootWifiAdapter(){

  if (millis() > lastReboot + msToReboot){
    lastReboot = millis();
    rebootWifiAdapter();
  }
}


void rebootWifiAdapter(){

  digitalWrite(externalWifiPowerPin, LOW);
  delay(1000);
  digitalWrite(externalWifiPowerPin, HIGH);
  delay(1000);
}

