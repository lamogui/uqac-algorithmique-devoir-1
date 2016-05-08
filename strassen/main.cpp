

/*
  Devoir 1, Ex1 Strassen 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Contient le programme de test de strassen
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
  std::cout << "UQAC - Algorithmique - Devoir 1" << std::endl;
  std::cout << "Ex 1: test strassen" << std::endl;
  std::cout << "Author: Julien De Loor (julien.de-loor1loor@uqac.ca)" << std::endl;

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
  
  std::cout << "================================================================" << std::endl;
  std::cout << "generate 2 random matrix (A and B) of size " << size << "x" << size << std::endl;
  std::cout << "================================================================" << std::endl;
  A.random(-10.0, 10.0); B.random(-10.0, 10.0);
  if (size < 10)
  {
    A.print();
    B.print();
  }
  std::cout << std::endl;

  std::cout << "================================================================" << std::endl;
  std::cout << "test strassen C=A*B " << std::endl;
  std::cout << "================================================================" << std::endl;
  Strassen = A * B;
  if (size < 10)
  {
    Strassen.print();
  }
  std::cout << std::endl;

  std::cout << "================================================================" << std::endl;
  std::cout << "test naive C=A*B" << std::endl;
  std::cout << "================================================================" << std::endl;
  Naive = Matrix<real>::mul_naive(A, B);
  if (size < 10)
  {
    Naive.print();
  }
  std::cout << std::endl;

  std::cout << "================================================================" << std::endl;
  std::cout << "test equality of A and B (should be false)" << std::endl;
  std::cout << "================================================================" << std::endl;
  bool equal = (A == B);
  std::cout << "A == B ? " << (equal ? "true" : "false") << std::endl;
  std::cout << std::endl;

  std::cout << "================================================================" << std::endl;
  std::cout << "test equality strassen and naive results (should be true)" << std::endl;
  std::cout << "================================================================" << std::endl;
  std::cout << "Strassen - Naive" << std::endl;
  s_n = Strassen - Naive;
  if (size < 10)
  {
    s_n.print();
  }
  equal = (Strassen == Naive);
  std::cout << "Strassen == Naive ? " << (equal ? "true" : "false") << std::endl;
  std::cout << std::endl;

  if (nb_test > 0)
  {

    clock_t  start,end;
    double ms;

    std::cout << "================================================================" << std::endl;
    std::cout << "test performances of naive mult (run " << nb_test << " times)" << std::endl;
    std::cout << "================================================================" << std::endl;

    start = clock();
    for (size_t n = 0; n < nb_test;  n++)
    {
      A.random(-10.0, 10.0); B.random(-10.0, 10.0);
      Naive = Matrix<real>::mul_naive(A, B);
    }
    end = clock();
    ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    std::cout << "Computed " << nb_test << " naive mult of " << size << "x" << size << " random matrix in " << ms << " ms" << std::endl;
    std::cout << std::endl;


    std::cout << "================================================================" << std::endl;
    std::cout << "test performances of strassen mult (run " << nb_test << " times)" << std::endl;
    std::cout << "================================================================" << std::endl;

    start = clock();
    for (size_t n = 0; n < nb_test;  n++)
    {
      A.random(-10.0, 10.0); B.random(-10.0, 10.0);
      Naive = A * B;
    }
    end = clock();
    ms = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    std::cout << "Computed " << nb_test << " strassen mult of " << size << "x" << size << " random matrix in " << ms << " ms" << std::endl;
    std::cout << std::endl;

  }

  
  system("PAUSE");
  return 0;
}