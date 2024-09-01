void displaytime() {
  String s1 = datestring;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connected ,enter set to setting");
  lcd.setCursor(0, 1);
  lcd.print(s1);
}
unsigned long lastDebounceTime = 0;
unsigned long lastSwitchPressTime = 0;
void screen() {

  if (flagscreen) { // if retern and startup display menu
    flagscreen = false;
    displayMenu();
  }

  if ((inSubMenu || inscreentimer || inmune) && (millis() - lastSwitchPressTime) > 20000) {

    inmune = false;  // Exit menu due to timeout
    inSubMenu = false;
    inscreentimer = false;
    displaytime();
  }
  if ((up == LOW || down == LOW || set == LOW || ok == LOW) && (millis() - lastDebounceTime) > 200) {
    lastDebounceTime = millis();
    lastSwitchPressTime = millis();
  }
  if (!inSubMenu && !inscreentimer) {  //in menu

    navigateMenu(menuItems, menuLength, currentMenuIndex);
    if (digitalRead(ok) == LOW) {
      if (currentMenuIndex == 0 || currentMenuIndex == 2) {  // use the timer class and show variables object
        currentSubMenuIndex = 0;
        displaySubMenu();
      } else if (currentMenuIndex == 1) {
        //control manul not use now
      }
    }
  } else {
    if (!inscreentimer && !inmune) {
      navigateMenu(subMenuItems, subMenuLength, currentSubMenuIndex);

      if (digitalRead(set) == LOW) {
        inSubMenu = false;
        choisemune = false;
        inscreentimer = false;
        choisemune = false;
        displayMenu();
      }
      if (digitalRead(ok) == LOW) {
        // Handle submenu item selection
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Selected: ");
        lcd.setCursor(0, 1);
        lcd.print(subMenuItems[currentSubMenuIndex]);

        choisemune = true;
      }
    }
    if (choisemune) {
      inmune = false;
      inSubMenu = false;
      inscreentimer = true;
      bool timermodeon;  /// in on object there two timer on and off by the menu you send the true to method if timer on true, else false
      if (currentSubMenuIndex == 0) {
        timermodeon = true;
        if (currentMenuIndex == 0) {                  // show the menu and check the index of submenu and menu
          yearlyTimer1.settimersscreen(timermodeon);  //
        } else {
          yearlyTimer1.lcdstatetime(timermodeon);
        }
      } else if (currentSubMenuIndex == 1) {
        timermodeon = false;  // if show Submenu is to use the settimer and show state timer
        if (currentMenuIndex == 0) {

          yearlyTimer1.settimersscreen(timermodeon);
        } else {
          yearlyTimer1.lcdstatetime(timermodeon);
        }
      } else if (currentSubMenuIndex == 2) {
        timermodeon = true;
        if (currentMenuIndex == 0) {

          yearlyTimer2.settimersscreen(timermodeon);
        } else {
          yearlyTimer2.lcdstatetime(timermodeon);
        }

      } else if (currentSubMenuIndex == 3) {
        timermodeon = false;
        if (currentMenuIndex == 0) {

          yearlyTimer2.settimersscreen(timermodeon);
        } else {
          yearlyTimer2.lcdstatetime(timermodeon);
        }
      } else if (currentSubMenuIndex == 4) {
        timermodeon = true;
        if (currentMenuIndex == 0) {


          yearlyTimer3.settimersscreen(timermodeon);
        } else {
          yearlyTimer3.lcdstatetime(timermodeon);
        }
      } else if (currentSubMenuIndex == 5) {
        timermodeon = false;
        if (currentMenuIndex == 0) {

          yearlyTimer3.settimersscreen(timermodeon);
        } else {
          yearlyTimer3.lcdstatetime(timermodeon);
        }
      }
    }

    // if(now.Second() - lasttime4 > 3 ){  // Return to main menu
    // lasttime4 =now.Second();
    // inSubMenu = false;
    // displayMenu();
    // }
  }
}
void navigateMenu(const char* items[], int length, int& index) {
  unsigned long currentTime = millis();

  if (digitalRead(down) == LOW && currentTime - lastButtonPressTime > debounceDelay) {
    lastButtonPressTime = currentTime;
    index--;
    if (index < 0) {
      index = length - 1;  // Wrap to the last item
    }
    if (inSubMenu && !inscreentimer) {
      displaySubMenu();
    } else if (!inSubMenu && !inscreentimer) {
      displayMenu();
    }
  }

  if (digitalRead(up) == LOW && currentTime - lastButtonPressTime > debounceDelay) {
    lastButtonPressTime = currentTime;
    index++;
    if (index >= length) {
      index = 0;  // Wrap to the first item
    }
    if (inSubMenu && !inscreentimer) {
      displaySubMenu();
    } else if (!inSubMenu && !inscreentimer) {
      displayMenu();
    }
  }
}

// Function to display the current main menu item
void displayMenu() {
  inmune = true;
  inSubMenu = false;
  inscreentimer = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[currentMenuIndex]);  // Display current menu item
}

// Function to display the current submenu item
void displaySubMenu() {
  inSubMenu = true;
  inmune = false;
  inscreentimer = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(subMenuItems[currentSubMenuIndex]);  // Display current submenu item
}
