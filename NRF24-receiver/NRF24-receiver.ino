#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

RF24 radio(7,8);
Servo ESC;
Servo ailerons;
Servo rudder;
Servo elevator;


const int buzzer = 2;
const byte address[6] = "00001";
int ail_L = 0;
int ail_R = 0;

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int flight_dat[] = {0,0,0,0};

void setup() {
  // put your setup code here, to run once:
  ailerons.attach(9);
  rudder.attach(3);
  ESC.attach(6);
  elevator.attach(5);
  
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  Serial.begin(9600);
  radio.startListening();
}

void loop() {
  
  
  if (radio.available()) {
    radio.read(&flight_dat, sizeof(flight_dat));
    int transData[] = {flight_dat[0], flight_dat[1], flight_dat[2], flight_dat[3]};

    
    //Serial.println(transData[0]);
    //Serial.print("\n");
    //Serial.print("Ailerons: ");
    ailerons.write(transData[0]);
    
    Serial.println(transData[1]);
    //Serial.print("\n");
    //Serial.print("Throttle: ");
    ESC.write(transData[1]);
    
    Serial.println(transData[2]);
    Serial.print("\n");
    Serial.print("Rudder: ");
    rudder.write(transData[2]);
    
    Serial.println(transData[3]);
    Serial.print("\n");
    Serial.print("Elevator: ");
    elevator.write(transData[3]);
    
    
    if (radio.available()) {
        digitalWrite(buzzer, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
      else{
        digitalWrite(buzzer, LOW);
        }
  }
}
