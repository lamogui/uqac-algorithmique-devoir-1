
#include "biginteger.hpp"
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <algorithm>

BigInteger::BigInteger(const std::string& n):
_n(n)
{
  removeUselessZeros();
  assert(isValid());
}

BigInteger::BigInteger(const BigInteger& n):
_n(n._n)
{
}

BigInteger::BigInteger(uint64_t n)
{
  std::stringstream s;
  s << n;
  s.flush();
  _n = s.str();
}

BigInteger::BigInteger(BigInteger&& n):
  _n(std::move(n._n))
{

}


const BigInteger& BigInteger::operator=(const BigInteger& cpy)
{
  _n = cpy._n;
  return *this;
}

const BigInteger& BigInteger::operator=(uint64_t cpy)
{
  std::stringstream s;
  s << cpy;
  s.flush();
  _n = s.str();
  return *this;
}

void BigInteger::removeUselessZeros()
{
  size_t i = 0;
  while (i < _n.size() && _n[i] == '0')
  {
    ++i;
  }
  _n.erase(0,i);
}

bool BigInteger::isValid() const
{
  for (std::string::const_iterator i = _n.cbegin(); i != _n.cend(); i++)
  {
    if (*i < '0' || *i > '9')
    {
      return false;
    }
  }
  return true;
}

void BigInteger::add(const BigInteger &a, const BigInteger& b, BigInteger& r)
{
  const std::string& greater = a._n.size() >= b._n.size() ? a._n : b._n;
  const std::string& lower = a._n.size() < b._n.size() ? a._n : b._n;
  const size_t greater_size = greater.size();
  const size_t lower_size = lower.size();

  r._n.clear();
  r._n.reserve(greater_size + 1); //+1 for carry

  int carry = 0;
  size_t i;
  for (i = 1; i <= lower_size; ++i)
  {
    int digit = (int)(greater[greater_size - i]) 
              + (int)(lower[lower_size - i]) 
              + carry 
              - 2 * (int)'0';
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
  for (; i <= greater_size; ++i)
  {
    int digit = (int)(greater[greater_size - i]) + carry - (int)'0';
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
  if (carry > 0) 
  {
    int digit = carry;
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
  r._n = std::move(std::string(r._n.rbegin(), r._n.rend())); //Reverse the order
}

void BigInteger::karastuba(const BigInteger& x, const BigInteger& y, BigInteger& result)
{
  if (x.isZero() || y.isZero())
  {
    result._n.clear(); // x * 0 = 0 trivial
    return;
  }

  if (y.size() == 1 || y.size() == 1)
  {
    result = std::move(BigInteger(x.toUnsigned() * y.toUnsigned()));
    return;
  }
  
  size_t m = std::max(x.size(), y.size());
  if (m % 2 != 0)
  {
    m -= 1;
  }
  size_t m2 = m / 2;

  std::string str_x1, str_x0;
  std::string str_y1, str_y0;

  if (x._n.size() > m2)
  {
    str_x1 = std::move(x._n.substr(0, x._n.size() - m2));
    str_x0 = std::move(x._n.substr(x._n.size() - m2));
  }
  else
  {
    str_x0 = x._n;
  }

  if (y._n.size() > m2)
  {
    str_y1 = std::move(y._n.substr(0, y._n.size() - m2));
    str_y0 = std::move(y._n.substr(y._n.size() - m2));
  }
  else
  {
    str_y0 = y._n;
  }

  BigInteger x1(str_x1), x0(str_x0);
  BigInteger y1(str_y1), y0(str_y0);
  BigInteger z0,z1,z2;

  karastuba(x1, y1, z2);
  karastuba(x1 + x0, y1 +y0, z1);
  karastuba(x0, y0, z0);

  z1 = (uint64_t)((int64_t)z1.toUnsigned() - (int64_t)z2.toUnsigned() - (int64_t)z0.toUnsigned());
  result = (z2 << m) + (z1 << m2) + z0;
}


uint64_t BigInteger::toUnsigned() const
{
  char* ptrstp;
#ifdef _WIN32
  return _strtoui64(_n.c_str(), &ptrstp, 10);
#else
  return strtoull(_n.c_str(), &ptrstp, 10);
#endif
}

size_t BigInteger::size() const
{
  if (isZero())
  {
    return 1;
  }
  else
  {
    return _n.size();
  }
}

std::ostream& operator<<(std::ostream& os, const BigInteger& n)
{
  os << n.str();
  return os;
}

BigInteger BigInteger::operator+(const BigInteger& right) const
{
  BigInteger r;
  BigInteger::add(*this, right, r);
  return std::move(r);
}


BigInteger BigInteger::operator*(const BigInteger& right) const
{
  BigInteger r;
  BigInteger::karastuba(*this, right, r);
  return std::move(r);
}


BigInteger BigInteger::operator<< (unsigned int shift) const
{
  if (isZero())
  {
    return std::move(BigInteger());
  }
  std::string n = _n + std::string(shift,'0');
  return std::move(BigInteger(n));
}

BigInteger BigInteger::operator>> (unsigned int shift) const
{
  if (shift >= _n.size())
  {
    return std::move(BigInteger()); //zero
  }
  return std::move(BigInteger(_n.substr(0, _n.size() - shift)));
}

