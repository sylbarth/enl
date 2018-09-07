/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/


#include "enl.h"

enl_tseries_mx::enl_tseries_mx(const long& n) : mx(0), byear(0), ncols(0), nseries(n)
{
	mx = new enl_tseries[nseries];
}


enl_tseries_mx::enl_tseries_mx(const enl_tseries_mx& v) : mx(0), byear(v.byear), ncols(v.ncols), nseries(v.nseries)
{
  mx = new enl_tseries[nseries];
  for(long i=0; i<nseries; i++)
	  mx[i] = v.mx[i];
}


enl_tseries_mx::~enl_tseries_mx()
{
	if(mx) delete[] mx;
	nseries = 0;
}


void enl_tseries_mx::SetSeriesID(const char* s)
{
  for(long i=0; i<nseries; i++)
    mx[i].SetSeriesID(s);
}


enl_tseries_mx& enl_tseries_mx::operator=(const enl_tseries_mx& v)
{
  if ( mx == v.mx) return *this;
  if( (nseries>0) && mx) delete[] mx;
  ncols   = v.ncols;
  byear   = v.byear;
  nseries = v.nseries;
  mx = new enl_tseries[nseries];
  for(long i=0; i<nseries; i++)
	  mx[i] = v.mx[i];  
  return *this;
}


enl_tseries_mx& enl_tseries_mx::operator=(const enl_data& d)
{
  for(long i=0; i<nseries; i++)
    mx[i] = d;
  return *this;
}


enl_tseries_mx enl_tseries_mx::operator+(const enl_tseries_mx& v) const
{
  enl_tseries_mx m(nseries);
  m.ncols = 0;
  m.byear = v.byear;
  for(long i=0; i<nseries; i++)
  {
	if( strcmp(mx[i].GetCountryID(),v.mx[i].GetCountryID())==0 )
		m.mx[i] = mx[i] + v.mx[i];
	if( m.ncols<m.mx[i].nrows() ) 
	    m.ncols = m.mx[i].nrows();

  }
  return m;
}


enl_tseries_mx enl_tseries_mx::operator-(const enl_tseries_mx& v) const
{
  enl_tseries_mx m(nseries);
  m.ncols = 0;
  m.byear = v.byear;
  for(long i=0; i<nseries; i++)
  {
	if( strcmp(mx[i].GetCountryID(),v.mx[i].GetCountryID())==0 )
		m.mx[i] = mx[i] - v.mx[i];
	if( m.ncols<m.mx[i].nrows() ) 
	    m.ncols = m.mx[i].nrows();
  }
  return m;
}


enl_tseries_mx enl_tseries_mx::operator*(const enl_tseries_mx& v) const
{
  enl_tseries_mx m(nseries);
  m.ncols = 0;
  m.byear = v.byear;
  for(long i=0; i<nseries; i++)
  {
	if( strcmp(mx[i].GetCountryID(),v.mx[i].GetCountryID())==0 )
		m.mx[i] = mx[i] * v.mx[i];
	if( m.ncols<m.mx[i].nrows() ) 
	    m.ncols = m.mx[i].nrows();
  }
  return m;
}


enl_tseries_mx enl_tseries_mx::operator/(const enl_tseries_mx& v) const
{
  enl_tseries_mx m(nseries);
  m.ncols = 0;
  m.byear = v.byear;
  for(long i=0; i<nseries; i++)
  {
	if( strcmp(mx[i].GetCountryID(),v.mx[i].GetCountryID())==0 )
		m.mx[i] = mx[i] / v.mx[i];
	if( m.ncols<m.mx[i].nrows() ) 
	    m.ncols = m.mx[i].nrows();
  }
  return m;
}

 enl_tseries_mx enl_tseries_mx::operator+= (const enl_tseries_mx& v) { *this = *this + v; return *this; }
 enl_tseries_mx enl_tseries_mx::operator-= (const enl_tseries_mx& v) { *this = *this - v; return *this; }
 enl_tseries_mx enl_tseries_mx::operator*= (const enl_tseries_mx& v) { *this = *this * v; return *this; }
 enl_tseries_mx enl_tseries_mx::operator/= (const enl_tseries_mx& v) { *this = *this / v; return *this; }

 enl_tseries_mx enl_tseries_mx::operator+= (const double& d) { *this = *this + d; return *this; }
 enl_tseries_mx enl_tseries_mx::operator-= (const double& d) { *this = *this - d; return *this; }
 enl_tseries_mx enl_tseries_mx::operator*= (const double& d) { *this = *this * d; return *this; }
 enl_tseries_mx enl_tseries_mx::operator/= (const double& d) { *this = *this / d; return *this; }



enl_tseries_mx operator+(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m(v);
  for ( long i=0; i<v.nseries; i++ )
    m.mx[i] = v.mx[i] + d;
  return m;
}


enl_tseries_mx operator-(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m(v);
  for ( long i=0; i<v.nseries; i++ )
    m.mx[i] = v.mx[i] - d;
  return m;
}


enl_tseries_mx operator*(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m(v);
  for ( long i=0; i<v.nseries; i++ )
    m.mx[i] = v.mx[i] * d;
  return m;
}


enl_tseries_mx operator/(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m(v);
  for ( long i=0; i<v.nseries; i++ )
    m.mx[i] = v.mx[i] / d;
  return m;
}

 enl_tseries_mx operator+ (const double& d, const enl_tseries_mx& v) { return v+d; }
 enl_tseries_mx operator- (const double& d, const enl_tseries_mx& v) { return d+(-1.0)*v; }
 enl_tseries_mx operator* (const double& d, const enl_tseries_mx& v) { return v*d; }

 
enl_tseries_mx operator/ (const double& d, const enl_tseries_mx& v) 
{ 
  enl_tseries_mx m = v;
  for(long i=0; i<v.nseries; i++)
    m.mx[i] = d / v.mx[i];
  return m;
}

 
enl_tseries_mx enl_tseries_mx::operator()(const long n) const
{
  enl_tseries_mx m(*this);
  for(long i=0; i<nseries; i++)
    {
      enl_tseries t = mx[i];
      m.mx[i] = t(n);
    }
  return m;
}

 
enl_tseries_mx enl_tseries_mx::forward(const long n) const
{
  enl_tseries_mx m(*this);
  for(long i=0; i<nseries; i++)
    {
      enl_tseries t = mx[i];
      m.mx[i] = t.forward(n);
    }
  return m;
}

 
  enl_tseries& enl_tseries_mx::operator[](const long n)       
  { 
	  return mx[n]; 
  }

  const enl_tseries& enl_tseries_mx::operator[](const long n) const 
  { 
	  return mx[n]; 
  }
