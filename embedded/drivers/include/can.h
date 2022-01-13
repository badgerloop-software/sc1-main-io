#ifndef __CAN_H__
#define __CAN_H__

#include <linux/can.h>
#include <pthread.h>
#include <stdint.h>

class Can {
 private:
  int sock;
  pthread_mutex_t canMutex;

 public:
  Can();
  int init();
  int canRead(struct can_frame *msg);
  int canSend(uint16_t id, uint8_t *data, int size);
};

#endif
