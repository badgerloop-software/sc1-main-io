#include "mppt.h"

#include <gtest/gtest.h>
#include <sys/wait.h>
#include <unistd.h>

static Can s("vcan0");
static Can r("vcan0");

TEST(MpptTest, QueueTest) {
  EXPECT_EQ(s.init(), 0);
  EXPECT_EQ(r.init(), 0);

  Mppt m(r);
  struct can_frame msg;

  int pid = fork();
  if (pid == 0) {
    uint32_t data = 0xDEADBEEF;
    usleep(50000);
    s.send(0x69, (uint8_t *)&data, sizeof(data));
    data = 0xF00DB00F;
    usleep(100000);
    s.send(0x69, (uint8_t *)&data, sizeof(data));
    exit(0);
  }
  m.pop(msg);
  EXPECT_EQ(msg.can_id, 0x69);
  EXPECT_EQ(*(uint32_t *)msg.data, 0xDEADBEEF);
  m.pop(msg);
  EXPECT_EQ(msg.can_id, 0x69);
  EXPECT_EQ(*(uint32_t *)msg.data, 0xF00DB00F);
}
