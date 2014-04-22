void dimLight(int light, int state){ // turn dimming on or off
  if (state && !dimState[light]){ // turn on if asked and nescecary
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" dimming ON");
    dimState[light] = 1;
  }
  
  if(!state){  // turn of if asked
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" dimming OFF");
    dimState[light] = 0;
  }
}

void toggleLight(int light){ // soft toggle a light
  if(target[light]){ // if it is on (on any power)
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" toggle OFF");
    target[light] = 0; // turn it of
  }
  
  else{ // else, set it to 100%
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" toggle ON");
    target[light] = 255;
  }
}

void hardToggleLight(int light){ // used to imediatly toggle a light
  if(target[light]){ // turn it on
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" toggle HARD OFF");
    target[light] = 0;
    value[light] = -1; // different value, otherwise writeTargets wouldn't do anyting
  }
  
  else{ // or off
    Serial.print("Light ");
    Serial.print(light);
    Serial.println(" toggle HARD ON");
    target[light]= 255;
    value[light] = 256; // different value, otherwise writeTargets wouldn't do anyting
  }
}

void setDimTargets(){ // used for dimming
  if ((millis() - dimMillis) > (dimTime / 255)){
    dimMillis = millis();
    for (int light = 0; light < numOfLights; light++){
      if (dimState[light]){
        target[light] += dimState[light];
        if (target[light] >= 254){
          dimState[light] = -1;
        }
        if (target[light] <=0){
          dimState[light] = 1;
        }
      }
    }
  }
}

void writeTargets(){
  if ( ( millis() - targetMillis) > (targetTime / 255 ) ){
    targetMillis = millis();
    for (int light = 0; light < numOfLights; light++){
      if (target[light] != value[light]){
        if (target[light] > value[light]) value[light]++;
        if (target[light] < value[light]) value[light]--;
        analogWrite(pwmPin[light], value[light]);
      }
    }
  }
}
