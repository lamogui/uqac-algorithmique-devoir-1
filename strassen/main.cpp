

/*
  Devoir 1, Ex1 Strassen 
  Julien De Loor (julien.de-loor1@uqac.ca)
*/

#include <iostream>
#include <cstdio>
#include <ctime>
#include "matrix.hpp"

typedef double real;

int main(int argc, char** argv)
{
  size_t size;
  size_t nb_test;

  srand(time(NULL));

  if (argc != 3)
  {
    std::cerr << "usage: " << argv[0] << " <matrix size> <nb test>" << std::endl;
    system("PAUSE");
    exit(1);
  }

  if (sscanf_s(argv[1], "%Iu", &size) != 1)
  {
    std::cerr << "error wrong value expected a number got " << argv[1] << std::endl;
    std::cerr << "usage: " << argv[0] << " <matrix size> <nb test>" << std::endl;
    system("PAUSE");
    exit(2);
  }
 
  if (sscanf_s(argv[2], "%Iu", &nb_test) != 1)
  {
    std::cerr << "error wrong value expected a number got " << argv[2] << std::endl;
    std::cerr << "usage: " << argv[0] << " <matrix size> <nb test>" << std::endl;
    system("PAUSE");
    exit(3);
  }

  if (!isPowerOfTwo(size))
  {
    std::cerr << "error wrong value expected a power of 2 for size got " << argv[1] << std::endl;
    system("PAUSE");
    exit(3);
  }

  Matrix<real> A(size, size), B(size, size);
  Matrix<real> Strassen(size, size), Naive(size, size);
  Matrix<real> s_n(size, size);
  
  std::cout << "generate 2 random matrix of size " << size << "x" << size << std::endl;
  A.random(-10.0, 10.0); B.random(-10.0, 10.0);
  A.print();
  B.print();

  std::cout << "test strassen" << std::endl;
  Strassen = A * B;
  Strassen.print();

  std::cout << "test naive" << std::endl;
  Naive = Matrix<real>::mul_naive(A, B);
  Naive.print();

  std::cout << "test equality of A and B (should be false)" << std::endl;
  bool equal = (A == B);
  std::cout << "A == B ? " << equal << std::endl;

  std::cout << "test equality strassen result and naive multiply result (should be true)" << std::endl;
  s_n = Strassen - Naive;
  s_n.print();
  equal = (Strassen == Naive);
  std::cout << "Strassen == Naive ? " << equal << std::endl;
  
  system("PAUSE");
  return 0;
}