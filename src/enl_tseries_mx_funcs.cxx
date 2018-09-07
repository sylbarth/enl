/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"


 
enl_tseries_mx sqrt(const enl_tseries_mx& v)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    m[i] = sqrt(v[i]);
  return m;
}

 
enl_tseries_mx mean(const enl_tseries_mx& v, const long& n)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    m[i] = mean(v[i],n);
  return m;
}

 
enl_tseries_mx sd(const enl_tseries_mx& v, const long& n)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    m[i] = sd(v[i],n);
  return m;
}

 
enl_tseries_mx pow(const enl_tseries_mx& v, const double& value)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    m[i] = pow(v[i],value);
  return m;
}

 
enl_tseries_mx ifover (const enl_tseries_mx& v, const enl_tseries_mx& t)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	if( strcmp(v[i].GetCountryID(),t[i].GetCountryID())==0 )
		m[i] = ifover(v[i],t[i]);
  }
  return m;
}

 
enl_tseries_mx ifover(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	m[i] = ifover(v[i],d);
  }
  return m;
}

 
enl_tseries_mx ifover_or_equal (const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	m[i] = ifover_or_equal(v[i],d);
  }
  return m;
}

 
enl_tseries_mx ifunder (const enl_tseries_mx& v, const enl_tseries_mx& t)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	if( strcmp(v[i].GetCountryID(),t[i].GetCountryID())==0 )
		m[i] = ifunder(v[i],t[i]);
  }
  return m;
}

 
enl_tseries_mx ifunder(const enl_tseries_mx& v, const double& d)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	m[i] = ifunder(v[i],d);
  }
  return m;
}

 
enl_tseries_mx ifequal(const enl_tseries_mx& v, const enl_tseries_mx& t, const double& r1, const double& r2)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	if( strcmp(v[i].GetCountryID(),t[i].GetCountryID())==0 )
		m[i] = ifequal(v[i],t[i],r1,r2);
  }
  return m;
}

 
enl_tseries_mx ifequal(const enl_tseries_mx& v, const double& d, const double& r1, const double& r2)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	m[i] = ifequal(v[i],d,r1,r2);
  }
  return m;
}

 
enl_tseries_mx ifisset(const enl_tseries_mx& v, const enl_tseries_mx& t)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
	if( strcmp(v[i].GetCountryID(),t[i].GetCountryID())==0 )
		m[i] = ifisset(v[i],t[i]);
  }
  return m;
}

 
enl_tseries_mx ifover (const enl_tseries_mx& v, const double& d, const enl_tseries_mx& t1, const enl_tseries_mx& t2)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    {
      if( (strcmp(v[i].GetCountryID(),t1[i].GetCountryID())==0) &&
	  (strcmp(v[i].GetCountryID(),t2[i].GetCountryID())==0) )
	m[i] = ifover(v[i],d,t1[i],t2[i]);
    }
  return m;
}

 
enl_tseries_mx ifafter (const enl_tseries_mx& v, const int& n, const enl_data& d)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
    {
      m[i] = ifafter(v[i],n,d);
    }
  return m;
}

 
enl_tseries_mx atoq(const enl_tseries_mx& v)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
    m[i] = atoq(v[i],true);
	if( m.ncols<m[i].nrows() ) 
	    m.ncols = m[i].nrows();
  }
  return m;
}

 
enl_tseries_mx atoq_planar(const enl_tseries_mx& v)
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
    m[i] = atoq_planar(v[i]);
	if( m.ncols<m[i].nrows() ) 
	    m.ncols = m[i].nrows();
  }
  return m;
}

 
double sum(const enl_tseries_mx& v)
{
  double s = 0.0;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
    s += sum(v[i]);
  }
  return s;
}


enl_tseries_mx sum(const enl_tseries_mx& v, const long& n )
{
  enl_tseries_mx m = v;
  for ( long i=0; i<v.GetNSeries(); i++ )
  {
    m[i] = sum(v[i],n);
	if( m.ncols<m[i].nrows() ) 
	    m.ncols = m[i].nrows();
  }
  return m;
}

 
enl_tseries_mx join(const enl_tseries_mx& v1, const enl_tseries_mx& v2)
{
  enl_tseries_mx m = v1;
  for ( long i=0; i<v1.GetNSeries(); i++ )
  {
	if( strcmp(v1[i].GetCountryID(),v2[i].GetCountryID())==0 )
	{
		if(v2.GetNSeries()>i)
			m[i] = join(v1[i],v2[i]);
	}
  }
  return m;
}

 
enl_tseries_mx ifAND(const enl_tseries_mx& Va, const double& a, const enl_tseries_mx& Vb, const double& b)
{
  enl_tseries_mx m = Va;
  for ( long i=0; i<m.GetNSeries(); i++ )
  {
	m[i] = ifAND( Va[i], a, Vb[i], b );
  }
  return m;
}

enl_tseries_mx completeWith(enl_tseries_mx& v1, const enl_tseries_mx& v2)
{
  enl_tseries_mx newser = v1;
  for ( long i=0; i<v1.GetNSeries(); i++ )
  {
	if( strcmp(v1[i].GetCountryID(),v2[i].GetCountryID())==0 )
		if (v1[i].avail() < 1 ) 
			newser[i] = v2[i];
  }
  return newser;
}
