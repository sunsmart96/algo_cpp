#include "algo.h"
#include "algo_test.h"
#include <gtest/gtest.h> // googletest header file
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using std::string;

int run_all_tests(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

int main(int argc, char **argv) { run_all_tests(argc, argv); }
