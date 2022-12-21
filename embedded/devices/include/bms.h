#include "can.h"
#define NUM_CELLS 30

class Bms : CanDevice {
 private:
  float cells[NUM_CELLS];
  mutex bmsMutex;
  mutexVar<float> packCurrent;
  mutexVar<float> packVoltage;
  mutexVar<int> imdStatus;
  mutexVar<uint16_t> packDCL;
  mutexVar<int16_t> packCCL;
  mutexVar<uint16_t> packResistance;
  mutexVar<uint8_t> packHealth;
  mutexVar<float> packOpenVoltage;
  mutexVar<uint16_t> packCycles;
  mutexVar<uint16_t> packAh;
  mutexVar<float> inputVoltage;
  mutexVar<uint8_t> Soc;
  mutexVar<uint16_t> relayStatus;
  mutexVar<uint8_t> highTemp;
  mutexVar<uint8_t> lowTemp;
  mutexVar<uint8_t> avgTemp;
  mutexVar<float> cellMaxVoltage;
  mutexVar<float> cellMinVoltage;
  mutexVar<uint16_t> cellAvgVoltage;
  mutexVar<uint8_t> maxCells;
  mutexVar<uint8_t> numCells;

 public:
  Bms(Can &bus);
  int bmsClearFaults(void);  // write function
  int bmsParseMsg();         // read function
};
