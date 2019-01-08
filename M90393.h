/*
  M90393.h - Library for simplified MLX90393 SPI communication.
  Created by Michael van den Bos, November 30, 2018.
  
*/
#ifndef M90393_h
#define M90393_h
#include "Energia.h"
#define MOSI0 7
#define DELAY_TIME 1
#define MISO0 6
#define MISO1 8
#define MISO2 9
#define MISO3 10
#define MISO4 23
#define MISO5 24
#define MISO6 25
#define MISO7 26
#define MISO8 27
#define MISO9 28
#define MISO10 29
#define MISO11 30
#define MISO12 40
#define MISO13 39
#define MISO14 38
#define MISO15 37
#define MISO16 36
#define SCLK 2
#define CS 5

class M90393
{
  public:
    M90393(int sensors);
	// test functions
    int pintest();
    int pintest2();
	//command functions
    unsigned char cmdNOP();
    unsigned char cmdEX();
    unsigned char cmdSB(char zyxt);
    unsigned char cmdSWOC(char zyxt);
    unsigned char cmdSM(char zyxt);
	// utility functions
    void writeMLX90393(unsigned char c);
	unsigned char readMLX90393();
	unsigned char sendCommand1(unsigned char c);
	float getGainZ(int res, int gain);
	float getGainXY(int res, int gain); 
	
	// example functions
	void dot();
    void dash();
    
    int num_s;
    int _selct;
    int sensorSelect;
   private:
  	int UsEL;
  	int _CS;
  	int _CLK;
  	int _ERLED;
	int _pin;

  	char _MISO_P[16];
  	char _MOSI_P[16];
  	int _MISO[17];
  	int _MOSI[17];
	int sensors;
	double gainlookup[7][2];
};

#endif