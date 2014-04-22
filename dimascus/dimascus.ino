#define ON 1
#define OFF 0
#define STANDBY -1
#define READLIGHT 1
#define READVAL 2
#define READPARTY 3
#define READWAKE 4
#define READALL 5


/* Some constants you may change */
const int debouceTime = 30;      //Time before a keypress gets registered
const int dimDelayTime = 1000;   //Delay before we start dimming a light
const int targetTime = 500;      //0-100% time for softTogle
const int dimTime = 4000;        //0-100% time for dimming
const unsigned long wakeTime = (unsigned long) 30 * 60 * 1000;  //0-100% time for wakup light

/* Some constants you should _not_ change */
const int numOfLights = 6;                    // number of light circuits
const int numOfSpecials = 3;                  // number of buttons for special features
const int buttonPin[numOfLights] =
              {19, 18, 17, 16, 15, 14};   // the pins the lightswitches are connected to
const int pwmPin[numOfLights] =
              {3, 5, 6, 9, 10, 11};       // the pins the ledstrips are connected to
const int specialPin[numOfSpecials] =
              {4, 7, 8}; // the pins the extra switches are connected to
                            // all off, partymode, wake up

/* some variables you schould *realy* _not_ change */
int readState[numOfLights];                  // used by readLights, to time keypresses
int specialReadState[numOfSpecials];         // used by readSpecials, to time keypresses
int dimState[numOfLights];                   // used to store wether a light is stable (0), dimming up (1), or dimming down(-1)
int target[numOfLights];                     // the targetvalue for a softwrite (see writeTargets())
int value[numOfLights];                      // the value written to the light

unsigned long buttonMillis[numOfLights];    // used by readLights, to time keypresses
unsigned long specialMillis[numOfSpecials]; // used by readSpecials, to time keypresses
unsigned long partyMillis[numOfLights];     // used doParty() to time randomness
unsigned long dimMillis = 0;                // used by setDimTargets(), for timing purposes
unsigned long targetMillis = 0;             // used by writeTargets(), for timing purposes
unsigned long wakeMillis = 0;               // used by doWakeupLight(), for timing purposes

int partyTime[numOfLights];                 // used doParty() to time randomness
int partyMin = 20;                          // minimum between to toggles in partymode
int partyMax = 300;                         // maximum between to toggles in partymode

int partyMode = 0;                          // Used to keep trach of wether or not partymode is on
int wakeupLight = 0;                        // Used to keep trach of wether or not wakup light is on

/* some variables for processing serial commands */
int serialBuffer[20];
int serialVal = -1;
int serialLight = -1;
int serialState = -1;
int serialMode = -1;

void setup(){
  Serial.begin(115200);
  Serial.println("Starting setup...");
  
  for (int light = 0; light < numOfLights; light++){
    pinMode(buttonPin[light], INPUT);      // set al buttonpins inputs
    pinMode(pwmPin[light], OUTPUT);        // set al lightpins outputs
    readState[light] = 0;                  // initialise some variables to 0
    dimState[light] = 0;
    target[light] = 0;
    value[light] = 0;
    buttonMillis[light] =0;
  }
  
  for (int special = 0; special < numOfSpecials; special++){
    pinMode(specialPin[special], INPUT);  // some more of the same, but for the specials
    specialMillis[special] = 0;
    specialReadState[special] = 0;
  }

  Serial.println("Setup done, Starting main loop");
}

void loop(){
//  readSerial();
  readLights();      // read the lightswitches
  readSpecials();    // read the special switches
  doWakeupLight();   // let wakeuplight set it's targets
  setDimTargets();   // let the dimmer set it's targets
  writeTargets();    // set the value's according to the targets
  doParty();         // if we wan't to party, flickr some lights
  
  
}
