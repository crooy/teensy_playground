int redPin =  12;
int greenPin =  15;
int bluePin =  14;
int buttonPin = 7;

void setup()   {                
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(38400);
   pinMode(buttonPin, INPUT_PULLUP);
}

int redIntensity = 0;

void loop()                     
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  analogWrite(greenPin, 255 - redIntensity);
  analogWrite(bluePin, 0);
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("red intensity : "+String(redIntensity));
    Serial.println("Button pressed!!!");
  }
  
  // remain at this color, but not for very long
  delay(10);
  
  // increase the red
  redIntensity = redIntensity + 1;
  
  // since 255 is the maximum, set it back to 0
  // when it increments beyond 255
  if (redIntensity > 255) {
    redIntensity = 0;
  }
}



