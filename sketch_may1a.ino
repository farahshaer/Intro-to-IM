//buttons (inputs)
const int redButtonPin = 2;
const int yellowButtonPin = 3;
const int blueButtonPin = 4;
const int greenButtonPin = 5;

//LED (output) (shows game state visually)
const int signalLedPin = 6;

//variables
int gameLevel = 0; //value coming from p5 (game state)
int buttonPressed = 0;//value sent to p5 (which button pressed)


void setup() {
  Serial.begin(9600);

  // inputs
  pinMode(redButtonPin, INPUT_PULLUP);//used inputpullup so buttons read high when not pressed and for no resistors
  pinMode(yellowButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);

  // output
  pinMode(signalLedPin, OUTPUT);//LED that reacts to game state
  pinMode(LED_BUILTIN, OUTPUT);//for debugging

  //blink test to check wiring
  digitalWrite(signalLedPin, HIGH);
  delay(150);
  digitalWrite(signalLedPin, LOW);


  //HANDSHAKE
  while (Serial.available() <= 0) {
    digitalWrite(LED_BUILTIN, HIGH); //blink while wating for serial data
    Serial.println("0"); //send default message to p5
    delay(300);//wait 1/3 second
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
}

void loop() {
//READ FROM P5
  while (Serial.available()) {//check if p5 is sending data
    digitalWrite(LED_BUILTIN, HIGH);//led on while recieving data
    gameLevel = Serial.parseInt(); //read game state number from p5 (used parseint to skp anything that isnt digits)
    Serial.read(); // clears '\n' after parseint
  }
  digitalWrite(LED_BUILTIN, LOW);

//LED behavior based on game state
if (gameLevel == 1) { //the playing state, faster flicker
  digitalWrite(signalLedPin, HIGH);
  delay(50);
  digitalWrite(signalLedPin, LOW);
  delay(50);
}
else if (gameLevel == 2) {//reveal state, slow flicker for a calmer feel
  digitalWrite(signalLedPin, HIGH);
  delay(200);
  digitalWrite(signalLedPin, LOW);
  delay(200);
}
else if (gameLevel == 3) {//end state, light stays fully on
  digitalWrite(signalLedPin, HIGH);
}
else { //for the start and instruction, led off
  digitalWrite(signalLedPin, LOW);
}


//SEND TO P5 (BUTTON INPUTS 1-4)
  if (digitalRead(redButtonPin) == LOW) {//if button pressed
    buttonPressed = 1;//assign value number
    Serial.println(buttonPressed);//prints value and moves to the next line, send to p5
    delay(100);//delay to prevent repeated button tirggers from one press

  if (digitalRead(yellowButtonPin) == LOW) {
    buttonPressed = 2;
    Serial.println(buttonPressed);
    delay(100);
  }

  if (digitalRead(blueButtonPin) == LOW) {
    buttonPressed = 3;
    Serial.println(buttonPressed);
    delay(100);
  }

  if (digitalRead(greenButtonPin) == LOW) {
    buttonPressed = 4;
    Serial.println(buttonPressed);
    delay(100);
  }
}
