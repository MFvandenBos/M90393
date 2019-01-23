/*
  M90393.h - Library for simplified MLX90393 SPI communication.
  Created by Michael van den Bos, November 30, 2018.
  
*/
#ifndef M90393_h
#define M90393_h
#include "Energia.h"
#define MOSI0 7		//P1.5
#define DELAY_TIME 1
#define MISO0 6    	//P4.3
#define MISO1 8		//P4.6
#define MISO2 23	//P6.1
#define MISO3 24
#define MISO4 25
#define MISO5 26
#define MISO6 27
#define MISO7 28
#define MISO8 29
#define MISO9 30
#define MISO10 40
#define MISO11 39
#define MISO12 38
#define MISO13 37
#define MISO14 36
#define MISO15 35
#define MISO16 34
#define SCLK 2		//P6.0
#define CS 5		//4.1
//SCL(1)=9 and SDA(1)=10, SDA(0) = 15, SCL(0) = 14 
class M90393
{
  public:
    M90393(int sensors);
	// test functions
    int pintest();
    int pintest2();
	void datamatrixrand();
	void resetdatamatrix();
	void resetdatamatrix(unsigned char zyxt, int ArraySize);
	//command functions
    unsigned char cmdNOP();
    unsigned char cmdEX();
    unsigned char cmdSB(char zyxt);
    unsigned char cmdSWOC(char zyxt);
    unsigned char cmdSM(char zyxt);
	void cmdRM(char zyxt);
	unsigned char cmdRT();
	unsigned char cmdWR(unsigned char c2, unsigned char c3, unsigned char c4);
	unsigned short cmdRR(unsigned char c2, unsigned char c3, unsigned char c4);
	// utility functions
    void writeMLX90393(unsigned char c);
	unsigned char readMLX90393();
	unsigned char sendCommand1(unsigned char c);
	void readMLX90393_multiC(int ArraySize);
	void readMLX90393_multiS(int ArraySize);
	void transportMLX90393C(int ArraySize);
	void transportMLX90393S(int ArraySize, int partsel);
	void writeseqMLX90393(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int writebytes);
	void sendCommandlong(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int ArraySize, int writebytes, int returnbytes);
	void sendCommandlong(unsigned char c, unsigned char c2, unsigned char c3, unsigned char c4, int ArraySize, int writebytes, int returnbytes, unsigned char zyxt);
	
	// retrieval functions
	float retrieve(int sensor, unsigned short mode);
	unsigned char retrieveS(int sensor);
	unsigned short boostRet(int sensor, unsigned short mode);
	float getGainZ(int res, int gain);
	float getGainXY(int res, int gain); 
	float getSenseZ();
	float getSenseX();
	float getSenseY();	
	void readRes();
	// example functions
	void dot();
    void dash();
    
    int num_s;
	unsigned short datamatrix[16][4];
	unsigned char statusmatrix[16];
	unsigned char charoutputmatrix[16];
	unsigned short shortoutputmatrix[16];
	float resultmatrix[16][4];
    int _selct;
    int sensorSelect;
   private:
  	int UsEL;
  	int _CS;
  	int _CLK;
	float sense_x;
	float sense_y;
	float sense_z;
	unsigned short res_x;
	unsigned short res_y;
	unsigned short res_z;
	bool knownRes;
  	char _MISO_P[16];
  	char _MOSI_P[16];
  	int _MISO[17];
  	int _MOSI[17];
	int sensors;
	double gainlookup[7][2];
};

#endif
