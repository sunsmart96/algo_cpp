#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <cassert>
#include <memory>

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
  }

  void set_value_by_ij(size_t i, size_t j, T value) {
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);

    this->p.get()[i][j] = value;
  }

  T get_value_by_ij(size_t i, size_t j) {
    assert(i >= 0 && i < rows);
    assert(j >= 0 && j < cols);
    return p.get()[i][j];
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

private:
  size_t cols;
  size_t rows;
  std::shared_ptr<T *> p;
};

#endif