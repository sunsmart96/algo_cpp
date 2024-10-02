#include "matrix_ops_test.h"
#include "matrix_ops.h"
#include <gtest/gtest.h> // googletest header file

TEST(TEST_MATRIX, BASE_TEST) {
  auto m1 = Matrix<int>(3, 4);
  m1.set_all_value(3);
  // m.print();
  m1.set_value_by_ij(0, 1, 10);
  // m.print();
  EXPECT_EQ(3, m1.get_value_by_ij(0, 2));
  EXPECT_EQ(10, m1.get_value_by_ij(0, 1));
  m1.transpose();
  EXPECT_EQ(10, m1.get_value_by_ij(1, 0));

  EXPECT_EQ(4, m1.get_rows());
  EXPECT_EQ(3, m1.get_cols());

  auto m2 = Matrix<int>(4, 3);
  m2.set_all_value(2);
  auto m3 = m1 + m2;
  auto m4 = m1 - m2;

  EXPECT_EQ(5, m3.get_value_by_ij(0, 0));
  EXPECT_EQ(12, m3.get_value_by_ij(1, 0));

  EXPECT_EQ(1, m4.get_value_by_ij(0, 0));
  EXPECT_EQ(8, m4.get_value_by_ij(1, 0));

  // m3.print();
  // m4.print();
}