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

  vector<callback> bms_callbacks{
      {0x6B0,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         packCurrent.setValue((msg[1] | msg[0] << 8) / 10);
         packVoltage.setValue((msg[3] | msg[2] << 8) / 10);
         Soc.setValue(msg[4] / 2);
         relayStatus.setValue(msg[6] | msg[5] << 8);
         cellMaxVoltage.setValue(((msg[5] << 8) | msg[6]) / 10000.0);
       }},
      {0x6B1,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         packDCL.setValue(msg[1] | msg[0] << 8);
         highTemp.setValue(msg[4]);
       }},
      {0x653,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         relayStatus.setValue(msg[1] | msg[0] << 8);
         relayStatus.setValue(msg[0]);
         inputVoltage.setValue((msg[2] | (msg[3] << 8)) / 10);
       }},
      {0x652,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         packCCL.setValue(msg[0] | (msg[1] << 8));
         packDCL.setValue(msg[2] | (msg[3] << 8));
       }},
      {0x651,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         maxCells.setValue(msg[6]);
         numCells.setValue(msg[7]);
       }},
      {0x650,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         Soc.setValue(msg[0]);
         Soc.setValue(Soc.getValue() / 2);
         packResistance.setValue(msg[1] | (msg[2] << 8));
         packHealth.setValue(msg[3]);
         packOpenVoltage.setValue((msg[4] | (msg[5] << 8)) / 10);
         packCycles.setValue(msg[6] | (msg[7] << 8));
       }},
      {0x150,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         packAh.setValue(msg[4] | (msg[5] << 8));
         highTemp.setValue(msg[6]);
         lowTemp.setValue(msg[7]);
       }},
      {0x6b2,
       [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         cellMinVoltage.setValue(((msg[0] << 8) | msg[1]) / 10000.0);
         avgTemp.setValue(msg[2]);
         imdStatus.setValue(msg[3]);
       }},
      {0x36, [this](struct can_frame &frame) {
         char *msg = (char *)frame.data;
         if (msg[0] >= 0 && msg[0] < 72)
           cells[msg[0]] = (msg[2] | (msg[1] << 8)) / 10000.0;
       }}};

 public:
  Bms(Can &bus);
  int bmsClearFaults(void);  // write function
  int bmsParseMsg();         // read function
};
