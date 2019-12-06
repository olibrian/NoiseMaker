/*
  NoiseMaker

  Plays wacky sounds based on various inputs

  circuit:
  - 8 ohm speaker on digital pin 8
  - Potentiometer on analog pin 0
  - Keypad pin 2,3,4,5,6,8,9,10

  created 01 Dez 2019
  modified 30 Aug 2011
  by olibrian
  
  
  This example code is in the public domain.

  Thanks to Tom Igoe http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
#include <SoftwareSerial.h>


// Include Keypad Library
#include <Key.h>
#include <Keypad.h>

#define XSTR(s) STR(s)
#define STR(s) #s

// Potentiometer sensor
#define SENSOR A0

// Speaker on digital pin and ground
#define SPEAKER 10

#define DEBUG true

// ** Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', ':', ';', '<'},
  {'?', '@', 'A', 'B'}
};

// Connect keypad R1, R2, R3 and R4 to these Arduino pins.
byte rowPins[ROWS] = { 5, 4, 3, 2 };
// Connect keypad C1, C2, C3 and C4 to these Arduino pins.
byte colPins[COLS] = { 6, 7, 8, 9 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// ** End keypad

// Keypad layout:
int keypadlayout[7][9] = {
  {NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1, NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1},
  {NOTE_C2, NOTE_CS2, NOTE_D2, NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2, NOTE_GS2},
  {NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3},
  {NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4},
  {NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5},
  {NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6},
  {NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7}
};


// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    Serial.begin(19200);
    debug("Start NoiseMaker");
}

void loop() {
  // get sensor for speed
  int pitch = analogRead(SENSOR);
  pitch = (pitch+1) * 6 / 900;

  char key = kpd.getKey();
  if (key != 0){
    debug("Key=" + String(keypadlayout[pitch][key-48]));
    debug("Pitch=" + String(pitch));
    tone(SPEAKER, keypadlayout[pitch][key-48], 500 / 4);
    
  }
  // iterate over the notes of the melody:
/**  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / noteDurations[thisNote] * pitch;
    tone(SPEAKER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);

    
  }
**/
  delay(10);
}



//-------------------------------------------------Debug Functions------------------------------------------------------

void debug(String Msg)
{
  if (DEBUG)
  {
    Serial.println(Msg);
  }
}
