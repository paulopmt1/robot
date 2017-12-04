

void processSerialCommand(){

  if (Serial.available() > 0 || Serial1.available() > 0){

    digitalWrite(ledSerialPin, HIGH);
    
    serialCommandInitialized = true;
    serialCommandStartedTimeInMs = millis();
    
    String recebido = leStringSerial();

    if (recebido == "OI"){
      MYSERIAL.println("OI");
    }
    
    if (recebido == "BATERIA" || recebido == "B"){
      MYSERIAL.print("BATERIA: ");
      MYSERIAL.print(getBatteryLevelInPercentage());
      MYSERIAL.println("%");
    }

    MYSERIAL.println(recebido);

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
      caractere = Serial.read();
      
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


