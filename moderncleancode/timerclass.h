//#include "setup.ino"

class YearlyTimer {
private:
  int hour = 0, minute = 0, day = 1, month = 1, year = 2024;
  bool settingHour = true;
  bool settingMinute = false;
  bool settingDay = false;
  bool settingMonth = false;
  bool settingYear = false;

  int hourOn, minuteOn, hourOff, minuteOff, dayon, monthon, yearon, dayoff, monthoff, yearoff, relayIndex;
  bool triggeredOn, triggeredOff;

public:
  // Constructor
  YearlyTimer(int hOn = 0, int mOn = 0, int hOff = 0, int mOff = 0, int don = 1, int moon = 1, int yon = 2023, int doff = 1, int mooff = 1, int yoff = 2023, int rIdx = 0)
    : hourOn(hOn), minuteOn(mOn), hourOff(hOff), minuteOff(mOff), dayon(don), monthon(moon), yearon(yon), dayoff(doff), monthoff(mooff), yearoff(yoff), relayIndex(rIdx), triggeredOn(false), triggeredOff(false) {}

  // Method to format time as string
  String timeOn() {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d:%02d %02d/%02d/%04d (ON)", hourOn, minuteOn, dayon, monthon, yearon);
    return String(buffer);
  }

  String timeOff() {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d:%02d %02d/%02d/%04d (OFF)", hourOff, minuteOff, dayoff, monthoff, yearoff);
    return String(buffer);
  }

  // Check if the timer should turn the relay on or off
  bool checkTriggerOn(RtcDateTime& now) {
    if (now.Year() == yearon && now.Month() == monthon && now.Day() == dayon && now.Hour() == hourOn && now.Minute() == minuteOn && !triggeredOn) {
      triggeredOn = true;
      return true;
    }

    return false;
  }

  bool checkTriggerOff(RtcDateTime& now) {
    if (now.Year() == yearoff && now.Month() == monthoff && now.Day() == dayoff && now.Hour() == hourOff && now.Minute() == minuteOff && !triggeredOff) {
      triggeredOff = true;
      return true;
    }

    return false;
  }

  FirebaseJson gettimerasjson() {
    FirebaseJson json;
    // Set the timer values into the JSON object
    json.set("dayon", dayon);
    json.set("monthon", monthon);
    json.set("yearon", yearon);
    json.set("dayoff", dayoff);
    json.set("monthoff", monthoff);
    json.set("yearoff", yearoff);
    json.set("hourOn", hourOn);
    json.set("minuteOn", minuteOn);
    json.set("hourOff", hourOff);
    json.set("minuteOff", minuteOff);
    json.set("relayIndex", relayIndex);
    return json;
    // Sending the JSON data to Firebase
  }
  // Set timer properties from Firebase JSON
  void setFromFirebase(FirebaseJson& json) {
    FirebaseJsonData jsonData;

    json.get(jsonData, "dayon");
    if (jsonData.success) dayon = jsonData.intValue;


    json.get(jsonData, "monthon");
    if (jsonData.success) monthon = jsonData.intValue;

    json.get(jsonData, "yearon");
    if (jsonData.success) yearon = jsonData.intValue;
    json.get(jsonData, "dayoff");
    if (jsonData.success) dayoff = jsonData.intValue;

    json.get(jsonData, "monthoff");
    if (jsonData.success) monthoff = jsonData.intValue;

    json.get(jsonData, "yearoff");
    if (jsonData.success) yearoff = jsonData.intValue;

    json.get(jsonData, "hourOn");
    if (jsonData.success) hourOn = jsonData.intValue;

    json.get(jsonData, "minuteOn");
    if (jsonData.success) minuteOn = jsonData.intValue;

    json.get(jsonData, "hourOff");
    if (jsonData.success) hourOff = jsonData.intValue;

    json.get(jsonData, "minuteOff");
    if (jsonData.success) minuteOff = jsonData.intValue;

    json.get(jsonData, "relayIndex");
    if (jsonData.success) relayIndex = jsonData.intValue;
  }

  // Send timer properties to Firebase


  // Control the relay based on timer settings
  void Control(int o, RtcDateTime now) {

    if (checkTriggerOn(now)) {
      digitalWrite(fieldspins[o], HIGH);  // Turn relay ON
    }

    if (checkTriggerOff(now)) {
      digitalWrite(fieldspins[o], LOW);
    }
  }

  // Getters and Setters
  int getRelayIndex() const {
    return relayIndex;
  }

  void setRelayIndex(int idx) {
    relayIndex = idx;
  }

  void setTimeOn(int h, int m, int d, int mo, int y) {
    hourOn = h;
    minuteOn = m;
    dayon = d;
    monthon = mo;
    yearon = y;
    triggeredOn = false;  // Reset triggered status when time changes
  }

  void setTimeOff(int h, int m, int d, int mo, int y) {
    hourOff = h;
    minuteOff = m;
    dayoff = d;
    monthoff = mo;
    yearoff = y;
    triggeredOff = false;  // Reset triggered status when time changes
  }

  unsigned long lastDebounceTime = 0; // delay and avoiding freezing code 
  void settimersscreen(bool timermodeon) {
    unsigned long currentTime = millis();

    if (digitalRead(up) == LOW && (currentTime - lastDebounceTime) > 200) {
      increaseValue();
      lastDebounceTime = currentTime;
    } else if (digitalRead(down) == LOW && (currentTime - lastDebounceTime) > 200) {
      decreaseValue();
      lastDebounceTime = currentTime;
    } else if (digitalRead(ok) == LOW && (currentTime - lastDebounceTime) > 200) {
      selectValue(timermodeon);  // timer on  or off
      lastDebounceTime = currentTime;
    } else if (digitalRead(set) == LOW && (currentTime - lastDebounceTime) > 200) {
      backValue();
      lastDebounceTime = currentTime;
    }

    displayMenutimer();
  }
  void lcdstatetime(bool timeon) {

     lcd.setCursor(0, 1);       
     lcd.print("                ");
    lcd.setCursor(0, 1);
    if (timeon) {
      lcd.print(timeOn());
    } else {
      lcd.print(timeOff());
    }
    if (up == LOW || down == LOW || set == LOW || ok == LOW) {
      inmune = true;
    }
  }

  void displayMenutimer() {

     lcd.setCursor(0, 1);       
     lcd.print("                ");
     lcd.setCursor(0, 1);

    if (settingHour) {
      lcd.print("Hour: ");
      lcd.print(hour);
    } else if (settingMinute) {
      lcd.print("Minute: ");
      lcd.print(minute);
    } else if (settingDay) {
      lcd.print("Day: ");
      lcd.print(day);
    } else if (settingMonth) {
      lcd.print("Month: ");
      lcd.print(month);
    } else if (settingYear) {
      lcd.print("Year: ");
      lcd.print(year);
    }
  }

  void increaseValue() {
    if (settingHour && hour < 23) {
      hour++;
    } else if (settingMinute && minute < 59) {
      minute++;
    } else if (settingDay && day < 31) {
      day++;
    } else if (settingMonth && month < 12) {
      month++;
    } else if (settingYear) {
      year++;
    }
  }

  void decreaseValue() {
    if (settingHour && hour > 0) {
      hour--;
    } else if (settingMinute && minute > 0) {
      minute--;
    } else if (settingDay && day > 1) {
      day--;
    } else if (settingMonth && month > 1) {
      month--;
    } else if (settingYear && year > 2024) {
      year--;
    }
  }

  void selectValue(bool timermodeon) {



    if (settingHour) {
      settingHour = false;
      settingMinute = true;
    } else if (settingMinute) {
      settingMinute = false;
      settingDay = true;
    } else if (settingDay) {
      settingDay = false;
      settingMonth = true;
    } else if (settingMonth) {
      settingMonth = false;
      settingYear = true;
    } else if (settingYear) {
      settingHour = true;
      settingYear = false;
      if (timermodeon) {
        setTimeOn(hour, minute, day, month, year);
      } else {
        setTimeOff(hour, minute, day, month, year);
      }
       flagscreen = true;
      inSubMenu = false;
      screentimer = false;

      // Finalize setting
      //  saveToFirebase();
    }
  }

  void backValue() {
    if (settingMinute) {
      settingMinute = false;
      settingHour = true;
    } else if (settingDay) {
      settingDay = false;
      settingMinute = true;
    } else if (settingMonth) {
      settingMonth = false;
      settingDay = true;
    } else if (settingYear) {
      settingYear = false;
      settingMonth = true;
    } else if (settingHour) {
      inSubMenu = false;
      screentimer = false;
      flagscreen = true;
    }
  }
};
