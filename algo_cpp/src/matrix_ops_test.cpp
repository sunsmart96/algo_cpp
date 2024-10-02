#include "matrix_ops_test.h"
#include "matrix_ops.h"
#include <gtest/gtest.h> // googletest header file

TEST(TEST_MATRIX, BASE_TEST) {
  EXPECT_EQ(3, 3);
  auto m = Matrix<int>(3, 3);
  m.set_all_value(3);
  // m.print();
  m.set_value_by_ij(0, 1, 10);
  // m.print();
  EXPECT_EQ(3, m.get_value_by_ij(0, 2));
  EXPECT_EQ(10, m.get_value_by_ij(0, 1));
  m.transpose();
  EXPECT_EQ(10, m.get_value_by_ij(1, 0));
  // m.print();
}