#pragma once

/*
  Devoir 1, Ex2 Tri 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Une classe pour pseudo automatiser les tests
*/

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cassert>

typedef std::shared_ptr<std::vector<int>> int_vector_ptr;
typedef std::vector<std::string> string_vector;

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



typedef void(*sort_func)(std::vector<int>::iterator, std::vector<int>::iterator);
class FuncBenchmark
{

public:

  std::string name;
  string_vector test_names;
  std::vector<int_vector_ptr> test_tables;
  sort_func func;
  size_t n;
  std::vector<double> times;

  typedef std::shared_ptr<FuncBenchmark> Ptr;


public:
  FuncBenchmark(
    const std::string& _name,
    sort_func _func,
    const std::vector<int_vector_ptr>& _test_tables,
    const string_vector& _test_names,
    size_t _n) :
    name(_name),
    test_names(_test_names),
    test_tables(_test_tables),
    func(_func),
    n(_n)
  {
  }

  bool test(const std::vector<int>& test, const std::vector<int>& result)
  {
    assert(test.size() == result.size());
    size_t size = test.size();
    std::vector<int> sorted = test;
    func(sorted.begin(), sorted.end());
    
    bool success = true;
    for (size_t n = 0; n < size; n++)
    {
      if (sorted[n] != result[n])
      {
        success = false;
      }
    }
    std::cout << name << ": " << (success ? "true" : "false") << std::endl;
    return success;
  }
  
  void print_bench_results()
  {
    printf("%20.20s |", name.c_str());
    for (n = 0; n < times.size(); n++)
    {
      printf("%6g |", times[n]/10.0);
    }
    printf("\n");
  }

  void fprint_bench_results(FILE* f)
  {
    fprintf(f, "%s;", name.c_str());
    for (n = 0; n < times.size(); n++)
    {
      fprintf(f, "%.9g;", times[n]/10.0);
    }
    fprintf(f,"\n");
  }
  
  void bench()
  {
    times.clear();

    assert(test_tables.size() == test_names.size());

    std::cout << "================================================================" << std::endl;
    std::cout << "Begin Benchmark of algorithm " << name << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "Duplicate 10 times " << test_tables.size() << " tables..." << name << std::endl;
    
    std::vector<std::vector<std::vector<int>>> tables; //[test_type][test_iteration][element]
    tables.resize(test_tables.size()); 
    for (size_t test_type = 0; test_type < test_tables.size(); test_type++)
    {
      tables[test_type].resize(10);
      std::cout << "Copy 10 times the " << test_names[test_type] << " tables of " << (*(test_tables[test_type])).size() << " elements " << std::endl;
      for (size_t test_iteration = 0; test_iteration < tables[test_type].size(); test_iteration++)
      {
        tables[test_type][test_iteration] = *(test_tables[test_type]);
      }
    }

    std::cout << "Ready to start " << tables.size() << " tests" << std::endl << std::endl;

    clock_t start, end;
    for (size_t test_type = 0; test_type < tables.size(); test_type++)
    {
      std::cout << "================================================================" << std::endl;
      std::cout << "Algorithm " << name  << " test " << test_names[test_type] << std::endl;
      std::cout << "================================================================" << std::endl;
      std::cout << "Runnning " << tables[test_type].size() << " times the function" << std::endl;

      start = clock();
      for (size_t i = 0; i < tables[test_type].size(); i++)
      {
        func(tables[test_type][i].begin(), tables[test_type][i].end());
      }
      end = clock();
      double t = (((double)(end)-(double)(start)) / (double)(CLOCKS_PER_SEC))*1000.0;
      times.push_back(t);
      std::cout << "Ended in  " << t << " ms" << std::endl << std::endl;
    }
  }
};
