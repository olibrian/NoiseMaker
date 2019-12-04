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
int keypadlayout[] = {
  NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, 
  NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4 
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
  pitch = pitch / 180;

//  debug("Sensor=" + String(pitch));
  
  char key = kpd.getKey();
  if (key != 0){
    debug("Key=" + String(keypadlayout[key-48] + pitch));
    tone(SPEAKER, keypadlayout[key-48]+1, 500 / 4 * pitch);
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
