#define SCLK 2
#define CS 5
#define MISO0 3
#define MOSI0 4

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

  Serial.begin(9600); 

}

void loop() 
{
  // put your main code here, to run repeatedly: 

  delay(1000);

  unsigned char t = resetIC();


  Serial.print(t, HEX);
  Serial.println();

  
  
}

unsigned char resetIC()
{
    return sendCommand1(0xF0);
}

unsigned char sendCommand1(unsigned char c)
{
  digitalWrite(SCLK, HIGH);
  digitalWrite(CS, LOW); 

  delay(DELAY_TIME);

  write(c);

  delay(DELAY_TIME);

  unsigned char tmp = read();

  delay(DELAY_TIME);

  digitalWrite(CS, HIGH);

  return tmp;
  
}

void write(unsigned char c)
{
  digitalWrite(MOSI0, c & 0x80 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  
  digitalWrite(MOSI0, c & 0x40 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x20 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x10 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x08 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x04 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x02 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(MOSI0, c & 0x01 ? HIGH : LOW);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);
  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);

  digitalWrite(SCLK, LOW);
  
}

unsigned char read()
{
  unsigned char tmp = 0;

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 7;
  delay(DELAY_TIME);
  digitalWrite(SCLK, LOW);
  delay(DELAY_TIME);

  digitalWrite(SCLK, HIGH);
  delay(DELAY_TIME);
  tmp |= (digitalRead(MISO0) & 0x01) << 6;
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
