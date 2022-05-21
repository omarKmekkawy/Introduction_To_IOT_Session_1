#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WIFI SSID"; // WIFI SSID
const char* password =  "Password"; // WIFI Password
const char* mqttServer = "MQTT Server IP"; // MQTT Broker IP
const int mqttPort = 1883; // MQTT Broker Port
const char* mqttUser = "MQTT UserName"; // MQTT Broket UserName
const char* mqttPassword = "MQTT Password"; // MQTT Broket Password

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Make the onboard LED's pin as output
  digitalWrite(LED_BUILTIN, LOW); // Turn of the LED
  // put your setup code here, to run once:
  WiFi.begin(ssid, password); // Begin the WIFI connection
  while (WiFi.status() != WL_CONNECTED) { // Loop until the ESP8266 connects to the WIFI
    delay(50);
    //Serial.println("Connecting to WiFi..");
  }
  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) { // If the WIFI is connected, connect to the MQTT broker
    //Serial.println("Connecting to MQTT...");
    if (client.connect("DashboardButton", mqttUser, mqttPassword )) {
    } else {
      delay(50); // wait for 50ms
    }
  }
  client.publish("cmnd/RelaySonoff_01/POWER", "2"); // Publish "2" on Topic cmnd/RelaySonoff_01/POWER (Toggle the Sonoff Relay) on each press
  delay(500); // delay for 500ms
  digitalWrite(LED_BUILTIN, HIGH); // Turn of the onboard LED
  ESP.deepSleep(0); // Go to deep sleep
}

void loop() {
  // put your main code here, to run repeatedly:
  yield(); // Loop
}
