#include <SoftwareSerial.h>
#define rxPin 11
#define txPin 10
#define baudrate 9600
SoftwareSerial mySerial(rxPin,txPin);

void setup() {
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);

  mySerial.begin(9600);
  Serial.begin(baudrate);
  Serial.println("demarrage");
}

void loop() {
  int i=2;
  double voltage;
  double resistance;
  voltage=analogRead(A0);
  //Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts");
  resistance=(1+100000/1000)*100000*(1023/voltage)-100000-10000;
  resistance=resistance/1000000;
  
  
  mySerial.print(resistance);
  Serial.println(resistance);
  delay(500);
  
  

}
