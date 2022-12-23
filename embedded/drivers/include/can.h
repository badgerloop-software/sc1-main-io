#ifndef __CAN_H__
#define __CAN_H__

#include <linux/can.h>
#include <stdint.h>

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

using std::condition_variable;
using std::lock_guard;
using std::mutex;
using std::queue;
using std::thread;  // for iterating over devices
using std::unique_lock;
using std::vector;  // for frames

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
  vector<CanDevice *> devices;
  mutex mu;
  thread t;
  const char *can_i;
  int sock;
  bool isInit = false;
  void loop();

 public:
  Can(const char *can_i);
  ~Can();
  void add(CanDevice *c);
  int read(struct can_frame &msg);
  int send(int id, uint8_t *data, uint8_t size);
  int init();
};

class CanDevice {
 private:
  mutex mu;
  condition_variable cv;
  queue<struct can_frame> frames;

 public:
  CanDevice(Can &bus) : bus(bus) { bus.add(this); }
  Can &bus;

  /*
  You are responsible for implementing
  this method to add messages to frames.
  Return 0 if the message belongs to you, -1 otherwise.
  */
  virtual int parse(struct can_frame &msg) = 0;

  void pop(struct can_frame &msg) {
    unique_lock<mutex> l(mu);
    cv.wait(l, [this] { return !frames.empty(); });
    msg = frames.front();
    frames.pop();
  }
  void push(struct can_frame &msg) {
    lock_guard<mutex> l(mu);
    frames.push(msg);
    cv.notify_one();
  }
};

#endif
