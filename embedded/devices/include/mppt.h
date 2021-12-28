#include <linux/can.h>
#include <pthread.h>

#include "can.h"

class Mppt {  // Mppt = Maximum Power Point Tracking. MPPT optimizes voltage
              // conversion between solar array and battery to minimize power
              // loss.
 private:
  Can canBus;

  pthread_mutex_t MpptMutex;
  float inputVoltage;
  float inputCurrent;
  float outputVoltage;
  float outputCurrent;
  float mosfetTemp;
  float controllerTemp;
  float v12;
  float v3;
  float maxOutputVoltage;
  float maxInputCurrent;

  uint8_t errorFlags;
  uint8_t limitFlags;
  uint8_t mode;

  float battOutputVoltage;
  float powerConnectorTemp;

 public:
  Mppt(Can canBus);
  int MpptParseMsg();

  int sendMode(uint8_t mode);
  int sendMaxOutputVoltage(float maxOutputVoltage);
  int sendMaxInputCurrent(float maxInputCurrent);

  float getInputVoltage();
  void setInputVoltage(float val);

  float getInputCurrent();
  void setInputCurrent(float val);

  float getOutputVoltage();
  void setOutputVoltage(float val);

  float getOutputCurrent();
  void setOutputCurrent(float val);

  float getMosfetTemp();
  void setMosfetTemp(float val);

  float getControllerTemp();
  void setControllerTemp(float val);

  float getV12();
  void setV12(float val);

  float getV3();
  void setV3(float val);

  float getMaxOutputVoltage();
  void setMaxOutputVoltage(float val);

  float getMaxInputCurrent();
  void setMaxInputCurrent(float val);

  uint8_t getErrorFlags();
  void setErrorFlags(uint8_t val);

  uint8_t getLimitFlags();
  void setLimitFlags(uint8_t val);

  uint8_t getMode();
  void setMode(uint8_t val);

  float getBattOutputVoltage();
  void setBattOutputVoltage(float val);

  float getPowerConnectorTemp();
  void setPowerConnectorTemp(float val);
};
