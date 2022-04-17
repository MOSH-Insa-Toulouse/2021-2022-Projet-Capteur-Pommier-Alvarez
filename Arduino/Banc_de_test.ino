//////////Définition des bibliotheques//////////

#include<SPI.h>
#include <Servo.h>

///// Definition des variables/////

const byte csPin=10;
const int maxPositions=256;
const long rAB=50000;
const byte rWiper=125;
const byte pot0=0x11;
const byte post0Shutdown=0x21;
double voltage;
double resistance;


Servo myservo;
int posmoteur=0;


/////// Definir les fonctions///////

void setPotWiper(int addr,int pos){
  pos=constrain(pos,0,255);
  digitalWrite(csPin, LOW);
  SPI.transfer(addr);
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);

  long resistanceWB=((rAB * pos)/ maxPositions)+rWiper; /*permet de tenir en compte la resistance d'entrée*/ 
  Serial.print("Wiper position: ");
  Serial.println(pos);
  Serial.print("Resistance wiper to B terminal:");
  Serial.print(resistanceWB);
  Serial.println("ohms");

  for(posmoteur=0;posmoteur<115;posmoteur+=1){
    myservo.write(posmoteur);
    voltage=analogRead(A0);
    Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts"); /* cette ligne sert à voir les volts qu'on obtient en même temps que le servo-moteur bouge*/
    resistance=(1+100000/resistanceWB)*100000*(1023/voltage)-100000-10000; /* calcul la resistance avec la formule vu en LTSPICE*/ 
    Serial.println("resistance associee "+String(resistance)+" Ohms"); /* affiche la resistance trouvee*/
  
    float angle=map(resistance, 0, 100000000, 0,90.0); /* permet d'avoir l'angle qui correspond à la résistance associée*/
    Serial.println("Bend:" +String(angle) + "degrees"); /* affiche l'angle*/ 
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

///////Programme principal////////

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
