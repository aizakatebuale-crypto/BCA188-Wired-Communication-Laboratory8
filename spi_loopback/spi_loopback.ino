#include <SPI.h>

const int SCK_PIN  = 18;
const int MISO_PIN = 19;
const int MOSI_PIN = 23;
const int CS_PIN   = 27;

void setup() {
  Serial.begin(115200);
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
}

void loop() {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS_PIN, LOW);
  byte received = SPI.transfer(0xA5);
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();

  Serial.print("Sent 0xA5, received 0x");
  Serial.println(received, HEX);
  delay(1000);
}
