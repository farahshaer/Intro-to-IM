int potentiometerPin = A1;  //pin where potentiometer is connected
int sensorValue = 0;        //variable to store sensor value

void setup() {
  Serial.begin(9600);  //start serial communication between Arduino and p5
}

void loop() {
  sensorValue = analogRead(potentiometerPin);  //read analog sensor value (0–1023)
  Serial.println(sensorValue);                 //sends value to p5 in a single line, with the \n tells telling p5 its the end of the message
  delay(10);                                   //small delay to stabilize the readings
}
