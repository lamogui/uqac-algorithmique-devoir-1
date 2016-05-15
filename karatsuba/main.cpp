
/*
Devoir 1, Ex3 Karatsuba
Julien De Loor (julien.de-loor1@uqac.ca)
Contient le programme de test de karastuba
*/

#include <iostream>
#include <cstdio>
#include <ctime>
#include "biginteger.hpp"

typedef double real;

void printInfo()
{
    std::cout << "UQAC - Algorithmique - Devoir 1" << std::endl;
    std::cout << "Ex 3: test karastuba" << std::endl;
    std::cout << "Author: Julien De Loor (julien.de-loor1loor@uqac.ca)" << std::endl;

}

int main(int argc, char** argv)
{
  if (argc != 4 || strlen(argv[2]) != 1)
  {
    printInfo();
    std::cerr << "usage: " << argv[0] << " <a> <'+' or '*'> <b>" << std::endl;
    system("PAUSE");
    exit(1);
  }

  char op = argv[2][0];
  BigInteger a(argv[1]);
  BigInteger b(argv[3]);
  BigInteger r;

  if (!a.isValid() || !b.isValid())
  {
    std::cerr << "error invalid number" << std::endl;
    printInfo();
    std::cerr << "usage: " << argv[0] << " <a> <'+' or '*'> <b>" << std::endl;
    system("PAUSE");
    exit(1);

  }
 

  switch (op)
  {
    case '+':
      r = a + b;
      break;
    /*case '*':
      r = a * b;
      break;*/
    default:
      printInfo();
      std::cerr << "usage: " << argv[0] << " <a> <+ or *> <b>" << std::endl;
      system("PAUSE");
      exit(1);
  }

  std::cout << r << std::endl;
  return 0;
}