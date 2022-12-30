#include "can.h"

#include <gtest/gtest.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mppt.h"

static Can s("vcan0");
static Can r("vcan0");

TEST(Can, callbacks) {
  volatile uint32_t flag = 0;
  vector<callback> callbacks{
      {0x21,
       [&flag](struct can_frame &frame) { flag = *(uint32_t *)frame.data; }},
      {0x39, [&flag](struct can_frame &frame) { flag = 0x1234; }},
  };

  assert(callbacks.size());

  CanDevice cd(r, callbacks);

  assert(!callbacks.size());

  EXPECT_EQ(s.init(), 0);
  EXPECT_EQ(r.init(), 0);

  uint32_t data = 0xDEADBEEF;
  s.send(0x21, (uint8_t *)&data, sizeof(data));

  while (!flag && !s.init() && !r.init())
    ;

  EXPECT_EQ(flag, 0xDEADBEEF);
  flag = 0;

  s.send(0x39, (uint8_t *)&data, sizeof(data));
  while (!flag && !s.init() && !r.init())
    ;
  EXPECT_EQ(flag, 0x1234);
}

TEST(Can, mppt) {
  volatile float flag = 0;
  volatile bool done = 0;
  struct can_frame msg;
  Mppt m(s);

  // make can device to read message from MPPT
  vector<callback> callbacks{
      {MaxOutputCurrent,
       [&flag, &done](struct can_frame &frame) {
         flag = *(float *)frame.data;
         done = true;
       }},
  };
  CanDevice cd(r, callbacks);

  float data = 2321.442;
  m.sendMaxOutputCurrent(data);

  while (!flag && !s.init() && !r.init())
    ;
  EXPECT_EQ(flag, data);
}
