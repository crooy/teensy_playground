const int ledpin = 11;
const int txpin = 8;
const int rxpin = 7;
const int buttonPin = 6;
const int analogPin = 0;
const unsigned long MAX_T = 1000000;
const int BUCKET_SIZE = 10;
const int BUCKETS = 1000;

void setup()
{
  Serial.begin(38400) ;
  Serial.println("setup\n\n");
  
  pinMode(ledpin, OUTPUT);
  pinMode(rxpin, INPUT);
  pinMode(txpin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  attachInterrupt(1, buttonPressed, FALLING);
  attachInterrupt(2, signalChange, CHANGE);

  initBuckets();
}


volatile unsigned long dt=0;
volatile unsigned long markedTime=0;
volatile unsigned int bucket[BUCKETS-1];

void initBuckets()
{
  for (int i=0; i<BUCKETS; ++i)
  {
    bucket[i]=0;
  }
}

void buttonPressed()
{

  digitalWrite(ledpin, HIGH);
  printBucket();
  delay(2000);
  digitalWrite(ledpin, LOW);

}

void printBucket()
{
  Serial.println();
  for(int i=0; i< BUCKETS; ++i)
  {
    if (bucket[i] > 0 ){
      Serial.print(i*BUCKET_SIZE);
      Serial.print(" : ");
      Serial.println(bucket[i]);
    }
  }
  Serial.println();
}

void signalChange()
{
  unsigned long time=micros();
  dt = time - markedTime;
  markedTime = time;
  int bucketIndex = dt / BUCKET_SIZE;
  ++bucket[bucketIndex];
}



void loop()
{

}


