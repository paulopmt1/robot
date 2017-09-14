

int xAxisData;
int yAxisData;

int hBridge1_PNP_A = 4;
int hBridge1_NPN_A = 5;
int hBridge1_PNP_B = 6;
int hBridge1_NPN_B = 7;

int hBridge2_PNP_A = 8;
int hBridge2_NPN_A = 9;
int hBridge2_PNP_B = 10;
int hBridge2_NPN_B = 11;

int xAxis = 2;
int yAxis = 3;

bool serialCommandInitialized = false;

void setup() {

  pinMode(xAxis, INPUT);
  pinMode(yAxis, INPUT);

  pinMode(hBridge1_PNP_A, OUTPUT);
  pinMode(hBridge1_NPN_A, OUTPUT);
  pinMode(hBridge1_PNP_B, OUTPUT);
  pinMode(hBridge1_NPN_B, OUTPUT);
  
  pinMode(hBridge2_PNP_A, OUTPUT);
  pinMode(hBridge2_NPN_A, OUTPUT);
  pinMode(hBridge2_PNP_B, OUTPUT);
  pinMode(hBridge2_NPN_B, OUTPUT);
  
  Serial.begin(9600);
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


void loop() {

  
  processSerialCommand();

  if ( ! serialCommandInitialized){
    processRemoteControl();
  }  
 
  delay(5);
}



void processSerialCommand(){

  if (Serial.available() > 0){

    serialCommandInitialized = true;
    
    String recebido = leStringSerial();
    int value = 75;

    if (recebido == "DIREITA"){
        goFrontBridge1(value);
        goBackBridge2(value);
    }

    else if (recebido == "ESQUERDA"){
        goBackBridge1(value);
        goFrontBridge2(value);
    }

    else if (recebido == "FRENTE"){
        goFrontBridge1(value);
        goFrontBridge2(value);
    }

    else if (recebido == "TRAS"){
        goBackBridge1(value);
        goBackBridge2(value);
    }

    else {
        disableHBridge1();
        disableHBridge2();
    }
  }
}


void processRemoteControl(){
  int disableAllBridgesByXaxis = false;
  int disableAllBridgesByYaxis = false;
  
  xAxisData = pulseIn(xAxis, HIGH, 25000);
  yAxisData = pulseIn(yAxis, HIGH, 25000);

  if (xAxisData != 0){
  
    int pwmValue = constrain(map(xAxisData, 974, 1980, 0, 255), 0, 255);
    //Serial.println(pwmValue);
  
    if (pwmValue > 135){
      int frontValue = map(pwmValue, 135, 255, 0, 255);
      Serial.print("valor pwm frente: ");
      Serial.println(frontValue);
      goFrontBridge1(frontValue);
      goBackBridge2(frontValue);
    }else if (pwmValue < 120){
      int backwardValue = map(pwmValue, 120, 0, 0, 255);
      Serial.print("valor pwm tras: ");
      Serial.println(backwardValue);
      goBackBridge1(backwardValue);
      goFrontBridge2(backwardValue);
    } else{
      disableAllBridgesByXaxis = true;
    }
  }

  if (yAxisData != 0){
    //Serial.print(yAxisData);
    //Serial.print(' ');
    int pwmValue = constrain(map(yAxisData, 974, 1980, 0, 255), 0, 255);
    //Serial.println(pwmValue);
  
    if (pwmValue > 135){
      int frontValue = map(pwmValue, 135, 255, 0, 255);
      Serial.print("valor pwm frente: ");
      Serial.println(frontValue);
      goFrontBridge1(frontValue);
      goFrontBridge2(frontValue);
    }else if (pwmValue < 120){
      int backwardValue = map(pwmValue, 120, 0, 0, 255);
      Serial.print("valor pwm tras: ");
      Serial.println(backwardValue);
      goBackBridge1(backwardValue);
      goBackBridge2(backwardValue);
    } else{
      disableAllBridgesByYaxis = true;
    }
  }

  if (disableAllBridgesByXaxis && disableAllBridgesByYaxis){
    disableHBridge1();
    disableHBridge2();
  }
}

void disableHBridge1(){
  digitalWrite(hBridge1_PNP_A, LOW);
  digitalWrite(hBridge1_NPN_A, LOW);
  digitalWrite(hBridge1_PNP_B, LOW);
  digitalWrite(hBridge1_NPN_B, LOW);
}
void goFrontBridge1(int pwmValue){
  digitalWrite(hBridge1_PNP_A, HIGH);
  digitalWrite(hBridge1_NPN_A, LOW);
  digitalWrite(hBridge1_PNP_B, LOW);
  analogWrite(hBridge1_NPN_B, pwmValue);
}
void goBackBridge1(int pwmValue){
  digitalWrite(hBridge1_PNP_A, LOW);
  digitalWrite(hBridge1_NPN_A, HIGH);
  analogWrite(hBridge1_PNP_B, pwmValue);
  digitalWrite(hBridge1_NPN_B, LOW);
}


void disableHBridge2(){
  digitalWrite(hBridge2_PNP_A, LOW);
  digitalWrite(hBridge2_NPN_A, LOW);
  digitalWrite(hBridge2_PNP_B, LOW);
  digitalWrite(hBridge2_NPN_B, LOW);
}
void goFrontBridge2(int pwmValue){
  digitalWrite(hBridge2_PNP_A, HIGH);
  digitalWrite(hBridge2_NPN_A, LOW);
  digitalWrite(hBridge2_PNP_B, LOW);
  analogWrite(hBridge2_NPN_B, pwmValue);
}
void goBackBridge2(int pwmValue){
  digitalWrite(hBridge2_PNP_A, LOW);
  digitalWrite(hBridge2_NPN_A, HIGH);
  analogWrite(hBridge2_PNP_B, pwmValue);
  digitalWrite(hBridge2_NPN_B, LOW);
}
