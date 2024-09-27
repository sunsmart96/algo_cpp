#include "algo.h"

uint64_t gcd(uint64_t p, uint64_t q) {
  if (q == 0) return p;

  uint64_t r = p % q;
  return gcd(q, r);
}