
void handleReceiveData() {
  if (server.hasArg("data")) {
    receivedArray = server.arg("data");
    
    // Split the received string into individual sensor values
    int data[5];
    parseArray(receivedArray, data, 9);

    
    Serial.println("Temperature: " + String(data[0]));
    Serial.println("Humidity: " + String(data[1]));
    Serial.println("Tank: " + String(data[2]));
    Serial.println("Sensor 1 Value: " + String(data[3]));
    Serial.println("Sensor 2 Value: " + String(data[4]));
    tanklevel_now= data[2];
     humdidty_now = data[1];
     temperature_now = data[0];
     humdidtyfields_now[0] = data[3]; 
     humdidtyfields_now[1] = data[4];
    server.send(200, "text/plain", "Array received and parsed");
  } else {
    server.send(400, "text/plain", "No array data received");
  }
}

void parseArray(String receivedArray, int *arr, int len) {
  int index = 0;
  int lastIndex = 0;

  for (int i = 0; i < len; i++) {
    index = receivedArray.indexOf(',', lastIndex);
    if (index == -1) index = receivedArray.length();
    arr[i] = receivedArray.substring(lastIndex, index).toInt();
    lastIndex = index + 1;
  }
}