#ifndef ALGO_H
#define ALGO_H
#include <cstdint>

template <typename T>
void swap(T &a, T &b) {
  T c = a;
  a = b;
  b = c;
}

uint64_t gcd(uint64_t p, uint64_t q);

#endif