
/*
  Devoir 1, Ex1 Strassen 
  Julien De Loor (julien.de-loor1@uqac.ca)
  Le code est décomposé en 2 classes:
   - MatrixData qui représente les donnés en mémoire d'une matrice (grosse matrice)
   - Matrix qui représente une matrice, plusieurs Matrix peuvent avoir la même MatrixData si elles sont 
   copiées.
*/

#pragma once

#include <cmath>
#include <cstdint>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip> //Format text


#include "../common/smartcopyableobjects.hpp"
#include "../common/mathutils.hpp"



//Class that contains our heavy matrix data 
template<typename real=double>
class MatrixData
{
private:
  size_t _rows;
  size_t _columns;
  std::vector<real> _matrix;

public:
  //Constructor 
  MatrixData(size_t rows, size_t cols):
    _rows(rows),
    _columns(cols),
    _matrix(_rows*_columns,0)
  {

  }

  //Copy constructor
  MatrixData(const MatrixData& m):
    _rows(m._rows),
    _columns(m._columns),
    _matrix(m._matrix)
  {
  }

  //Copy assignement
  inline MatrixData& operator= (const MatrixData& m)
  {
    _rows = m._rows;
    _columns = m._columns;
    _matrix = m._matrix;
    return *this;
  }

  // Get sizes 
  inline size_t rows() const { return _rows;  }
  inline size_t columns() const { return _columns;  }
  inline size_t size() const { return _matrix.size();  }


  // setters/getters 
  inline void set(size_t row, size_t col, real value)
  {
    assert(row < rows() && "row out of range");
    assert(col < columns() && "col out of range");

    _matrix.at(row*col + col) = ;
  }

  inline const real& get(size_t row, size_t col) const
  {
    assert(row < rows() && "row out of range");
    assert(col < columns() && "col out of range");

    return _matrix.at(row*columns() + col);
  }

  inline real& get(size_t row, size_t col) 
  {
    assert(row < rows() && "row out of range");
    assert(col < columns() && "col out of range");

    return _matrix.at(row*columns() + col);
  }


  // Beautifull getters with overloading
  inline real& operator() (size_t row, size_t col)
  {
    return get(row, col);
  }

  inline real operator() (size_t row, size_t col) const
  {
    return get(row, col);
  }


  //Utility
  inline void fill(real value)
  {
    std::fill(_matrix.begin(), _matrix.end(), value);
  }

  inline void zeroes()
  {
    fill(0);
  }

  inline void random(real min, real max)
  {
    std::vector<real>::iterator it;
    for (it = _matrix.begin(); it != _matrix.end(); it++)
    {
      *it = randomRangeReal(min, max);
    }
  }

  //resize and erase matrix
  inline void erase(size_t row, size_t cols)
  {
    _rows = row;
    _columns = cols;
    _matrix.resize(_rows * _columns);
    zeroes();
  }

  //Math Operators
  static void add(const MatrixData& a, const MatrixData& b, MatrixData& result)
  {
    assert(a.rows() == b.rows());
    assert(a.columns() == b.columns());

    size_t rows = a.rows();
    size_t columns = a.columns();

    result.erase(rows, columns);
    for (size_t n = 0; n < result.size(); n++)
    {
      result._matrix[n] = a._matrix[n] + b._matrix[n];
    }

  }

  static void sub(const MatrixData& a, const MatrixData& b, MatrixData& result)
  {
    assert(a.rows() == b.rows());
    assert(a.columns() == b.columns());

    size_t rows = a.rows();
    size_t columns = a.columns();

    result.erase(rows, columns);
    for (size_t n = 0; n < result.size(); n++)
    {
      result._matrix[n] = a._matrix[n] - b._matrix[n];
    }
  }

  static bool isEqual(const MatrixData& a, const MatrixData& b, real eps)
  {
    if (a.rows() != b.rows() ||
      a.columns() != b.columns())
    {
      return false;
    }

    for (size_t n = 0; n < a.size(); n++)
    {
      if (isRealEqual(a._matrix[n], b._matrix[n], eps)==false)
      {
        return false;
      }
    }
    return true;
  }
  

  MatrixData& operator+=(const MatrixData& m)
  {
    assert(rows() == m.rows());
    assert(columns == m.columns());
    for (size_t n = 0; n < size(); n++)
    {
      _matrix[n] += m._matrix[n];
    }
  }

  MatrixData& operator-=(const MatrixData& m)
  {
    assert(rows() == m.rows());
    assert(columns == m.columns());
    for (size_t n = 0; n < size(); n++)
    {
      _matrix[n] -= m._matrix[n];
    }
  }

  /*
    Strassen
    J'ai utilisé wikipedia comme principale source (https://fr.wikipedia.org/wiki/Algorithme_de_Strassen)
    C = A * B

    Pour chaque matrice M la notation suivante est utilisé pour découper la matrice en 4 sous matrices:

    M = [ M11 M12
          M21 M22 ]

    On effectue ce traitement pour A, B et C. Le reste des opérations sont tirés de wikipédia
    (voir plus bas)
  
  */

  static void strassen(const MatrixData<real>& a, const MatrixData<real>& b, MatrixData<real>& c, size_t n)
  {
    assert(a.rows() == n && a.columns() == n);
    assert(b.rows() == n && b.columns() == n);
    assert(c.rows() == n && c.columns() == n);
    assert(isPowerOfTwo(n));

    if (n == 1)
    {
      c(0,0) = a(0,0) * b(0,0);
    }
    else
    {
      const size_t next_n = n / 2;
      MatrixData<real> a11(next_n, next_n), a12(next_n, next_n), a21(next_n, next_n), a22(next_n, next_n);
      MatrixData<real> b11(next_n, next_n), b12(next_n, next_n), b21(next_n, next_n), b22(next_n, next_n);
      MatrixData<real> c11(next_n, next_n), c12(next_n, next_n), c21(next_n, next_n), c22(next_n, next_n);

      MatrixData<real> m1(next_n, next_n), m2(next_n, next_n), m3(next_n, next_n), m4(next_n, next_n);
      MatrixData<real> m5(next_n, next_n), m6(next_n, next_n), m7(next_n, next_n);

      for (size_t i=0; i < next_n; i++)
      {
        for (size_t j = 0; j < next_n; j++)
        {
          a11(i,j) = a(i,j);
          a12(i,j) = a(i, j + next_n);
          a21(i,j) = a(i + next_n, j);
          a22(i,j) = a(i + next_n, j + next_n);

          b11(i,j) = b(i,j);
          b12(i,j) = b(i, j + next_n);
          b21(i,j) = b(i + next_n, j);
          b22(i,j) = b(i + next_n, j + next_n);
        }
      }

      MatrixData<real> ra(next_n,next_n), rb(next_n,next_n); //Pour stocker les resultats des additions
      MatrixData<real>::add(a11,a22,ra);            // a11 + a22
      MatrixData<real>::add(b11, b22, rb);          // b11 + b22
      MatrixData<real>::strassen(ra,rb,m1,next_n);  // m1 = (a11+a22) * (b11+b22)

      MatrixData<real>::add(a21, a22, ra);          // a21 + a22
      MatrixData<real>::strassen(ra,b11,m2,next_n); // m2 = (a21+a22) * (b11)

      MatrixData<real>::sub(b12, b22, rb);          // b12 - b22
      MatrixData<real>::strassen(a11,rb,m3,next_n); // m3 = (a11) * (b12 - b22)
      
      MatrixData<real>::sub(b21, b11, rb);          // b21 - b11
      MatrixData<real>::strassen(a22,rb,m4,next_n); // m4 = (a22) * (b21 - b11)

      MatrixData<real>::add(a11, a12, ra);          // a11 + a12
      MatrixData<real>::strassen(ra,b22,m5,next_n); // m5 = (a11+a12) * (b22)

      MatrixData<real>::sub(a21, a11, ra);          // a21 - a11
      MatrixData<real>::add(b11, b12, rb);          // b11 + b12
      MatrixData<real>::strassen(ra,rb,m6,next_n);  // m6 = (a21-a11) * (b11+b12)

      MatrixData<real>::sub(a12, a22, ra);          // a12 - a22 
      MatrixData<real>::add(b21, b22, rb);          // b21 + b22
      MatrixData<real>::strassen(ra,rb,m7,next_n);  // m7 = (a12-a22) * (b21+b22)
      

      //Compute C values
      MatrixData<real>::add(m3, m5, c12);           // c12 = m3 + m5
      MatrixData<real>::add(m2, m4, c21);           // c21 = m2 + m4

      MatrixData<real>::add(m1, m4, ra);            // m1 + m4
      MatrixData<real>::add(ra, m7, rb);            // m1 + m4 + m7
      MatrixData<real>::sub(rb, m5, c11);           // c11 = m1 + m4 - m5 + m7
      
      MatrixData<real>::add(m1, m3, ra);            // m1 + m3
      MatrixData<real>::add(ra, m6, rb);            // m1 + m3 + m6
      MatrixData<real>::sub(rb, m2, c22);           // c22 = m1 + m3 - m2 + m6

      for (size_t i = 0; i < next_n; i++)
      {
        for (size_t j = 0; j < next_n; j++)
        {
          c(i, j) = c11(i, j);
          c(i, j + next_n) = c12(i, j);
          c(i + next_n, j) = c21(i, j);
          c(i + next_n, j + next_n) = c22(i, j);
        }
      }
    }
  }
  
  static void mul(const MatrixData<real>& a, const MatrixData<real>& b, MatrixData<real>& r)
  {
    size_t n = a.rows();
    assert(a.columns() == n);
    assert(b.rows() == n && b.columns() == n);

    r.erase(n, n);
    MatrixData<real>::strassen(a, b, r, n);
  }

  static void mul_naive(const MatrixData<real>& a, const MatrixData<real>& b, MatrixData<real>& r)
  {
    assert(a.rows() == b.rows());
    assert(a.columns() == b.columns());

    size_t rows = a.rows();
    size_t columns = a.columns();

    r.erase(rows, columns);

    for (size_t i = 0; i < a.rows(); i++)
    {
      for (size_t j = 0; j < b.columns(); j++)
      {
        for (size_t k = 0; k < a.columns(); k++)
        {
          r(i, j) += a(i, k)*b(k, j);
        }
      }
    }
  }

};



template<typename real=double>
class Matrix : public SmartCopyableObject<MatrixData<real>>
{
public:
  //Constructor
  Matrix(size_t rows, size_t cols):
    SmartCopyableObject(new MatrixData<real>(rows, cols))
  {

  }

  //Copy constructor
  Matrix(const Matrix& m):
    SmartCopyableObject(m)
  {

  }

  //Copy assignment
  const Matrix& operator= (const Matrix& m)
  {
    smartcopy(m);
    return *this;
  }

  // Get sizes 
  inline size_t rows() const { return _object->rows(); }
  inline size_t columns() const { return _object->columns(); }
  inline size_t size() const { return _object->size(); }


  // setters/getters 
  inline void set(size_t row, size_t col, real value)
  {
    ensureUnique();
    _object->reset(row, col, value);
  }

  inline const real& get(size_t row, size_t col) const
  {
    return _object->get(row, col);
  }

  inline real& get(size_t row, size_t col)
  {
    ensureUnique();
    return _object->get(row, col);
  }


  // Beautifull getters with overloading
  inline real& operator() (size_t row, size_t col)
  {
    return get(row, col);
  }

  inline real operator() (size_t row, size_t col) const
  {
    return get(row, col);
  }

  inline bool isSquareMatrix() const
  {
    return (rows() == columns());
  }

  static bool isEqual(const Matrix& a, const Matrix& b, real eps=0.0001)
  {
    if (a._object.get() == b._object.get())
    {
      return true;
    }
    return (MatrixData<real>::isEqual(*(a._object),*(b._object),eps));
  }

  inline static Matrix add(const Matrix& a, const Matrix& b)
  {
    assert(a.rows() == b.rows());
    assert(a.columns == b.columns());

    size_t rows = a.rows();
    size_t columns = a.columns();

    Matrix m(rows, columns);
    MatrixData<real>::add(*(a._object), *(b._object), *(m._object));
    return m;
  }

  inline static Matrix sub(const Matrix& a, const Matrix& b)
  {
    assert(a.rows() == b.rows());
    assert(a.columns() == b.columns());

    size_t rows = a.rows();
    size_t columns = a.columns();

    Matrix m(rows, columns);
    MatrixData<real>::sub(*(a._object), *(b._object), *(m._object));
    return m;
  }

  inline static Matrix mul(const Matrix& a, const Matrix& b)
  {
    assert(a.rows() == b.columns());
    assert(a.columns() == b.rows());

    size_t rows = a.rows();
    size_t columns = b.columns();

    Matrix m(rows, columns);
    MatrixData<real>::mul(*(a._object), *(b._object), *(m._object));
    return m;
  }

  inline static Matrix mul_naive(const Matrix& a, const Matrix& b)
  {
    size_t rows = a.rows();
    size_t columns = b.columns();

    Matrix m(rows, columns);
    MatrixData<real>::mul_naive(*(a._object), *(b._object), *(m._object));
    return m;
  }

  Matrix operator+ (const Matrix& m) const
  {
    return Matrix::add(*this, m);
  }

  Matrix operator- (const Matrix& m) const
  {
    return Matrix::sub(*this, m);
  }
  
  Matrix operator* (const Matrix& m) const
  {
    return Matrix::mul(*this, m);
  }

  Matrix& operator+= (const Matrix& m)
  {
    ensureUnique();
    *_object += *(m._object);
    return *this;
  }

  Matrix& operator-= (const Matrix& m)
  {
    ensureUnique();
    *_object -= *(m._object);
    return *this;
  }

  bool operator== (const Matrix& m)
  {
    return Matrix<real>::isEqual(*this, m);
  }

  inline void fill(real value)
  {
    ensureUnique();
    _object->fill(value);
  }

  inline void zeroes()
  {
    ensureUnique();
    _object->zeroes();
  }

  inline void random(real min, real max)
  {
    ensureUnique();
    _object->random(min, max);
  }
  

  inline void print()
  {
    std::cout << "Matrix (" << this << ") MatrixData (" << _object.get() << ") [" << rows() << "x" << columns() << "]" << std::endl;
    for (size_t i = 0; i < rows(); i++)
    {
      for (size_t j = 0; j < columns(); j++)
      {
        std::cout << std::fixed << std::setw(7) << std::setprecision(2) << std::setfill(' ') <<  get(i, j) << " ";
      }
      std::cout << std::endl;
    }
  }

};

typedef Matrix<float> Matrixf;
