//////////Définition des bibliotheques//////////
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

///////// Definition des pins///////
/***encodeur***/
#define encoder0pinA 3 // CLK
#define encoder0pinB 4 // DATA
#define Switch 5 // switch


/***oled***/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*** Bluetooth***/ 
#define rxpin 11
#define txpin 10
#define baudrate 9600
SoftwareSerial mySerial(rxpin,txpin);
#define Periode 50 
#define analog_port 0

///// Definition des variables/////
/**Bluetooth***/
unsigned long temps_ref;

/***oled et debouncing***/
const int ledPin=13;
int ledState=HIGH;
int buttonState;
int lastButtonState=HIGH;
int compteur_filtre;
int compteur_non_filtre;

long lastDebounceTime=0;
long debounceDelay=50;

Adafruit_SSD1306 ecranOLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

byte dir = 0;

int compteurSwitch=0;

/***encoder***/
volatile unsigned int encoder0pos=0;
int Switchstate=0;


//////// Programme principal////////


void setup() {

//Bluetooth
  pinMode (rxpin, INPUT);
  pinMode (txpin, OUTPUT);
  temps_ref=millis();
  mySerial.begin(baudrate);
  Serial.begin(baudrate);

  
// OLED
  ecranOLED.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  pinMode (encoder0pinA,INPUT);
  digitalWrite(encoder0pinA,HIGH);
  pinMode (encoder0pinB,INPUT);
  digitalWrite(encoder0pinB,HIGH);
  pinMode(Switch, INPUT);
  
  attachInterrupt(0,doEncoder,RISING);

  

  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    while(1);
  }
  
  ecranOLED.setTextColor(SSD1306_WHITE);
  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(1);

//affichage OLED
  ecranOLED.setCursor(0,0);
  ecranOLED.print("Projet Capteur");
  ecranOLED.print(" Pommier et Alvarez");
  ecranOLED.display();
  delay(2000);
  ecranOLED.clearDisplay();
  
//Debouncing
  Serial.begin(9600);
  pinMode(Switch,INPUT);
  pinMode(ledPin,OUTPUT);
 }

void loop() {
  
  ecranOLED.clearDisplay();
  Serial.print("Position:");
  Serial.println(encoder0pos, DEC);

  double voltage;
  double resistance;
  voltage=analogRead(A0); // recupere la valeur en sortie 
  resistance=(1+100000/1000)*100000*(1023/voltage)-100000-10000; // calcul de la resistance à partir de la tension (voir LTSPICE)
  
//Bluetooth
  if (abs(millis()-temps_ref) > Periode)
  {
//    byte V = map(voltage,0,1023,0,255);
//    mySerial.write(V);
      mySerial.print(resistance);
      Serial.println(resistance);
      
  }
  temps_ref=millis();
  Serial.println("la valeur de ADC "+ String(voltage*5/1023)+ " Volts");
  delay(500);
  
  // etat bouton encodeur
  Switchstate=digitalRead(Switch);

    if(compteur_filtre == 0){
      ecranOLED.setCursor(0,0);
      ecranOLED.print("Projet Capteur");
      ecranOLED.setCursor(0,15 );
      ecranOLED.print("Appuyez sur encodeur");
      ecranOLED.setCursor(0,25 );
      ecranOLED.print("pour changer de menu");
      ecranOLED.display();
      
    }

   
    if(compteur_filtre == 1){
      ecranOLED.setCursor(0,0);
      ecranOLED.clearDisplay();
      ecranOLED.print("Page resistance");
      ecranOLED.setCursor(10,15);
      ecranOLED.println(resistance);
      ecranOLED.setCursor(10,25);
      ecranOLED.print("ohms");
      ecranOLED.display();
      

    }

     if(compteur_filtre == 2){
      ecranOLED.setCursor(10,0);
      ecranOLED.clearDisplay();
      ecranOLED.print("Voici un capteur");
      ecranOLED.setCursor(10,7);
      ecranOLED.print(" a base de graphite");
      ecranOLED.setCursor(10,17);
      ecranOLED.print(" dont le mesurande");
      ecranOLED.setCursor(10,25);
      ecranOLED.print("est une resistance");
      ecranOLED.display();
      

    }

     if(compteur_filtre == 3){
      compteur_filtre=0;

    }
    
// Debouncing

    int reading=digitalRead(Switch);
    if(reading!=lastButtonState){
      lastDebounceTime=millis();
      if(reading==0){
        compteur_filtre=compteur_filtre+1;
      }
      buttonState=reading;
    }
    digitalWrite(ledPin,buttonState);
    lastButtonState=reading;
    Serial.print("Compteurs:");
    Serial.print(compteur_non_filtre);
    Serial.print(",");
    Serial.println(compteur_filtre);
}


/////// Definir les fonctions///////

void doEncoder() {
  if (digitalRead(encoder0pinA) == HIGH) {
    if (digitalRead(encoder0pinB) == LOW && encoder0pos > 0) {
      encoder0pos = encoder0pos - 1;
      dir = 0;
    }
    else {
      encoder0pos = encoder0pos + 1;
      dir = 1;
    }
  }
  else
  {
    if (digitalRead(encoder0pinB) == LOW ) {
      encoder0pos = encoder0pos + 1;
      dir = 1;
    }
    else {
      if (encoder0pos > 0) {
        encoder0pos = encoder0pos - 1;
        dir = 0;
      }
    }
  }
}
