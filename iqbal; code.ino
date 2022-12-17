#define BLYNK_PRINT Serial   
#define BLYNK_TEMPLATE_ID "TMPLGkJTJJfW"
#define BLYNK_DEVICE_NAME "Plant Monitoring"
#define BLYNK_AUTH_TOKEN "Hh1G4ksZbwX3DSGPXafpUt63cBm95hVf"

#define BLYNK_PRINT Serial
#include <OneWire.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SimpleTimer.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char auth[] ="Hh1G4ksZbwX3DSGPXafpUt63cBm95hVf";               //Authentication code sent by Blynk
char ssid[] = "pixellhub";                       //WiFi SSID
char pass[] = "596@pixim";                       //WiFi Password

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void sendSensor()
{
 float h = dht.readHumidity();
 float t = dht.readTemperature();

 if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
 }

 Blynk.virtualWrite(V5, h); //V5 is for Humidity
 Blynk.virtualWrite(V6, t); //V6 is for Temperature
}
void setup()
{
 Serial.begin(9600);
   Blynk.begin(auth, ssid, pass);
 dht.begin();

 timer.setInterval(1000L, sendSensor);
 Blynk.begin(auth, ssid, pass);
  sensors.begin();
}
 int sensor=0;
 int output=0;
 void sendTemps()
{
sensor=analogRead(A0);
output=(145-map(sensor,0,1023,0,100)); //in place 145 there is 100(it change with the change in sensor)
delay(1000);
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);
Serial.println(temp);
Serial.print("moisture = ");
Serial.print(output);
Serial.println("%");
Blynk.virtualWrite(V1, temp);
Blynk.virtualWrite(V2,output);
delay(1000);
}
void loop()
{
Blynk.run();
timer.run();
sendTemps();
}
if (sensorState == 1 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
