#include "gpio.h"

#include <gtest/gtest.h>

class GpioTest : public testing::Test {
 public:
  GpioTest() : a("/dev/gpiochip0") {}
  Gpio a;
};

TEST_F(GpioTest, mockup) {
  bool reads[3];

  EXPECT_EQ(a.begin(), 0);
  EXPECT_EQ(a.write({{0, 1}}, "TEST_REQUEST\0"), 0);
  EXPECT_EQ(a.write({{0, 1}}, "TEST_REQUEST\0"), 0);
}
