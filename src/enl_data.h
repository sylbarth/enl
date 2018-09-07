/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_DATA_H_
#define _ENL_DATA_H_


#include "enl.h"

class enl_data {

  bool   m_avail;
  bool   m_estim;
  double m_value;
	
  void AdjustFields ( const enl_data& other );

public:

  // --- constructeur (destructeur inutile)
  enl_data(); 
  enl_data(const enl_data&  d); 
  enl_data(const double& d); 
  enl_data(const long& d); 
  enl_data(const int& d); 

  // --- opérateurs affect
  enl_data& operator= (const enl_data&  d);
  enl_data& operator= (const double& value);
  enl_data& operator= (const long& value);
  enl_data& operator= (const int& value);

  // --- accès aux membres
  inline bool   GetIsAvailable() const { return m_avail; }
  inline bool   GetIsEstimate()  const { return m_estim; }
  inline double GetValue()       const { return m_value; }

  inline void SetIsAvailable ( const bool&   avail) { m_avail = avail; }
  inline void SetIsEstimate  ( const bool&   estim) { m_estim = estim; }
  inline void SetValue       ( const double& value) { m_value = value; }

  // --- operateurs unaires
  enl_data& operator+ () { return *this; }
  enl_data  operator- () { enl_data d; d.m_value = -d.m_value; return d; }

  // --- opérateurs arithm: affect+compar
  enl_data& operator+= (const enl_data& d);
  enl_data& operator-= (const enl_data& d);
  enl_data& operator*= (const enl_data& d);
  enl_data& operator/= (const enl_data& d);

  inline enl_data& operator+= (const double& d) { *this += enl_data(d); return *this; }
  inline enl_data& operator-= (const double& d) { *this -= enl_data(d); return *this; }
  inline enl_data& operator*= (const double& d) { *this *= enl_data(d); return *this; }
  inline enl_data& operator/= (const double& d) { *this /= enl_data(d); return *this; }

  // --- opérateurs arithm standards
  friend enl_data operator+ (const enl_data& v1, const enl_data& v2);
  friend enl_data operator- (const enl_data& v1, const enl_data& v2);
  friend enl_data operator* (const enl_data& v1, const enl_data& v2);
  friend enl_data operator/ (const enl_data& v1, const enl_data& v2);
  
  // --- opérateurs arithm avec double
  friend inline enl_data operator+ (const enl_data& v, const double& d) { return v+enl_data(d); }
  friend inline enl_data operator- (const enl_data& v, const double& d) { return v-enl_data(d); }
  friend inline enl_data operator* (const enl_data& v, const double& d) { return v*enl_data(d); }
  friend inline enl_data operator/ (const enl_data& v, const double& d) { return v/enl_data(d); }
  
  friend inline enl_data operator+ ( const double& d, const enl_data& v ) { return  v+d; }
  friend inline enl_data operator- ( const double& d, const enl_data& v ) { return -1.0*v+d; }
  friend inline enl_data operator* ( const double& d, const enl_data& v ) { return  v*d; }
  friend inline enl_data operator/ ( const double& d, const enl_data& v ) { return  pow(v,-1.0)*d; }

  // --- operateurs de comparaison
  friend int operator== (const enl_data& v1, const enl_data& v2);
  friend int operator!= (const enl_data& v1, const enl_data& v2);
  friend int operator>  (const enl_data& v1, const enl_data& v2);
  friend int operator<  (const enl_data& v1, const enl_data& v2);
  friend int operator>= (const enl_data& v1, const enl_data& v2);
  friend int operator<= (const enl_data& v1, const enl_data& v2);
  
  friend int operator== (const enl_data& v,  const double& d);
  friend int operator!= (const enl_data& v,  const double& d);
  friend int operator>  (const enl_data& v,  const double& d);
  friend int operator<  (const enl_data& v,  const double& d);
  friend int operator>= (const enl_data& v,  const double& d);
  friend int operator<= (const enl_data& v,  const double& d);
  
  // --- fonctions de <cmath>
  friend enl_data pow  (const enl_data& dat, const double& dValue);
  friend enl_data sqrt (const enl_data& dat);

  friend enl_data log  (const enl_data& dat);
  friend enl_data log10(const enl_data& dat);
  friend enl_data exp  (const enl_data& dat);
    
  friend enl_data logit(const enl_data& dat, const double& a, const double& b);

  friend enl_data fabs (const enl_data& dat);

  friend enl_data sin  (const enl_data& dat);
  friend enl_data cos  (const enl_data& dat);
  friend enl_data tan  (const enl_data& dat);
  friend enl_data sinh (const enl_data& dat);
  friend enl_data cosh (const enl_data& dat);
  friend enl_data tanh (const enl_data& dat);
  friend enl_data asin (const enl_data& dat);
  friend enl_data acos (const enl_data& dat);
  friend enl_data atan (const enl_data& dat);
  friend enl_data atan2(const enl_data& dat1, const enl_data& dat2);

};

inline
enl_data::enl_data() :
  m_avail(false),
  m_estim(false),
  m_value(0)
{
}

inline
enl_data::enl_data(const enl_data& d) :
  m_avail(d.m_avail),
  m_estim(d.m_estim),
  m_value(d.m_value)
{
}

inline
enl_data::enl_data(const double& d) :
  m_avail(true),
  m_estim(false),
  m_value(d)
{
}

inline
enl_data::enl_data(const long& d) :
  m_avail(true),
  m_estim(false),
  m_value(double(d))
{
}

inline
enl_data::enl_data(const int& d) :
  m_avail(true),
  m_estim(false),
  m_value(double(d))
{
}

inline
enl_data& enl_data::operator=(const enl_data& d)
{	
  if ( this == &d ) return *this;
  m_avail = d.m_avail;
  m_estim = d.m_estim;
  m_value = d.m_value;
  return *this;
}

inline
enl_data& enl_data::operator=(const double& value)
{
  m_avail = true;
  m_value = value;
  return *this;
}

inline
enl_data& enl_data::operator=(const long& value)
{
  m_avail = true;
  m_value = double(value);
  return *this;
}


inline
enl_data& enl_data::operator=(const int& value)
{
  m_avail = true;
  m_value = double(value);
  return *this;
}


inline
void enl_data::AdjustFields ( const enl_data& other )
{
  if ( (m_avail==false) || (other.m_avail==false) ) 
    m_avail = false;
  if ( (m_estim==true)  || (other.m_estim==true) )
    m_estim = true;
}

inline
enl_data& enl_data::operator+= (const enl_data& d)
{
  AdjustFields(d);
  m_value += d.m_value;
  return *this;
}

inline
enl_data& enl_data::operator-= (const enl_data& d)
{
  AdjustFields(d);
  m_value -= d.m_value;
  return *this;
}

inline
enl_data& enl_data::operator*= (const enl_data& d)
{
  AdjustFields(d);
  m_value *= d.m_value;
  return *this;
}

inline
enl_data& enl_data::operator/= (const enl_data& d) 
{
  AdjustFields(d);
  if(d.m_value != double(0))
    m_value /= d.m_value;
  else
    m_avail = false;
  return *this;
}

inline
int operator==(const enl_data& v1, const enl_data& v2)
{	
  if ( &v1 == &v2 ) return 1;

  if ( v1.m_avail != v2.m_avail ) return 0;
  if ( v1.m_value != v2.m_value ) return 0;

  return 1;
}

inline
int operator!= (const enl_data& v1, const enl_data& v2)
{	
  return !(v1 == v2);
}

inline
int operator<(const enl_data& v1, const enl_data& v2)
{	
  if ( &v1 == &v2 ) return 1;

  if ( v1.m_avail != v2.m_avail ) return 0;
  if ( v1.m_value >= v2.m_value ) return 0;

  return 1;
}

inline
int operator> (const enl_data& v1, const enl_data& v2)
{	
  return !(v1 <= v2);
}

inline
int operator<=(const enl_data& v1, const enl_data& v2)
{	
  if ( &v1 == &v2 ) return 1;

  if ( v1.m_avail != v2.m_avail ) return 0;
  if ( v1.m_value >  v2.m_value ) return 0;

  return 1;
}

inline
int operator>= (const enl_data& v1, const enl_data& v2)
{	
  return !(v1 < v2);
}

inline
int operator== (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value == d);
}

inline
int operator!= (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value != d);
}

inline
int operator> (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value > d);
}

inline
int operator< (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value < d);
}

inline
int operator>= (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value >= d);
}

inline
int operator<= (const enl_data& v, const double& d)
{	
  if ( v.m_avail == false ) return 0;
  return (v.m_value <= d);
}

inline
enl_data operator+(const enl_data& v1, const enl_data& v2)
{
  enl_data ed = v1;
  return ed += v2;
}

inline
enl_data operator-(const enl_data& v1, const enl_data& v2)
{
  enl_data ed = v1;
  return ed -= v2;
}

inline
enl_data operator*(const enl_data& v1, const enl_data& v2)
{
  enl_data ed = v1;
  return ed *= v2;
}

inline
enl_data operator/(const enl_data& v1, const enl_data& v2)
{
  enl_data ed = v1;
  return ed /= v2;
}

inline
enl_data pow(const enl_data& dat, const double& d)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::pow(ed.m_value, d);
  return ed;
}

inline
enl_data sqrt(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail && (ed.m_value >= double(0)) )
    ed.m_value = ::sqrt(ed.m_value);
  return ed;
}

inline
enl_data log(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail && (ed.m_value > double(0)) )
    ed.m_value = ::log(ed.m_value);
  return ed;
}

inline
enl_data log10(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail && (ed.m_value > double(0)) )
    ed.m_value = ::log10(ed.m_value);
  return ed;
}

inline
enl_data exp(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::exp(ed.m_value);
  return ed;
}


inline
enl_data fabs(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::fabs(ed.m_value);
  return ed;
}

inline
enl_data sin(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::sin(ed.m_value);
  return ed;
}

inline
enl_data cos(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::cos(ed.m_value);
  return ed;
}

inline
enl_data tan(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::tan(ed.m_value);
  return ed;
}

inline
enl_data sinh(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::sinh(ed.m_value);
  return ed;
}

inline
enl_data cosh(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::cosh(ed.m_value);
  return ed;
}

inline
enl_data tanh(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::tanh(ed.m_value);
  return ed;
}

inline
enl_data asin(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::asin(ed.m_value);
  return ed;
}

inline
enl_data acos(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::acos(ed.m_value);
  return ed;
}

inline
enl_data atan(const enl_data& dat)
{
  enl_data ed = dat;
  if ( dat.m_avail ) ed.m_value = ::atan(ed.m_value);
  return ed;
}

inline
enl_data atan2(const enl_data& dat1, const enl_data& dat2)
{
  enl_data ed = dat1;
  if ( dat1.m_avail && dat2.m_avail ) 
    ed.m_value = ::atan2(dat1.m_value,dat2.m_value);
  return ed;
}

inline enl_data na() { return enl_data(); }

#endif
