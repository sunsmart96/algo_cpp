#include "algo.h"

#include <cmath>

using std::vector;

uint64_t gcd(uint64_t p, uint64_t q) {
  if (q == 0)
    return p;

  uint64_t r = p % q;
  return gcd(q, r);
}

Search_Res binary_search(vector<int> v, int target_value) {
  if (v.size() == 0)
    return Search_Res(0, false);
  size_t index_l = 0;
  size_t index_r = v.size() - 1;

  while (index_l <= index_r) {
    auto mid = size_t(std::floor((index_l + index_r) / 2));
    if (v[mid] == target_value)
      return Search_Res(mid, true);
    else if (v[mid] < target_value)
      index_l = mid + 1;
    else if (v[mid] > target_value)
      index_r = mid - 1;
  }

  return Search_Res(0, false);
}

template class Bag<double>;
template class Bag<float>;
template class Bag<int>;

template <typename T> Bag<T>::Bag() { this->v = std::vector<T>(); }

template <typename T> void Bag<T>::add(T data) { this->v.push_back(data); }

template <typename T> bool Bag<T>::is_empty() {
  return this->v.size() == 0 ? true : false;
}

template <typename T> size_t Bag<T>::size() { return this->v.size(); }
