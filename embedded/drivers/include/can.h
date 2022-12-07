#ifndef __CAN_H__
#define __CAN_H__

#include <linux/can.h>
#include <pthread.h>
#include <stdint.h>

template <typename T>
struct mutexVar {
 private:
  pthread_mutex_t mutex;
  T value = -1;

 public:
  /* volatile cannot be memcpy'd
   * so memcpy to a tmp var
   * then set the volatile
   */
  void setValue(T data) {
    pthread_mutex_lock(&mutex);
    value = data;
    pthread_mutex_unlock(&mutex);
  }
  /* reading a variable
   * doesn't require a
   * mutex lock and unlock
   *
   * but the value is private
   * so it can only be changed
   * via setValue, utilizing the mutex
   */
  T getValue(void) {
    T data;
    pthread_mutex_lock(&mutex);
    data = value;
    pthread_mutex_unlock(&mutex);
    return data;
  }
};

class Can {
 private:
  int sock;
  bool isInit = false;
  pthread_mutex_t canMutex;

 public:
  Can() {};
  int init();
  int canRead(struct can_frame *msg);
  int canSend(uint16_t id, uint8_t *data, int size);
};

#endif
