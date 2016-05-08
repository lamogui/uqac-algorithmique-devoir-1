

/*
  Devoir 1 
  Julien De Loor (julien.de-loor1@uqac.ca)
*/

#include "mathutils.hpp"

bool isPowerOfTwo(size_t x)
{
  unsigned int numberOfOneBits = 0;

  while (x && numberOfOneBits <= 1)
  {
    if ((x & 1) == 1)
    {
      numberOfOneBits++;
    }
    x >>= 1;
  }

  return (numberOfOneBits == 1);
}