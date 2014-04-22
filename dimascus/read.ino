void readLights(){   // used to read the lightswitches
  
  for( int light = 0; light < numOfLights; light++){ // for all switches
    int pinValue;            // used to store the value of the pin we are reading
    unsigned long deltaTime; // used to store the time the button has been pressed
        
    deltaTime = millis() - buttonMillis[light];
    pinValue = digitalRead(buttonPin[light]);
    
    if (readState[light]){ // if the input pin was high the previous time
      if(!pinValue){       // but isn't now
        if(deltaTime > dimDelayTime){ // see if has been on long enough for the dimming
          dimLight(light, OFF);           // if so, turn dimming off
          setWakuplight(OFF);             // and turn off the wakeuplicht (if nescecary)
          readState[light] = 0;           // the pin was low this time
        }
        
        else if (deltaTime > debouceTime){ // if it wasn't on long enoug for dimming, but longer then the debounceTime
          toggleLight(light);   // togle the light
          setWakuplight(OFF);   // and turn off the wakeuplicht (if nescecary)
          readState[light] = 0; // the pin was low this time
        }
      }
      
     if(pinValue){ // if it was on the previous time and this time
      if (deltaTime > dimDelayTime){ // see if it is on long enoug to start the dimming
        dimLight(light, ON); // if so, start thte dimming
      }
     }
    }
    
    if(!readState[light] && pinValue){  //it it was low, but is high
      readState[light] = 1;  // set the readState for the next time
      buttonMillis[light] = millis(); // start the timer
    }
  }
}

void readSpecials(){  // used to read the extra buttons
  for (int special = 0; special < numOfSpecials; special++){ // for all special buttons
    int pinValue;  // used to store the value of the pin we are reading
    unsigned long deltaTime; // used to store the time the button has been pressed
    
    deltaTime = millis() - specialMillis[special];
    pinValue = digitalRead(specialPin[special]);
   
    if (specialReadState[special]){ // if the input pin was high the previous time
      if(!pinValue){  // but isn't now
        if(deltaTime > debouceTime){ // and has been on for longer then the debounceTime
          doSpecial(special); // do the corresponding special
          specialReadState[special] = 0; // the pin was low this time
        }
      }
    }
      if(!specialReadState[special]  && pinValue){ //it it was low, but is high
        specialReadState[special] = 1;  // set the readState for the next time
        specialMillis[special] = millis();  // start the timer
      }
  }
    
}
