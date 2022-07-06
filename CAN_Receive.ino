/*
  _   _ _             __        __    _
  | \ | (_)_ __   ___  \ \      / /__ | |_   _____  ___
  |  \| | | '_ \ / _ \  \ \ /\ / / _ \| \ \ / / _ \/ __|
  | |\  | | | | |  __/   \ V  V / (_) | |\ V /  __/\__ \
  |_| \_|_|_| |_|\___|    \_/\_/ \___/|_| \_/ \___||___/

  Hacked together by: Christian Robards
  Date:
*/



#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SPI.h>


const int SPI_CS_PIN = 10;              // CANBed V1
// const int SPI_CS_PIN = 3;            // CANBed M0
// const int SPI_CS_PIN = 9;            // CAN Bus Shield

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  while (CAN_OK != CAN.begin(CAN_500KBPS))   // init can bus : baudrate = 500k
  {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  Serial.println("CAN BUS INITIALIZED!");
}


void loop()
{
  unsigned char len = 0;
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive())           // check if data coming
  {
    CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

    unsigned long canId = CAN.getCanId();

    // Serial.println("-----------------------------");
    //Serial.print("Get data from ID: ");
    //Serial.println(canId, HEX);

    if (canId == 0x0308) {  //RPM Filter

      for (int i = 0; i < len; i++) // print the data
      {
        Serial.print(buf[i]);
        Serial.print("\t");
      }
      Serial.println();
    }
  }

}
