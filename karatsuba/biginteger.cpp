
#include "biginteger.hpp"
#include <cassert>

BigInteger::BigInteger(const std::string& n):
_n(n.rbegin(), n.rend())
{
  removeUselessZeros();
  assert(isValid());
}

BigInteger::BigInteger(const BigInteger& n):
_n(n._n)
{

}

void BigInteger::removeUselessZeros()
{
  while (!_n.empty() && _n.back() == '0')
  {
    _n.resize(_n.size() - 1);
  }
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
  const std::string& greater = a._n.size() > b._n.size() ? a._n : b._n;
  const std::string& lower = a._n.size() < b._n.size() ? a._n : b._n;

  r._n.clear();
  r._n.reserve(greater.size() + 1); //+1 for carry

  int carry = 0;
  size_t i;
  for (i = 0; i < lower.size(); i++)
  {
    int digit = (int)(greater[i]) + (int)(lower[i]) + carry - 2 * (int)'0';
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
  for (i = lower.size(); i < greater.size(); i++)
  {
    int digit = (int)(greater[i]) + carry - (int)'0';
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
  while (carry > 0) //No need to be while here
  {
    int digit = carry;
    carry = digit / 10;
    digit %= 10;
    digit += (int)'0';
    r._n += (char)digit;
  }
}

void BigInteger::karastuba(const BigInteger& a, const BigInteger& b, BigInteger& result)
{
  
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


