#include "bms.h"

Bms::Bms(Can &canBus) : CanDevice(canBus) {}

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

int Bms::bmsParseMsg()  // read CAN bus
{
  struct can_frame frame;
  bus.read(&frame);  // read CAN bus to get id
  uint32_t id = frame.can_id;
  uint8_t *msg = (frame.data);

  switch (id) {
    case 0x6B0:
      packCurrent.setValue((msg[1] | msg[0] << 8) / 10);
      packVoltage.setValue((msg[3] | msg[2] << 8) / 10);
      Soc.setValue(msg[4] / 2);
      relayStatus.setValue(msg[6] | msg[5] << 8);
      cellMaxVoltage.setValue(((msg[5] << 8) | msg[6]) / 10000.0);
      break;
    case 0x6B1:
      packDCL.setValue(msg[1] | msg[0] << 8);
      highTemp.setValue(msg[4]);
      break;
    case 0x653:
      relayStatus.setValue(msg[1] | msg[0] << 8);
      relayStatus.setValue(msg[0]);
      inputVoltage.setValue((msg[2] | (msg[3] << 8)) / 10);
      break;
    case 0x652:
      packCCL.setValue(msg[0] | (msg[1] << 8));
      packDCL.setValue(msg[2] | (msg[3] << 8));
      break;
    case 0x651:
      maxCells.setValue(msg[6]);
      numCells.setValue(msg[7]);
      break;
    case 0x650:
      Soc.setValue(msg[0]);
      Soc.setValue(Soc.getValue() / 2);
      packResistance.setValue(msg[1] | (msg[2] << 8));
      packHealth.setValue(msg[3]);
      packOpenVoltage.setValue((msg[4] | (msg[5] << 8)) / 10);
      packCycles.setValue(msg[6] | (msg[7] << 8));
      break;
    case 0x150:
      packAh.setValue(msg[4] | (msg[5] << 8));
      highTemp.setValue(msg[6]);
      lowTemp.setValue(msg[7]);
      break;
    case 0x6b2:
      cellMinVoltage.setValue(((msg[0] << 8) | msg[1]) / 10000.0);
      avgTemp.setValue(msg[2]);
      imdStatus.setValue(msg[3]);
      break;
    case 0x80:
      break;
    case 0x36:
      if (msg[0] >= 0 && msg[0] < 72)
        cells[msg[0]] = (msg[2] | (msg[1] << 8)) / 10000.0;
      break;

    default:
      return 0;
  }
  return 1;
}
