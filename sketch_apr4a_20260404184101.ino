int sensorPin = A0;//the analog pin connected to the photocell sensor
int redLED = 8;//the digital pin connected to the red led (only needs to be fully on or off)
int greenLED = 9;//the PWM pin connected to the green led for brightness control with analogwrite
int buttonPin = 2;//the digital pin connected to the push button
int brightness = 0;//variable for the led brightness for pwm 0-255

void setup() {
  Serial.begin(9600);//to start serial communcation so we can see the sensor values
  pinMode(redLED, OUTPUT);//sets the red led pin as an output
  pinMode(greenLED, OUTPUT);//sets the green led pin as an output
  pinMode(buttonPin, INPUT);//sets the button pin as a digital input
}

void loop() {

  int sensorValue = analogRead(sensorPin);//reads the analog values from the photocell
  int buttonState = digitalRead(buttonPin);//reads the digital value from the button (pressed or not)
  Serial.println(sensorValue);//prints the sensor value to the serial moniter so I can get the values

  sensorValue = constrain(sensorValue, 720, 860);   //to constraint the sensor reading to a range based on the min and max value from the serial monitor 
  brightness = map(sensorValue, 720, 860, 0, 255);  //to map the sensor readings range 0-255 (converts to PWM range) which lets me control the led brightness with analogwrite

  //Dark Environment
  if (sensorValue < 790) { //if the light level is below the midpoint value = dark
    digitalWrite(greenLED, LOW); //turns the green led off in the dark
    if (buttonState == HIGH) { //and if the button is pressed make the red led blink
      digitalWrite(redLED, HIGH);
      delay(50);
      digitalWrite(redLED, LOW);
      delay(50);
    } else {
      digitalWrite(redLED, HIGH); //if the button is not pressed keep the red led on
    }
  }
  //Bright Environment
  else { //if the light level is above the midpoint value = light
    digitalWrite(redLED, LOW);//turn off the red led in the light
    if (buttonState == HIGH) {//if the button is pressed make the green led blink
      analogWrite(greenLED, brightness);  //to set the brightness based on the mapped sensor values 
      delay(50);
      analogWrite(greenLED, 0);
      delay(50);
    } else { //if the button is not pressed keep the green led on
      analogWrite(greenLED, brightness);  //to set the brightness based on the mapped sensor values 
  }
}
}
