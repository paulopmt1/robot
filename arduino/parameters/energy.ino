
unsigned long previousMillis = 0;
unsigned long lastBatteryStatusSentMillis = 0;
bool isConnectedToChargerBase();
void startBatteryCharging();
bool isChargingStatus = false;

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


void checkChargingBase(){
  if (isConnectedToChargerBase()){
    #ifdef DEBUG_BATTERY
      MYSERIAL.println("Conectado a base de carregamento da bateria");
    #endif

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= timeInSecondsToStartCharging * 1000 && getBatteryLevelInPercentage() < batteryPercentageToStartCharging && ! isChargingStatus) {
      #ifdef DEBUG_BATTERY
        MYSERIAL.println("Iniciando carregamento da bateria");
      #endif
      
      startBatteryCharging();
    }
  }else{
    isChargingStatus = false;
    previousMillis = millis();
  }
}

void startBatteryCharging(){
  isChargingStatus = true;
  
  // Ativacao do rele eh invertida
  digitalWrite(externalBatteryChargerPin, 0);
  delay(2000);
  digitalWrite(externalBatteryChargerPin, 1);
  delay(1000);
  digitalWrite(externalBatteryChargerPin, 0);
  delay(1000);
  digitalWrite(externalBatteryChargerPin, 1);

  #ifdef DEBUG_BATTERY
    MYSERIAL.println("Carregamento da bateria iniciado");
  #endif
}

bool isConnectedToChargerBase(){
  
  if (digitalRead(externalPowerPin)){
    return true;
  }

  return false;
}

void sendBatteryStatus(){
  if (lastBatteryStatusSentMillis + 30000 < millis()){
    lastBatteryStatusSentMillis = millis();
    printBatteryLevel();
  }
  
}

void printBatteryLevel(){
  MYSERIAL.print("BATERIA: ");
  MYSERIAL.print(getBatteryLevelInPercentage());
  MYSERIAL.println("%");
  Serial1.println("BATERIA:" + String(readBatteryLevel()));
}

