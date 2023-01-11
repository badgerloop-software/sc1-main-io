#include "gpio.h"

#include <gtest/gtest.h>
#include <unistd.h>

class GpioTest : public testing::Test {
 protected:
  const string sim = "/sys/devices/platform/gpio-sim.0";

  const string chip0 = sim + "/gpiochip0";
  const string chip1 = sim + "/gpiochip1";

  const string line0 = chip0 + "/sim_gpio0";
  const string line1 = chip0 + "/sim_gpio1";
  const string line2 = chip0 + "/sim_gpio2";

  const string line31 = chip0 + "/sim_gpio31";
  const string line32 = chip1 + "/sim_gpio0";

  const string line62 = chip1 + "/sim_gpio62";
  const string line63 = chip1 + "/sim_gpio63";

  void _getValue(const string &path, char &value) {
    int fd = open(path.c_str(), O_RDONLY);
    EXPECT_FALSE(fd < 0);
    read(fd, &value, sizeof(value));
    close(fd);
  }

 public:
  GpioTest() : DUT({"/dev/gpiochip0", "/dev/gpiochip1"}) {}
  Gpio DUT;
};

TEST_F(GpioTest, gpio_sim) {
  EXPECT_EQ(DUT.begin(), 0);
  Gpio::Pin p0 = Gpio::Pin(DUT, 0, GPIOHANDLE_REQUEST_OUTPUT);
  Gpio::Pin p62 = Gpio::Pin(DUT, 62, GPIOHANDLE_REQUEST_INPUT);
  Gpio::Pin p63 = Gpio::Pin(DUT, 63, GPIOHANDLE_REQUEST_INPUT);

  char value;

  EXPECT_EQ(DUT.setValue(p0, 1), 0);
  _getValue(line0 + "/value", value);
  EXPECT_EQ(value, '1');

  EXPECT_EQ(DUT.setValue(p0, 0), 0);
  _getValue(line0 + "/value", value);
  EXPECT_EQ(value, '0');

  bool input;

  EXPECT_EQ(DUT.getValue(p62, input), 0);
  EXPECT_EQ(input, 1);

  EXPECT_EQ(DUT.getValue(p63, input), 0);
  EXPECT_EQ(input, 0);
}
