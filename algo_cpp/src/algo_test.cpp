#include "algo_test.h"

#include <gtest/gtest.h> // googletest header file

#include "algo.h"

// gtest example
const char *actualValTrue = "hello gtest";
const char *expectVal = "hello gtest";
TEST(StrCompare, CStrEqual) { EXPECT_STREQ(expectVal, actualValTrue); }

// test gcd algorithm
TEST(TESTGCD, GCD_BASE1) {
  EXPECT_EQ(10, gcd(10, 10));
  EXPECT_EQ(1, gcd(1, 10));
}

TEST(TESTGCD, GCD_BASE2) {
  EXPECT_EQ(1, gcd(10, 3));
  EXPECT_EQ(2, gcd(10, 2));
}

// test binary search algorithm
TEST(TEST_BINARY_SEARCH, BINARY_SEARCH) {
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
TEST(TEST_BAG, BASE_TEST) {
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

TEST(TEST_FIFO_QUEUE, BASE_TEST) {
  auto n1 = std::make_shared<Node<int>>(1);
  auto n2 = std::make_shared<Node<int>>(2);
  auto n3 = std::make_shared<Node<int>>(3);

  auto q = std::make_shared<FIFO_QUEUE<Node<int>>>();
  q->enqueue(n1);
  q->enqueue(n2);
  q->enqueue(n3);

  EXPECT_EQ(3, q->size());

  // q->print();

  auto x = q->dequeue();

  EXPECT_EQ(3, x.get()->value);

  EXPECT_EQ(2, q->size());
}

int run_all_tests(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}