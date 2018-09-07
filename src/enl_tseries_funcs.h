/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_TSERIES_FUNCS_
#define _ENL_TSERIES_FUNCS_

enl_tseries pow (const enl_tseries& v, const double& d);
enl_tseries sqrt(const enl_tseries& v);
enl_tseries log (const enl_tseries& v);
enl_tseries exp (const enl_tseries& v);
enl_tseries logit(const enl_tseries& v,const double& a, const double& b);

enl_tseries ifover(const enl_tseries& v, const enl_tseries& t);
enl_tseries ifover(const enl_tseries& v, const double& d);
enl_tseries ifover_or_equal(const enl_tseries& v, const double& d);
enl_tseries ifunder(const enl_tseries& v, const enl_tseries& t);
enl_tseries ifunder(const enl_tseries& v, const double& d);
enl_tseries ifequal(const enl_tseries& v, const enl_tseries& t, const enl_data& r1, const enl_data& r2);
enl_tseries ifequal(const enl_tseries& v, const double& d, const enl_data& r1, const enl_data& r2);
enl_tseries ifisset(const enl_tseries& v, const enl_tseries& t);
enl_tseries ifover (const enl_tseries& v, const double& d, const enl_tseries& t1, const enl_tseries& t2);

enl_tseries ifafter(const enl_tseries& v, const int& n, const enl_data& d);

enl_tseries over        (const enl_tseries& v, const double& dThr);
enl_tseries greater_else(const enl_tseries& v, const double& dThr, const enl_data& other);
enl_tseries under       (const enl_tseries& v, const double& dThr);
enl_tseries over_abs    (const enl_tseries& v, const double& dThr);
enl_tseries under_abs   (const enl_tseries& v, const double& dThr);

enl_tseries fabs (const enl_tseries& v);

enl_tseries atoq       (const enl_tseries& v, const bool hender);
enl_tseries atoq_planar(const enl_tseries& v);
enl_tseries qtoa_s     (const enl_tseries& v);
enl_tseries qtoa_m     (const enl_tseries& v);
enl_tseries qtoa_eop   (const enl_tseries& v);
enl_tseries mtoa_m     (const enl_tseries& v);
enl_tseries mtoq_m     (const enl_tseries& v);

enl_tseries base       (const enl_tseries& v, const long& year, const long& subp);

enl_tseries sum      (const enl_tseries& v, const long& n );
enl_tseries mean     (const enl_tseries& v, const long& n);
enl_tseries sd       (const enl_tseries& v, const long& n);
enl_tseries sde      (const enl_tseries& v, const long& n);
enl_tseries trend    (const enl_tseries& v, const double& c);
enl_tseries trend_exp(const enl_tseries& v, const double& c);
enl_tseries mean4321 (const enl_tseries& v);
enl_tseries mean4    (const enl_tseries& v);
enl_tseries sum4     (const enl_tseries& v);

enl_tseries yoy (const enl_tseries& v);
enl_tseries lint(const enl_tseries& v);

inline enl_data maxval(const enl_tseries& v);
inline enl_data minval(const enl_tseries& v);

enl_tseries max_sized(const enl_tseries& v, const long& n);
enl_tseries min_sized(const enl_tseries& v, const long& n);

inline enl_data maxval(const enl_tseries& v, const long& year);
inline enl_data minval(const enl_tseries& v, const long& year);

enl_tseries join(const enl_tseries& v1, const enl_tseries& v2);

enl_tseries ifAND(const enl_tseries& Va, const double& a, const enl_tseries& Vb, const double& b);

double sum ( const enl_tseries& v );
double mean( const enl_tseries& v );
double sd  ( const enl_tseries& v );
double cov ( const enl_tseries& v1, const enl_tseries& v2 );
double cor ( const enl_tseries& v1, const enl_tseries& v2 );

#endif
