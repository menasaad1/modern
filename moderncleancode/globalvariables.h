
#include "EEPROM.h"


//rtc pins
const int Data = 32;
const int SCLK = 33;
const int RST = 25;
RtcDateTime now;  //object shared

// lcdpin
const int sda = 13;
const int scl = 14;

//relays pin
const int field1 = 23;
const int field2 = 22;
const int field3 = 1;
const int submersiblepumppin = 21;
const int waterpump = 3;
const int fieldspins[] = {field1, field2, field3}; // to easy and use for loop

//input switchpins
const int ok = 17;
const int set = 16;
const int up = 34;
const int down = 35;

// varibles to control system and use EEProm to restore my varible setting
float temperature_now;
float humdidty_now;
int humdidtyfields_now[3];//(field 1 ,field 2,field 3)
int tanklevel_now;
int settanklevel = EEPROM.read(1);
int settemp = EEPROM.read(2);
bool timermode = EEPROM.read(3);
bool Smart = EEPROM.read(4);  // to control by using just phone
int sethumdidtyfields[3] = {EEPROM.read(5),EEPROM.read(6),EEPROM.read(7)};//(field 1 ,field 2,field 3)
int countoftimers=EEPROM.read(8);
// to get time String and control format
char datestring[20];

// firebase connection
 FirebaseData fbdo;
 FirebaseAuth auth;
FirebaseConfig config;

//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16 chars and 2 line display