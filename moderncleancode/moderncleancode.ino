#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT.h>
#include <EEPROM.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
// to shared variables
#include <globalvariables.h>
//menu class
#include <menu.h>
// timer yearly class
#include <timerclass.h>

// make 3 object to 3 field
YearlyTimer yearlyTimer1;
YearlyTimer yearlyTimer2;
YearlyTimer yearlyTimer3;
//LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 chars and 2 line display

ThreeWire myWire(Data, SCLK, RST);
RtcDS1302<ThreeWire> Rtc(myWire);

//setting wifi to connect database and network
#define WIFI_SSID "Mina1"
#define WIFI_PASSWORD "M01281691888"
#define API_KEY "AIzaSyB0MwK7YrANxPeXQxVW94-bMSq1PyQ3rFE"
#define DATABASE_URL "https://modern-irrigation-a28eb-default-rtdb.firebaseio.com/"
#define USER_EMAIL "menasaad09@gmail.com"
#define USER_PASSWORD "M01281691888"

// accsespoint to connect another esp by wbserver (local)
const char *ssid = "ESP32_AP";
const char *password = "12345678";
WebServer server(80);
void handleRoot() {
  server.send(200, "text/plain", "Connected to ESP32");
}


void setup();

void loop() {
  screen();
  firebase();
  controlpumbs();
  now = Rtc.GetDateTime();
  printDateTime(now);
  server.handleClient();
  saveEEprom();
}


void printDateTime(const RtcDateTime &dt) {

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Day(),
             dt.Month(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  // Serial.print(datestring);
}
