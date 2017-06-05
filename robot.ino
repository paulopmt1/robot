#include <Servo.h>
Servo myservo;

String getValue(String, char, int);
int getNotebookStatus ();
void powerUpNotebook ();
String leStringSerial1();

int servoValue = 80;
int powerUpNotebookPin = 23;
int notebookSensor = A0;

void setup() {
  pinMode(powerUpNotebookPin, OUTPUT);
  pinMode(notebookSensor, INPUT);

  myservo.attach(12);

  myservo.write(servoValue);
  delay(2000);
  //myservo.write(145);
  delay(2000);
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial.println("ok");
}

void freeSerial1(){
	while(Serial1.available() > 0){
		Serial1.read();
	}
}

// the loop routine runs over and over again forever:
void loop() {
 

  if (Serial1.available() > 0){
    	String recebido = leStringSerial1();
	
      if (recebido.indexOf("MOVE_WEBCAM") != -1){
        String desiredPosition = getValue(recebido, ':', 1);
        
        Serial.print("movimentar camera: ");
        int value = desiredPosition.toInt();
        Serial.println(value);
        
        myservo.write(map(value, 0,100,145,80));
        //Serial1.print("Recebido: ");
        //Serial1.println(recebido);
      }else

    	if (recebido == "LIGAR_NOTEBOOK"){
    		if (getNotebookStatus()){
    			Serial1.println("JA_LIGADO");
    		}else{
    			powerUpNotebook();
    			Serial1.println("LIGANDO_NOTEBOOK");
    		}

		powerUpNotebook();
    	}

      else{
        Serial1.print("Recebido: ");
        Serial1.println(recebido);
      }
  }
 
  int notebookSensorValue = getNotebookStatus();

  Serial1.print("note status: ");
  Serial1.println(notebookSensorValue);

  for (int i = 80; i <= 150; i+= 1){
	//myservo.write(i);
	//delay(50);
  }

  //digitalWrite(powerUpNotebook, HIGH);
  //delay(1000);
  //digitalWrite(powerUpNotebook, LOW);
  //delay(1000);

  delay(100);
  //Serial1.println("aa");
 
  for (int i = 150; i >= 80; i-= 1){
        //myservo.write(i);
        //delay(50);
  }
}

void powerUpNotebook(){
  digitalWrite(powerUpNotebookPin, HIGH);
  delay(300);
  digitalWrite(powerUpNotebookPin, LOW);
}



// Pode demorar até6 segundos para responder
int getNotebookStatus(){

  if (analogRead(notebookSensor > 100)){
	return 1;
  }

  return 0;

  int status = 0;
  bool changed = false;

  for (int i = 0; i < 60; i++){
	int notebookSensorValue = analogRead(notebookSensor);
	return notebookSensorValue;

	if (notebookSensorValue > 300){
		status = 1;
	}

	if ( ! notebookSensorValue){
		if (status){
			changed = true;
			break;
		}
	}

	delay(100);
  }


  if (changed){
	return 2;
  }

  return status;
}



/**
 * Faz o explode e retorna um valor de acordo com o indice
 */
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial1(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial1.available() > 0) {
    // Lê byte da serial
    caractere = Serial1.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  
  Serial1.flush();  
  //Serial1.print("Recebi: ");
  //Serial1.println(conteudo);
    
  return conteudo;
}
