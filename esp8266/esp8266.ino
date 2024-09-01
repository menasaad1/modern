#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN D4 // Pin where the DHT sensor is connected
#define DHTTYPE DHT22 // DHT 22  (AM2302)

// Define the pins for the buttons and additional sensors
#define BUTTON1_PIN D1
#define BUTTON2_PIN D2
#define BUTTON3_PIN D3
#define BUTTON4_PIN D5
#define BUTTON5_PIN D6
#define SENSOR1_PIN A0
#define SENSOR2_PIN D7

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
int tankLevel;
const char *ssid = "ESP32_AP";      // Set your ESP32 Access Point SSID
const char *password = "12345678";  // Set your ESP32 Access Point password

const String serverAddress = "http://192.168.4.1/send";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to ESP32...");
  }

  Serial.println("Connected to ESP32");
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

 http.begin(client, serverAddress);
    // Read data from DHT sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    // Read button states
    int button1State = digitalRead(BUTTON1_PIN);
    int button2State = digitalRead(BUTTON2_PIN);
    int button3State = digitalRead(BUTTON3_PIN);
    int button4State = digitalRead(BUTTON4_PIN);
    int button5State = digitalRead(BUTTON5_PIN);

if (button1State == LOW) {
    tankLevel = 100;  // Tank is full
  } else if (button2State == LOW) {
    tankLevel = 80;  // 80% full
  } else if (button3State == LOW) {
    tankLevel = 60;  // 60% full
  } else if (button4State == LOW) {
    tankLevel = 40;  // 40% full
  } else if (button5State == LOW) {
    tankLevel = 20;  // 20% full
  } else {
    tankLevel = 0;  // Tank is empty
  }
    // Read additional sensor data
    int sensor1Value = analogRead(SENSOR1_PIN);
    int sensor2Value = analogRead(SENSOR2_PIN);

    // Create a comma-separated string to send
    String dataString = String(temperature) + "," +
                        String(humidity) + "," +
                        String(tankLevel) + "," +
                        String(sensor1Value) + "," +
                        String(sensor2Value);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "data=" + dataString;

    // Send the request
    int httpResponseCode = http.POST(postData);

    // Check the response
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response from server: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("Disconnected from WiFi, trying to reconnect...");
    WiFi.begin(ssid, password);
  }

  delay(5000);  // Send data every 5 seconds
}
