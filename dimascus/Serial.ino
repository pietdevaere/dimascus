//void resetSerial(int clean){
//  serialState = STANDBY;
//  serialLight = -1;
//  serialVal = -1;
//  serialMode = -1;
//  Serial.println("Serial reset");
//  if (clean){
//    Serial.flush();
//    Serial.println("Serial flush");
//  }
//
//}
//
//int readSerialInt(){
//  char incomming;
//  int value = 0;
//  while (Serial.available() > 0 && incomming != '#'){
//    if ('0' <= incomming  && incomming <= '9'){
//      value = 10 * value + int(incomming);
//    }
//    else{
//      resetSerial(1);
//      return -1;
//    }
//  }
//  serialState = STANDBY;
//  return value;
//}
//
//
//
//void readSerial(){
//  if (Serial.available() > 0){
//    char incomming;
//    incomming = Serial.read();
//
//    if (incomming == 'R') resetSerial(1);
//    else if (serialState == STANDBY){
//      switch (incomming){
//      case 'L':
//        serialState = serialMode = READLIGHT;
//        Serial.println("INPUT Lightnr 0-6");
//        break;
//      case 'S':
//        serialState = READVAL;
//        Serial.println("INPUT value 0-255");
//        break;
//      case 'P':
//        serialState = serialMode = READPARTY;
//        Serial.println("INPUT 0 or 1");
//        break;
//      case 'A':
//        serialState = serialMode = READALL;
//        break;
//      case 'W':
//        serialState = serialMode = READWAKE;
//        Serial.println("INPUT 0 or 1");
//        break;
//      default:
//        resetSerial(1);
//        break;
//      }
//    }
//    else if (serialState == READLIGHT){
//      if ('0' <= incomming  && incomming <= '6'){
//        serialLight = int(incomming);
//        serialState = STANDBY;
//      }
//      else resetSerial(1);
//    }
//
//    else if (serialState == READVAL || serialState == READALL){
//      serialVal = readSerialInt();
//      serialState = STANDBY;
//    }
//
//    else if (serialState == READPARTY){
//      switch (incomming){
//      case '0':
//        setPartyMode(OFF);
//        break;
//      case '1':
//        setPartyMode(ON);
//        break;
//      default:
//        resetSerial(1);
//        break;
//      }
//      serialState = STANDBY;
//    }
//
//    else if (serialState == READWAKE){
//      switch (incomming){
//      case '0':
//        setWakuplight(OFF);
//        break;
//      case '1':
//        setWakuplight(ON);
//        break;
//      default:
//        resetSerial(1);
//        break;
//      }
//      serialState = STANDBY;
//    }
//
//  if (serialMode == READALL && serialVal != -1){
//    for (int light = 0; light < numOfLights; light++){
//      target[light] = serialVal;
//      resetSerial(0);
//    }
//  }
//  
//  if (serialMode == 1);
//  
//}
//}

