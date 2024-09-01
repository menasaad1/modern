
bool statefields[3];
void controlpumbs() {

bool statefields[3];
//if any field to open by timer or by phone startup the pump
  for (int i = 0; i < 3; i++) {
    statefields[i] = digitalRead((fieldspins[i]));
  }
  if (statefields[0] || statefields[1] || statefields[2]) {
    digitalWrite(waterpump, HIGH);

  } else {
    digitalWrite(waterpump, LOW);
  }
  if (Smart) {
    if (tanklevel_now < settanklevel) {

      digitalWrite(submersiblepumppin, HIGH);

    } else {
      digitalWrite(submersiblepumppin, LOW);
    }
    // use timer
    if (timermode) {

      yearlyTimer1.Control(field1,now);
      yearlyTimer2.Control(field2,now);
      yearlyTimer3.Control(field3,now);

    }

    //use humditiy sensor
    else {
      for (int i = 0; i < 3; i++) {

        if (humdidtyfields_now[i]<sethumdidtyfields[i] ) {
          digitalWrite(fieldspins[i] , HIGH);
        } else {
          digitalWrite(fieldspins[i], LOW);
        }
      }
    }
  }


  // if(temperature_now>settemp){
  //  digitalWrite(submersiblepumppin, HIGH);
  //   digitalWrite(relaypin[7], HIGH);

  // }else{
  //     digitalWrite(relaypin[6], LOW);
  //   digitalWrite(relaypin[7], LOW);

  // }
}