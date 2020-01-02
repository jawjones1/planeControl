
#include <Servo.h>

Servo ESC;

Servo aileron_L;
Servo aileron_R;

int ail_L = 0;
int ail_R = 0;
// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output


int armed = 1;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
  ESC.attach(9, 1000, 2000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // initialise ailerons

  aileron_L.attach(10);
  aileron_R.attach(11);

}

void loop() {

  if (digitalRead(SW_pin) == 0){
    Serial.println("PRESSED");
    if (armed == 0 ){
      armed = 1;
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
      } else if (armed == 1 ) {
        delay(100);
        armed = 0;
        digitalWrite(LED_BUILTIN, HIGH);
        delay(50);
        }
      
  
  } else  {
    //digitalWrite(LED_BUILTIN, LOW);
  
    }
  int throttle =analogRead(A0);

  // motor should run when armed == 0
  if (armed == 0 ) {
    //thrust controll  - need to make summation/latch. 
   // ----------------------------
    Serial.println("armed\n");
    throttle = map(throttle, 504, 1023, 0, 180);
    ESC.write(throttle);
    Serial.println(throttle);
  //  -----------------------------

  //aileron/roll control
    ail_L = map(analogRead(A2), 504, 1023, -90, 90);
    ail_R = -map(analogRead(A2), 504, 1023, -90, 90);
    aileron_L.write(ail_L);
    aileron_R.write(ail_R);
  
    }
    // motor will not run when armed == 1
    else if (armed == 1) {
      Serial.println("NOT armed\n");
      ESC.write(0);
      }
  
  //throttle = map(throttle, 504, 1023, 0, 180);
  //ESC.write(throttle);
  //Serial.println(throttle);
  //Serial.print("Switch:  ");
 // Serial.print(digitalRead(SW_pin));
 // Serial.print("\n");
//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.println("Armed?: ");
//Serial.println(armed);
  //Serial.println("\n");
 // Serial.print("\n\n");
}
