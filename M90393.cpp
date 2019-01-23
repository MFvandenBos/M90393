#include "Energia.h"
/*
  M90393.ccp - Library for simplified MLX90393 SPI communication.
  Created by Michael van den Bos, January 19th, 2019
*/

#include "Energia.h"
#include "M90393.h"

// constructor assigns pins according to the number of sensors
// constructor contains gain lookup table
// constructor adds pullups to inputs
// constructor sets output pins for CS, SCLK, MOSI
M90393::M90393(int sensors){
	num_s = sensors;


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
  digitalWrite(CS, HIGH); 
  digitalWrite(SCLK, HIGH); 
  digitalWrite(MOSI0, HIGH);
  pinMode(CS, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(MOSI0, OUTPUT);
 
  // set knownRes to false: this forces to run readRes. 
	knownRes = false;
	// end of constructor
};







//+++++++++++++++++++++++++++++++++++++++++++++++++++++ Command functions +++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned char M90393::cmdNOP(){
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
void M90393::cmdRM(char zyxt){
    unsigned char inputchar = 0x40;
    // warning add zyxt
    inputchar = inputchar|zyxt;
    //readMLX90393_multi(shortoutputmatrix, numsensors);
    sendCommandlong(inputchar, 0x00, 0x00, 0x00, num_s, 1 ,8);
}
unsigned char M90393::cmdRT(){
    unsigned char inputchar = 0xF0;
    return sendCommand1(inputchar);
}
unsigned char M90393::cmdWR(unsigned char c2, unsigned char c3, unsigned char c4){
	unsigned char inputchar = 0x60;
	sendCommandlong(inputchar, c2, c3, (c4<<2), num_s, 4, 0);
	return statusmatrix[0];
	// maybe return a bitwise sum instead of just the first one. This allows for finding errors.  	
}
unsigned short M90393::cmdRR(unsigned char c2, unsigned char c3, unsigned char c4){
	resetdatamatrix();
	unsigned char inputchar = 0x50;
	sendCommandlong(inputchar, (c2<<2), c3, c4, num_s, 2, 2);
	return datamatrix[0][0];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++ Utility functions +++++++++++++++++++++++++++++++++++++++++++++++++++++
unsigned char M90393::sendCommand1(unsigned char c){
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
void M90393::sendCommandlong(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int ArraySize, int writebytes, int returnbytes){
  // send command bytes
  writeseqMLX90393(c, c2, c3, c4, writebytes); //writeseq sets CS low. 
  // read return status byte CS remains low
  readMLX90393_multiC(ArraySize); // status byte is first byte of return
  transportMLX90393C(ArraySize); // status byte is transported to status matrix
  
  if (returnbytes > 0 ) {
	//read return data bytes
	for(int count8 = 0; count8 < (returnbytes/2); count8++){
	readMLX90393_multiS(ArraySize);
	transportMLX90393S(ArraySize, count8); // transfers bytes from short output to datamatrix
	delay(DELAY_TIME);
	}
  }
   digitalWrite(CS, HIGH); //command sequence finished. Reset by CS HIGH
   digitalWrite(MOSI0, HIGH);//command sequence finished. Reset by MOSI HIGH
}
void M90393::sendCommandlong(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int ArraySize, int writebytes, int returnbytes, unsigned char zyxt){
  // send command bytes
  // this overload is used when zxyt is not 0x0F and retrieving a measurement (cmd RM)
  writeseqMLX90393(c, c2, c3, c4, writebytes); //writeseq sets CS low. 
  // read return status byte CS remains low
  readMLX90393_multiC(ArraySize); // status byte is first byte of return
  transportMLX90393C(ArraySize); // status byte is transported to status matrix
  bool _ex = true;
	if (zyxt & 0x01) {
		//read return data bytes
		readMLX90393_multiS(ArraySize);
		transportMLX90393S(ArraySize, 0); // transfers bytes from short output to datamatrix for temperature
		delay(DELAY_TIME);
	}else{resetdatamatrix(zyxt, ArraySize); _ex = false;}
	if (zyxt & 0x02) {
		//read return data bytes
		readMLX90393_multiS(ArraySize);
		transportMLX90393S(ArraySize, 1); // transfers bytes from short output to datamatrix for x-axis
		delay(DELAY_TIME);
	}else{if(_ex){resetdatamatrix(zyxt, ArraySize); _ex = false;}}
	if (zyxt & 0x04) {
		//read return data bytes
		readMLX90393_multiS(ArraySize);
		transportMLX90393S(ArraySize, 2); // transfers bytes from short output to datamatrix for y-axis
		delay(DELAY_TIME);
	}else{if(_ex){resetdatamatrix(zyxt, ArraySize); _ex = false;}}
	if (zyxt & 0x08) {
		//read return data bytes
		readMLX90393_multiS(ArraySize);
		transportMLX90393S(ArraySize, 3); // transfers bytes from short output to datamatrix for z-axis
		delay(DELAY_TIME);
	}else{if(_ex){resetdatamatrix(zyxt, ArraySize); _ex = false;}}
  
   digitalWrite(CS, HIGH); //command sequence finished. Reset by CS HIGH
   digitalWrite(MOSI0, HIGH);//command sequence finished. Reset by MOSI HIGH
}


void M90393::readMLX90393_multiC(int ArraySize){
// this function reads one byte	
// charoutputmatrix is set to 0
// for loop takes 37 microseconds for 16 pins. which is not a problem as long as we use delay(). once using delaymicros() it becomes a problem. 
for(int count2 = 0; count2 < ArraySize; count2++){
		charoutputmatrix[count2] =0x00; // set variable to zero
      }

	  // first loop goes through 8 bits
 for(int count = 1; count < 9; count++){
	  // clock goes high
      digitalWrite(SCLK, HIGH);
      delay(DELAY_TIME); // wait
	  // second loop goes through all relevant read pins.
	  // for loop takes 37 microseconds for 16 pins. 
      for(int count2 = 0; count2 < ArraySize; count2++){
        charoutputmatrix[count2] |= (digitalRead(_MISO[count2]) & 0x01 ) << (8 - count);
      }
      delay(DELAY_TIME);
      digitalWrite(SCLK, LOW); // clock goes low. (here the values are thought of as read)
      delay(DELAY_TIME);   
  }
  digitalWrite(SCLK, HIGH); // clock goes high at the end
}
void M90393::readMLX90393_multiS(int ArraySize){
// this function reads two bytes	
// first loop goes through 16 bits
// for loop takes 37 microseconds for 16 pins. which is not a problem as long as we use delay(). once using delaymicros() it becomes a problem.
// this has to be here because the entire array can only be edited in a for loop. 
// this has to be here because if it isn't it is possible that a 1 of an old measurement remains, where there should be a 0. 
 for(int count2 = 0; count2 < ArraySize; count2++){
		shortoutputmatrix[count2] = 0x00; // set variable to zero
      }
 for(int count = 1; count < 17; count++){
	  // clock goes high
      digitalWrite(SCLK, HIGH);
      delay(DELAY_TIME); // wait
	  // second loop goes through all relevant read pins.
	  // for loop takes 37 microseconds for 16 pins. 
      for(int count2 = 0; count2 < ArraySize; count2++){
		//Serial.print("this is readMLX90393_multiS, I am at count2 ");
		//Serial.println(count2);
		//Serial.print("this is readMLX90393_multiS, I am at count ");
		//Serial.println(count);
		//Serial.print("this is readMLX90393_multiS, the retun is ");
		//Serial.println(digitalRead(_MISO[count2]) & 0x01);
        shortoutputmatrix[count2] |= (digitalRead(_MISO[count2]) & 0x01 ) << (16 - count);
      }
      delay(DELAY_TIME);
      digitalWrite(SCLK, LOW); // clock goes low. (here the values are read)
      delay(DELAY_TIME);   
  }
  digitalWrite(SCLK, HIGH);
}
void M90393::transportMLX90393C(int ArraySize){
  
  for(int count = 0; count < ArraySize; count++){
    
    statusmatrix[count] = charoutputmatrix[count];
  }
}
void M90393::transportMLX90393S(int ArraySize, int partsel){
  
  for(int count = 0; count < ArraySize; count++){
    //Serial.print("this is transportMLX90393S I am transporting ");
	//Serial.println(shortoutputmatrix[count], BIN);
    datamatrix[count][partsel] = shortoutputmatrix[count];
  }
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

void M90393::writeMLX90393(unsigned char c){
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

void M90393::writeseqMLX90393(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int writebytes){
  digitalWrite(SCLK, HIGH); 
  digitalWrite(CS, LOW); 
  delay(DELAY_TIME*4); 
  writeMLX90393(c);
  delay(DELAY_TIME*3);
    if ( writebytes == 1 ) {}
	else {
        writeMLX90393(c2);
		delay(DELAY_TIME*3);
		if ( writebytes == 3 ){
		  writeMLX90393(c3);
          delay(DELAY_TIME*3);
		  }
        if (writebytes == 4){
			writeMLX90393(c3);
			delay(DELAY_TIME*3);
            writeMLX90393(c4);
            delay(DELAY_TIME*4);
          }     
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++ retrieval functions +++++++++++++++++++++++++++++++++++++++++++++++++++++
float M90393::getSenseZ(){
	float tmp;
	int gain = 0;
	int res = 0;
	unsigned short value_gain;
	unsigned short value_res;
	unsigned short value_hallconf;
	unsigned short readout;
	readout = cmdRR(0x00, 0x00, 0x00);
	value_gain = (readout & 0x70) >> 4;
	value_hallconf = (readout & 0xF);
	readout = cmdRR(0x0A, 0x00, 0x00);
	value_res = (readout & 0x60) >> 5;
	tmp = gainlookup[gain][1];
	res = value_res;
	gain = value_gain;
	tmp = gainlookup[gain][1];
	if (res==0){
	return tmp;
	}
	else{
		tmp = tmp*(float)(1 << res);
		return tmp; 
	}
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
float M90393::getSenseX(){
	float tmp;
	int gain = 0;
	int res = 0;
	unsigned short value_gain;
	unsigned short value_res;
	unsigned short value_hallconf;
	unsigned short readout;
	readout = cmdRR(0x00, 0x00, 0x00);
	value_gain = (readout & 0x70) >> 4;
	value_hallconf = (readout & 0xF);
	readout = cmdRR(0x0A, 0x00, 0x00);
	value_res = (readout & 0x600) >> 9;
	tmp = gainlookup[gain][1];
	res = value_res;
	gain = value_gain;
	tmp = gainlookup[gain][1];
	tmp = gainlookup[gain][0];
	if (res==0){
	return tmp;
	}
	else{
		tmp = tmp*(float)(1 << res);
		return tmp; 
	}
}
float M90393::getSenseY(){
	float tmp;
	int gain = 0;
	int res = 0;
	unsigned short value_gain;
	unsigned short value_res;
	unsigned short value_hallconf;
	unsigned short readout;
	readout = cmdRR(0x00, 0x00, 0x00);
	value_gain = (readout & 0x70) >> 4;
	value_hallconf = (readout & 0xF);
	readout = cmdRR(0x0A, 0x00, 0x00);
	value_res = (readout & 0x180) >> 7;
	tmp = gainlookup[gain][1];
	res = value_res;
	gain = value_gain;
	tmp = gainlookup[gain][1];
	tmp = gainlookup[gain][0];
	if (res==0){
	return tmp;
	}
	else{
		tmp = tmp*(float)(1 << res);
		return tmp; 
	}
}
void M90393::readRes(){
	//should be called after modfiying the res and gain 
	unsigned short value_res;
	unsigned short readout;
	readout = cmdRR(0x03, 0x00, 0x00); //read memory no. 3 you toady
	value_res = (readout & 0x600) >> 9;
	res_x = value_res;
	value_res = (readout & 0x180) >> 7;
	res_y = value_res;
	value_res = (readout & 0x60) >> 5;
	res_z = value_res;
	sense_x = getSenseX();
	sense_y = getSenseX();
	sense_z = getSenseX();
}

unsigned short M90393::boostRet(int sensor, unsigned short mode){
	switch(mode){
		case 0: {
			unsigned short tmp = 0;
			tmp = statusmatrix[sensor];
			return tmp; } break;
		case 1:
			return datamatrix[sensor][0];
			break;
		case 2: 
			return datamatrix[sensor][1];
			break;
		case 3:
			return datamatrix[sensor][2];
			break;
		case 4:
			return datamatrix[sensor][3];
			break;
		default: 
		{unsigned short tmp = 0x00;
		return tmp;}
			break;
	}
}

float M90393::retrieve(int sensor, unsigned short mode){
	if (knownRes){}
	else{readRes(); 
		knownRes = true;}
	switch(mode){
		case 0: {
			unsigned short tmp = 0;
			tmp = statusmatrix[sensor];
			return tmp; } break;
		case 1: {
		float temp = 1; 
		// datamatrix[sensor][0] = temperature
			unsigned short temp2 = 0;
			if (datamatrix[sensor][0] == 46244){temp = 25;}
			else if (datamatrix[sensor][0]>46244){
				temp2 = datamatrix[sensor][0]-46244;
				temp = 25 + temp2/45.2; 
			}// is this consistent with int math?
			else if (datamatrix[sensor][0]<46244){	
				temp2 = 46244-datamatrix[sensor][0];
				temp = 25 - temp2/45.2; 
			}
			return temp;}
			break;
		case 2:{
			//datamatrix[sensor][1] = x-axis
			float temp = 0; 
			unsigned short tmpda = datamatrix[sensor][1];
			if (res_x <2){
					signed short tmpdx = tmpda;
					temp = tmpdx*sense_x;
					// this should be it (O_O)
			}
			// you should put an else here if res > 1
			return temp;}
		break;
		case 3: {
			//datamatrix[sensor][2] = y-axis
			float temp = 0; 
			unsigned short tmpda = datamatrix[sensor][2];
			if (res_x <2){
					signed short tmpdx = tmpda;
					temp = tmpdx*sense_y;
					// this should be it (O_O)
			}
			return temp;}
			break;
		case 4: {
				//datamatrix[sensor][3] = z-axis
			float temp = 0; 
			unsigned short tmpda = datamatrix[sensor][3];
			if (res_x <2){
					signed short tmpdx = tmpda;
					temp = tmpdx*sense_z;
					// this should be it (O_O)
			}
			return temp;}
			break;
		default: {
			unsigned short tmp = 0x00;
		return tmp;}
			break;
	}
}
unsigned char M90393::retrieveS(int sensor){
	return statusmatrix[sensor];
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++ test functions +++++++++++++++++++++++++++++++++++++++++++++++++++++
void M90393::datamatrixrand(){
	int randa = rand(); // outside the loop since rand is slow. 
	for(int count = 0; count < 17; count++){  
      for(int count2 = 0; count2 < 5; count2++){
		  
		  unsigned short temprand;
			temprand = randa;
			temprand = (temprand + count + count2) >> 1;
		datamatrix[count][count2] = temprand; // set variable to temprand
      }
  }
 
}
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

void M90393::resetdatamatrix(){
	for(int count = 0; count < 17; count++){  
      for(int count2 = 0; count2 < 5; count2++){
		datamatrix[count][count2] = 0x00; // set variable to zero
      }
  }
}
void M90393::resetdatamatrix(unsigned char zyxt, int ArraySize){
	 
		if ((zyxt & 0x01)>0){}
			else{
				for(int count = 0; count < ArraySize; count++){ 
				datamatrix[count][0] = 0x00; // set variable temp to zero	
				}
			}
		if ((zyxt & 0x02)>0){}
			else{
				for(int count = 0; count < ArraySize; count++){ 
				datamatrix[count][1] = 0x00; // set variable x to zero
				}
			}
		if ((zyxt & 0x04)>0){}
			else{
				for(int count = 0; count < ArraySize; count++){ 
				datamatrix[count][3] = 0x00; // set variable y to zero
				}
			}
		if ((zyxt & 0x04)>0){}
		else{
				for(int count = 0; count < ArraySize; count++){ 
				datamatrix[count][4] = 0x00; // set variable z to zero
				}
			}
}
