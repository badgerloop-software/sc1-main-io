#ifndef _CAN_H__
#define _CAN_H__

#include <linux/can.h>
#include <net/if.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <queue>
#include <thread>
#include <vector>

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
