#include "mppt.h"
#define ID 0x0000
#include <cstdint>
#include <cstring>
#include <iostream>

mppt::mppt(Can canBus) { this->canBus = canBus; }

int mppt::sendMode(uint8_t mode) {
  return this->canBus.canSend(ID + 8, &mode, 1);
}
int mppt::sendMaxOutputVoltage(float maxOutputVoltage) {
  return this->canBus.canSend(ID + 10, (uint8_t*)&maxOutputVoltage, 4);
}
int mppt::sendMaxInputCurrent(float maxInputCurrent) {
  return this->canBus.canSend(ID + 11, (uint8_t*)maxInputCurrent, 4);
}

int mppt::mpptParseMsg() {
  struct can_frame frame;
  this->canBus.canRead(&frame);
  uint32_t id = frame.can_id;
  uint8_t* msg = frame.data;
  uint8_t temp;
  uint32_t temp2;

  switch (id) {
    case ID:
      memcpy(&temp2, msg, 4);
      setInputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setInputCurrent((float)temp2);
    case ID + 1:
      memcpy(&temp2, msg, 4);
      setOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setOutputCurrent((float)temp2);
    case ID + 2:
      memcpy(&temp2, msg, 4);
      setMosfetTemp((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setControllerTemp((float)temp2);
    case ID + 3:
      memcpy(&temp2, msg, 4);
      setV12((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setV3((float)temp2);
    case ID + 4:
      memcpy(&temp2, msg, 4);
      setMaxOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setMaxInputCurrent((float)temp2);
    case ID + 5:
      memcpy(&temp, msg + 3, 1);
      setErrorFlags(temp);
      memcpy(&temp, msg + 4, 1);
      setLimitFlags(temp);
      memcpy(&temp, msg + 5, 1);
      setMode(temp);
    case ID + 6:
      memcpy(&temp2, msg, 4);
      setBattOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setPowerConnectorTemp((float)temp2);
    default:
      return 0;
  }
  return 1;
}

float mppt::getInputVoltage() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->inputVoltage;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setInputVoltage(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->inputVoltage = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getInputCurrent() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->inputCurrent;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setInputCurrent(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->inputCurrent = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getOutputVoltage() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->outputVoltage;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setOutputVoltage(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->outputVoltage = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getOutputCurrent() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->outputCurrent;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setOutputCurrent(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->outputCurrent = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getMosfetTemp() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->mosfetTemp;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setMosfetTemp(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->mosfetTemp = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getControllerTemp() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->controllerTemp;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setControllerTemp(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->controllerTemp = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getV12() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->v12;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setV12(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->v12 = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getV3() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->v3;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setV3(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->v3 = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getMaxOutputVoltage() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->maxOutputVoltage;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setMaxOutputVoltage(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->maxOutputVoltage = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getMaxInputCurrent() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->maxInputCurrent;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setMaxInputCurrent(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->maxInputCurrent = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

uint8_t mppt::getErrorFlags() {
  pthread_mutex_lock(&this->mpptMutex);
  uint8_t val = this->errorFlags;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setErrorFlags(uint8_t val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->errorFlags = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

uint8_t mppt::getLimitFlags() {
  pthread_mutex_lock(&this->mpptMutex);
  uint8_t val = this->limitFlags;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setLimitFlags(uint8_t val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->limitFlags = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

uint8_t mppt::getMode() {
  pthread_mutex_lock(&this->mpptMutex);
  uint8_t val = this->mode;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setMode(uint8_t val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->mode = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getBattOutputVoltage() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->battOutputVoltage;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setBattOutputVoltage(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->battOutputVoltage = val;
  pthread_mutex_unlock(&this->mpptMutex);
}

float mppt::getPowerConnectorTemp() {
  pthread_mutex_lock(&this->mpptMutex);
  float val = this->powerConnectorTemp;
  pthread_mutex_unlock(&this->mpptMutex);
  return val;
}
void mppt::setPowerConnectorTemp(float val) {
  pthread_mutex_lock(&this->mpptMutex);
  this->powerConnectorTemp = val;
  pthread_mutex_unlock(&this->mpptMutex);
}
