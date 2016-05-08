/*
  Devoir 1, Ex2 Tri 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Contient le programme de test des algorithmes de tri
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <memory> //C++ 11
#include <ctime>
#include <vector>
#include <climits>
#include <functional> //c++ 11


#include "../common/mathutils.hpp"

void print_usage(const char* argv_0)
{
  std::cout << "usage: " << argv_0 << " <n elements>" << std::endl;
}

void print_usage_and_exit(const char* argv_0,int code)
{
  print_usage(argv_0);
  system("PAUSE");
  exit(code);
}

void print_int_vector(const std::vector<int>& v)
{
  std::cout << " [";
  size_t bounds = v.size() > 4 ? 4 : v.size() - 1;
  for (size_t i = 0; i < bounds; i++)
  {
    std::cout << v[i] << ", ";
  }
  if (v.size() > 1)
  {
    std::cout << " ... , " << v[v.size() - 1] << "] " << std::endl;
  }
  else
  {
    std::cout << " ]" << std::endl;
  }
}


typedef std::shared_ptr<std::vector<int>> int_vector_ptr;

int main(int argc, char** argv)
{
  size_t n = 100;

  srand(time(NULL));
  std::cout << "UQAC - Algorithmique - Devoir 1" << std::endl;
  std::cout << "Ex 2: test des algorithmes de tri" << std::endl;
  std::cout << "Author: Julien De Loor (julien.de-loor1loor@uqac.ca)" << std::endl;


  if (argc < 2)
  {
    std::cout << "warning: no arguments use n = " << n << std::endl;
  }
  else if (sscanf_s(argv[1], "%Iu", &n) != 1 || n < 1 )
  {
    print_usage_and_exit(argv[0], 1);
  }
  

  std::vector<int_vector_ptr> tables;
  std::vector<int_vector_ptr> tables_sorted;
  std::vector<int_vector_ptr> tables_sorted_inv;
  int multipliers[7] = { 1, 2, 3, 5, 7, 10, 100 };


  for (size_t k = 0; k < 7; k++)
  {

    std::cout << "================================================================" << std::endl;
    std::cout << "Generate random table of " << n * multipliers[k] << " elements" << std::endl;
    std::cout << "================================================================" << std::endl;

    int_vector_ptr table(new std::vector<int>(n * multipliers[k], 0));

    std::vector<int>::iterator it;
    for (it = table->begin(); it != table->end(); it++)
    {
      *it = rand64();
    }
    std::cout << "t_random = ";
    print_int_vector(*table);
    tables.push_back(table);
    
    if (multipliers[k] >= 10)
    {
      int_vector_ptr table_sorted(new std::vector<int>(n * multipliers[k]));
      int_vector_ptr table_sorted_inv(new std::vector<int>(n * multipliers[k]));
      
      *table_sorted = *table;
      std::sort(table_sorted->begin(), table_sorted->end(), std::less<int>());
      std::cout << "t_sorted = ";
      print_int_vector(*table_sorted);
      tables_sorted.push_back(table_sorted);


      *table_sorted_inv = *table;
      std::cout << "t_sorted_inv = ";
      print_int_vector(*table_sorted_inv);
      std::sort(table_sorted_inv->begin(), table_sorted_inv->end(), std::greater<int>());
      tables_sorted_inv.push_back(table_sorted_inv);
    }

    std::cout << std::endl;
  }

  system("PAUSE");
  return 0;
}