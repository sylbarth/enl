/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_VECTOR_H
#define _ENL_VECTOR_H

#include "enl_matrix.h"

// forward declarations
template <class T> class enl_vector;
#define enl_vectorT enl_vector<T>

template <class T> enl_vectorT enl_conj(const enl_vectorT &);
template <class T> T           enl_dot (const enl_vectorT &, const enl_vectorT &);
template <class T> T           enl_norm(const enl_vectorT &);

template <class T> 
class enl_vector : public enl_matrix<T> {

public:
  // constructors and destructor
  enl_vector ();
  explicit enl_vector (const long& r, const T& t = T(0));
  enl_vector (const enl_vectorT& v);

  // assignment
  enl_vectorT& operator=(const enl_vectorT& v);
  enl_vectorT& operator=(const T&			c);

  T& operator[](const long& n);
  const T& operator[](const long& n) const;

  // enl_vector operations
  enl_vectorT& operator+= (const enl_vectorT &);
  enl_vectorT& operator-= (const enl_vectorT &);
  enl_vectorT  operator+  (const enl_vectorT &) const;
  enl_vectorT  operator-  (const enl_vectorT &) const;

  // arithmetic operations
  enl_vectorT& operator*= (const T &);
  enl_vectorT& operator/= (const T &);
  enl_vectorT  operator*  (const T &) const;
  enl_vectorT  operator/  (const T &) const;
  friend enl_vectorT operator* (const T &n, const enl_vectorT &v) {
    return(enl_vectorT(v) *= n);
  }

  // logical operators
  int operator==(const enl_vectorT &) const;
  int operator!=(const enl_vectorT &) const;

  // enl_vector products
  friend enl_vectorT enl_conj(const enl_vectorT &);
  friend T           enl_dot (const enl_vectorT &, const enl_vectorT &);
  friend T           enl_norm(const enl_vectorT &);

};

template <class T> inline
enl_vectorT::enl_vector():
  enl_matrix<T>(0,0,T(0))
{
}

template <class T> inline
enl_vectorT::enl_vector(const long& r,const T& t):
  enl_matrix<T>(r,1,T(t))
{
}

template <class T> inline 
enl_vectorT::enl_vector(const enl_vectorT& v):
  enl_matrix<T>(v.nr,1,T(0))
{
  for (long i=0; i<nr; i++)
    mat[i][0] = v.mat[i][0];
}

// assignment 
template <class T> inline
enl_vectorT& enl_vectorT::operator=(const enl_vectorT& v)
{
  if (mat == v.mat) return(*this);
	
	resize(v.nr,v.nc);

  for (long i=0; i<nr; i++)
    for(long j=0; j<nc; j++)
      mat[i][j] = v.mat[i][j];

  return *this;
}

template <class T> inline
enl_vectorT& enl_vectorT::operator=(const T& c)
{
  for (long i=0; i<nr; i++)
    mat[i][0] = c;
  return *this;
}

template <class T> inline
T& enl_vectorT::operator[](const long& n)
{
  if ( n >= nr )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");
  if ( n < 0 )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");  
  return mat[n][0];
}

template <class T> inline
const T& enl_vectorT::operator[](const long& n) const
{
  if ( n >= nr )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");
  if ( n < 0 )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");  
  return mat[n][0];
}

// vector operations
template <class T> inline
enl_vectorT& enl_vectorT::operator+=(const enl_vectorT& v)
{
  if ( nr != v.nr )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");
  for (long i = 0; i<nr; i++)
      mat[i][0] += v.mat[i][0];
  return *this;
}

template <class T> inline
enl_vectorT& enl_vectorT::operator-=(const enl_vectorT& v)
{
  if ( nr != v.nr )
    REPORT_ERROR( "enl_vector::operator(): Index out of range!");
  for (long i = 0; i<nr; i++)
      mat[i][0] -= v.mat[i][0];
  return *this;
}

template <class T> inline
enl_vectorT enl_vectorT::operator+(const enl_vectorT& v) const
{
  return enl_vectorT(*this) += v;
}

template <class T> inline
enl_vectorT enl_vectorT::operator-(const enl_vectorT& v) const
{
  return enl_vectorT(*this) -= v;
}

// vector and scalar operations
template <class T> inline enl_vectorT& enl_vectorT::operator*=(const T &n)
{
  if ( nr <= 0 )
    REPORT_ERROR( "enl_vector::operator*=: Index out of range!");  
  for (long i=0; i<nr; i++)
    mat[i][0] *= n;
  return *this;
}

template <class T> inline
enl_vectorT& enl_vectorT::operator/=(const T &n)
{
  if ( nr <= 0 )
    REPORT_ERROR( "enl_vector::operator/=: Index out of range!");  
  if ( n == 0 )
    REPORT_ERROR( "enl_vector::operator/=: div by 0!");  
  for (long i=0; i<nr; i++)
    mat[i][0] /= n;
  return *this;
}

template <class T> inline
enl_vectorT enl_vectorT::operator*(const T &n) const
{
  return enl_vectorT(*this) *= n;
}

template <class T> inline
enl_vectorT enl_vectorT::operator/(const T &n) const
{
  return enl_vectorT(*this) /= n;
}

// logical operators
template <class T> inline
int enl_vectorT::operator==(const enl_vectorT &v) const
{
  return *this==v;
}

template <class T> inline
int enl_vectorT::operator!=(const enl_vectorT &v) const
{
  return !(*this== v);
}

// vector products
inline double conj(const double& d) { return(d); }
inline float  conj(const float&  f) { return(f); }
inline int    conj(const int&    i) { return(i); }

template <class T> inline
enl_vectorT enl_conj(const enl_vectorT &v)
{
  if ( v.nr <= 0 )
    REPORT_ERROR( "enl_vector::enl_conj=: Index out of range!");  
  enl_vectorT tmp(v.nr);
  for (long i=0; i<v.nr; i++)
    tmp[i] = conj(v[i]);
  return tmp;
}

template <class T> inline
T enl_dot(const enl_vectorT &v1, const enl_vectorT &v2)
{
  if ( v1.nr <= 0 )
    REPORT_ERROR( "enl_vector::enl_dot=: Index out of range!");  
  if ( v2.nr <= 0 )
    REPORT_ERROR( "enl_vector::enl_dot=: Index out of range!");  

  // calculate dot product
  T sum = T(0);
  long maxd = (v1.nr < v2.nr) ? v1.nr : v2.nr;
  for (long i=0; i<maxd; i++)
    sum += v1[i]*conj(v2[i]);

  return sum;
}

template <class T> inline
T enl_norm(const enl_vectorT &v)
{
  return(sqrt(dot(v,v)));
}


#endif
