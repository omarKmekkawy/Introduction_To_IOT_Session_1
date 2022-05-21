#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BMP085.h>

const char* ssid = "WIFI SSID"; // WIFI SSID
const char* password =  "Password"; // WIFI Password
const char* mqttServer = "MQTT Server IP"; // MQTT Broker IP
const int mqttPort = 1883; // MQTT Broker Port
const char* mqttUser = "MQTT UserName"; // MQTT Broket UserName
const char* mqttPassword = "MQTT Password"; // MQTT Broket Password

Adafruit_BMP085 bmp;
WiFiClient wifiClient;
PubSubClient client(wifiClient);

char TempString[10];

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password); // Begin the WIFI connection

  client.setServer(mqttServer, mqttPort);

  while (WiFi.status() != WL_CONNECTED) { // Loop until the ESP8266 connects to the WIFI
    delay(500);
    //Serial.println("Connecting to WiFi..");
  }

  while (!client.connected()) { // Loop until the ESP8266 connects to the WIFI
    //Serial.println("Connecting to MQTT...");

    if (client.connect("TemperatureSensor", mqttUser, mqttPassword )) {
    } else {
      delay(2000); // wait for 50ms
    }
  }
  client.publish("Log", "TemperatureSensor Is Alive!"); // Publish message "TemperatureSensor Is Alive!" on topic "Log"

  if (!bmp.begin()) { // Initialize the BMP180 sensor
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }

}

void loop() {

  itoa(bmp.readTemperature(), TempString, 10); // Convert the sensor's reading to character array
  client.publish("TemperatureSensor", TempString); // Publish the sensor's reading on topic "TemperatureSensor"
  delay(1000);
  client.loop();
}
