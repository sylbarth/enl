/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_OLS_H_
#define _ENL_OLS_H_

#include "enl_matrix.h"
#include "enl_vector.h"

class enl_ols {

  int byear;

public:

  unsigned int nreg;
  unsigned int nobs;
  unsigned int df;

  enl_data R2;
  enl_data R2adj;
  enl_data dw;
  
  enl_data vres;
  enl_data tss;
  enl_data rss;
  enl_data ess;

  enl_matrix<enl_data> maty;
  enl_matrix<enl_data> matx;

  enl_matrix<enl_data> matbeta;
  enl_matrix<enl_data> matstud;
  enl_matrix<enl_data> matiss;
  enl_matrix<enl_data> matvarcov;
  enl_matrix<enl_data> matsigma;

  enl_tseries resid;

  // --- cons/des
  enl_ols();
  ~enl_ols();

  // --- fonctions 
  int addy(const enl_vector<enl_data>& v);
  int addy(const enl_matrix<enl_data>& m);
  int addx(const enl_matrix<enl_data>& m);
  int addy(const enl_tseries&          ts);
  int addx(const enl_tseries&          ts);

  void remove();

  int estimate(const size_t& start = 0, const size_t& end = 0);

  friend int enl_olsv( enl_ols*           e,
		       enl_tseries*       beta, 
		       enl_tseries*       stud, 
		       enl_tseries*       R2, 
		       enl_tseries*       nobs, 
		       const char*        prefix, 
		       const enl_tseries& _vinit,
		       const int size);
  
};

#endif
