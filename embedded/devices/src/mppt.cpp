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
      setInputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setInputCurrent((float)temp2);
    case MPPT_BASE_ID + 1:
      memcpy(&temp2, msg, 4);
      setOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setOutputCurrent((float)temp2);
    case MPPT_BASE_ID + 2:
      memcpy(&temp2, msg, 4);
      setMosfetTemp((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setControllerTemp((float)temp2);
    case MPPT_BASE_ID + 3:
      memcpy(&temp2, msg, 4);
      setV12((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setV3((float)temp2);
    case MPPT_BASE_ID + 4:
      memcpy(&temp2, msg, 4);
      setMaxOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setMaxInputCurrent((float)temp2);
    case MPPT_BASE_ID + 5:
      memcpy(&temp, msg + 3, 1);
      setErrorFlags(temp);
      memcpy(&temp, msg + 4, 1);
      setLimitFlags(temp);
      memcpy(&temp, msg + 5, 1);
      setMode(temp);
    case MPPT_BASE_ID + 6:
      memcpy(&temp2, msg, 4);
      setBattOutputVoltage((float)temp2);
      memcpy(&temp2, msg + 4, 4);
      setPowerConnectorTemp((float)temp2);
    default:
      return 0;
  }
  return 1;
}

float Mppt::getInputVoltage() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->inputVoltage;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setInputVoltage(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->inputVoltage = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getInputCurrent() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->inputCurrent;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setInputCurrent(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->inputCurrent = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getOutputVoltage() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->outputVoltage;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setOutputVoltage(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->outputVoltage = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getOutputCurrent() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->outputCurrent;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setOutputCurrent(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->outputCurrent = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getMosfetTemp() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->mosfetTemp;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setMosfetTemp(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->mosfetTemp = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getControllerTemp() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->controllerTemp;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setControllerTemp(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->controllerTemp = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getV12() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->v12;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setV12(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->v12 = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getV3() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->v3;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setV3(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->v3 = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getMaxOutputVoltage() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->maxOutputVoltage;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setMaxOutputVoltage(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->maxOutputVoltage = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getMaxInputCurrent() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->maxInputCurrent;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setMaxInputCurrent(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->maxInputCurrent = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

uint8_t Mppt::getErrorFlags() {
  pthread_mutex_lock(&this->MpptMutex);
  uint8_t val = this->errorFlags;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setErrorFlags(uint8_t val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->errorFlags = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

uint8_t Mppt::getLimitFlags() {
  pthread_mutex_lock(&this->MpptMutex);
  uint8_t val = this->limitFlags;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setLimitFlags(uint8_t val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->limitFlags = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

uint8_t Mppt::getMode() {
  pthread_mutex_lock(&this->MpptMutex);
  uint8_t val = this->mode;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setMode(uint8_t val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->mode = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getBattOutputVoltage() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->battOutputVoltage;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setBattOutputVoltage(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->battOutputVoltage = val;
  pthread_mutex_unlock(&this->MpptMutex);
}

float Mppt::getPowerConnectorTemp() {
  pthread_mutex_lock(&this->MpptMutex);
  float val = this->powerConnectorTemp;
  pthread_mutex_unlock(&this->MpptMutex);
  return val;
}
void Mppt::setPowerConnectorTemp(float val) {
  pthread_mutex_lock(&this->MpptMutex);
  this->powerConnectorTemp = val;
  pthread_mutex_unlock(&this->MpptMutex);
}
