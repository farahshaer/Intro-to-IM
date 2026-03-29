void setup() {
pinMode(13, OUTPUT); //sets pin 13 as an output for the LED
pinMode(2, INPUT); //sets pin 2 as an input for the switch
}

void loop() {
int buttonState =digitalRead(2); //to read the state of the switch, high if pressed low if not

if (buttonState == HIGH) { //if the switch is pressed
digitalWrite (13,HIGH); //the LED turns on
delay(100); //cause a delay so I can produce a fast blinking effect
digitalWrite (13,LOW); //to turn the LED off for the blink effect
delay(100); //the fast delay to complete the blink full cycle
}
else {
  digitalWrite(13,LOW); //if the switch is not pressed keep the LED off
}
}
