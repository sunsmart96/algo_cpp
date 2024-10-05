#include "matrix_ops_test.h"
#include "matrix_ops.h"
#include <gtest/gtest.h> // googletest header file

TEST(TEST_MATRIX, BASE_TEST) {
  auto m1 = Matrix<float>(3, 4);
  m1.set_all_value(3);

  m1.set_value_by_ij(0, 1, 10);

  EXPECT_EQ(3, m1.get_value_by_ij(0, 2));
  EXPECT_EQ(10, m1.get_value_by_ij(0, 1));
  m1.transpose();
  EXPECT_EQ(10, m1.get_value_by_ij(1, 0));

  EXPECT_EQ(4, m1.get_rows());
  EXPECT_EQ(3, m1.get_cols());

  auto m2 = Matrix<float>(4, 3);
  m2.set_all_value(2);
  auto m3 = m1 + m2;
  auto m4 = m1 - m2;

  EXPECT_EQ(5, m3.get_value_by_ij(0, 0));
  EXPECT_EQ(12, m3.get_value_by_ij(1, 0));

  EXPECT_EQ(1, m4.get_value_by_ij(0, 0));
  EXPECT_EQ(8, m4.get_value_by_ij(1, 0));

  auto m5 = m2 * 2;
  EXPECT_FLOAT_EQ(4.0, m5.get_value_by_ij(0, 0));
  m5 = m2 * 2.1;
  EXPECT_FLOAT_EQ(4.2, m5.get_value_by_ij(0, 0));
  // m1.print();
  // m2.print();
  // m3.print();
  // m4.print();
  // m5.print();
}

TEST(TEST_MATRIX, MATRIX_MUL_TEST) {
  auto m1 = Matrix<int>(2, 2);
  auto m2 = Matrix<int>(2, 2);

  m1.set_value_by_ij(0, 0, 1);
  m1.set_value_by_ij(0, 1, 2);
  m1.set_value_by_ij(1, 0, 2);
  m1.set_value_by_ij(1, 1, 3);

  m2.set_value_by_ij(0, 0, 1);
  m2.set_value_by_ij(0, 1, 2);
  m2.set_value_by_ij(1, 0, 3);
  m2.set_value_by_ij(1, 1, 3);

  auto m3 = m1.matrix_mul(m2);
  // m3.print();

  EXPECT_EQ(7, m3.get_value_by_ij(0, 0));
  EXPECT_EQ(8, m3.get_value_by_ij(0, 1));
  EXPECT_EQ(11, m3.get_value_by_ij(1, 0));
  EXPECT_EQ(13, m3.get_value_by_ij(1, 1));

  auto m4 = Matrix<int>(2, 3);
  auto m5 = Matrix<int>(3, 4);

  std::vector<int> v1 = {1, 2, 3, 2, 3, 4};
  std::vector<int> v2 = {2, 1, 3, 4, 1, 2, 3, 4, 2, 3, 4, 5};

  m4.init(v1);
  m5.init(v2);

  auto m6 = m4.matrix_mul(m5);
  EXPECT_EQ(10, m6.get_value_by_ij(0, 0));
  EXPECT_EQ(14, m6.get_value_by_ij(0, 1));
  EXPECT_EQ(31, m6.get_value_by_ij(1, 2));
  EXPECT_EQ(40, m6.get_value_by_ij(1, 3));
  // m6.print();

  std::vector<int> v3 = {1, 2, 3, 1, 2, 3};
  std::vector<int> v4 = {2, 3, 4, 4, 5, 6};

  auto m7 = Matrix<int>(2, 3);
  auto m8 = Matrix<int>(2, 3);
  m7.init(v3);
  m8.init(v4);
  m7.matrix_point_mul(m8);
  EXPECT_EQ(2, m7.get_value_by_ij(0, 0));
  EXPECT_EQ(6, m7.get_value_by_ij(0, 1));
  // m7.print();
  m7.matrix_point_div(m8);
  // m7.print();
  EXPECT_EQ(1, m7.get_value_by_ij(0, 0));
  EXPECT_EQ(2, m7.get_value_by_ij(0, 1));
}

TEST(TEST_VECTOR, BASE_TEST) {
  auto v1 = Vector<float>(10);
  v1.set_all_value(1);
  v1.set_value_by_index(2, 10);
  EXPECT_EQ(1, v1.get_element_by_index(0));
  EXPECT_EQ(10, v1.get_element_by_index(2));

  auto v2 = Vector<float>(10);
  v2.set_all_value(2.1);
  auto v3 = v1 + v2;
  EXPECT_FLOAT_EQ(3.1, v3.get_element_by_index(0));
  EXPECT_FLOAT_EQ(12.1, v3.get_element_by_index(2));

  Vector<float> v4 = v3 - v2;
  EXPECT_FLOAT_EQ(1.0, v4.get_element_by_index(0));
  EXPECT_FLOAT_EQ(10.0, v4.get_element_by_index(2));

  v1.point_mul(v2);
  EXPECT_FLOAT_EQ(2.1, v1.get_element_by_index(0));
  EXPECT_FLOAT_EQ(21.0, v1.get_element_by_index(2));

  v1.point_div(v2);
  EXPECT_FLOAT_EQ(1.0, v1.get_element_by_index(0));
  EXPECT_FLOAT_EQ(10.0, v1.get_element_by_index(2));

  EXPECT_FLOAT_EQ(109.0, v1 * v4);

  v1.saxpy(v2, 2.1);

  EXPECT_FLOAT_EQ(5.41, v1.get_element_by_index(0));
  EXPECT_FLOAT_EQ(14.41, v1.get_element_by_index(2));
}