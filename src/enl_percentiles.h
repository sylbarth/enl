/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_PERCENTILES_
#define _ENL_PERCENTILES_

struct enl_grade {
  enl_data percentile;
  enl_data grade;
  enl_data threshold;
  enl_grade(const enl_data& p = 0, const enl_data& g = 0, const enl_data& t = 0)
  {
    percentile = p;
    grade      = g;
	threshold  = t;
  }
};

enl_tseries_mx percentiles     (const enl_tseries_mx& ts, const vectorG& g);
enl_tseries_mx percentiles_hist(const enl_tseries_mx& ts, const vectorG& g, const long& year);

#endif
