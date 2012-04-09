const int redPin =  12;
const int greenPin =  15;
const int bluePin =  14;
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
    if (state == 1)
    {
        blinkTemperature(getTemperature());
        state = 0;  
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
  
  
