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