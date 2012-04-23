const int ledpin = 11;
const int txpin = 8;
const int rxpin = 7;
const int buttonPin = 6;
const int analogPin = 0;
const unsigned long MAXT = 200;
const int BUCKET_SIZE = 2;
const int BUCKETS = (MAXT/BUCKET_SIZE)+1;

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
volatile unsigned long bucket[BUCKETS-1];

void initBuckets()
{
  for (int i=0; i<BUCKETS; ++i)
  {
    bucket[i]=0;
  }
}

void buttonPressed()
{
  noInterrupts();
  printBucket();
  interrupts();
}

void printBucket()
{
  unsigned long sum = 0;
  for(int i=0; i< BUCKETS-1; ++i)
  {
    sum += bucket[i];
  }
  unsigned long minimum = sum / 100;
  Serial.println();
  for(int i=0; i< BUCKETS-1; ++i)
  {
    if (bucket[i] > minimum ){
      int bucketrange = i*BUCKET_SIZE;
      Serial.print("[");
      Serial.print(bucketrange-BUCKET_SIZE);
      Serial.print("-");
      Serial.print(bucketrange);
      Serial.print("] microsec");
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
  if (dt < MAXT){
    int bucketIndex = dt / BUCKET_SIZE;
    ++bucket[bucketIndex];
  }
}



void loop()
{
  digitalWrite(ledpin, HIGH);
  delay(2000);
  digitalWrite(ledpin, LOW);
  delay(2000);
}



