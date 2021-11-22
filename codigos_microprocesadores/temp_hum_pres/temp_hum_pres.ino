#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

/*#include "../net_secrets.h" // buscar la carpeta donde esté el archivo .h de la contraseña y nombre del Wi-Fi

char ssid[] = "sakura-5G"; // nombre Wi-Fi
char pass[] = "Laura?2012"; // contraseña Wi-Fi
*/

String topics[2] = {"pressure/", "hum/" /*"temp/"*/}; // temas para recibir
String deviceId = "AAL"; 

Adafruit_BME280 bme; // sensor de tem, hum, pressure 
//BH1750 lightMeter(0x23); // sensor de lux

int luz = 16;
int ventilador = 13;
float temp;

// la guia del codigo es basado en los ejemplos de ArduinoMqttClient (WiFiAdvancedCallback

void setup(){
  Serial.begin(9600);

  pinMode(luz, OUTPUT);
  pinMode(ventilador, OUTPUT);

  Wire.begin();
  
  while (!Serial) {
    ;
  }

/*
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();
*/

  bool status = bme.begin(0x76);  
}


void loop() {
  //mqttClient.poll();
  
  //mediciones: [presión en hPa, humedad, temperatura, lux]
  double measurement[2] = {bme.readPressure()/100.0F, bme.readHumidity() /*bme.readTemperature()*/};

  //creación de las payload con los datos a ser enviado a cada tema
  String payloads[2] = {"", ""};

  for(int i = 0; i < 2; i++)
    payloads[i] += measurement[i];
  
    bool retained = false; 
    int qos = 2; 
    bool dup = false;
  
   for(int i = 0; i < 2; i++){
      //mqttClient.beginMessage("esp/"+topics[i]+deviceId, payloads[i].length(), retained, qos, dup);
      //mqttClient.print(payloads[i]);
      //mqttClient.endMessage();

      Serial.println();
      Serial.print(topics[i]+deviceId);
      Serial.print("/");
      Serial.print(payloads[i]);
      Serial.println();
    }

  temp = bme.readTemperature();
  Serial.print("temp/");
  Serial.println(temp);
   
  if (temp < 21) {
    digitalWrite(ventilador, LOW);
    Serial.println("Ventilador apagado");  
  }

  if (temp >= 23) {
    digitalWrite(ventilador, HIGH);
    Serial.println("Ventilador encendido");   
  }
  
  digitalWrite(luz,HIGH);
  delay(10000);
  digitalWrite(luz,LOW);

  delay(5000);
}
