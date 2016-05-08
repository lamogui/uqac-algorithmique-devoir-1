
/*
  Devoir 1
  Julien De Loor (julien.de-loor1@uqac.ca)
*/

#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>

bool isPowerOfTwo(size_t x);

template<typename real>
bool isRealEqual(real a, real b, real eps)
{
  return (abs(a - b) < eps);
}

template<typename real>
real randomReal()
{
  return (real)rand() / (real)RAND_MAX;
}

template<typename real>
real randomRangeReal(real min, real max)
{
  return randomReal<real>()*(max-min) + min;
}
