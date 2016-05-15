/*
  Devoir 1, Ex2 Tri 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Contient le programme de test des algorithmes de tri
*/

#include "funcbenchmark.hpp"
#include "sortalgorithms.hpp"

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



int main(int argc, char** argv)
{
  size_t n = 100;

  srand((unsigned int)time(NULL));
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
  int multipliers[7] = { 1, 2, 3, 5, 7, 10, 100 };
  string_vector test_names;
  test_names.push_back("n");
  test_names.push_back("2*n");
  test_names.push_back("3*n");
  test_names.push_back("5*n");
  test_names.push_back("7*n");
  test_names.push_back("10*n");
  test_names.push_back("10*n sorted");
  test_names.push_back("10*n sorted inverted");
  test_names.push_back("100*n");
  test_names.push_back("100*n sorted");
  test_names.push_back("100*n sorted inverted");


  for (size_t k = 0; k < 7; k++)
  {

    std::cout << "================================================================" << std::endl;
    std::cout << "Generate random table of " << n * multipliers[k] << " elements" << std::endl;
    std::cout << "================================================================" << std::endl;

    int_vector_ptr table(new std::vector<int>(n * multipliers[k], 0));

    std::vector<int>::iterator it;
    for (it = table->begin(); it != table->end(); it++)
    {
      *it = (int)(rand64()%INT_MAX);
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
      tables.push_back(table_sorted);


      *table_sorted_inv = *table;
      std::cout << "t_sorted_inv = ";
      print_int_vector(*table_sorted_inv);
      std::sort(table_sorted_inv->begin(), table_sorted_inv->end(), std::greater<int>());
      tables.push_back(table_sorted_inv);
    }



  }

  //TESTS !!!
  std::vector<FuncBenchmark::Ptr> benchmarks;
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Tri par fusion", sort_merge<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Tri par bulles", sort_bubble<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Quicksort", sort_quick<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Quicksort rand", sort_quick_rand<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Tri par insertion", sort_insertion<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Tri par tas", sort_heap<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("Tri par base", sort_radix<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("std::sort", std::sort<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("std::sort_heap", std_sort_heap<std::vector<int>::iterator>, tables, test_names, n)));
  benchmarks.push_back(FuncBenchmark::Ptr( new FuncBenchmark("std::stable_sort", std::stable_sort<std::vector<int>::iterator>, tables, test_names, n)));


  for (size_t t = 0; t < benchmarks.size(); t++)
  {
    (*(benchmarks[t])).bench();
  }

  std::cout << "================================================================" << std::endl;
  std::cout << "Check algos results" << std::endl;
  std::cout << "================================================================" << std::endl;
  

  std::vector<int> test_table(20), sorted_table;
  std::vector<int>::iterator it;
  for (it = test_table.begin(); it != test_table.end(); it++)
  {
    *it = (int)(rand64() % INT_MAX);
  }
  sorted_table = test_table;
  std::sort(sorted_table.begin(), sorted_table.end());


  for (size_t t = 0; t < benchmarks.size(); t++)
  {
    (*(benchmarks[t])).test(test_table,sorted_table);
  }

  std::cout << "================================================================" << std::endl;
  std::cout << "Bench Results " << std::endl;
  std::cout << "================================================================" << std::endl;

  printf("\n%20.20s |", "Tps moyen (ms)");
  for (n = 0; n < test_names.size(); n++)
  {
    printf("%6.6s |", test_names[n].c_str());
  }
  printf("\n");
  printf(" ------------------------------------------------------------------------------------------------------------\n");
  for (size_t t = 0; t < benchmarks.size(); t++)
  {
    (*(benchmarks[t])).print_bench_results();
  }


  FILE* f = fopen("output.csv", "w");
  if (f)
  {
    fprintf(f, "%s;", "Tps moyen (ms)");
    for (n = 0; n < test_names.size(); n++)
    {
      fprintf(f, "%s;", test_names[n].c_str());
    }
    fprintf(f,"\n");
    for (size_t t = 0; t < benchmarks.size(); t++)
    {
      (*(benchmarks[t])).fprint_bench_results(f);
    }
    fclose(f);
    std::cout << "results saved in 'output.csv'" << std::endl;
  }

  system("PAUSE");
  return 0;
}