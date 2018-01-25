
unsigned long previousMillis = 0;
unsigned long lastBatteryStatusSentMillis = 0;
unsigned long lastBatteryReadMillis = 0;

const int batteryReadSamples = 30;
int batteryReads[batteryReadSamples];
int batteryReadPointer = 0;

bool isConnectedToChargerBase();
void startBatteryCharging();
bool isChargingStatus = false;

int readBatteryLevel(){
  
  if (lastBatteryReadMillis + 1000 < millis()){
    lastBatteryReadMillis = millis();

    makeBatteryRead();
    batteryLevel = getBatteryMediaLevel();

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
    
  }
  
  return batteryLevel;
}

void makeBatteryRead(){
  batteryReads[batteryReadPointer++] = analogRead(powerInVoltage);
  
  if (batteryReadPointer == batteryReadSamples){
    #ifdef DEBUG_BATTERY
      MYSERIAL.print("batteryReadPointer = 0");
    #endif
    
    batteryReadPointer = 0;
  }
}

int getBatteryMediaLevel(){
  int allReads = 0;
  int numberOfValidSamples = 0;

  for (int i = 0; i < batteryReadSamples; i++){
    if (batteryReads[i]){
      numberOfValidSamples++;
      allReads += batteryReads[i];
    }
  }

  return allReads / numberOfValidSamples;
}

int getBatteryLevelInPercentage(){
  return map(batteryLevel, batteryMinimumLevelInStep, batteryMaximumLevelInStep, 0, 100);
}

void checkIfNeedsToShutdown(){

  if (batteryLevel > 0 && batteryLevel <= batteryMinimumLevelInStep){
    Serial1.println("FATAL_SHUTDOWN: Desligando para nao afetar a bateria");
    MYSERIAL.println("Desligado para nao afetar a bateria");
    delay(1000);
    powerDown();
  }
}


void powerUp(){
  digitalWrite(powerOnPin, HIGH);
  Serial1.println("ROBOT_STARTUP");
}
void powerDown(){
  //digitalWrite(powerOnPin, LOW);
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

  Serial1.println("BATTERY_CHARGING_STARTED");
  
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
  Serial1.println("BATERIA_ORIGINAL:" + String(readBatteryLevel()) + " BATERIA_PERCENTUAL:" + getBatteryLevelInPercentage());
}

