/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_TSERIES_
#define _ENL_TSERIES_

#include "fstream.h"

class enl_tseries {

  enl_data    init; // default init value
  enl_data*   mat;  // data


  char m_countryID[4];
  char m_seriesID [50];
  long m_updateID;
  long m_recodID;
  long m_byear;

  bool MakeFields ( enl_tseries* ret, const enl_tseries* t1, const enl_tseries* t2 ) const;
  void empty();

public:

  enl_tseries();
  enl_tseries(const long& r, const long& f , const long& b, const enl_data& t = enl_data(0));
  enl_tseries(const enl_tseries& v);
  ~enl_tseries();

  long nr;
  long m_freq;

  // --- opérateurs d'affectation
  enl_tseries& operator=(const enl_tseries& v);
  enl_tseries& operator=(const enl_data& t);

  void resize (const long& r);

  // --- opérateurs arithmétiques enl_tseries
  enl_tseries operator+(const enl_tseries& v) const;
  enl_tseries operator-(const enl_tseries& v) const;
  enl_tseries operator*(const enl_tseries& v) const;
  enl_tseries operator/(const enl_tseries& v) const;

  enl_tseries operator+= (const enl_tseries& v);
  enl_tseries operator-= (const enl_tseries& v);
  enl_tseries operator*= (const enl_tseries& v);
  enl_tseries operator/= (const enl_tseries& v);

  // --- opérateurs arithmétiques double
  enl_tseries operator+= (const double& d);
  enl_tseries operator-= (const double& d);
  enl_tseries operator*= (const double& d);
  enl_tseries operator/= (const double& d);

  friend enl_tseries operator+ (const enl_tseries& v, const double& d);
  friend enl_tseries operator- (const enl_tseries& v, const double& d);
  friend enl_tseries operator* (const enl_tseries& v, const double& d);
  friend enl_tseries operator/ (const enl_tseries& v, const double& d);

  friend enl_tseries operator+ (const double& d, const enl_tseries& v);
  friend enl_tseries operator- (const double& d, const enl_tseries& v);
  friend enl_tseries operator* (const double& d, const enl_tseries& v);
  friend enl_tseries operator/ (const double& d, const enl_tseries& v);

  // --- opérateurs d'accès
  enl_tseries operator()(const long n) const;
  enl_tseries forward(const long n) const;
  enl_data&       operator[](const long n);
  const enl_data& operator[](const long n) const;

  
  // to transform to get() / add() / getval()
  void add( const enl_data& ed );
  enl_data get(const long& year, const long& subp);
  long avail();
  enl_data first() const;
  enl_data last() const;

  inline long nrows() const { return nr; }

  bool adjust_byear(const long& byear);

  // --- Get/Set sur les membres privés
  long GetIndex(const long& year, const long& subp) const ;
  long GetYear (const long& n) const ;
  long GetSubp (const long& n) const ;
  const char*  GetCountryID()     const ;
  const char*  GetSeriesID()      const ;
  const int    GetUpdateID()      const ;
  const int    GetRecodID()       const ;
  const int    GetDataFreq()      const ;
  const int    GetBaseYear()      const ;
  const enl_data  GetInit()		  const ;	

  void SetCountryID  (const char* s) ;
  void SetSeriesID   (const char* s) ;
  void SetUpdateID   (const long& n) ;
  void SetRecodID    (const long& n) ;
  void SetDataFreq   (const long& n) ;
  void SetBaseYear   (const long& n) ;

  void fill_na();
  long last_indice() const;
  friend enl_tseries basev(const enl_tseries& v, const std::vector<enl_date> by);
  bool adjust_lyear(const long& lyear);
  void dump(ostream& os);

};


#endif
