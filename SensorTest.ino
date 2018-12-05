#define SCLK 2
#define CS 5
#define MISO0 6
#define MOSI0 7
#define LED RED_LED

#define DELAY_TIME 1

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
  Serial.begin(9600); 

}

void loop() 
{
  // put your main code here, to run repeatedly: 
  delay(100);
  //Serial.println("At least you know the serial port is open");
  delay(1000);
  bool ledflip = true; 
  unsigned char t = resetIC();
  //unsigned char t = NOPIC();
  digitalWrite(LED, ledflip ? HIGH : LOW); 
  //digitalWrite(CS, value ? HIGH : LOW);
  Serial.println(t, HEX);
  Serial.println(t, BIN);
  //Serial.println(0xF0, BIN);
  Serial.write(63);
  Serial.println();
  ledflip = !ledflip;
  
  
}

unsigned char NOPIC()
{
    unsigned char inputchar = 0x00;
    return sendCommand1(inputchar);
}

unsigned char EX_it(){
     unsigned char inputchar = 0x80;
    return sendCommand1(inputchar);
}
    
unsigned char resetIC()
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

  return tmp;
  
}

void writeMLX90393(unsigned char c)
{
  digitalWrite(MOSI0, (c & 0x80) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(5);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  
  digitalWrite(MOSI0, (c & 0x40) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x20) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x10) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x08) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x04) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x02) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, (c & 0x01) ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  delay(5);
  
}

unsigned char readMLX90393()
{
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
