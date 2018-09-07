/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"
#include "iostream.h"

enl_db::enl_db (const long& updateID,std::map<std::string,enl_tseries>* table_series)
{
  m_updateID = updateID;
  m_table_series=table_series;
}

enl_db::~enl_db ()
{
}

std::string enl_db::getKey(const enl_tseries& v)
{
  return getKey(v.GetCountryID(),v.GetSeriesID(),v.GetDataFreq());
}

std::string enl_db::getKey(const char* cid, const char* sid, const long& freq)
{
  static char szKey[1024];
  szKey[0] = '\0';
  sprintf(szKey,"%s_%s_%i_%i",cid, sid, m_updateID, freq);
#ifdef WIN32
  strlwr(szKey);
#else
  for(int i=0; i<strlen(szKey); i++)
    szKey[i] = tolower(szKey[i]);
#endif
  return szKey;
}

int enl_db::add ( const enl_tseries& v, const int& replace )
{
	(*m_table_series)[getKey(v)]=v;

	return 0;
}

enl_tseries enl_db::get  ( const char*  cid, const char* sid, const long& freq)
{
	enl_tseries v=(*m_table_series)[getKey(cid,sid,freq)];
	return v;
}
 
inline int enl_db::addmx ( const enl_tseries_mx& v, const int& replace )
{
  for(long i=0; i<v.GetNSeries(); i++)
    add(v[i],replace);
  return 1;
}

inline enl_tseries_mx enl_db::getmx(const char** cid, const long& n, const char* sid, const long& freq)
{
  enl_tseries_mx m(n);
  m.byear = 0;

  for(long i=0; i<n; i++)
    {
      if(cid[i])
	{
	  enl_tseries t = get(cid[i],sid,freq);

	  if(i==0) m.byear = t.GetBaseYear();

	  if( m.byear!=t.GetBaseYear() ) {
	    m[i] = enl_tseries();
	    m[i].SetCountryID(cid[i]);
	  } else {
	    m[i] = t;
	    m[i].SetCountryID(cid[i]);
	  }

	  if( m.ncols<m[i].nrows() ) 
	    m.ncols = m[i].nrows();
	}
      else
	{
	  m[i] = enl_tseries();
	}
    }
  return m;
}


inline int enl_db::getparam ( const char* group, const char* name, double* value)
{
  if ( !group || !name ) return 0;
  return 1;
}

inline int enl_db::saveparams ()
{
  return 0;
}

