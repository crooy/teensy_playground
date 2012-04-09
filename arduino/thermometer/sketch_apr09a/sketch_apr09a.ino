const int redPin =  15;
const int greenPin =  14;
const int bluePin =  12;
const int buttonPin = 7;
const int wheelPin = 0;
const int statusLed = 11;
const int tempSensor = 1;

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
  volatile int colorValue[3] = {0, 0, 255};
  volatile int selectedColor = 0;
  // 0 : red
  // 1 : blue
  // 2 : green
  
  volatile int state = 0;
  // 0 : idle
  // 1 : settings
  
  boolean goingToRed = true;
  
  void loop()
  {
    if (state == 1)
    {
        blinkTemperature(getTemperature());
        state = 0;  
    }else{
      
      if (goingToRed)
      {
        colorValue[0]+=1;
        colorValue[2]-=1;
      }else{
        colorValue[0]-=1;
        colorValue[2]+=1;
      }
      if (colorValue[0]==255)
      {
          goingToRed = false;
      }
      if (colorValue[2]==255)
      {
          goingToRed = true;
      }            
      setColor();
      delay(50);
    }
  }

  void onButtonPress()
  {
    Serial.print(getTemperature());
    Serial.print(" graden celcius\n");
    state = 1;
  }
  
  /*
   * getVoltage() - returns the voltage on the analog input
   * defined by pin
   */
  float getVoltage(int pin)
  {
    return (analogRead(pin) * .004882814);//converting from a 0
    //to 1024 digital range
    // to 0 to 5 volts
    //(each 1 reading equals ~ 5 millivolts
  }
  float getTemperature()
  {
    return  (getVoltage(tempSensor) - .5) * 100;
    //converting from 10 mv
    //per degree wit 500 mV  
    //degrees ((volatge - 500mV) times 100)
  }
  
  void setColor()
  {
        Serial.println("color : "+String(colorValue[0])+","+String(colorValue[1])+","+String(colorValue[2]));
    analogWrite(colorIndex[0], colorValue[0]);
    analogWrite(colorIndex[1], colorValue[1]);
    analogWrite(colorIndex[2], colorValue[2]);
  }
  
  void blinkTemperature(float temp)
  {
    int count = int(temp);
    Serial.println(count);
    for (int i=0;i < count+1 ; i++)
    {
      blinkOnce();
    }
  }
  
  void blinkOnce()
  {
     analogWrite(redPin, 255);
     delay(300);
     analogWrite(redPin, 0);
     delay(300);
  }
  
  
