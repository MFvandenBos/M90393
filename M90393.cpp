#include "Energia.h"
/*
  M90393.ccp - Library for simplified MLX90393 SPI communication.
  Created by Michael van den Bos, November 30, 2018.
*/

#include "Energia.h"
#include "M90393.h"

/* Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}
*/
// constructor assigns pins according to the number of sensors
M90393::M90393(int sensors)
{
  int _ERLED = 14; //Led pin
  pinMode(_ERLED, OUTPUT);
  num_s = sensors;
  _pin = _ERLED;

 // int MISO1 = 34;  int MOSI1 = 55;
 // int MISO2 = 35;  int MOSI2 = 56;
 // int MISO3 = 57;  int MOSI3 = 58;
 // int MISO4 = 59;  int MOSI4 = 60;
 // int MISO5 = 9;  int MOSI5 = 61;
 // int MISO6 = 62;  int MOSI6 = 63;
 // int MISO7 = 79;  int MOSI7 = 68;
 // int MISO8 = 78;  int MOSI8 = 69;
 // int MISO9 = 22;  int MOSI9 = 21;
 // int MISO10 = 20;  int MOSI10 = 32;
 // int MISO11 = 70;  int MOSI11 = 71;
 // int MISO12 = 81;  int MOSI12 = 10;
 // int MISO13 = 19;  int MOSI13 = 11;
 // int MISO14 = 65;  int MOSI14 = 64;
 // int MISO15 = 37;  int MOSI15 = 66;
//  int MISO16 = 39;  int MOSI16 = 38;
_MISO[0] = MISO0;
_MISO[1] = MISO1;
_MISO[2] = MISO2;
_MISO[3] = MISO3;
_MISO[4] = MISO4;
_MISO[5] = MISO5;
_MISO[6] = MISO6;
_MISO[7] = MISO7;
_MISO[8] = MISO8;
_MISO[9] = MISO9;
_MISO[10] = MISO10;
_MISO[11] = MISO11;
_MISO[12] = MISO12;
_MISO[13] = MISO13;
_MISO[14] = MISO14;
_MISO[15] = MISO15;
_MISO[16] = MISO16;

gainlookup[0][0]=0.751;gainlookup[0][1]=1.210;
gainlookup[1][0]=0.601;gainlookup[1][1]=0.968;
gainlookup[2][0]=0.451;gainlookup[2][1]=0.726;
gainlookup[3][0]=0.376;gainlookup[3][1]=0.605;
gainlookup[4][0]=0.3004;gainlookup[4][1]=0.484;
gainlookup[5][0]=0.2504;gainlookup[5][1]=0.403;
gainlookup[6][0]=0.2004;gainlookup[6][1]=0.323;
gainlookup[7][0]=0.1502;gainlookup[7][1]=0.242;
 // can only initialize the values like this when assigning the array. Otherwise it has to be done item by item. 
 // _MISO[17] = {MISO0, MISO1, MISO2, MISO3, MISO4, MISO5, MISO6, MISO7, MISO8, MISO9, MISO10, MISO11, MISO12, MISO13, MISO14, MISO15, MISO16};
 // int _MOSI = {0, MOSI1, MOSI2, MOSI3, MOSI4, MOSI5, MOSI6, MOSI7, MOSI8, MOSI9, MOSI10, MOSI11, MOSI12, MOSI13, MOSI14, MOSI15, MOSI16};  

  
   // use a for loop to initialize each pin as an output for Master Out Slave In:
   // MOSI pins are connected to a pull up. 
//  for (int sensorSelect = 1; sensorSelect < num_s+1; sensorSelect++)  {
//    pinMode(_MOSI(sensorSelect), OUTPUT);
//  }
  
  // pins are automatically set to input without pull up. Make sure to connect a pull up to each input pin. 
  // 
   for (sensorSelect = 0; sensorSelect < num_s+1; sensorSelect++)  {
    pinMode(_MISO[sensorSelect], INPUT_PULLUP);
  }
  
  
};


int M90393::pintest()
{ 
	
    digitalWrite(MOSI0, LOW);   // turn output pin low
    digitalWrite(MOSI0, HIGH);   // turn the pin high
	
    delay(1000); // keep high for one second
	int tim = micros();
    digitalWrite(MOSI0, LOW); //turn the pin low. 
	tim = micros()-tim;
	return tim;
  }

int M90393::pintest2(){
	char tempchar;
	int tim = micros();
	int count = 1;
	for(int count2 = 0; count2 < 16; count2++){
        tempchar |= (digitalRead(_MISO[count2]) & 0x01 ) << (8 - count);
      }
	tim = micros()-tim;
	return tim; 
}

float M90393::getGainZ(int res, int gain){
	float tmp;
	tmp = gainlookup[gain][1];
	if (res==0){
	return tmp;
	}
	else{
		tmp = tmp*(float)(1 << res);
		return tmp; 
	}
}
float M90393::getGainXY(int res, int gain){
	float tmp;
	tmp = gainlookup[gain][0];
	if (res==0){
	return tmp;
	}
	else{
		tmp = tmp*(float)(1 << res);
		return tmp; 
	}
}


void M90393::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);
}

void M90393::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
unsigned char M90393::cmdNOP()
{
    unsigned char inputchar = 0x00;
    return sendCommand1(inputchar);
}
unsigned char M90393::cmdEX(){
    unsigned char inputchar = 0x80;
    return sendCommand1(inputchar);
}
unsigned char M90393::cmdSB(char zyxt){
    unsigned char inputchar = 0x10;
    // warning add zyxt
    //inputchar |= zyxt;
    return sendCommand1(inputchar);
}
unsigned char M90393::cmdSWOC(char zyxt){
    unsigned char inputchar = 0x20;
    // warning add zyxt
    //inputchar = inputchar|zyxt;
    return sendCommand1(inputchar);
}
unsigned char M90393::cmdSM(char zyxt){
    unsigned char inputchar = 0x30;
    // warning add zyxt
    inputchar = inputchar|zyxt;
    return sendCommand1(inputchar);
}

unsigned char M90393::sendCommand1(unsigned char c)
{
  digitalWrite(SCLK, HIGH);
  digitalWrite(CS, LOW); 

  delay(DELAY_TIME*4);

  writeMLX90393(c);

  delay(DELAY_TIME);

  unsigned char tmp = readMLX90393();

  delay(DELAY_TIME);

  digitalWrite(CS, HIGH);
  digitalWrite(MOSI0, HIGH);

  return tmp;
  
}

unsigned char M90393::readMLX90393(){

  unsigned char tmp = 0;

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01 ) <<7;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01 ) <<6;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 5;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 4;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 3;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 2;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 1;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01);
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);

  return tmp;
  
  
}	

void M90393::writeMLX90393(unsigned char c)
{
  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x80) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  
  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x40) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x20) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x10) ? HIGH : LOW); 
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x08) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x04) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x02) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  digitalWrite(MOSI0, (c & 0x01) ? HIGH : LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  delay(5);
  
}



