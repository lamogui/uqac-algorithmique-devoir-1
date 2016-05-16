
#pragma once

/*
  Devoir 1, Ex2 Tri 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Les diffrents algo de tri, adaptés pour qu'ils 
  aient tous le même style et pour qu'ils soient 
  tous utilisables de la même manière avec des iterateur c++.
  Certains sont codés depuis 0 d'autres non.
  Il y a la source sur laquelle je me suis basé avec chaque fonction 
*/

#include <algorithm>
#include <iterator>
#include <vector>


/*
  Tri par fusion 
  Sources:
   - https://fr.wikipedia.org/wiki/Tri_fusion
   - http://codereview.stackexchange.com/questions/78129/merge-sort-in-c-with-Iterators

  L'algorithme est composé de 2 fonctions:
   - Une fonction fusion (merge) qui prend en entre 2 tableaux (ici les 2 tableaux a la 
     suite dans le même vector d'ou le fait que l'on utilise 3 iterators au lieu de 2 tableaux).
     Cette fonction crée un nouveau tableau avec l'ensemble des elements triés dans l'autre

     Fonction fusion(T1, T2):
      Créer un nouveau tableau T
      Pour chaque element des 2 tableaux:
        Si element T1 <= element T2
          ajouter à T element courant de T1 
          element courant de T1 = element suivant de T1
        Sinon
          ajouter à T element courant de T2
          element courant de T2 = element suivant de T2

      ajouter les elements restants de T1 à T
      ajouter les elements restant de T2 à T
     Fin fonction

   - Une fonction triFusion (sort_merge) qui prend en entré un tableau. 
     Fonction triFusion(T):
      si T contient un seul element:
        Fin fonction
      sinon:
        Créer T1 et T2 en coupant le tableau T au milieu
        triFusion(T1)
        triFusion(T2)
        fusion(T1,T2) dans T
     Fin fonction
     
*/

template<typename Iterator>
std::vector<typename Iterator::value_type> merge(const Iterator begin, const Iterator mid, const Iterator end)
{
  std::vector<typename Iterator::value_type> v;
  v.reserve(std::distance(begin, end));
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
  size_t size = std::distance(begin, end);
  if (size < 2)
  {
    return;
  }

  Iterator mid = std::next(begin, size / 2);
  sort_merge(begin, mid);
  sort_merge(mid, end);

  std::vector<typename Iterator::value_type> &&v = merge(begin, mid, end);
  std::move(v.cbegin(), v.cend(), begin);
}

/*
  Tri par bulles
  Source: codé depuis 0 avec https://fr.wikipedia.org/wiki/Tri_%C3%A0_bulles

  Fonction triBulles(T):
    Parcourir les elements i de T dans le sens inverse
      Parcourir les elements j de T du debut jusqu'à i
        Si element j+1 < element j
          echanger elements j et j+1
  Fin fonction

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
        std::iter_swap(i, j); 
      }
    }
  }
}

/*
  Quicksort 
  Sources : 
   - https://openclassrooms.com/courses/le-tri-rapide-qsort
   - http://arsenmk.blogspot.ca/2013/03/quick-sort-implementation.html

   Fonction Quicksort(debut,fin)
    gauche = debut
    droite = fin-1
    Selectionner un pivot entre debut et fin 
    echanger valeur droite et valeur pivot
    Tant que gauche != droite:
      Si gauche < pivot
        echanger valeur gauche avec valeur pivot
        pivot = pivot + 1
      gauche = gauche + 1
    echanger valeur droite et valeur pivot
    droite = pivot + 1 
    Quicksort(debut,pivot)
    Quicksort(droite,fin)
   Fin Fonction


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
  Quicksort rand
  La même chose que le précédent sauf que le
  pivot est séléctionné aléatoirement
  */

template <typename Iterator>
void sort_quick_rand(Iterator begin, Iterator end)
{
  if (std::distance(begin, end) < 2)
  {
    return;
  }

  Iterator pivot = begin;
  std::advance(pivot, randomRange(0, std::distance(begin, end))); //Ligne modifiée ici
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
  Source:
   - https://fr.wikipedia.org/wiki/Tri_par_insertion
   - http://stackoverflow.com/questions/18453945/c-generic-insertion-sort

  Fonction triInsertion(T)
    Pour tous les elements i de T
      Pour tous les elements j depuis le debut de T jusqu'à i
        Si element j > element i alors
          echanger les elements de [j , i+1] vers [i , j]
  Fin fonction

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
  Source: codé depuis zéro à partir de https://fr.wikipedia.org/wiki/Tri_par_tas#Pseudo-code

  Le tri par tas utilise 2 fonctions
   - Une fonction tamiser (sift ?)  
      Fonction tamiser(arbre, noeud, n) :
        k = noeud
        j = 2 * k
        Tant que j <= n
          si j < n et element j < element j+1
            j = j+1
          Si element k < element j
            échanger element k avec element j
            k = j
            j = 2 * k
          Sinon
            Fin Fonction
      Fin fonction
    - Une triTas
       Fonction triTas(T)
        Pour tout les elements i de T jusqu'à la moitié de T
          tamiser(T, i, taille de T)
        Pour tout les elements i de T dans l'ordre inverse
          echanger element i avec element 0
          tamiser(T, 1, i-1)
       Fin Fonction
*/


//Fonction "tamiser" de wikipedia la traduction n'est peut-être pas correcte
template <typename Iterator>
void sift(Iterator tree_begin, size_t node, size_t n)
{
  size_t k = node;
  size_t j = 2 * k;
  while (j <= n)
  {
    if (j < n && *(tree_begin+j) < *(tree_begin+j+1))
    {
      j++;
    }
    if (*(tree_begin + k) < *(tree_begin + j))
    {
      std::iter_swap(tree_begin + k, tree_begin + j);
      k = j;
      j = 2 * k;
    }
    else
    {
      break;
    }
  }
}

template<typename Iterator>
void sort_heap(Iterator begin, Iterator end)
{
  size_t length = std::distance(begin, end) - 1;
  for (int64_t i = (int64_t)(length >> 1); i >= 0; i--)
  {
    sift(begin, (size_t)i, length);
  }
  for (size_t i = length; i > 0; i--)
  {
    std::iter_swap(begin + i, begin);
    sift(begin, 0, i - 1);
  }
}


/*
  Tri par base
  Seul les nombres non signés sont triés correctements
  Source: codé depuis zéro à partir de http://www.giacomazzi.fr/infor/Tri/TRadix.htm 

  Fonction triBase(T)
    Creer 2 tableaux T0 et T1 
    Pour chaque bit (du moins significatif vers le plus significatif)
      Pour chaque élément du tableau (du premier vers le dernier)
        Créer un masque avec le bit concerné
        Si l'element AND masque
          placer l'element dans T1
        Sinon 
          placer l'element dans T0

      ecraser T par un tableau vide
      Pour chaque element de T0
        ajouter l'element a T
      Pour chaque element de T1
        ajouter l'element a T
  Fin fonction
*/
template <typename Iterator>
void sort_radix(Iterator begin, Iterator end)
{
  size_t bits = sizeof(std::iterator_traits<Iterator>::value_type) * 8;
  size_t size = std::distance(begin, end);
  std::vector<std::iterator_traits<Iterator>::value_type> bit_0_vec, bit_1_vec;
  std::vector<std::iterator_traits<Iterator>::value_type>::iterator bit_it;
  for (size_t b = 0; b < bits; b++)
  {
    uint64_t mask = 1 << b;
    bit_0_vec.clear(); bit_0_vec.reserve(size);
    bit_1_vec.clear(); bit_1_vec.reserve(size);
    for (Iterator it = begin; it != end; it++)
    {
      if ((uint64_t)(*it) & mask)
      {
        bit_1_vec.push_back(*it);
      }
      else
      {
        bit_0_vec.push_back(*it);
      }
    }

    Iterator it = begin;
    for (bit_it = bit_0_vec.begin(); bit_it != bit_0_vec.end(); bit_it++)
    {
      *it = *bit_it;
      ++it; 
    }
    for (bit_it = bit_1_vec.begin(); bit_it != bit_1_vec.end(); bit_it++)
    {
      *it = *bit_it;
      ++it; 
    }
  }
}

/*
std::sort_heap
Le tri par tas est dans les fonctions standards
mais il faut d'abord créer le tas d'ou ce wrapper.
*/
template<typename Iterator>
void std_sort_heap(Iterator begin, Iterator end)
{
  std::make_heap(begin, end);
  std::sort_heap(begin, end);
}
