#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <cassert>
#include <cmath>
#include <memory>
#include <vector>

const double EPS = 1e-9;

enum class Gaxpy_Class {
  ROW_ORIENTED,
  COLUMN_ORIENTED

};

template <typename T> void Matrix_Deleter(T **ptr, size_t rows) {
  for (int i = 0; i < rows; ++i) {
    delete[] ptr[i];
  }
  delete[] ptr;
}

template <typename T> class Matrix {
public:
  Matrix(size_t rows, size_t cols) {
    this->cols = cols;
    this->rows = rows;

    std::shared_ptr<T *> p_2d_array(
        new T *[rows], [rows](T **ptr) { Matrix_Deleter(ptr, rows); });

    this->p = p_2d_array;
    for (int i = 0; i < rows; ++i) {
      this->p.get()[i] = new T[cols];
    }

    this->set_all_value(0);
  }

  void init(const std::vector<T> &v) {
    assert(this->rows * this->cols == v.size());
    for (size_t i = 0; i < this->rows; ++i) {
      for (size_t j = 0; j < this->cols; ++j) {
        this->p.get()[i][j] = v[i * this->cols + j];
      }
    }
  }

  void set_all_value(T value) {
    for (size_t i = 0; i < this->rows; i++) {
      for (size_t j = 0; j < this->cols; j++) {
        this->p.get()[i][j] = value;
      }
    }
  }

  void print() const {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        std::cout << this->p.get()[i][j] << "   ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void set_value_by_ij(size_t i, size_t j, T value) {
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);

    this->p.get()[i][j] = value;
  }

  T get_value_by_ij(size_t i, size_t j) const {
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);
    return this->p.get()[i][j];
  }

  void transpose() {
    size_t new_rows = this->cols;
    size_t new_cols = this->rows;
    std::shared_ptr<T *> new_p(new T *[new_rows], [new_rows](T **ptr) {
      Matrix_Deleter(ptr, new_rows);
    });

    for (int i = 0; i < new_rows; ++i) {
      new_p.get()[i] = new T[new_cols];
    }

    for (size_t i = 0; i < new_rows; ++i) {
      for (size_t j = 0; j < new_cols; ++j) {
        new_p.get()[i][j] = this->p.get()[j][i];
      }
    }

    this->p = new_p;
    this->cols = new_cols;
    this->rows = new_rows;
  }

  size_t get_cols() const { return this->cols; }
  size_t get_rows() const { return this->rows; }

  Matrix<T> operator+(const Matrix<T> &new_matrix) const {
    assert(this->rows == new_matrix.get_rows());
    assert(this->cols == new_matrix.get_cols());
    Matrix<T> res = Matrix<T>(this->rows, this->cols);

    for (size_t i = 0; i < this->rows; ++i) {
      for (size_t j = 0; j < this->cols; ++j) {
        res.set_value_by_ij(
            i, j, this->p.get()[i][j] + new_matrix.get_value_by_ij(i, j));
      }
    }

    return res;
  }

  Matrix<T> operator-(const Matrix<T> &new_matrix) const {
    assert(this->rows == new_matrix.get_rows());
    assert(this->cols == new_matrix.get_cols());
    Matrix<T> res = Matrix<T>(this->rows, this->cols);

    for (size_t i = 0; i < this->rows; ++i) {
      for (size_t j = 0; j < this->cols; ++j) {
        res.set_value_by_ij(
            i, j, this->p.get()[i][j] - new_matrix.get_value_by_ij(i, j));
      }
    }

    return res;
  }

  Matrix<T> operator*(T value) const {
    Matrix<T> res = Matrix<T>(this->rows, this->cols);

    for (size_t i = 0; i < this->rows; ++i) {
      for (size_t j = 0; j < this->cols; ++j) {
        res.set_value_by_ij(i, j, this->p.get()[i][j] * value);
      }
    }

    return res;
  }

  Matrix<T> operator*(const Matrix<T> &new_matrix) {
    assert(this->cols == new_matrix.get_rows());
    Matrix<T> res = Matrix<T>(this->rows, new_matrix.get_cols());
    res.set_all_value(0);

    for (size_t i = 0; i < this->rows; ++i) {
      for (size_t j = 0; j < new_matrix.get_cols(); ++j) {
        for (size_t k = 0; k < this->cols; ++k) {
          res.set_value_by_ij(i, j,
                              res.get_value_by_ij(i, j) +
                                  this->p.get()[i][k] *
                                      new_matrix.get_value_by_ij(k, j));
        }
      }
    }
    return res;
  }

  void matrix_point_mul(const Matrix<T> &new_matrix) {
    assert(this->rows == new_matrix.get_rows());
    assert(this->cols == new_matrix.get_cols());

    for (size_t i = 0; i < this->rows; ++i)
      for (size_t j = 0; j < this->cols; ++j) {
        this->set_value_by_ij(i, j,
                              this->get_value_by_ij(i, j) *
                                  new_matrix.get_value_by_ij(i, j));
      }
  }

  bool is_has_zero() const {
    for (size_t i = 0; i < this->rows; ++i)
      for (size_t j = 0; j < this->cols; ++j) {
        if (abs(this->p.get()[i][j]) < EPS)
          return true;
      }
    return false;
  }

  void matrix_point_div(const Matrix<T> &new_matrix) {
    assert(this->rows == new_matrix.get_rows());
    assert(this->cols == new_matrix.get_cols());
    assert(new_matrix.is_has_zero() == false);

    for (size_t i = 0; i < this->rows; ++i)
      for (size_t j = 0; j < this->cols; ++j) {
        this->set_value_by_ij(i, j,
                              this->get_value_by_ij(i, j) /
                                  new_matrix.get_value_by_ij(i, j));
      }
  }

private:
  size_t cols;
  size_t rows;
  std::shared_ptr<T *> p;
};

template <typename T> class Vector {
public:
  Vector(size_t size) : size(size), p(new T[size], std::default_delete<T[]>()) {
    this->set_all_value(0);
  }

  void set_all_value(T value) {
    for (size_t i = 0; i < this->size; i++) {
      this->p.get()[i] = value;
    }
  }

  void print() {
    for (size_t i = 0; i < this->size; i++) {
      std::cout << this->p.get()[i] << std::endl;
    }
    std::cout << std::endl;
  }

  void set_value_by_index(size_t index, T value) {
    assert(index >= 0 && index < this->size);
    this->p.get()[index] = value;
  }

  Vector<T> operator*(T value) const {
    Vector<T> res = Vector<T>(this->size);

    for (size_t i = 0; i < this->cols; ++i) {
      this->p.get()[i] = this->p.get()[i] * value;
    }

    return res;
  }

  size_t get_size() const { return this->size; }

  T get_element_by_index(size_t index) const {
    assert(index >= 0 && index < this->size);
    return this->p.get()[index];
  }

  Vector<T> operator+(const Vector<T> &v) const {
    Vector<T> res = Vector<T>(this->size);
    assert(this->size == v.get_size());

    for (size_t i = 0; i < this->size; ++i) {

      res.set_value_by_index(i, this->get_element_by_index(i) +
                                    v.get_element_by_index(i));
    }
    return res;
  }

  Vector<T> operator-(const Vector<T> &v) const {
    Vector<T> res = Vector<T>(this->size);
    assert(this->size == v.get_size());

    for (size_t i = 0; i < this->size; ++i) {

      res.set_value_by_index(i, this->get_element_by_index(i) -
                                    v.get_element_by_index(i));
    }
    return res;
  }

  T operator*(const Vector<T> &v) const {
    T res = 0;

    for (size_t i = 0; i < this->size; ++i) {

      res = res + (this->get_element_by_index(i) * v.get_element_by_index(i));
    }
    return res;
  }

  bool is_has_zero() const {
    for (size_t i = 0; i < this->size; ++i) {
      if (abs(this->p.get()[i]) < EPS)
        return true;
    }
    return false;
  }

  void point_mul(const Vector<T> &v) {
    for (size_t i = 0; i < this->size; ++i) {
      this->set_value_by_index(i, this->get_element_by_index(i) *
                                      v.get_element_by_index(i));
    }
  }

  void point_div(const Vector<T> &v) {
    assert(v.is_has_zero() == false);
    for (size_t i = 0; i < this->size; ++i) {
      this->set_value_by_index(i, this->get_element_by_index(i) /
                                      v.get_element_by_index(i));
    }
  }

  void saxpy(const Vector<T> &v, T a) {
    assert(v.is_has_zero() == false);
    for (size_t i = 0; i < this->size; ++i) {
      this->set_value_by_index(i, this->p.get()[i] +
                                      a * v.get_element_by_index(i));
    }
  }

  void matrix_vector_mul(const Matrix<T> &A, const Vector<T> &x,
                         Gaxpy_Class preference = Gaxpy_Class::ROW_ORIENTED) {
    assert(A.get_cols() == x.get_size());
    assert(A.get_rows() == this->size);

    if (preference == Gaxpy_Class::ROW_ORIENTED) {
      for (size_t i = 0; i < A.get_rows(); ++i) {
        for (size_t j = 0; j < A.get_cols(); ++j) {
          this->set_value_by_index(i, this->get_element_by_index(i) +
                                          A.get_value_by_ij(i, j) *
                                              x.get_element_by_index(j));
        }
      }
    } else {
      for (size_t j = 0; j < A.get_cols(); ++j) {
        for (size_t i = 0; i < A.get_rows(); ++i) {
          this->set_value_by_index(i, this->get_element_by_index(i) +
                                          A.get_value_by_ij(i, j) *
                                              x.get_element_by_index(j));
        }
      }
    }
  }

  void init(const std::vector<T> &v) {
    assert(this->size == v.size());
    for (size_t i = 0; i < this->size; ++i) {
      this->set_value_by_index(i, v[i]);
    }
  }

private:
  size_t size;
  std::shared_ptr<T[]> p;
};

#endif