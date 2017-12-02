
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <WebSocketsClient.h>

#include <Hash.h>

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;


#define USE_SERIAL Serial

#define MESSAGE_INTERVAL 3000
#define HEARTBEAT_INTERVAL 2500

uint64_t messageTimestamp = 0;
uint64_t heartbeatTimestamp = 0;
bool isConnected = false;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {


    switch(type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[WSc] Disconnected!\n");
            isConnected = false;
            break;
        case WStype_CONNECTED:
            {
                USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
                isConnected = true;

              // send message to server when Connected
              // socket.io upgrade confirmation message (required)
              webSocket.sendTXT("5");
            }
            break;
        case WStype_TEXT:
            //USE_SERIAL.printf("[WSc] get text: %s\n", payload);            
            processReturn(payload);
            
            // send message to server
            // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
            hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
    }

}

void setup() {
    // USE_SERIAL.begin(921600);
    USE_SERIAL.begin(9600);

    //Serial.setDebugOutput(true);
    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("999mor", "999mor20171720");

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.beginSocketIO("54.94.244.175", 3001);
    //webSocket.setAuthorization("user", "Password"); // HTTP Basic Authorization
    webSocket.onEvent(webSocketEvent);

    identifyRobot();
}

void loop() {
    webSocket.loop();

    if(isConnected) {
        
        uint64_t now = millis();

        if(now - messageTimestamp > MESSAGE_INTERVAL) {
            messageTimestamp = now;
            // example socket.io message with type "messageType" and JSON payload
            //webSocket.sendTXT("42[\"messageType\",{\"greeting\":\"hello\"}]");
            
            //webSocket.sendTXT("42[\"userCommand\",\"S\"]");
            
        }
    }
}

void identifyRobot(){
  while (!isConnected){
    webSocket.loop();
  }

  webSocket.sendTXT("42[\"identify\",{\"type\":\"robot\"}]");  
}

void processReturn(uint8_t * serverData){
  String str = String((char*)serverData);
  
  // Se recebeu mensagem válida
  if (str.indexOf("42") != -1){
    String data = str.substring(2);

    // Remove o que não precisa
    data.replace("[","");
    data.replace("]","");

    String command = getValue(data, ',', 0);
    command.replace("\"", "");

    String commandAction = getValue(data, ',', 1);
    commandAction.replace("\"", "");

    //Serial.print("comando: ");
    //Serial.println(command);

    if (command == "userCommand"){
      //Serial.println("Vou enviar para serial: ");
      Serial.println(commandAction);
    }
  }
  
}


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


