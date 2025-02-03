
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL218chNMQY"
#define BLYNK_TEMPLATE_NAME "smartAquaruim"
#define BLYNK_AUTH_TOKEN "6F7DPKFeYTaszMfc0bjZ6oHwbaF5ar5A"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Ahmed Saber1";
char pass[] = "Ahmed Saber";

#include <Arduino.h>
const int analogPin = 35; 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <OneWire.h>
#include <DallasTemperature.h>
const int oneWireBus = 27;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <ESP32Servo.h>

// Define the servo pin connected to the servo motor
const int servoPin = 12;

// Create a Servo object to control the motor
Servo myServo;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int minValue = 4095;    
const int maxValue = 3000;  
const float newRangeMin = 0.0;  
const float newRangeMax = 14.0; 

void setup()
{

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  myServo.attach(servoPin);
  sensors.begin();
}

void loop() {

  sensors.requestTemperatures();
  
  double temperatureC = sensors.getTempCByIndex(0);

  int sensorValue = analogRead(analogPin); 
  double PH = map(sensorValue, minValue, maxValue, newRangeMin, newRangeMax);
  Blynk.run();

  if(sensorValue > 3900){
  myServo.write(90); 
  Blynk.logEvent("ph_is_low","less than 7");
      delay(200);
  }
  myServo.write(0); 

    Blynk.virtualWrite(V0,PH);
    Blynk.virtualWrite(V1,temperatureC);

  }
