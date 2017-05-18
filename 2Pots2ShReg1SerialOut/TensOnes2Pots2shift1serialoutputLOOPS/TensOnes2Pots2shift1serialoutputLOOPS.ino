//shfit register data https://www.arduino.cc/en/Tutorial/SwitchCase
int clockPin = 2;
int latchPin = 4;
int dataPin = 3;
//pot data
int potPin=A4;
int potPinTwo=A5;
//button data
int buttonInputPin=12;
int debounceDelay=100;
boolean buttonOn=0;
boolean buttonOff=0;
//clear flash n=flashes, d=delay
int n = 2;
int d = 500;
//count
int countDelay=100;
//array data
const int arraySize = 10;
byte dataArray[arraySize];
void setup() 
  {
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);
  dataArray[0] = 0x3F;//0
  dataArray[1] = 0x06;//1 
  dataArray[2] = 0x5B;//2 
  dataArray[3] = 0x4F;//3 
  dataArray[4] = 0x66;//4 
  dataArray[5] = 0x6D;//5 
  dataArray[6] = 0x7D;//6 
  dataArray[7] = 0x07;//7 
  dataArray[8] = 0x7F;//8 
  dataArray[9] = 0x67;//9
  dataArray[10] = 0;
  blinkClear(n,d);
  }
void loop() 
  {  
  int potValue = analogRead(potPin);
  int potValueTwo = analogRead(potPinTwo);
  potValue = map(potValue,1,1024,0,10);
  potValueTwo=map(potValueTwo,1,1024,0,10);
  int tens=dataArray[potValue];
  int ones=dataArray[potValueTwo];
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, tens);
  shiftOut(dataPin, clockPin, ones);
  digitalWrite(latchPin, 1);
  delay(countDelay);
   }
void shiftOut(int myDataPin, int myClockPin, byte myDataOut)
  {
   int i = 0;
   int pinState;
   pinMode(myClockPin,OUTPUT);
   pinMode(myDataPin,OUTPUT);
   digitalWrite(myDataPin,0);
   digitalWrite(myClockPin,0);
   for(i=7;i>=0;i--)
    {
      digitalWrite(myClockPin,0);
      if(myDataOut & (1<<i))
        {
          pinState=1;
        }
      else
        {
          pinState=0;     
        }
      digitalWrite(myDataPin,pinState);
      digitalWrite(myClockPin,1);
      digitalWrite(myDataPin,0);
    }
    digitalWrite(myClockPin,0);
  }
void blinkClear(int n,int d)
  {
    for(int x=0;x<n;x++)
      {
        digitalWrite(latchPin,0);
        shiftOut(dataPin,clockPin,255);
        shiftOut(dataPin,clockPin,255);
        digitalWrite(latchPin,1);
        delay(d);
        digitalWrite(latchPin,0);
        shiftOut(dataPin,clockPin,0);
        shiftOut(dataPin,clockPin,0);
        digitalWrite(latchPin,1);
        delay(d);
      }
      
  }

