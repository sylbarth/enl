/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_TSERIES_MX_
#define _ENL_TSERIES_MX_

class enl_tseries_mx {

  enl_tseries* mx;
  long nseries;

public:

  long byear;
  long ncols;

  enl_tseries_mx(const long& n = 0);
  enl_tseries_mx(const enl_tseries_mx& v);
  ~enl_tseries_mx();

  void SetSeriesID   (const char* s);

  // --- opérateurs d'affectation
  enl_tseries_mx& operator= (const enl_tseries_mx& v);
  enl_tseries_mx& operator= (const enl_data&  d);

  // --- opérateurs arithmétiques enl_tseries_mx
  enl_tseries_mx operator+  (const enl_tseries_mx& v) const;
  enl_tseries_mx operator-  (const enl_tseries_mx& v) const;
  enl_tseries_mx operator*  (const enl_tseries_mx& v) const;
  enl_tseries_mx operator/  (const enl_tseries_mx& v) const;

  enl_tseries_mx operator+= (const enl_tseries_mx& v);
  enl_tseries_mx operator-= (const enl_tseries_mx& v);
  enl_tseries_mx operator*= (const enl_tseries_mx& v);
  enl_tseries_mx operator/= (const enl_tseries_mx& v);

  // --- opérateurs arithmétiques double
  enl_tseries_mx operator+= (const double& d);
  enl_tseries_mx operator-= (const double& d);
  enl_tseries_mx operator*= (const double& d);
  enl_tseries_mx operator/= (const double& d);

  friend enl_tseries_mx operator+ (const enl_tseries_mx& v, const double&      d);
  friend enl_tseries_mx operator- (const enl_tseries_mx& v, const double&      d);
  friend enl_tseries_mx operator* (const enl_tseries_mx& v, const double&      d);
  friend enl_tseries_mx operator/ (const enl_tseries_mx& v, const double&      d);

  friend enl_tseries_mx operator+ (const double&      d, const enl_tseries_mx& v);
  friend enl_tseries_mx operator- (const double&      d, const enl_tseries_mx& v);
  friend enl_tseries_mx operator* (const double&      d, const enl_tseries_mx& v);
  friend enl_tseries_mx operator/ (const double&      d, const enl_tseries_mx& v);

  // --- opérateurs d'accès
  enl_tseries_mx operator() (const long n) const;
  enl_tseries_mx forward(const long n) const;
  enl_tseries&       operator[](const long n);
  const enl_tseries& operator[](const long n) const;

  inline long GetNSeries() const { return nseries; }

};



#endif
