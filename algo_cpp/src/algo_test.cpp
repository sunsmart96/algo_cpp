#include "algo_test.h"

#include <gtest/gtest.h>  // googletest header file

#include "algo.h"

// gtest example
const char *actualValTrue = "hello gtest";
const char *expectVal = "hello gtest";
TEST(StrCompare, CStrEqual) { EXPECT_STREQ(expectVal, actualValTrue); }

// test gcd algorithm
TEST(TESTGCD, gcd_base1) {
  EXPECT_EQ(10, gcd(10, 10));
  EXPECT_EQ(1, gcd(1, 10));
}

TEST(TESTGCD, gcd_base2) {
  EXPECT_EQ(1, gcd(10, 3));
  EXPECT_EQ(2, gcd(10, 2));
}

int run_all_tests(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}