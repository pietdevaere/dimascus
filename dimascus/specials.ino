/* Special mapping:
 --> 0: all off button
 --> 1: partymode
 --> 2: wakeup light
 */

void doParty(){
  if (partyMode){ // if we are in partymode
    for (int light; light < numOfLights; light++){ // do some random flickering of the lights
      if ( millis() - partyMillis[light] > partyTime[light]){
        partyMillis[light] = millis();
        partyTime[light] = random(partyMin, partyMax);
        hardToggleLight(light);
      }
    }
  }
}

void doWakeupLight(){ 
  if (wakeupLight){ // if the wakeuplight is on
    int done = 1; // used to see if we are done
    if((millis() - wakeMillis) > wakeTime / 255){ //if the timedelay for the steps has passed
      wakeMillis = millis();   // reset the timer
      for (int light = 0; light < numOfLights; light++){ 
        if (target[light] < 255){ // and for lights that aren't 100% on yet
          target[light]++; // bump it up one step
          done = 0; // we had to do something, so not done
        }
      }
      Serial.println("wakeupLight++");
      if (done == 1){ // if we are done
        wakeupLight = 0; // turn off the wakeuplight
        Serial.println("wakeupLight DONE");
      }
    }
  }
}

void doSpecial(int special){ // activate the specials
  switch (special){
    
  case 0:  // special 0: all off
    for (int light = 0; light < numOfLights; light++){
      target[light] = 0; // set the targets for all lights to 0
    }
    Serial.println("ALL OFF");
    break;

  case 1: // special 1: partymode
    partyMode = !partyMode; // toggle the partymode 
    if (partyMode) Serial.println("partymode ON");
    else Serial.println("Partymode OFF");
    break;

  case 2:  // special 2: wakeup light
    wakeupLight = !wakeupLight; // toggle the wakeuplight
    if (wakeupLight) Serial.println("wakeupLight ON");
    else Serial.println("wakeupLight OFF");
    break;
  }
}

void setWakuplight(int state){ // used to specifie a state for the wakeup light
  if (wakeupLight != state){
     wakeupLight = state;
     if (wakeupLight) Serial.println("wakeupLight ON");
      else Serial.println("wakeupLight OFF");
  }
}

void setPartyMode(int state){ // used to specifie a state for the wakeup light
  if (partyMode != state){
     partyMode = state;
     if (partyMode) Serial.println("partyMode ON");
      else Serial.println("partyMode OFF");
  }
}
