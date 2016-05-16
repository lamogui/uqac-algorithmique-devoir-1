
/*
  Devoir 1, Ex3 Karatsuba
  Julien De Loor (julien.de-loor1@uqac.ca)
  La classe grandEntier (BigInteger), par simplicité j'ai 
  choisi d'utiliser les chaines de caractères et une base 10
*/

#pragma once

#include <string>
#include <iostream>
#include <cstdint>

class BigInteger
{
public:
  BigInteger(const std::string& n = std::string());
  BigInteger(uint64_t n);
  BigInteger(const BigInteger& n);
  BigInteger(BigInteger&& n);

  const BigInteger& operator=(const BigInteger& cpy);
  const BigInteger& operator=(uint64_t cpy);

  static void add(const BigInteger& a, const BigInteger& b, BigInteger& result);
  static void karastuba(const BigInteger& a, const BigInteger& b, BigInteger& result);

  inline bool isZero() const { return _n.empty(); }
  inline std::string str() const
  {
    if (isZero())
    {
      return std::move(std::string("0"));
    }
    return std::move(std::string(_n));
  }

  uint64_t toUnsigned() const;

  //Taille en base 10
  size_t size() const;

  BigInteger operator+(const BigInteger& right) const;
  BigInteger operator*(const BigInteger& right) const;

  //Operateurs de decalage en base 10
  BigInteger operator<< (unsigned int shift) const;
  BigInteger operator>> (unsigned int shift) const;


  bool isValid() const;

private:

  void removeUselessZeros();
  std::string _n; 


};


std::ostream& operator<<(std::ostream& os, const BigInteger& n);

