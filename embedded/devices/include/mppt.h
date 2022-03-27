#include <linux/can.h>
#include <pthread.h>

#include "can.h"

class Mppt {  // Mppt = Maximum Power Point Tracking. MPPT optimizes voltage
              // conversion between solar array and battery to minimize power
              // loss.
 private:
  Can* canBus;
  pthread_mutex_t MpptMutex;
  mutexVar<float> inputVoltage;
  mutexVar<float> inputCurrent;
  mutexVar<float> outputVoltage;
  mutexVar<float> outputCurrent;
  mutexVar<float> mosfetTemp;
  mutexVar<float> controllerTemp;
  mutexVar<float> v12;
  mutexVar<float> v3;
  mutexVar<float> maxOutputVoltage;
  mutexVar<float> maxInputCurrent;

  mutexVar<uint8_t> errorFlags;
  mutexVar<uint8_t> limitFlags;
  mutexVar<uint8_t> mode;

  mutexVar<float> battOutputVoltage;
  mutexVar<float> powerConnectorTemp;

 public:
  Mppt(Can* canBus);
  int MpptParseMsg();

  int sendMode(uint8_t mode);
  int sendMaxOutputVoltage(float maxOutputVoltage);
  int sendMaxInputCurrent(float maxInputCurrent);
};
