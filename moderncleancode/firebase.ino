

unsigned long lastFirebaseUpdateTime = 0;
void firebase() {

  // Check if it time to update Firebase
  if (Firebase.ready() && millis() - lastFirebaseUpdateTime >= 500) {
    lastFirebaseUpdateTime = millis();
    updateFirebaseData();
  }
}

void updateFirebaseData() {
  // Prepare a FirebaseJson object for sending data
  FirebaseJson sendJson;
  // Collect field states

  for (int i = 0; i < 3; i++) {

    sendJson.set("p" + String(i + 1), (int)digitalRead(fieldspins[i]));

    sendJson.set("set hum field " + String(i + 1), sethumdidtyfields[i]);
  }

  // Add sensor and status data
  sendJson.set("temperature", temperature_now);
  sendJson.set("settemp", settemp);
  sendJson.set("humidity", humdidty_now);
  sendJson.set("time", datestring);
  sendJson.set("level", tanklevel_now);
  sendJson.set("timermode", timermode);
  sendJson.set("subpump", (int)digitalRead(submersiblepumppin));
  sendJson.set("pump", (int)digitalRead(waterpump));

  // Send JSON data to Firebase
  if (Firebase.RTDB.updateNode(&fbdo, "/state", &sendJson)) {
    // After successfully sending  read control data back
    FirebaseJson receiveJson;
    if (Firebase.RTDB.getJSON(&fbdo, "/control", &receiveJson)) {
      processControlData(receiveJson);
    } else {
      Serial.println("Failed to receive control data: " + fbdo.errorReason());
    }
  } else {
    Serial.println("Failed to send data: " + fbdo.errorReason());
  }
}
void processControlData(FirebaseJson& json) {

  FirebaseJsonData jsonData;
  // Process relay controls

  // Process timer mode
  if (json.get(jsonData, "timermode")) {
    timermode = jsonData.boolValue;
  }
  if (json.get(jsonData, "Smart")) {
    Smart = jsonData.boolValue;
  }
  if (json.get(jsonData, "level")) {
    settanklevel = jsonData.intValue;
  }
  if (!Smart) {
    for (int i = 0; i < 3; i++) {
      if (json.get(jsonData, "r" + String(i + 1))) {
        bool state = jsonData.boolValue;
        digitalWrite(fieldspins[i], state ? HIGH : LOW);
      }
    }
    if (json.get(jsonData, "subpump")) {
      bool state = jsonData.boolValue;
      digitalWrite(submersiblepumppin, state ? HIGH : LOW);
    }
  }
  if (json.get(jsonData, "settemp")) {
    settemp = jsonData.intValue;
  }

  //jsonData if the data is already in a FirebaseJsonData object
  FirebaseJson timerJson;

  if (json.get(jsonData, "timer1")) {
    if (jsonData.type == "object") {
      jsonData.getJSON(timerJson);
      //
      yearlyTimer1.setFromFirebase(timerJson);
    }
  }
  if (json.get(jsonData, "timer2")) {
    if (jsonData.type == "object") {
      jsonData.getJSON(timerJson);
      yearlyTimer2.setFromFirebase(timerJson);
    }
  }
  if (json.get(jsonData, "timer3")) {
    if (jsonData.type == "object") {
      jsonData.getJSON(timerJson);
      yearlyTimer3.setFromFirebase(timerJson);
    }
  }
}



void sendtopreparedatapase() {
  //if i prepare variable in my database to recive my varible again
  FirebaseJson datajsontosend;


  for (int i = 0; i < 3; i++) {
    datajsontosend.set("r" + String(i + 1), 0);
  }
  datajsontosend.set("subpump", 0);
  datajsontosend.set("Smart", true);
  datajsontosend.set("level", tanklevel_now);
  datajsontosend.set("timermode", true);
  datajsontosend.set("settemp", settemp);
  datajsontosend.set("timer1", yearlyTimer1.gettimerasjson());
  datajsontosend.set("timer2", yearlyTimer2.gettimerasjson());
  datajsontosend.set("timer3", yearlyTimer3.gettimerasjson());
  if (Firebase.RTDB.setJSON(&fbdo, "/control", &datajsontosend)) {
  }
}