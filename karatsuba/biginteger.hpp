
/*
  Devoir 1, Ex3 Karatsuba
  Julien De Loor (julien.de-loor1@uqac.ca)
  La classe grandEntier (BigInteger), par simplicité j'ai 
  choisi d'utiliser les chaines de caractères et une base 10
*/

#pragma once

#include <string>
#include <iostream>

class BigInteger
{
public:
  BigInteger(const std::string& n = std::string());
  BigInteger(const BigInteger& n);

  static void add(const BigInteger& a, const BigInteger& b, BigInteger& result);
  static void karastuba(const BigInteger& a, const BigInteger& b, BigInteger& result);

  inline bool isZero() const { return _n.empty(); }
  inline std::string str() const
  {
    if (isZero())
    {
      return std::move(std::string("0"));
    }
    return std::move(std::string(_n.rbegin(),_n.rend()));
  }

  BigInteger operator+(const BigInteger& right) const;

  bool isValid() const;

private:

  void removeUselessZeros();
  std::string _n; //The order is reversed


};


std::ostream& operator<<(std::ostream& os, const BigInteger& n);

