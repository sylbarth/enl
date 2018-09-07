/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_MATRIX_H_
#define _ENL_MATRIX_H_

#include <stdlib.h>
#include <math.h>
#include <iostream.h>
#include <vector>

// --- forward decl
class enl_tseries;
template <class T> class enl_vector;
template <class T> class enl_matrix;

// --- error manag
#define enl_matrixT enl_matrix<T>

inline void _enl_matrix_error (const char* pMsg)
{
  printf("%sn",pMsg);
  exit(1);
}

#define REPORT_ERROR(msg)  _enl_matrix_error(msg);

// --- matrix class
template <class T>
class enl_matrix {

protected:
  T       init;
  T**     mat; // data
  long  nr;  // num rows
  long  nc;  // num cols
  T       det; // determinant


	void realloc (const long& r, const long& c);

public:
  // --- constructors
  enl_matrix ();
  explicit enl_matrix (const long& r, const long& c, const T& t = T(0));
  enl_matrix (const enl_matrixT& m);
	virtual ~enl_matrix();

  // --- assignment operators
  enl_matrixT& operator= (const enl_matrixT& m);
  enl_matrixT& operator= (const T& c);

  // --- alloc
  void empty();
  void resize(const long& r, const long& c = 1);

  // --- subscript operator
  T* operator[] (const long& n);
  const T* operator[] (const long& n) const;
//  std::vector<T>& operator[] (const long& n);
//  const std::vector<T>& operator[] (const long& n) const;

  // --- unary operators
  enl_matrixT operator+() const;
  enl_matrixT operator-() const;

  // --- Combined assignment - calculation operators
  enl_matrixT& operator+= (const enl_matrixT& m);
  enl_matrixT& operator-= (const enl_matrixT& m);
  enl_matrixT& operator*= (const enl_matrixT& m);
  enl_matrixT& operator/= (const enl_matrixT& m);

  enl_matrixT& operator+= (const T& c);
  enl_matrixT& operator-= (const T& c);
  enl_matrixT& operator*= (const T& c);
  enl_matrixT& operator/= (const T& c);

  enl_matrixT& operator^= (const long& pow);

  // Calculation operators
  friend enl_matrixT operator+ (const enl_matrixT& m1, const enl_matrixT& m2);
  friend enl_matrixT operator- (const enl_matrixT& m1, const enl_matrixT& m2);
  friend enl_matrixT operator* (const enl_matrixT& m1, const enl_matrixT& m2);
  friend enl_matrixT operator/ (const enl_matrixT& m1, const enl_matrixT& m2);

  friend enl_matrixT operator+ (const enl_matrixT& m,  const T& c);
  friend enl_matrixT operator- (const enl_matrixT& m,  const T& c);
  friend enl_matrixT operator* (const enl_matrixT& m,  const T& c);
  friend enl_matrixT operator/ (const enl_matrixT& m,  const T& c);

  friend inline enl_matrixT operator+ (const T& c, const enl_matrixT& m) { enl_matrixT ret =  m; return  ret+=c; }
  friend inline enl_matrixT operator- (const T& c, const enl_matrixT& m) { enl_matrixT ret = -m; return  ret+=c; }
  friend inline enl_matrixT operator* (const T& c, const enl_matrixT& m) { enl_matrixT ret =  m; return  ret*=c; }
  friend inline enl_matrixT operator/ (const T& c, const enl_matrixT& m) { enl_matrixT ret =  enl_invert(m); return  ret*=c; }

  friend enl_matrixT operator^ (const enl_matrixT& m, const long& pow);

  // --- logical operators
  friend bool operator== (const enl_matrixT& m1, const enl_matrixT& m2);
  friend bool operator!= (const enl_matrixT& m1, const enl_matrixT& m2);

  // --- member utility methods
  void identity();
  T GetDeterminant() const;
  T GetNorm       () const;
  T GetCofactor   (const long& r, const long& c) const;
  T GetCondition  () const;

  // --- friend utility methods
  friend enl_matrixT enl_transpose(const enl_matrixT& m);
  friend enl_matrixT enl_invert   (const enl_matrixT& m);
  friend enl_matrixT enl_adjoin   (const enl_matrixT& m);

  // --- append vectors
  friend void operator<< (enl_matrixT& m, const enl_vector<T>& v);
  friend void operator<< (enl_matrixT& m, const enl_tseries&   v);

  // --- misc func
  inline long nrows() const { return nr; }
  inline long ncols() const { return nc; }
  inline long nelem() const { return nr*nc; }
  void dump(ostream& os) const;
  friend ostream& operator<< (ostream& ostrm, const enl_matrixT& m);
};

// constructor
template <class T>
inline enl_matrixT::enl_matrix() : 
  mat (0),
  nr  (0),
  nc  (0),
	init(T(0))
{
}

template <class T>
inline enl_matrixT::enl_matrix(const long& r, const long& c, const T& t) : 
  mat (0),
  nr  (r),
  nc  (c),
	init(t)
{
		if( (nr==0) || (nc==0) ) {
			nr = 0;
			nc = 0;
			return;
		}
  mat = new T* [nr];
  for (long i=0; i<nr; i++) {
    mat[i] = new T [nc];
    for(long j=0; j<nc; j++)
      mat[i][j] = t;
  }
}

// copy constructor
template <class T>
inline enl_matrixT::enl_matrix(const enl_matrixT& m) : 
  mat (0),
  nr  (m.nr),
  nc  (m.nc),
	init(m.init)
{
  if( (nr==0) || (nc==0) ) {
    nr = 0;
    nc = 0;
    return;
  }
  mat = new T* [nr];
  for (long i=0; i<nr; i++) {
    mat[i] = new T [nc];
    for(long j=0; j<nc; j++)
      mat[i][j] = m.mat[i][j];
  }
}

template <class T>
inline enl_matrixT::~enl_matrix()
{
  empty();
}


// assignment operator
template <class T>
inline enl_matrixT& enl_matrixT::operator= (const enl_matrixT& m) 
{
  if (mat == m.mat) return *this;

  if (nr != m.nr || nc != m.nc)
    resize(m.nr,m.nc);

	init = m.init;

  for (long i=0; i<nr; i++)
    for(long j=0; j<nc; j++)
      mat[i][j] = m.mat[i][j];
  
  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator= (const T& c) 
{
  for (long i=0; i<nr; i++)
    for(long j=0; j<nc; j++)
      mat[i][j] = c;
  return *this;
}

  // --- empty/resize
template <class T>
inline void enl_matrixT::empty()
{ 
  for (long i=0; i < nr; i++)
    if(mat[i]) delete[] mat[i];
  if(mat) delete[] mat;
  mat = 0;
  nr  = 0;
  nc  = 0;
}
  
//  reallocation method
template <class T> 
inline void enl_matrixT::realloc (const long& r, const long& c)
{
  long i,j;
  if ( (r==nr) && (c==nc) ) return;

  // --- alloc nouvelle mat
  T** mat1 = new T* [r];
  for (i=0; i<r; i++)
    mat1[i] = new T [c];

  // --- copie ancienne mat
  if( (nr>0) && (nc>0) ) {
    long min_nr = min(nr,r);
    long min_nc = min(nc,c);
    
    for (i=0; i<min_nr; i++)
      for (j=0; j<min_nc; j++)
	mat1[i][j] = mat[i][j];

    for (i=0; i<nr; i++)
      if(mat[i]) delete[] mat[i];
    if(mat) delete[] mat;
  }

  //--- affectation nouvelle mat
  mat = mat1;
  nr  = r;
  nc  = c;

  return;
}

template <class T> 
inline void enl_matrixT::resize (const long& r, const long& c)
{
//  long i,j;
  long oldRow = nr;
  long oldCol = nc;

  if ( (r!= nr) || (c!=nc) )
    realloc(r,c);

  if ( (r==0) || (c==0) )
    return;
  /*
    if (r > oldRow) {
    for (i=oldRow; i<nr; i++)
    for (j=0; j<nc; j++)
    mat[i][j] = init;
    }
    if (c > oldCol) {
    for (i=0; i<nr; i++)
    for (j=oldCol; j<nc; j++)
    mat[i][j] = init;
    }
  */
  return;
}

// --- access
template <class T>
inline T* enl_matrixT::operator[] (const long& n)
{
  return mat[n];
}

template <class T>
inline const T* enl_matrixT::operator[] (const long& n) const
{
  return (const_cast<enl_matrixT*>(this))->mat[n];
}

// logical equal-to operator
template <class T>
inline bool operator== (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  bool retmat = false;

  if (m1.nrows() != m2.nrows() || m1.ncols() != m2.ncols())
    return retmat;

  for (long i=0; i < m1.nrows(); i++)
    for (long j=0; j < m1.ncols(); i++)
      if ( m1[i][j] != m2[i][j] )
	return retmat;

  return true;
}

// logical no-equal-to operator
template <class T>
inline bool operator!= (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  return (m1 == m2) ? false : true;
}


// combined addition and assignment operator
template <class T>
inline enl_matrixT& enl_matrixT::operator+= (const enl_matrixT& m) 
{
  if (nr != m.nr || nc != m.nc)
    REPORT_ERROR( "enl_matrixT::operator+= : Inconsistent enl_matrixT size in addition!");

  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] += m.mat[i][j];

  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator-= (const enl_matrixT& m) 
{
  if (nr != m.nr || nc != m.nc)
    REPORT_ERROR( "enl_matrixT::operator-= : Inconsistent enl_matrixT size in subtraction!");

  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] -= m.mat[i][j];

  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator*= (const enl_matrixT& m2) 
{
  if (nc != m2.nr)
    REPORT_ERROR( "enl_matrixT::operator*= : Inconsistance enl_matrixT size in multiplication!");

  enl_matrixT m1 = *this;
  resize(m1.nr,m2.nc);

  for (long i=0; i<m1.nr; i++) {
    for (long j=0; j<m2.nc; j++) {
      T sum = T(0);
      for (long k=0; k<m1.nc; k++)
	sum += m1[i][k] * m2[k][j];
	  mat[i][j] = sum;
    }
  }
  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator/= (const enl_matrixT& m) 
{
  if (nc != m.nr)
    REPORT_ERROR( "enl_matrixT::operator*= : Inconsistance enl_matrixT size in multiplication!");
  *this *= enl_invert(m);
  return *this;
}


// combined scalar multiplication and assignment operator
template <class T>
inline enl_matrixT& enl_matrixT::operator+= (const T& c) 
{
  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] += c;
  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator-= (const T& c) 
{
  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] -= c;
  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator*= (const T& c) 
{
  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] *= c;
  return *this;
}

template <class T>
inline enl_matrixT& enl_matrixT::operator/= (const T& c) 
{
  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] /= c;
  return *this;
}

// combined power and assignment operator
template <class T>
inline enl_matrixT& enl_matrixT::operator ^= (const long& pow) 
{
  for (long i=2; i <= pow; i++)
    *this = *this * *this;
  return *this;
}

// --- unary operators
template <class T>
inline enl_matrixT enl_matrixT::operator+ () const
{
  return *this;
}

template <class T>
inline enl_matrixT enl_matrixT::operator- () const
{
  enl_matrixT temp(nr,nc);
  for (long i=0; i<nr; i++)
    for (long j=0; j<nc; j++)
      mat[i][j] = -mat[i][j];
  return temp;
}

// binary addition operator
template <class T>
inline enl_matrixT operator+ (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  enl_matrixT ret = m1;
  return ret += m2;
}

template <class T>
inline enl_matrixT operator- (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  enl_matrixT ret = m1;
  return ret -= m2;
}

template <class T>
inline enl_matrixT operator* (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  enl_matrixT ret = m1;
  return ret *= m2;
}

template <class T>
inline enl_matrixT operator/ (const enl_matrixT& m1, const enl_matrixT& m2) 
{
  enl_matrixT ret = m1;
  return ret /= m2;
}


// binary addition operator
template <class T>
inline enl_matrixT operator+ (const enl_matrixT& m, const T& c) 
{
  enl_matrixT ret = m;
  return ret += c;
}

template <class T>
inline enl_matrixT operator- (const enl_matrixT& m, const T& c) 
{
  enl_matrixT ret = m;
  return ret -= c;
}

template <class T>
inline enl_matrixT operator* (const enl_matrixT& m, const T& c) 
{
  enl_matrixT ret = m;
  return ret *= c;
}

template <class T>
inline enl_matrixT operator/ (const enl_matrixT& m, const T& c) 
{
  enl_matrixT ret = m;
  return ret /= c;
}

// binary power operator
template <class T>
inline enl_matrixT operator^ (const enl_matrixT& m, const long& pow) 
{
  enl_matrixT temp = m;
  for (long i=2; i <= pow; i++)
    temp *= temp;
  return temp;
}

// set this enl_matrixT to unity
template <class T>
inline void enl_matrixT::identity() 
{
  long row = min(nr,nc);
  nr = nc = row;

  resize(nr,nc);

  for (long i=0; i<nr; i++) {
    for (long j=0; j<nc; j++) {
      if(i==j) mat[i][j] = T(1);
      else     mat[i][j] = T(0);
    }
  }
  return;
}

// calculate the determinant of a enl_matrix
template <class T>
inline T enl_matrixT::GetDeterminant () const
{
  if (nr != nc)
    REPORT_ERROR( "enl_matrixT::det(): determinant a non-square enl_matrix!");
  enl_matrixT temp = enl_invert(*this);
  return det;
}

// calculate the norm of a enl_matrix
template <class T>
inline T enl_matrixT::GetNorm () const
{
  T retmat = T(0);

  for (long i=0; i < nr; i++)
    for (long j=0; j < nc; j++)
      retmat += (*this)[i][j] * (*this)[i][j];
  retmat = sqrt(retmat);

  return retmat;
}

// calculate the condition number of a enl_matrix
template <class T>
inline T enl_matrixT::GetCondition () const
{
  enl_matrixT minv(nr,nc);
  minv = enl_invert(minv);
  T retmat = GetNorm() * minv.GetNorm();
  return retmat;
}


// calculate the cofactor of a enl_matrixT for a given element
template <class T>
inline T enl_matrixT::GetCofactor (const long& r, const long& c) const
{
  long i,i1,j,j1;

  if (nr != nc)
    REPORT_ERROR( "enl_matrixT::cofact(): cofactor of a non-square enl_matrix!");

  if (r > nr || c > nc)
    REPORT_ERROR( "enl_matrixT::cofact(): Index out of range!");

  enl_matrixT temp (nr-1,nc-1);

  for (i=i1=0; i < nr; i++) {
    if (i == r) continue;
    for (j=j1=0; j < nc; j++) {
      if (j == c)	continue;
      temp[i1][j1] = (*this)[i][j];
      j1++;
    }
    i1++;
  }
  T cof = temp.GetDeterminant();
  if ((r+c)%2 == 1) cof = -cof;

  return cof;
}


// unary transpose operator
template <class T>
inline enl_matrixT enl_transpose(const enl_matrixT& m)
{
  enl_matrixT temp(m.nc,m.nr);
  for (long i=0; i < m.nr; i++)
    for (long j=0; j < m.nc; j++)
      temp[j][i] = m[i][j];
  return temp;
}


// inversion/determinant operator
template <class T>
inline enl_matrixT enl_invert(const enl_matrixT& ms)
{
  if (ms.nr != ms.nc)
    REPORT_ERROR( "enl_matrixT::operator!: Inversion of a non-square enl_matrix");

  long     i,j,k;
  T          det = T(1);
  enl_matrixT m   = ms;

  for(i=0; i<m.nr; i++){

    T pivot = m[i][i];
    if( pivot == T(0) ) break;

    det *= pivot;
    m[i][i] = T(1);

    for (j=0; j<m.nc; j++)
      m[i][j] /= pivot;

    for (k=0; k<m.nr; k++){
      if(k==i) continue;
      pivot = m[k][i];
      m[k][i] = T(0);
      for(j=0; j<m.nc; j++)
	m[k][j] -= pivot*m[i][j];
    }

  }

  m.det = det;

  return m;
}

template <class T>
inline enl_matrixT enl_adjoin (const enl_matrixT& m)
{
  if (m.nr != m.nc)
    REPORT_ERROR( "enl_matrixT::Adj(): Adjoin of a non-square enl_matrix.");

  enl_matrixT temp(m.nr,m.nc);

  for (long i=0; i<m.nr; i++)
    for (long j=0; j<m.nc; j++)
      temp[i][j] = m.GetCofactor[i][j];

  temp = enl_invert(temp);

  return temp;
}

template <class T> 
inline void operator<< (enl_matrixT& m, const enl_vector<T>& v)
{
	// --- agrandit la matrice si vec plus grand
	long rmax = (m.nr>v.nr)?m.nr:v.nr;
  m.resize(rmax,m.nc+1);
	// --- copie
  for(long i=0;i<m.nr;i++)
    if(i<v.nr) m[i][m.nc-1] = v[i];
}

template <class T> 
inline void operator<< (enl_matrixT& m, const enl_tseries& v)
{
	// --- agrandit la matrice si vec plus grand
	long rmax = (m.nr>v.nr)?m.nr:v.nr;
  m.resize(rmax,m.nc+1);
	// --- copie
  for(long i=0;i<m.nr;i++) {
    if(i<v.nr) 
			m[i][m.nc-1] = T(v[i]);
		else
			m[i][m.nc-1] = v.GetInit();
	}
}

template <class T>
inline void enl_matrixT::dump(ostream& os) const
{
    for (long i=0; i < nr; i++) {
      for (long j=0; j < nc; j++)
				os << mat[i][j] << "\t";
      os << endl;
    }
      os << endl;
}

template <class T>
inline ostream& operator<< (ostream& os, const enl_matrixT& m)
{
	m.dump(os);
	return os;
}

#endif

