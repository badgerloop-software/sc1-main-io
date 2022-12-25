#ifndef __CAN_H__
#define __CAN_H__

#include <linux/can.h>
#include <stdint.h>

#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

using std::function;
using std::lock_guard;
using std::mutex;
using std::pair;
using std::thread;
using std::unordered_map;
using std::vector;

typedef pair<int, function<void(struct can_frame &)>> callback;

template <typename T>
struct mutexVar {
 private:
  mutex mu;
  T value = -1;

 public:
  void setValue(T data) {
    lock_guard<mutex> l(mu);
    value = data;
  }
  T getValue(void) {
    lock_guard<mutex> l(mu);
    return value;
  }
};

class CanDevice;

class Can {
 private:
  unordered_map<int, function<void(struct can_frame &)>> callback_map;
  mutex mu;
  thread t;
  const char *can_i;
  int sock;
  bool isInit = false;
  void loop();
  int read(struct can_frame &msg);

 public:
  Can(const char *can_i);
  ~Can();
  void add(vector<callback> &callbacks);
  int send(int id, uint8_t *data, uint8_t size);
  int init();
};

class CanDevice {
 private:
  mutex mu;

 public:
  CanDevice(Can &bus, vector<callback> &callbacks) : bus(bus) {
    bus.add(callbacks);
  }
  Can &bus;
};

#endif
