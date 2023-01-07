#include "gpio.h"

#include <gtest/gtest.h>

class GpioTest : public testing::Test {
 public:
  GpioTest() : a({"/dev/gpiochip0"}) {}
  Gpio a;
};

TEST_F(GpioTest, mockup) {
  // EXPECT_EQ(a.begin(), 0);
  // io_req req;
  // a.mark_pin(req, 0, 1);
  // EXPECT_EQ(a.Io(req), 0);
}
