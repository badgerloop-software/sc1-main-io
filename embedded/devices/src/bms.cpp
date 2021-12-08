#include "bms.h"
Bms::Bms(Can canBus) { this->canBus = canBus; }
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

  this->canBus.canSend(can_id, TxData, length);

  return 0;
}

int Bms::bmsParseMsg()  // read CAN bus
{
  struct can_frame frame;
  this->canBus.canRead(&frame);  // read CAN bus to get id
  uint32_t id = frame.can_id;
  uint8_t* msg = (frame.data);

  switch (id) {
    case 0x6B0:
      setBmsPackCurrent((msg[1] | msg[0] << 8) / 10);
      setBmsPackVoltage((msg[3] | msg[2] << 8) / 10);
      setBmsSoc(msg[4] / 2);
      setBmsRelayStatus(msg[6] | msg[5] << 8);
      setBmsCellMaxVoltage(((msg[5] << 8) | msg[6]) / 10000.0);

      break;
    case 0x6B1:
      setBmsPackDCL(msg[1] | msg[0] << 8);
      setBmsHighTemp(msg[4]);

      break;
    case 0x653:

      setBmsRelayStatus(msg[1] | msg[0] << 8);
      setBmsRelayStatus(msg[0]);
      setBmsInputVoltage((msg[2] | (msg[3] << 8)) / 10);
      break;
    case 0x652:

      setBmsPackCCL(msg[0] | (msg[1] << 8));
      setBmsPackDCL(msg[2] | (msg[3] << 8));

      break;
    case 0x651:

      setBmsMaxCells(msg[6]);
      setBmsNumCells(msg[7]);
      break;
    case 0x650:

      setBmsSoc(msg[0]);
      setBmsSoc(getBmsSoc() / 2);
      setBmsPackResistance(msg[1] | (msg[2] << 8));
      setBmsPackHealth(msg[3]);
      setBmsPackOpenVoltage((msg[4] | (msg[5] << 8)) / 10);
      setBmsPackCycles(msg[6] | (msg[7] << 8));
      break;
    case 0x150:
      setBmsPackAh(msg[4] | (msg[5] << 8));
      setBmsHighTemp(msg[6]);
      setBmsLowTemp(msg[7]);
      break;
    case 0x6b2:
      setBmsCellMinVoltage(((msg[0] << 8) | msg[1]) / 10000.0);

      setBmsAvgTemp(msg[2]);
      setBmsImdStatus(msg[3]);
      break;
    case 0x80:
      break;
    case 0x36:
      if (msg[0] >= 0 && msg[0] < 72)
        this->cells[msg[0]] = (msg[2] | (msg[1] << 8)) / 10000.0;
      break;

    default:
      return 0;
  }
  return 1;
}

float Bms::getBmsPackCurrent() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->packCurrent;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackCurrent(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packCurrent = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

float Bms::getBmsPackVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->packVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackVoltage(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

int Bms::getBmsImdStatus() {
  pthread_mutex_lock(&this->bmsMutex);
  int val = this->imdStatus;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsImdStatus(int val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->imdStatus = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsPackDCL() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->packDCL;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackDCL(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packDCL = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

int16_t Bms::getBmsPackCCL() {
  pthread_mutex_lock(&this->bmsMutex);
  int16_t val = this->packCCL;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackCCL(int16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packCCL = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsPackResistance() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->packResistance;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackResistance(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packResistance = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsPackHealth() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->packHealth;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackHealth(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packHealth = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

float Bms::getBmsPackOpenVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->packOpenVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackOpenVoltage(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packOpenVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsPackCycles() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->packCycles;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackCycles(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packCycles = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsPackAh() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->packAh;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsPackAh(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->packAh = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

float Bms::getBmsInputVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->inputVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsInputVoltage(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->inputVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsSoc() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->Soc;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsSoc(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->Soc = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsRelayStatus() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->relayStatus;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsRelayStatus(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->relayStatus = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsHighTemp() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->highTemp;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsHighTemp(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->highTemp = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsLowTemp() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->lowTemp;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsLowTemp(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->lowTemp = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsAvgTemp() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->avgTemp;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsAvgTemp(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->avgTemp = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

float Bms::getBmsCellMaxVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->cellMaxVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsCellMaxVoltage(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->cellMaxVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

float Bms::getBmsCellMinVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  float val = this->cellMinVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsCellMinVoltage(float val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->cellMinVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint16_t Bms::getBmsCellAvgVoltage() {
  pthread_mutex_lock(&this->bmsMutex);
  uint16_t val = this->cellAvgVoltage;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsCellAvgVoltage(uint16_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->cellAvgVoltage = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsMaxCells() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->maxCells;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsMaxCells(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->maxCells = val;
  pthread_mutex_unlock(&this->bmsMutex);
}

uint8_t Bms::getBmsNumCells() {
  pthread_mutex_lock(&this->bmsMutex);
  uint8_t val = this->numCells;
  pthread_mutex_unlock(&this->bmsMutex);
  return val;
}

void Bms::setBmsNumCells(uint8_t val) {
  pthread_mutex_lock(&this->bmsMutex);
  this->numCells = val;
  pthread_mutex_unlock(&this->bmsMutex);
}
