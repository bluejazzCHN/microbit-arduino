/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <Adafruit_Microbit.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#define DHTPIN 0     // Digital pin connected to the DHT sensor
#include "DHT.h"

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

Adafruit_Microbit_Matrix microbit;

//initialize the library of DHT
DHT dht(DHTPIN, DHTTYPE);

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 13, en = 14, d4 = 15, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int buttonA = 5;
bool buttonStatus = false;

void setup() {
  pinMode(buttonA, INPUT_PULLUP);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Initializing.....!");
  dht.begin();
  delay(2000);
}


void loop() {

  if (!digitalRead(buttonA))
  {
    buttonStatus = !buttonStatus;
  }

  if(buttonStatus == true)
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    lcdDisplay(t,h);   
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ON/OFF:press A!");
  }
  delay(500);
}

void lcdDisplay(float t,float h)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.setCursor(6,1);
  lcd.print(h);
}
