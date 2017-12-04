
int readBatteryLevel(){
  batteryLevel = analogRead(powerInVoltage);

  #ifdef DEBUG_BATTERY
    MYSERIAL.print("VALOR BATERIA: ");
    MYSERIAL.print(batteryLevel);
    MYSERIAL.print(" OU ");
    MYSERIAL.print(getBatteryLevelInPercentage());
    MYSERIAL.print("%  ");
    MYSERIAL.print("   MINIMO: ");
    MYSERIAL.print(batteryMinimumLevelInStep);
    MYSERIAL.print(" - MAXIMO: ");
    MYSERIAL.println(batteryMaximumLevelInStep);
  #endif
  return batteryLevel;
}

int getBatteryLevelInPercentage(){
  return map(batteryLevel, batteryMinimumLevelInStep, batteryMaximumLevelInStep, 0, 100);
}

void checkIfNeedsToShutdown(){
  
  if (readBatteryLevel() <= batteryMinimumLevelInStep){
    sameResultsOnBatteryStatusCount++;
    
    MYSERIAL.print("Pico de uso da bateria: ");
    MYSERIAL.println(sameResultsOnBatteryStatusCount);
    
    if (sameResultsOnBatteryStatusCount == 10){
      powerDown();
      MYSERIAL.println("Desligado para nao afetar a bateria");
    }
  }else{
    sameResultsOnBatteryStatusCount = 0;
  }
  
}


void powerUp(){
  digitalWrite(powerOnPin, HIGH);
}
void powerDown(){
  digitalWrite(powerOnPin, LOW);
}
