#include <ESP8266WiFi.h>
#include "Gsender.h"
#include "timer.h"

#pragma region Globals
const char* ssid = "Arduino";                           // WIFI network name
const char* password = "@rdu1n0s";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
#pragma endregion Globals

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
  static uint16_t attempt = 0;
  Serial.print("Connecting to ");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    Serial.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    Serial.println(ssid);
  }

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)
  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available or SSID and Password\r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("Got IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void Awaits()
{
  uint32_t ts = millis();
  while (!connection_state)
  {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
  }
}

void sender() {
  connection_state = WiFiConnect();
  if (!connection_state) // if not connected to WIFI
    Awaits();          // constantly trying to connect
    
  Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
  if (gsender->Subject(subject)->Send(e_mail, assunto)) {
    Serial.println("Message send.");
  } else {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }

}
void setup()
{
  Serial.begin(115200);
  config_setup ();
}

void loop() {
  //verificacao no loop
  valor_AD = analogRead(A0);
  soma = soma + valor_AD;
  i++;

  if(_timeout3){
      digitalWrite(D5,!digitalRead(D5));
       _timeout3 = false;
  }else if (media > 50 && (state == 0 || state == 1)) {
       reset_timer1();
       state = 3;
  } else if (_timeout2 && (state == 0 || state == 2)) {
      state = 1;
      assunto = "A rádio está fora do ar, ou Sem áudio perceptível.";
      subject = "Som Maior - FM - 100.7 - information Radio: OFF";
      e_mail = "gustavo.lucca@satc.edu.br";
      sender();
      e_mail = "arthurlessa@gmail.com";
      sender();
      e_mail = "marceloloch.newaa@gmail.com";
      sender();
      _timeout1 = false;
  }else if (media > 50 && _timeout1 && (state == 0 || state == 3)) {
      
      state = 2;
      subject = "Som Maior - FM - 100.7 - information Radio: ON";
      assunto = "A rádio está ativa e estável.";
      e_mail = "gustavo.lucca@satc.edu.br";
      sender();
      e_mail = "arthurlessa@gmail.com";
      sender();
      e_mail = "marceloloch.newaa@gmail.com";
      sender();
      _timeout2 = false;
    
  }

  if ( i == 25) {
    media = soma / i;
    soma1 = soma1 + media;
    i = 0;
    x++;
    soma = 0;
  }else if ( x == 10) {
    media1 = soma1 / x;
    Serial.println(media1);
    x = 0;
    soma1 = 0;
  }else if (x == 3 && media1 > 35) {
    reset_timer2();
    yield();
  } 
}  
