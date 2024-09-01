// void solartracker(){
// int ldr1Value = ldr1  // read the value from LDR 1       can you read from esp8266 and control 
// int ldr2Value =  ldr2 // read the value from LDR 2
// int error = ldr1Value - ldr2Value;
// if (abs(error) > 50) {  // if the difference is significant
//     if (error > 0) {
//       digitalWrite(left, HIGH); 
//       digitalWrite(right, LOW); // move servo one step
//     } else {
//     digitalWrite(left, HIGH); 
//     digitalWrite(right, LOW); // move servo one step
//     }
//   }else{
      
//       digitalWrite(left, LOW); 
//       digitalWrite(right, LOW);

//   }
//   Serial.println(String(ldr1Value)+" "+String(ldr2Value)+" "+error);
// }