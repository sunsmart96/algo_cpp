#include <gtest/gtest.h>  // googletest header file

#include <iostream>
#include <string>

using namespace std;
using std::string;

const char *actualValTrue = "hello gtest";
const char *expectVal = "hello gtest";

TEST(StrCompare, CStrEqual) { EXPECT_STREQ(expectVal, actualValTrue); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
