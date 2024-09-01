void connectToWiFi() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting: ");
  lcd.setCursor(0, 1);
  int count = 0;
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    if (count > 15) { ESP.restart(); }  //restart to fast a connected to wifi for esp32
    lcd.print(".");
    Serial.print(".");
    delay(300);
  }
}

void setup() {

  //lcd
  Wire.begin(sda, scl);  //SDA_PIN, SCL_PIN
  lcd.init();            // initialize the lcd
  lcd.backlight();       // Turn on the lcd screen backlight
  Serial.begin(115200);

  connectToWiFi();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // accespoint recive data
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.on("/send", HTTP_POST, handleReceiveData);
  server.begin();


  // firebase connection
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.begin(&config, &auth);

  // pinmode for input and output
  pinMode(field1, OUTPUT);
  pinMode(field2, OUTPUT);
  pinMode(field3, OUTPUT);
  pinMode(submersiblepumppin, OUTPUT);
  pinMode(waterpump, OUTPUT);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(set, INPUT_PULLUP);
  pinMode(ok, INPUT_PULLUP);

  //time now
  Rtc.Begin();  // initialize the RTC
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  now = Rtc.GetDateTime();

  //first send to database
  sendtopreparedatapase();
}