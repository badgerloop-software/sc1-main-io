#include <gtest/gtest.h>

#include "LogPrinter.h"

char executable_path[128];
// Run all GTest Tests
int main(int argc, char **argv) {
  // Set executable path
  strcpy(executable_path, argv[0]);

  testing::InitGoogleTest(&argc, argv);

  testing::UnitTest &unit_test = *testing::UnitTest::GetInstance();
  testing::TestEventListeners &listeners = unit_test.listeners();

  listeners.Append(new LogPrinter);  // has to be on heap
                                     // implicitly calls free()
  return RUN_ALL_TESTS();
}
