/////////Définition des bibliotheques//////////
#include <SoftwareSerial.h>

///////// Definition des pins///////

#define rxPin 11
#define txPin 10
#define baudrate 9600
SoftwareSerial mySerial(rxPin,txPin);

//////// Programme principal////////

void setup() {
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);

  mySerial.begin(9600);
  Serial.begin(baudrate);
  Serial.println("demarrage"); /* cette ligne permet de savoir quand les mesures commencent, pratiques pour le banc de test*/ 
}

void loop() {
  int i=2;
  double voltage;
  double resistance;
  voltage=analogRead(A0); /* permet de réccupérer la tension*/ 
  //Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts"); /* permet de convertir ce qu'on reccupère en volt*/ 
  resistance=(1+100000/1000)*100000*(1023/voltage)-100000-10000; /* calcul de la resistance a partir de la tension */ 
  resistance=resistance/1000000;
  
  
  mySerial.print(resistance);
  Serial.println(resistance);
  delay(500);
  
  

}
