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

#define DEBUG true

// ** Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'a'},
  {'4', '5', '6', 'b'},
  {'7', '8', '9', 'c'},
  {'d', 'p', 'u', 'd'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 6, 4, 2 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 10, 8, 5, 3 };

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// ** End keypad


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

  debug("Sensor=" + String(pitch));

  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / noteDurations[thisNote] * pitch;
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);

    
  }
  delay(400);
}


//-------------------------------------------------Debug Functions------------------------------------------------------

void debug(String Msg)
{
  if (DEBUG)
  {
    Serial.println(Msg);
  }
}
