#include "bms.h"

Bms::Bms(Can &canBus) : CanDevice(canBus, bms_callbacks) {}

int Bms::bmsClearFaults(void)  // send CAN info
{
  uint16_t can_id = 0x7e3;
  uint8_t TxData[8];          // TODO: find out why this is diff
  uint8_t length = 16 /*8*/;  // TODO p2: than this

  TxData[0] = 0x01;
  TxData[1] = 0x04;
  TxData[2] = 0x00;
  TxData[3] = 0x00;
  TxData[4] = 0x00;
  TxData[5] = 0x01;
  TxData[6] = 0x00;
  TxData[7] = 0x00;

  bus.send(can_id, TxData, length);

  return 0;
}
