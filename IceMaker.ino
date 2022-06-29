/*
  Ice Maker
*/
#include "src/LiquidCrystal_PCF8574.h"

LiquidCrystal_PCF8574 lcd(0x27);

// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

const int TH1 = 2;    //Thermostat
const int S1  = A1;   //NTC sensor
const int S2  = 3;    //Pressure sensor  

const int Y1  = 4;  //Valve1
const int Y2  = 5;  //Valve2
const int Y3  = 6;  //Motor1
const int Y4  = 7;  //Motor2
const int Y5  = 8;  //Motor3
  
const int UP_PB = 9;  //Up pushbutton
const int DN_PB = 10; //Down pushbutton


// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
long interval = 1000;           // interval at which to blink (milliseconds)
int SetTemperature;
int NTCTemperature;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  
  pinMode(TH1, INPUT_PULLUP);
  pinMode(S1, INPUT);        
  pinMode(S2, INPUT_PULLUP);
  
  pinMode(Y1, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(Y4, OUTPUT);
  pinMode(Y5, OUTPUT);
  
  pinMode(UP_PB, INPUT_PULLUP);
  pinMode(DN_PB, INPUT_PULLUP);
  
  SetTemperature = -35; 
  NTCTemperature = 0;

  lcd.begin(20,4);
  lcd.setBacklight(255);
  
  lcd.setCursor(0,0);
  //          "0123456789012345"
  lcd.print(F("   ICE Maker    "));
  lcd.setCursor(0,1);
  lcd.print(F("                "));
}

int NTC_Table[101] = {
  218,233,250,267,285,
  304,324,345,367,390,
  414,440,466,493,522,
  552,583,615,649,683,
  719,755,793,832,872,
  914,956,999,1043,1088,
  1134,1180,1228,1276,1324,
  1374,1423,1473,1524,1575,
  1626,1677,1728,1780,1831,
  1882,1933,1984,2034,2085,
  2134,2184,2232,2280,2328,
  2375,2421,2467,2511,2555,
  2599,2641,2683,2723,2763,
  2802,2840,2877,2914,2949,
  2983,3017,3050,3082,3113,
  3143,3172,3200,3228,3255,
  3281,3306,3331,3354,3377,
  3400,3421,3442,3463,3482,
  3501,3520,3537,3555,3571,
  3587,3603,3618,3633,3647,
  3661}
  ;

int GetTemperatur()
{
  int Temp = NTC_Table[NTCTemperature/5];
  if (Temp>analogRead(S1)&&NTCTemperature>0) {
    NTCTemperature--;
  } 
  else if (Temp<analogRead(S1)&&NTCTemperature<500) {
    NTCTemperature++;
  }
  return (NTCTemperature+2)/5;
}

void loop() {
  unsigned long currentMillis = millis();
 if ((GetTemperatur()<SetTemperature)&&(ledState == LOW)) {
    ledState = HIGH;
    previousMillis = currentMillis;
  }
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
 if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    ledState = LOW;
  }
  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
  if (ledState==HIGH) {
    digitalWrite(Y1, HIGH);
    digitalWrite(Y2, HIGH);
    digitalWrite(Y3, LOW);
    digitalWrite(Y4, LOW);
    digitalWrite(Y5, LOW);
  } else {
    digitalWrite(Y1, LOW);
    digitalWrite(Y2, LOW);
    digitalWrite(Y3, HIGH);
    digitalWrite(Y4, HIGH);
    digitalWrite(Y5, HIGH);
  }
}
