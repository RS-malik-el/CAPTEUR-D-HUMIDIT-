/**
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 * 
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 08/07/2022
 * 
 * 
 * Ce programme consiste à gerer l'arrrosage automatique.
 * *Outils : 
 * *Arduino board
 * *Capteur d'humidité
 * *Pompe à eau
 * *Deux leds
 * *Driver L298N
 * *Ecran LCD I2C
 **/
#include <LiquidCrystal_I2C.h> // Ecran LCD I2C

#define PIN_DIGIT_SOL   2
#define PIN_MOTEUR      3 // PWM pin
#define PIN_LED_ROUGE   4
#define PIN_LED_VERTE   5
#define PIN_ANALOG_SOL  A0

LiquidCrystal_I2C lcd(0x27,16,2); // Ecran LCD I2C

void setup() {
  pinMode(PIN_DIGIT_SOL,INPUT);
  pinMode(PIN_ANALOG_SOL,INPUT);
  pinMode(PIN_MOTEUR,OUTPUT);
  pinMode(PIN_LED_ROUGE,OUTPUT);
  pinMode(PIN_LED_VERTE,OUTPUT);
  //-------- Initialisation de l'écran I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  bool seuil = digitalRead(PIN_DIGIT_SOL);
  int  Hsol  = map(analogRead(A0),0,1023,100,0);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HUMIDITE = ");
  lcd.print(Hsol);
  lcd.print("%");
  lcd.setCursor(0,1);

  // ARROSAGE
  if (seuil==true){
    lcd.print("SOL SEC");
    digitalWrite(PIN_LED_ROUGE,HIGH); // Terre sec ON
    digitalWrite(PIN_LED_VERTE,LOW);  // Terre humide OFF
    analogWrite(PIN_MOTEUR,100);      // Pompe ON (~39%)
  }
  else{
    lcd.print("SOL HUMIDE");
    digitalWrite(PIN_LED_ROUGE,LOW); // Terre sec OFF
    digitalWrite(PIN_LED_VERTE,HIGH); // Terre humide ON
  }

  // ARRET ARROSAGE
  if (Hsol>=70)
  analogWrite(PIN_MOTEUR,0);

  delay(500); // Attente
}