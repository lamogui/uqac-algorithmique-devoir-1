
#pragma once

/*
  Devoir 1, Ex2 Tri 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Les diffrents algo de tri, je ne les ai pas codés 
  juste modifiés pour avoir le même style partout et utiliser 
  la 
  il y a la source originale avec chaque fonction 
  
*/

#include <algorithm>
#include <iterator>
#include <vector>
#


/*
  Tri par fusion 
  Source: http://codereview.stackexchange.com/questions/78129/merge-sort-in-c-with-Iterators
*/

template<typename Iterator>
std::vector<typename Iterator::value_type> merge(const Iterator begin, const Iterator mid, const Iterator end)
{
  std::vector<typename Iterator::value_type> v;
  Iterator it_l = begin, it_r =  mid;
  const Iterator it_mid{ mid }, it_end{ end };

  while (it_l != it_mid && it_r != it_end)
  {
    v.push_back((*it_l <= *it_r) ? *it_l++ : *it_r++);
  }

  v.insert(v.end(), it_l, it_mid);
  v.insert(v.end(), it_r, it_end);

  return std::move(v);
}

template<typename Iterator>
void sort_merge(Iterator begin, Iterator end)
{
  auto size = std::distance(begin, end);
  if (size < 2)
  {
    return;
  }

  auto mid = std::next(begin, size / 2);
  sort_merge(begin, mid);
  sort_merge(mid, end);

  auto &&v = merge(begin, mid, end);
  std::move(v.cbegin(), v.cend(), begin);
}

/*
  Tri par bulles
  Source: https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Bubble_sort#C.2B.2B
*/

template<typename Iterator>
void sort_bubble(Iterator first, Iterator last)
{
  Iterator i, j;
  for (i = first; i != last; i++)
  {
    for (j = first; j != i; j++)
    {
      if (*i < *j)
      {
        std::iter_swap(i, j); // or std::swap(*i, *j);
      }
    }
  }
}

/*
  Quicksort 
  source : http://arsenmk.blogspot.ca/2013/03/quick-sort-implementation.html
*/

 template <typename Iterator>
void sort_quick(Iterator begin, Iterator end)
{
       if (std::distance(begin, end) < 2)
       {
              return;
       }

       Iterator pivot = begin;
       std::advance(pivot, std::distance(begin, end) / 2);
       std::iterator_traits<Iterator>::value_type val = *pivot;

       Iterator left = begin;
       Iterator right = end;

       std::advance(right, -1);

       std::swap(*pivot, *right);

       Iterator pivot_position = left;

       while (left != right)
       {
              if (*left < val)
              {
                     std::swap(*left, *pivot_position);
                     std::advance(pivot_position, 1);
              }
              std::advance(left, 1);
       }

       std::swap(*pivot_position, *right);

       right = pivot_position;
       std::advance(right, 1);

       sort_quick(begin, pivot_position);
       sort_quick(right, end);
}

/*
  Tri par insertion
  source: http://stackoverflow.com/questions/18453945/c-generic-insertion-sort
*/

template<typename Iterator>
void sort_insertion(Iterator first, Iterator last)
{
  for (Iterator it = first; it != last; ++it)
  {
    std::rotate(std::upper_bound(first, it, *it), it, std::next(it));
  }
}

/*
  Tri par tas 
  Le tri par tas est dans les fonctions standards
  mais il faut d'abord créer le tas.
*/
template<typename Iterator>
void sort_heap(Iterator begin, Iterator end)
{
  std::make_heap(begin, end);
  std::sort_heap(begin, end);
}

/*
  Tri par base
*/




