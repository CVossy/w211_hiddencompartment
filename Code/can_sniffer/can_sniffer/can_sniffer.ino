#include <SPI.h>
#include "mcp_can.h"

const int SPI_CS_PIN = 10;
MCP_CAN CAN(SPI_CS_PIN);    // Set CS

void setup() {
  Serial.begin(115200);
  while (CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ)) {
    Serial.println("CAN init failed, retrying...");
    delay(500);
  }
  Serial.println("CAN init OK!");
  CAN.setMode(MCP_NORMAL);
}

void loop() {
  if (CAN_MSGAVAIL == CAN.checkReceive()) {
    long unsigned int rxId;
    byte len = 0;
    byte rxBuf[8];
    CAN.readMsgBuf(&rxId, &len, rxBuf);

    Serial.print("ID: 0x");
    Serial.print(rxId, HEX);
    Serial.print(" Data: ");
    for (byte i = 0; i < len; i++) {
      if (rxBuf[i] < 0x10) Serial.print("0");
      Serial.print(rxBuf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
