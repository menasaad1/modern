const char* menuItems[] = {
  "Item 1: Set timers",
  "Item 2: control mode",
  "Item 3: state timer"
};

bool inmune = false;
bool inSubMenu = false;
bool inscreentimer = false;
bool flagscreen = false;  // if retern and startup display menu
bool choisemune = false;
int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
int currentMenuIndex = 0;


// Submenu Items
const char* subMenuItems[] = {
  "timer 1 on",
  "timer 1 off",
  "timer 2 on",
  "timer 2 off",
  "timer 3 on",
  "timer 3 off"
};
int subMenuLength = sizeof(subMenuItems) / sizeof(subMenuItems[0]);
int currentSubMenuIndex = 0;
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 200;

int lasttime1 = 0;
int lasttime2 = 0;
int lasttime3 = 0;
int lasttime4 = 0;

int menuIndex = 0;
