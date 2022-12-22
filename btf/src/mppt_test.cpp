#include <gtest/gtest.h>
#include "mppt.h"

TEST(MpptTest, CanAssertions) {
  Can c("vcan0");
  Mppt mppt(c);
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
