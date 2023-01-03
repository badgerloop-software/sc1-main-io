#ifndef __LOG_PRINTER_H__
#define __LOG_PRINTER_H__

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <string>

#include "gtest/gtest.h"

using testing::EmptyTestEventListener;
using testing::TestCase;
using testing::UnitTest;

class LogPrinter : public EmptyTestEventListener {
  struct Log {
    std::string TestName;
    std::string STDOUT;
    std::string STDERR;
  };
  std::vector<Log> Logs;

 public:
  virtual void OnTestProgramEnd(const UnitTest &unit_test);
  virtual void OnTestStart(const testing::TestInfo &test_info);
  virtual void OnTestEnd(const testing::TestInfo &test_info);
};

#endif
