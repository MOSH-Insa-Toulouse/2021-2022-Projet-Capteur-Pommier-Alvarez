#include<SPI.h>
const byte csPin=10;
const int maxPositions=256;
const long rAB=50000;
const byte rWiper=125;
const byte pot0=0x11;
const byte post0Shutdown=0x21;
double voltage;
double resistance;

#include <Servo.h>
Servo myservo;
int posmoteur=0;



void setPotWiper(int addr,int pos){
  pos=constrain(pos,0,255);
  digitalWrite(csPin, LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);

  long resistanceWB=((rAB * pos)/ maxPositions)+rWiper;
  Serial.print("Wiper position: ");
  Serial.println(pos);
  Serial.print("Resistance wiper to B terminal:");
  Serial.print(resistanceWB);
  Serial.println("ohms");

  for(posmoteur=0;posmoteur<115;posmoteur+=1){
    myservo.write(posmoteur);
    voltage=analogRead(A0);
    Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts");
    resistance=(1+100000/resistanceWB)*100000*(1023/voltage)-100000-10000;
    Serial.println("resistance associee "+String(resistance)+" Ohms");
  
    float angle=map(resistance, 0, 100000000, 0,90.0);
    Serial.println("Bend:" +String(angle) + "degrees");
    Serial.println();
    delay(100);
  }
//  for(posmoteur=95;posmoteur>=0;posmoteur-=1){
//    myservo.write(posmoteur);
//    voltage=analogRead(A0);
//    Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts");
//    resistance=(1+100000/resistanceWB)*100000*(1023/voltage)-100000-10000;
//    Serial.println("resistance associee "+String(resistance)+" Ohms");
//    delay(50);
//  }

}

void setup() {
  Serial.begin(9600);
  Serial.println("MCP41100 Demo");

  digitalWrite(csPin, HIGH);
  pinMode(csPin, OUTPUT);
  SPI.begin();

  myservo.attach(9);


  
}

void loop() {

  
  Serial.println("Pot 0 control");
  setPotWiper(pot0,5);
  delay(1000);
  
}
