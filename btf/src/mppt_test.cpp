#include "mppt.h"
#include <gtest/gtest.h>

TEST(MpptTest, CanAssertions) {
  Can c("vcan0");
  Mppt mppt(c);
  struct can_frame msg;
  float data = 9;
  //mppt.bus.send(MaxOutputCurrent, (uint8_t *)&data, sizeof(float));

  c.read(&msg);
  EXPECT_EQ(msg.can_id, MaxOutputCurrent);
}
