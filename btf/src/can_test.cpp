#include <gtest/gtest.h>
#include <sys/wait.h>
#include <unistd.h>

#include "mppt.h"

class CanTest : public testing::Test {
 private:
  Can c;
  CanDevice d;

 protected:
  uint32_t i;
  float f;
  Can DUTbus;
  CanTest()
      : c("vcan0"),
        DUTbus("vcan0"),
        d(c,
          {
              {0x21,
               [this](struct can_frame &frame) {
                 i = *(uint32_t *)frame.data;
               }},
              {0x39, [this](struct can_frame &frame) { i = 0x1234; }},

              {MaxOutputCurrent,
               [this](struct can_frame &frame) { f = *(float *)frame.data; }},

          }) {}
  void SetUp() override { EXPECT_EQ(c.init(), 0); }
};

TEST_F(CanTest, callbacks) {
  EXPECT_EQ(DUTbus.init(), 0);

  uint32_t data = 0xDEADBEEF;
  i = 0;
  DUTbus.send(0x21, (uint8_t *)&data, sizeof(data));

  while (!i && !DUTbus.init())
    ;

  EXPECT_EQ(i, 0xDEADBEEF);
  i = 0;

  DUTbus.send(0x39, (uint8_t *)&data, sizeof(data));
  while (!i && !DUTbus.init())
    ;
  EXPECT_EQ(i, 0x1234);
}

TEST_F(CanTest, mppt) {
  Mppt DUT(DUTbus);

  f = 0;
  float data = 2321.442;
  DUT.sendMaxOutputCurrent(data);

  while (!f && !DUTbus.init())
    ;
  EXPECT_EQ(f, data);
}
