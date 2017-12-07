

void processSerialCommand(){

  if (Serial.available() > 0 || Serial1.available() > 0){

    digitalWrite(ledSerialPin, HIGH);
    
    serialCommandInitialized = true;
    serialCommandStartedTimeInMs = millis();
    
    String recebido = leStringSerial();

    #ifdef DEBUG_SERIAL
      MYSERIAL.print("recebido: ");
      MYSERIAL.println(recebido);
    #endif
    
    
    if (recebido == "OI"){
      MYSERIAL.println("OI");
    }
    
    if (recebido == "BATERIA" || recebido == "B"){
      MYSERIAL.print("BATERIA: ");
      MYSERIAL.print(getBatteryLevelInPercentage());
      MYSERIAL.println("%");
    }
    
    
    if (recebido.equals("D")){
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

    else if (recebido == "DF"){
      goFrontRightBridge();
    }
    else if (recebido == "DT"){
      goBackRightBridge();
    }
    else if (recebido == "EF"){
      goFrontLeftBridge();
    }
    else if (recebido == "ET"){
      goBackLeftBridge();
    }

    else if (recebido == "SS"){
      stopNow();
    }

    else {
      //stopNow();
    }
    

    digitalWrite(ledSerialPin, 0);

    serialFlush();
  }
}



/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  if (Serial.available() > 0){
    // Enquanto receber algo pela serial
    while(Serial.available() > 0) {
      // Lê byte da serial
      caractere = Serial1.read();

      if (validateCommand(caractere)){
        return String(caractere);
      }
      
      // Concatena valores
      conteudo.concat(caractere);
      
      // Aguarda buffer serial ler próximo caractere
      delay(10);
    }
  }
  
  
  else if (Serial1.available() > 0){
    
    // Enquanto receber algo pela serial
    while(Serial1.available() > 0) {    
      // Lê byte da serial
      caractere = Serial1.read();

      if (validateCommand(caractere)){
        return String(caractere);
      }
      
      // Concatena valores
      conteudo.concat(caractere);
      
      // Aguarda buffer serial ler próximo caractere
      delay(10);
    }
  }

  // Remove caracteres especiais
  conteudo.trim();
  
  return conteudo;
}


boolean serialLastCommandTimeout(){
  if (millis() - serialCommandStartedTimeInMs > serialReceiveTimeoutInMs){
    return true;
  }
  
  return false;
}


char lastChar = NULL;

boolean validateCommand(char character){
  char validCommands[] = {'A','D','W','S','T'};

  for (int i = 0; i < sizeof(validCommands); i++){
    if (lastChar == '|' && validCommands[i] == character){
      lastChar = character;
      return true;
    }    
  }

  lastChar = character;
  return false;
}


void serialFlush(){
  while(Serial.available()){Serial.read();}
  while(Serial1.available()){Serial1.read();}
}

