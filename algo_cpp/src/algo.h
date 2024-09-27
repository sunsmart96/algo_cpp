#ifndef ALGO_H
#define ALGO_H
#include <cstdint>
#include <vector>

template <typename T>
void swap(T &a, T &b) {
  T c = a;
  a = b;
  b = c;
}

struct Search_Res {
  Search_Res(size_t index_in, bool is_found_in) {
    index = index_in;
    is_found = is_found_in;
  }

  size_t index;
  bool is_found;
};

uint64_t gcd(uint64_t p, uint64_t q);

// vector v is ascending order
Search_Res binary_search(std::vector<int> v, int target_value);

#endif