#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);


const byte address[6] = "00001";
int ail = 0;
int throttle = 0;
int rudder = 0;
int elevator = 0;



void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  for(int i =0;i < sizeof(address); i++){
  }
  
  
   
  int thro = map(analogRead(A2), 0, 1023, -180, 180);
  if(throttle <= 180 && throttle >= 0){
    throttle += thro/50;
    throttle = constrain(round(throttle), 0, 180);
    }

  
  
  ail = map(analogRead(A1), 0, 1023, 0, 180);
  rudder = map(analogRead(A3), 0, 1023, 0, 180);
  elevator = map(analogRead(A4), 0, 1023, 0, 180);

  
    //Serial.print("\n");
    //Serial.print("Ailerons: ");
    //Serial.println(ail);
    
    
    //Serial.print("\n");
    //Serial.print("Throttle: ");
    //Serial.println(throttle);

    //Serial.print("\n");
    //Serial.print("Rudder: ");
    //Serial.println(rudder);
    
   
    //Serial.print("\n");
    //Serial.print("Elevator: ");
    //Serial.println(elevator);

   //delay(200);
  
  int flight_data[] = {ail, throttle, rudder, elevator};
  const char text[] = "nrftest";
  //Serial.println(flight_data[0]);
  //Serial.println(flight_data[1]);
  //Serial.println(flight_data[2]);
  //Serial.println(flight_data[3]);
  radio.write(&flight_data, sizeof(flight_data));
}
