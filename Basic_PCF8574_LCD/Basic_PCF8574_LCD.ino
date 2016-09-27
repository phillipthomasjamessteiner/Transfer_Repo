#include <Wire.h>

#define address 63
int x;

void setup() {
//  Serial.begin(9600);
  Wire.begin(address);
  delay(250);
  Wire.beginTransmission(address);
  Wire.write(B00000000);
  Wire.endTransmission(true);
  delay(250);
  lcdBegin();
}

void loop() {
  clearDisplay();
  setCur(x%17, 1);
  lcdPrint("hello");
  delay(125);
  x ++;
}

void lcdBegin() {

  // Function Set
  lcdWrite(B00101100);
  lcdWrite(B00001100);
  lcdWrite(B00101100);
  lcdWrite(B10001100);

  delay(1);

  // Display Control
  lcdWrite(B00001100);
  lcdWrite(B11111100);

  delay(1);

  // Display Clear
  lcdWrite(B00001100);
  lcdWrite(B00011100);

  delay(2);

  // Entry Mode Set

  lcdWrite(B00001100);
  lcdWrite(B00100000);
}

void setCur(uint8_t c, uint8_t l) {
  delay(5);
  uint8_t a;
  a = c + (40*(l-1));
  uint8_t oOne;
  oOne = ((a&B11110000) | B10001100);
  uint8_t oTwo;
  oTwo = (((a&B00001111)<<4) | B00001100);
  
  lcdWrite(oOne);
  lcdWrite(oTwo);
  
}

void writeDDRAM(uint8_t d) {
  delay(5);
  uint8_t oOne;
  oOne = ((d&B11110000) | B00001101);
  uint8_t oTwo;
  oTwo = (((d&B00001111)<<4) | B00001101);

  lcdWrite(oOne);
  lcdWrite(oTwo);
  
}

void lcdPrint(String i) {
  delay(5);
  uint8_t L = i.length();
  char str[L];
  i.toCharArray(str, L+1);
  for (int z = 0; z < L; z++) {
    writeDDRAM(str[z]);
//    Serial.print(str[z]);
  }
//  Serial.println("");
}

void clearDisplay() {
  lcdWrite(B00001100);
  lcdWrite(B00011100);
  delay(2);
}

void lcdWrite(byte b) {
  delayMicroseconds(4);
  Wire.beginTransmission(address);
  Wire.write(B00001100); // Enable On
  Wire.write(b);
  Wire.write(B00001000);
  Wire.endTransmission(true);
}




