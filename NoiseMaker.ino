/*
  NoiseMaker

  Plays wacky sounds based on various inputs

  circuit:
  - 8 ohm speaker on digital pin 8
  - Potentiometer on analog pin 0

  created 01 Dez 2019
  modified 30 Aug 2011
  by olibrian
  
  
  This example code is in the public domain.

  Thanks to Tom Igoe http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"
#include <SoftwareSerial.h>


// Potentiometer sensor
#define SENSOR A0

#define DEBUG true


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
  int vx = analogRead(SENSOR);
  vx = vx / 180;

  debug("Sensor=" + String(vx));

  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 500 / noteDurations[thisNote] * vx;
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
