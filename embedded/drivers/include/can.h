#ifndef _CAN_H__
#define _CAN_H__

#include <linux/can.h>  // for can_frame (ptr only), sockaddr_can
#include <net/if.h>     // for ifreq
#include <semaphore.h>  // for sem_t
#include <stdint.h>     // for uint32_t, uint8_t

#include <queue>   // for queue
#include <thread>  // for thread
#include <vector>  // for vector

#define NO_FILTER 0

#ifdef USE_VCAN
#define CAN_INTF "vcan0"
#else
#define CAN_INTF "can0"
#endif

class CAN;
class CANDevice;

class CANDevice {
 private:
  std::thread canDeviceThread;
  void canDeviceLoop();

 public:
  std::queue<can_frame*> messages;
  CAN* can;
  virtual int parser(uint32_t id, uint8_t* data, uint32_t filter) = 0;
  virtual int validMsg(can_frame* can_mesg) = 0;
  virtual int begin();

  CANDevice(CAN* c);
  virtual ~CANDevice() {}
};

class CAN {
 private:
  struct sockaddr_can addr;
  struct ifreq ifr;
  int socket;
  std::thread canThread;
  void canLoop();

 public:
  sem_t canSem;
  CAN() {}
  std::vector<CANDevice*> devices;
  int begin();
  int canRead(struct can_frame* can_mesg);
  int canSend(uint32_t id, uint8_t* data, uint8_t size);
};

#endif
