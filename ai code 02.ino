#define BLYNK_TEMPLATE_ID "TMPLGkJTJJfW"
#define BLYNK_DEVICE_NAME "Plant Monitoring"
#define BLYNK_AUTH_TOKEN "Hh1G4ksZbwX3DSGPXafpUt63cBm95hVf"

#include <DHT.h> // include the DHT library
#include <ESP8266WiFi.h> // include the ESP8266WiFi library
#include <BlynkSimpleEsp8266.h> // include the Blynk library

const char* ssid = "pixellhub"; // replace with your Wi-Fi network SSID
const char* password = "596@pixim"; // replace with your Wi-Fi network password
char auth[] = "Hh1G4ksZbwX3DSGPXafpUt63cBm95hVf"; // replace with your Blynk auth token

const int soilMoisturePin = D3; // soil moisture sensor pin
const int temperatureHumidityPin = D4; // temperature and humidity sensor pin

DHT dht(temperatureHumidityPin, DHT11); // create a DHT object

void setup() {
  Serial.begin(115200); // start serial communication
  dht.begin(); // start the DHT sensor
  WiFi.begin(ssid, password); // connect to the Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) { // wait until connected
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Blynk.begin(auth, ssid, password); // connect to Blynk server
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin); // read soil moisture value
  float temperature = dht.readTemperature(); // read temperature value
  float humidity = dht.readHumidity(); // read humidity value

  // send data to Blynk
  Blynk.virtualWrite(V2, soilMoisture);
  Blynk.virtualWrite(V6, temperature);
  Blynk.virtualWrite(V5, humidity);

  // wait 15 seconds before sending the next update
  delay(15000);
}
