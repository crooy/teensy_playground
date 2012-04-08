const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;
const int buttonPin = 7;
const int wheelPin = 0;
const int statusLed = 11;

void setup()   {
  pinMode(statusLed, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(38400);
  pinMode(buttonPin, INPUT_PULLUP);
  
  attachInterrupt(2, onButtonPress, FALLING);
}

const int colorIndex[3] = {redPin, greenPin, bluePin};
volatile int colorValue[3] = {0, 0, 0};
volatile int selectedColor = 0;
// 0 : red
// 1 : blue
// 2 : green

volatile int state = 0;
// 0 : idle
// 1 : settings

void loop()
{
  if (state == 1){
    Serial.println("color : "+String(colorValue[0])+","+String(colorValue[1])+","+String(colorValue[2]));
    int val = getWheelInput();
    colorValue[selectedColor] = val;
    setColor();
  }
}

void onButtonPress()
{
  if (state == 0){
    digitalWrite(statusLed, LOW);
    selectedColor = changeSelectedColor(selectedColor);
    Serial.println("selected : "+String(selectedColor));
    state = 1;
  }else{
    state = 0;
    digitalWrite(statusLed, HIGH);
  }
}


int changeSelectedColor(int selectedColor)
{
  selectedColor++; 
  if (selectedColor > 2 ) selectedColor = 0;
  return selectedColor;
}

void setColor()
{
  analogWrite(colorIndex[0], colorValue[0]);
  analogWrite(colorIndex[1], colorValue[1]);
  analogWrite(colorIndex[2], colorValue[2]);
}

int getWheelInput()
{
  return analogRead(wheelPin) / 4;
}

