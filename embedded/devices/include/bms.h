#include <linux/can.h>
#include <pthread.h>

#include "can.h"
#define NUM_CELLS 30

class Bms {
 private:
  Can canBus;
  float cells[NUM_CELLS];
  pthread_mutex_t bmsMutex;
  float packCurrent;
  float packVoltage;
  int imdStatus;
  uint16_t packDCL;
  int16_t packCCL;
  uint16_t packResistance;
  uint8_t packHealth;
  float packOpenVoltage;
  uint16_t packCycles;
  uint16_t packAh;
  float inputVoltage;
  uint8_t Soc;
  uint16_t relayStatus;
  uint8_t highTemp;
  uint8_t lowTemp;
  uint8_t avgTemp;
  float cellMaxVoltage;
  float cellMinVoltage;
  uint16_t cellAvgVoltage;
  uint8_t maxCells;
  uint8_t numCells;

 public:
  Bms(Can canBus);
  int bmsClearFaults(void);  // write function
  int bmsParseMsg();         // read function

  float getBmsPackCurrent();
  void setBmsPackCurrent(float val);

  float getBmsPackVoltage();
  void setBmsPackVoltage(float val);

  int getBmsImdStatus();
  void setBmsImdStatus(int val);

  uint16_t getBmsPackDCL();
  void setBmsPackDCL(uint16_t val);

  int16_t getBmsPackCCL();
  void setBmsPackCCL(int16_t val);

  uint16_t getBmsPackResistance();
  void setBmsPackResistance(uint16_t val);

  uint8_t getBmsPackHealth();
  void setBmsPackHealth(uint8_t val);

  float getBmsPackOpenVoltage();
  void setBmsPackOpenVoltage(float val);

  uint16_t getBmsPackCycles();
  void setBmsPackCycles(uint16_t val);

  uint16_t getBmsPackAh();
  void setBmsPackAh(uint16_t val);

  float getBmsInputVoltage();
  void setBmsInputVoltage(float val);

  uint8_t getBmsSoc();
  void setBmsSoc(uint8_t val);

  uint16_t getBmsRelayStatus();
  void setBmsRelayStatus(uint16_t val);

  uint8_t getBmsHighTemp();
  void setBmsHighTemp(uint8_t val);

  uint8_t getBmsLowTemp();
  void setBmsLowTemp(uint8_t val);

  uint8_t getBmsAvgTemp();
  void setBmsAvgTemp(uint8_t val);

  float getBmsCellMaxVoltage();
  void setBmsCellMaxVoltage(float val);

  float getBmsCellMinVoltage();
  void setBmsCellMinVoltage(float val);

  uint16_t getBmsCellAvgVoltage();
  void setBmsCellAvgVoltage(uint16_t val);

  uint8_t getBmsMaxCells();
  void setBmsMaxCells(uint8_t val);

  uint8_t getBmsNumCells();
  void setBmsNumCells(uint8_t val);
};
