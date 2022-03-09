#include "mppt.h"
#define MPPT_BASE_ID 0x0000
#include <cstdint>
#include <cstring>
#include <iostream>

Mppt::Mppt(Can canBus) { this->canBus = canBus; }

int Mppt::sendMode(uint8_t mode) {
  return this->canBus.canSend(MPPT_BASE_ID + 8, &mode, 1);
}
int Mppt::sendMaxOutputVoltage(float maxOutputVoltage) {
  return this->canBus.canSend(MPPT_BASE_ID + 10, (uint8_t*)&maxOutputVoltage,
                              4);
}
int Mppt::sendMaxInputCurrent(float maxInputCurrent) {
  return this->canBus.canSend(MPPT_BASE_ID + 11, (uint8_t*)&maxInputCurrent, 4);
}

int Mppt::MpptParseMsg() {
  struct can_frame frame;
  this->canBus.canRead(&frame);
  uint32_t id = frame.can_id;
  uint8_t* msg = frame.data;
  uint8_t temp;
  uint32_t temp2;

  switch (id) {
    case MPPT_BASE_ID:
      memcpy(&temp2, msg, 4);
      inputVoltage.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      inputCurrent.setValue((float)temp2);
    case MPPT_BASE_ID + 1:
      memcpy(&temp2, msg, 4);
      outputVoltage.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      outputCurrent.setValue((float)temp2);
    case MPPT_BASE_ID + 2:
      memcpy(&temp2, msg, 4);
      mosfetTemp.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      controllerTemp.setValue((float)temp2);
    case MPPT_BASE_ID + 3:
      memcpy(&temp2, msg, 4);
      v12.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      v3.setValue((float)temp2);
    case MPPT_BASE_ID + 4:
      memcpy(&temp2, msg, 4);
      maxOutputVoltage.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      maxInputCurrent.setValue((float)temp2);
    case MPPT_BASE_ID + 5:
      memcpy(&temp, msg + 3, 1);
      errorFlags.setValue(temp);
      memcpy(&temp, msg + 4, 1);
      limitFlags.setValue(temp);
      memcpy(&temp, msg + 5, 1);
      mode.setValue(temp);
    case MPPT_BASE_ID + 6:
      memcpy(&temp2, msg, 4);
      battOutputVoltage.setValue((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      powerConnectorTemp.setValue((float)temp2);
    default:
      return 0;
  }
  return 1;
}
