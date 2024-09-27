#include "algo_test.h"

#include <gtest/gtest.h> // googletest header file

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

// test binary search algorithm
TEST(TEST_BINARY_SEARCH, binary_search) {
  std::vector<int> v = {1, 2, 3, 3, 4, 5, 6, 9, 12};

  auto res1 = binary_search(v, 1);
  auto res2 = binary_search(v, 12);
  auto res3 = binary_search(v, 3);
  auto res4 = binary_search(v, 7);

  EXPECT_EQ(0, res1.index);
  EXPECT_EQ(true, res1.is_found);

  EXPECT_EQ(8, res2.index);
  EXPECT_EQ(true, res2.is_found);

  EXPECT_EQ(2, res3.index);
  EXPECT_EQ(true, res3.is_found);

  EXPECT_EQ(0, res4.index);
  EXPECT_EQ(false, res4.is_found);
}

// test Bag data structure
TEST(TEST_BAG, base_test) {
  auto bag = Bag<double>();
  EXPECT_EQ(0, bag.size());
  EXPECT_EQ(true, bag.is_empty());

  bag.add(1.2);
  EXPECT_EQ(1, bag.size());
  EXPECT_EQ(false, bag.is_empty());
  bag.add(1.8);

  double s = 0;
  for (auto x : bag)
    s = s + x;

  EXPECT_EQ(3.0, s);
}

int run_all_tests(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}