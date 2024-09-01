void saveEEprom() {

  EEPROM.write(1, settanklevel);
  EEPROM.write(2, settemp);
  EEPROM.write(3, timermode);
  EEPROM.write(4, Smart);

  for (int i = 0; i < 3; i++) {
    EEPROM.write(5 + i, sethumdidtyfields[i]);
  }

  EEPROM.write(8, countoftimers);
  EEPROM.commit();
}
