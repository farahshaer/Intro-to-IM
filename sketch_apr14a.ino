#include "pitches.h"

//pins variables
int buzzer = 8;
int button = A1;
int potentiometer = A0;
int led = 9;

//the modes
int mode = 0;                //keeps track of which melody is playing 0 or 1
int lastButtonState = HIGH;  //stores the previous button state so i can detect a new press
int thisNote = 0;            //keeps track of the current note idex in the melody

//melody 1: jennifers body by ken carson
int melody1[] = {  //stores notes
  NOTE_C4, NOTE_F4, NOTE_DS4, NOTE_GS4,
  NOTE_G4, NOTE_C4, NOTE_CS4, NOTE_C4,
  NOTE_C4, NOTE_F4, NOTE_DS4, NOTE_GS4,
  NOTE_G4, NOTE_G4, NOTE_C4
};

int noteDurations1[] = {  //controls how long each note is played (the duration)
  2, 4, 4, 3,
  2, 6, 4, 3,
  2, 4, 4, 3,
  2, 4, 2
};

//melody 2: die with a smile by bruno mars
int melody2[] = {  //stores notes
  NOTE_FS4, NOTE_FS4, NOTE_A4,
  NOTE_FS4, NOTE_A4,
  NOTE_FS4, NOTE_GS4, NOTE_GS4, NOTE_A4, NOTE_B4,
  NOTE_E4, NOTE_GS4,
  NOTE_CS5, NOTE_GS4, NOTE_FS4,
  NOTE_FS4, NOTE_FS4, NOTE_A4,
  NOTE_FS4, NOTE_E4, NOTE_GS4,
  NOTE_CS5, NOTE_GS4, NOTE_FS4
};

int noteDurations2[] = {  //stores duration for the melody
  4, 4, 3,
  4, 3,
  4, 3, 8, 4, 3,
  4, 1,
  4, 4, 1,
  4, 4, 3,
  4, 3, 3,
  4, 4, 1
};

void setup() {
  pinMode(buzzer, OUTPUT);        //sets buzzer pin as output so it can play sound
  pinMode(led, OUTPUT);           //sets led pin as output so i can turn it on and off
  pinMode(button, INPUT_PULLUP);  //button uses the internal pull up resistor so the default is high and when pressed its low
}

void loop() {

  //button input
  int buttonState = digitalRead(button);  //reads whether button is pressed or not. high if not pressed and low if pressed

  if (buttonState == LOW && lastButtonState == HIGH) {  //detects a new button press from high to low
    mode++;                                             //switch to the next mode/melody
    if (mode > 1) mode = 0;                             //if the mode goes past 1, reset back to 0
    thisNote = 0;                                       //restart song from beginning
    delay(50);                                          //small delay to prevent the button bouncing/accident double clicks
  }

  lastButtonState = buttonState;  //saves the current button state for next loop

  //potentiometer for pitch control
  int sensorValue = analogRead(potentiometer);       //reads the knob position from 0 to 1023
  int pitch = map(sensorValue, 0, 1023, -200, 200);  //converts it into a freq range and this controls how high or low the sound is

  //mode 0 (melody 1)
  if (mode == 0) {

    int size1 = 15;                                      //number of notes in melody 1
    int noteDuration = 1000 / noteDurations1[thisNote];  //converts note type into time in milliseconds
    int finalPitch = melody1[thisNote] + pitch;          //combines the meoldy note and the knob turning (can adjust the note using the potentiometer)
    tone(buzzer, finalPitch, noteDuration);              //plays sound on buzzer
    digitalWrite(led, HIGH);                             //turns led on while the note is playing
    delay(noteDuration);                                 //waits for note to finish
    digitalWrite(led, LOW);                              //turns the led off between the notes and for blinking effect
    delay(noteDuration * 0.3);                           //short pause between the notes to make the melody clearer
    noTone(buzzer);                                      //stops sound before next note
    thisNote++;                                          //moves to next note in the melody
    if (thisNote >= size1) thisNote = 0;                 //if at the end of the melody go back to the start (loop song)
  }


  if (mode == 1) {
    int size2 = 23;                                      //number of notes in melody 2
    int noteDuration = 1000 / noteDurations2[thisNote];  //converts note into time (mill sec)
    int finalPitch = melody2[thisNote] + pitch;          //applys the pitch shift from the potentmeter
    tone(buzzer, finalPitch, noteDuration);              //plays sound
    digitalWrite(led, HIGH);                             //turns led on during the sound
    delay(noteDuration);                                 //wait for note
    digitalWrite(led, LOW);                              //led off
    delay(noteDuration * 0.3);                           //pause between notes
    noTone(buzzer);                                      //stops sound

    thisNote++;                           //go to the next note when done
    if (thisNote >= size2) thisNote = 0;  //loop back to start when song ends
  }
}