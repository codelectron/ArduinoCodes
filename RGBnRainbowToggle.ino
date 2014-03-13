/*
RGBnRainbowToggle
It uses pin 13, 12,11,10,9,8,7,6,5 for Common cathode RGB LEDS
Pin 2 (interrupt 1)  for toggle switch 
A0, A1, A2 for POTs to controll the Reg, Green, Blue color in RGB mode and A2 in rainbow mode for adjusting the timing 
This code is testing for Arduino Leonardo.
 */

int permute[11][3] = {{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1},{0,0,1},{0,1,0},{0,1,1},{1,0,0} };

int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorValue = 0; 
int sensorValue1 = 0; 
int sensorValue2 = 0; 
int sensorValue3 = 0; 
int pushButtonState = HIGH;
long debouncing_time = 20; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

void setup()  { 
  // nothing happens in setup 
   pinMode(13, OUTPUT);
   pinMode(12, OUTPUT);
   pinMode(11, OUTPUT);
   pinMode(10, OUTPUT);
   pinMode(9, OUTPUT);
   pinMode(8, OUTPUT);
   pinMode(7, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(5, OUTPUT);
   attachInterrupt(1, debounceInterrupt, FALLING);
          
} 

void loop()  { 
  
  if( HIGH == pushButtonState)
  {
    for(int fadeValue = 0 ; fadeValue <= 8; fadeValue +=1) { 
    sensorValue = analogRead(sensorPin3);   
    setBulb(1, permute[fadeValue]);
    setBulb(2, permute[fadeValue + 1]);
    setBulb(3, permute[fadeValue + 2]);
    if (HIGH != pushButtonState)
       break;
    delay(1024 - sensorValue);
    } 
  } 
  else {
     sensorValue1 = analogRead(sensorPin1);   
     sensorValue2 = analogRead(sensorPin2);   
     sensorValue3 = analogRead(sensorPin3);  
     //sensorValue1 = map(sensorValue1, 0, 1023, 0, 255);
     //sensorValue2 = map(sensorValue2, 0, 1023, 0, 255);     
     //sensorValue3 = map(sensorValue3, 0, 1023, 0, 255);     
     fadeBulb(1,sensorValue1);
     fadeBulb(2,sensorValue2);     
     fadeBulb(3,sensorValue3);          
  }
}

void setBulb(int no, int val[3])
{
  switch(no)
  {
    case 1:
       digitalWrite(13, val[0]);
       digitalWrite(12, val[1]);
       digitalWrite(11, val[2]);
    break;
    case 2:
       digitalWrite(10, val[0]);
       digitalWrite(9,  val[1]);
       digitalWrite(8,  val[2]);
    break;
    case 3:
       digitalWrite(7, val[0]);
       digitalWrite(6,  val[1]);
       digitalWrite(5,  val[2]);
    break;    
  }
}
void fadeBulb(int no, int val)
{
    switch(no)
  {
    case 1:
       analogWrite(13, val);
       analogWrite(10, val);
       analogWrite(7, val);
    break;
    case 2:
       analogWrite(12, val);
       analogWrite(9,  val);
       analogWrite(6,  val);
    break;
    case 3:
       analogWrite(11, val);
       analogWrite(8,  val);
       analogWrite(5,  val);
    break;    
  }
}
void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    changeStateInterrupt();
    last_micros = micros();
  }
}
void changeStateInterrupt() {
  if( pushButtonState == HIGH)
  {
    pushButtonState = LOW;
  }
  else 
  {
    pushButtonState = HIGH;
  }
    
}

