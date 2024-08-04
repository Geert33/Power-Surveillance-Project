/***************************************************
  This is an example for our Adafruit FONA Cellular Module

  Designed specifically to work with the Adafruit FONA
  ----> http://www.adafruit.com/products/1946
  ----> http://www.adafruit.com/products/1963
  ----> http://www.adafruit.com/products/2468
  ----> http://www.adafruit.com/products/2542

  These cellular modules use TTL Serial to communicate, 2 pins are
  required to interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

/*
THIS CODE IS STILL IN PROGRESS!

Open up the serial console on the Arduino at 115200 baud to interact with FONA

Note that if you need to set a GPRS APN, username, and password scroll down to
the commented section below at the end of the setup() function.
*/

#include "Adafruit_FONA.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
// *****************************************
#include "Timers.h"

LiquidCrystal_I2C lcd(0x27,20,4); 

Timers timer;

int S1 = 10;     // Relais contakt is verbonden met Digital 10
int S2 = 11;     // Reset button
int D1 = 12;      // Led
int t1;          // the number of timer 1
int t2;          // the number of timer 2
int t3;          // the number of timer 3
int StatusS1 = LOW; // Variabele om de status van S1 in te lezen, deze is ingesteld op LOW
int StatusS2 = LOW; // Variabele om de status van S2 in te lezen, deze is ingesteld op LOW

// *******************************************

#define FONA_RST 4

// this is a large buffer for replies
char replybuffer[255];

#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial,
// we default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>

#define FONA_RX 2
#define FONA_TX 3

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
HardwareSerial *fonaSerial = &Serial1;

#endif

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
// Use this one for FONA 3G
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);

uint8_t type;

void setup() {
lcd.init(); 

//*************************************************
pinMode(S1, INPUT); 
pinMode(D1, OUTPUT);
  t1 = 0;
//**************************************************
  while (!Serial);

  Serial.begin(115200);
  Serial.println(F("FONA basic test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  type = fona.type();
  Serial.println(F("FONA is OK"));
    lcd.setCursor(0,2);
    lcd.print("Scanning Source..."); 
    lcd.setCursor(0,3);  
    lcd.print("POWER Active!       ");      
  Serial.print(F("Found "));
 
  switch (type) {
    case FONA800L:
      Serial.println(F("FONA 800L")); break;
    case FONA800H:
      Serial.println(F("FONA 800H")); break;
    case FONA808_V1:
      Serial.println(F("FONA 808 (v1)")); break;
    case FONA808_V2:
      Serial.println(F("FONA 808 (v2)")); break;
    case FONA3G_A:
      Serial.println(F("FONA 3G (American)")); break;
    case FONA3G_E:
      Serial.println(F("FONA 3G (European)")); break;
    default: 
      Serial.println(F("???")); break;
  }
  // Print module IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("Module IMEI: "); 
    Serial.println(imei);

    lcd.setCursor(0,0);
      lcd.print("ARDUINO OPEN SOURCE "); 
      lcd.setCursor(0,1);
      lcd.print("Github: Geert33     ");  

  }

  // Optionally configure a GPRS APN, username, and password.
  // You might need to do this to access your network's GPRS/data
  // network.  Contact your provider for the exact APN, username,
  // and password values.  Username and password are optional and
  // can be removed, but APN is required.
  //fona.setGPRSNetworkSettings(F("your APN"), F("your username"), F("your password"));

  // Optionally configure HTTP gets to follow redirects over SSL.
  // Default is not to follow SSL redirects, however if you uncomment
  // the following line then redirects over SSL will be followed.
  //fona.setHTTPSRedirect(true);

 }

void loop() {
lcd.backlight(); 

 //***************************************

 StatusS1 = digitalRead(S1);
  if (StatusS1 == HIGH && t1<1){
       // Unlock the SIM with a PIN code
        digitalWrite (12, LOW);
        Serial.println(F("Enter 4-digit PIN"));
        Serial.print(F("Unlocking SIM card: "));  
         # XXXX = PINCODE SIMCARD.... example: 1234
        if (! fona.unlockSIM("1234")) { 
           Serial.println(F("Failed"));
        } else {
          Serial.println(F("OK!"));
          }
        } 

        // **** SMS STROOMUITVAL ZENDEN *************************
        if (StatusS1 == HIGH && t1<3){     

           (!fona.sendSMS("003248XXXXXXX", "ALARM !!! STROOMUITVAL !!!")) ;
            # 0032XXXXXX... = Phonenumber to send...

           lcd.setCursor(0,2);
           lcd.print("ALARM! STROOMUITVAL!"); 
           t1++;
           Serial.print("Sent ");
           Serial.print("SMS: ");
           Serial.print(t1);
           lcd.setCursor(0,3);
           lcd.print("Sending SMS Nr. "); 
           lcd.print(t1); 
           lcd.print("   ");
           digitalWrite (12, HIGH);
           delay (3000);
           digitalWrite (12, LOW);
           delay (10000);
          }
                 
        //*** SMS SPANNING TERUG AANWEZIG ZENDEN *************************
        StatusS1 = digitalRead(S1);
        if (StatusS1 == LOW && t1>0){       
        t1++;
        (!fona.sendSMS("003248XXXXXXX", "SPANNING TERUG AANWEZIG!!!"));
         # 003248XXXXXXX... = Phonenumber to send...

         lcd.setCursor(0,2);
         lcd.print("SPANNING AANWEZIG!!!"); 
          Serial.print("Sent ");
          Serial.print("SMS: ");
           lcd.setCursor(0,3);
           lcd.print("Sending SMS Nr."); 
           lcd.print(t1); 
           lcd.print("   "); 
          Serial.print(t1);
         
          t1=0;
          digitalWrite (12, HIGH);
          delay (3000);
           digitalWrite (12, LOW);
            }}
       
        

        
        
        

  


  
  
  

  
   