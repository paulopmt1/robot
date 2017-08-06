int entireRoundStep = 125;
int enginePower = 100;
int stepsPerAction = 40;


const int sensorRightPin = A0;
const int sensorDirMiddleValue = 300;
int sensorRightLastState = 0;
int sensorRightStepCount = 0;

const int sensorLeftPin = A1;
const int sensorLeftMiddleValue = 350;
int sensorLeftLastState = 0;
int sensorLeftStepCount = 0;




int xAxisData;
int yAxisData;

int leftBridge_PNP_A = 4;
int leftBridge_NPN_A = 5;
int leftBridge_PNP_B = 7;
int leftBridge_NPN_B = 6;

int rightBridge_PNP_A = 8;
int rightBridge_NPN_A = 9;
int rightBridge_PNP_B = 11;
int rightBridge_NPN_B = 10;

int xAxis = 2;
int yAxis = 3;

bool serialCommandInitialized = false;




void proccessLeftMotor();
void proccessRightMotor();




void setup(){
  Serial.begin(115200);
  Serial.println("Inicio ok");
  
  
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
}

void loop(){
  readStepSensors();
  processSerialCommand();
  
    Serial.print(sensorLeftStepCount);
    Serial.print(" - ");
    Serial.println(sensorRightStepCount);
}



void readStepSensors(){
  proccessRightMotor();
  proccessLeftMotor();
  delay(10);
}






/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}





void processSerialCommand(){

  if (Serial.available() > 0){

    serialCommandInitialized = true;
    
    String recebido = leStringSerial();

    if (recebido == "D"){
      goRight();
    }

    else if (recebido == "A"){
      goLeft();
    }

    else if (recebido == "W"){
      goFront();
    }

    else if (recebido == "S"){
      goBack();
    }

    else {
      stopNow();
    }
  }
}


void stopNow(){
  disableLeftBridge();
  disableRightBridge();
}

void goFront(){
  goFrontWithBalancing();
}

void goBack(){
  goBackWithBalancing();
}

void goLeft(){
  goLeftWithBalancing();
}

void goRight(){
  goRightWithBalancing();
}



void goLeftWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerAction / 2){
   
    if (sensorRightStepCount > sensorLeftStepCount){
      goBackLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goFrontRightBridge();
      disableLeftBridge();
    } 
    
    else{
      goBackLeftBridge();
      goFrontRightBridge();
    }
    
    Serial.print(sensorLeftStepCount);
    Serial.print(" - ");
    Serial.println(sensorRightStepCount);
    
    readStepSensors();
  }
  
  stopNow();
}



void goRightWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerAction / 2){
   
    if (sensorRightStepCount > sensorLeftStepCount){
      goFrontLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goBackRightBridge();
      disableLeftBridge();
    } 
    
    else{
      goBackRightBridge();
      goFrontLeftBridge();
    }
    
    Serial.print(sensorLeftStepCount);
    Serial.print(" - ");
    Serial.println(sensorRightStepCount);
    
    readStepSensors();
  }
  
  stopNow();
}



void goFrontWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerAction){
   
    if (sensorRightStepCount > sensorLeftStepCount){
      goFrontLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorRightStepCount < sensorLeftStepCount){
      goFrontRightBridge();
      disableLeftBridge();
    } 
    
    else{
      goFrontLeftBridge();
      goFrontRightBridge();
    }
    
    Serial.print(sensorLeftStepCount);
    Serial.print(" - ");
    Serial.println(sensorRightStepCount);
    
    readStepSensors();
  }
  
  stopNow();
}

void goBackWithBalancing(){
  sensorRightStepCount = 0;
  sensorLeftStepCount = 0;
  
  while(sensorRightStepCount < stepsPerAction){
    
    if (sensorRightStepCount == sensorLeftStepCount){
      goBackLeftBridge();
      goBackRightBridge();
    }
    
    else if (sensorRightStepCount > sensorLeftStepCount){
      goBackLeftBridge();
      disableRightBridge();
    }
    
    else if (sensorLeftStepCount > sensorRightStepCount){
      goBackRightBridge();
      disableLeftBridge();
    }
    
    Serial.print(sensorLeftStepCount);
    Serial.print(" - ");
    Serial.println(sensorRightStepCount);
    
    readStepSensors();
  }
  
  stopNow();
}





void disableLeftBridge(){
  digitalWrite(leftBridge_PNP_A, LOW);
  digitalWrite(leftBridge_NPN_A, LOW);
  digitalWrite(leftBridge_PNP_B, LOW);
  digitalWrite(leftBridge_NPN_B, LOW);
}
void goFrontLeftBridge(){
  digitalWrite(leftBridge_PNP_A, HIGH);
  digitalWrite(leftBridge_NPN_A, LOW);
  digitalWrite(leftBridge_PNP_B, LOW);
  analogWrite(leftBridge_NPN_B, enginePower);
}
void goBackLeftBridge(){
  digitalWrite(leftBridge_PNP_A, LOW);
  digitalWrite(leftBridge_NPN_A, HIGH);
  analogWrite(leftBridge_PNP_B, enginePower);
  digitalWrite(leftBridge_NPN_B, LOW);
}


void disableRightBridge(){
  digitalWrite(rightBridge_PNP_A, LOW);
  digitalWrite(rightBridge_NPN_A, LOW);
  digitalWrite(rightBridge_PNP_B, LOW);
  digitalWrite(rightBridge_NPN_B, LOW);
}
void goFrontRightBridge(){
  digitalWrite(rightBridge_PNP_A, LOW);
  digitalWrite(rightBridge_NPN_A, HIGH);
  analogWrite(rightBridge_PNP_B, enginePower);
  digitalWrite(rightBridge_NPN_B, LOW);
}
void goBackRightBridge(){
  digitalWrite(rightBridge_PNP_A, HIGH);
  digitalWrite(rightBridge_NPN_A, LOW);
  digitalWrite(rightBridge_PNP_B, LOW);
  analogWrite(rightBridge_NPN_B, enginePower);
}







void proccessRightMotor(){
  
  int sensorRightValue = analogRead(sensorRightPin);
  
  //Serial.println(sensorRightValue);
  boolean changed = 0;
  
  if (sensorRightValue <= sensorDirMiddleValue){
    if (sensorRightLastState != 0){
      sensorRightLastState = 0;
      changed = 1;
    }
  }else{
    if (sensorRightLastState != 1){
      sensorRightLastState = 1;
      changed = 1;
    }
  }
  
  if (changed){
    sensorRightStepCount++;
    //Serial.println(sensorRightStepCount);

    /*    
    if (sensorRightStepCount == entireRoundStep){
      Serial.println("Volta completa");
      sensorRightStepCount = 0;
    }
    */
  }
  
}


void proccessLeftMotor(){
  
  int sensorLeftValue = analogRead(sensorLeftPin);
  
  //Serial.println(sensorRightValue);
  boolean changed = 0;
  
  if (sensorLeftValue <= sensorLeftMiddleValue){
    if (sensorLeftLastState != 0){
      sensorLeftLastState = 0;
      changed = 1;
    }
  }else{
    if (sensorLeftLastState != 1){
      sensorLeftLastState = 1;
      changed = 1;
    }
  }
  
  if (changed){
    sensorLeftStepCount++;
    //Serial.println(sensorLeftStepCount);

    /*    
    if (sensorLeftStepCount == entireRoundStep){
      Serial.println("Volta completa");
      sensorLeftStepCount = 0;
    }
    */
  }
  
}
