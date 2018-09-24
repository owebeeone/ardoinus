#ifndef SETL_TEST_FRAMEWORK__H
#define SETL_TEST_FRAMEWORK__H

// WARNING - Only include this header in test executables. Do not include
// in production binaries.

#include "setl_utils.h"

#include "setlx_cassert.h"

namespace setl_test {

class SetlTest;

class TestRegister : setl::not_copyable {
public:
  static const unsigned MAX_TESTS = 40;

  static TestRegister& getRegister() {
    static TestRegister testRegister;
    return testRegister;
  }

  void registerTest(SetlTest * test) {
    // TODO: Provide a registry of tests and their result.
    if (count < MAX_TESTS) {
      test_registry[count++] = test;
    } else {
      assert(false);
    }
  }

  ~TestRegister() {
    assert(count > 0);
    assert(count == success);
  }

  void run();
  
  unsigned count = 0;
  unsigned success = 0;
  SetlTest* test_registry[MAX_TESTS];
};


class SetlTest : setl::not_copyable {
public:
  SetlTest() {
    TestRegister::getRegister().registerTest(this);
  }

  virtual ~SetlTest() {}

  virtual bool run() = 0;
};

inline void TestRegister::run() {
  for (unsigned i = 0; i < count; ++i) {
    if (test_registry[i]->run()) {
      ++success;
    }
  }
}

unsigned runAllTests() {
  TestRegister::getRegister().run();
  return TestRegister::getRegister().success;
}

}

#endif