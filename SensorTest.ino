#define SCLK 2
#define CS 5
#define MISO0 6
#define MOSI0 7
#define LED RED_LED
#define show1 75
#define show2 76
#define show3 77
#define show4 78

#define DELAY_TIME 1
bool ledflip = true;

void setup() 
{
  // put your setup code here, to run once:
  digitalWrite(CS, HIGH); 
  digitalWrite(SCLK, HIGH); 
  digitalWrite(MOSI0, HIGH);
  pinMode(CS, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(MISO0, INPUT_PULLUP);
  pinMode(MOSI0, OUTPUT);
  pinMode(LED, OUTPUT); 
   pinMode(show1, OUTPUT);
    pinMode(show2, OUTPUT);
     pinMode(LED, OUTPUT);
      pinMode(LED, OUTPUT);
  Serial.begin(9600); 

}

void loop() 
{
  // put your main code here, to run repeatedly: 
  delay(100);
  //Serial.println("At least you know the serial port is open");
  delay(5000);
  //Serial.println(ledflip ? "true" : "false");
  unsigned char t;
  // t = cmdRT();
  t = cmdEX();
  //  t = cmdNOP();
  //Serial.println(t, HEX);
  Serial.println();
  Serial.println(t, BIN);
  //Serial.println(0xF0, BIN)//Serial.write(63);
  t = cmdSM(0xF);
  //Serial.println("send measurement command zxyt = 1111");
  unsigned char cmdChar = 0x30 | 0xF; 
  unsigned char inputchar = 0x30;
  inputchar |= 0xF;
  Serial.print("inputchar = ");Serial.println(inputchar, BIN);
  delay(DELAY_TIME);
  Serial.print("CdmSM = "); Serial.println(cmdChar, BIN);
  Serial.print("CdmSMstatus = "); Serial.println(t, BIN);
  unsigned int  meas = cmdRM(0xF);
  Serial.println("read measurement");
  Serial.print("CmdRM = " ); Serial.println(meas, BIN);
  
  
  
}

unsigned char cmdNOP()
{
    unsigned char inputchar = 0x00;
    return sendCommand1(inputchar);
}
unsigned char cmdEX(){
    unsigned char inputchar = 0x80;
    return sendCommand1(inputchar);
}
unsigned char cmdSB(char zyxt){
    unsigned char inputchar = 0x10;
    // warning add zyxt
    //inputchar |= zyxt;
    return sendCommand1(inputchar);
}
unsigned char cmdSWOC(char zyxt){
    unsigned char inputchar = 0x20;
    // warning add zyxt
    //inputchar = inputchar|zyxt;
    return sendCommand1(inputchar);
}
unsigned char cmdSM(char zyxt){
    unsigned char inputchar = 0x30;
    // warning add zyxt
    inputchar = inputchar|zyxt;
    return sendCommand1(inputchar);
}
unsigned int cmdRM(char zyxt){
    unsigned char inputchar = 0x40;
    // warning add zyxt
    inputchar = inputchar|zyxt;
    return sendCommandAdv(inputchar);
}

unsigned char cmdRT()
{
    unsigned char inputchar = 0xF0;
    return sendCommand1(inputchar);
}

unsigned char sendCommand1(unsigned char c)
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
unsigned int sendCommandAdv(unsigned char c){
  digitalWrite(SCLK, HIGH); 
  digitalWrite(CS, LOW); 
  delay(DELAY_TIME*4); 
  writeMLX90393(c);
  delay(DELAY_TIME*4);
  unsigned char tmp1 = readMLX90393();
  unsigned char tmp2;
  unsigned char tmp3;
  unsigned char tmp4;
  
  if (tmp1 & 0x02){
    delay(DELAY_TIME);
    tmp2 = readMLX90393();
    tmp3 = readMLX90393();
    if (tmp1 & 0x01){
      delay(DELAY_TIME);
      tmp4 = readMLX90393();
    }
  }
  
    else{
  unsigned int tmpI = (unsigned int)tmp1; 
  delay(DELAY_TIME);
  digitalWrite(CS, HIGH);   
  return tmpI;
  }
  unsigned int tmpI;
  tmpI |= (unsigned int)tmp1 << 24;
  tmpI |= (unsigned int)tmp2 << 16;
  tmpI |= (unsigned int)tmp3 << 8;
  tmpI |= (unsigned int)tmp4 << 0;
  delay(DELAY_TIME);
  digitalWrite(CS, HIGH);
  digitalWrite(MOSI0, HIGH);
return tmpI; 
}

void writeMLX90393(unsigned char c)
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

unsigned char readMLX90393(){

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
void setCS(bool value)
{
  digitalWrite(CS, value ? HIGH : LOW);
}
