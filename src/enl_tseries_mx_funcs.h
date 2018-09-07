/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_TSERIES_MX_FUNCS_
#define _ENL_TSERIES_MX_FUNCS_

  enl_tseries_mx sqrt  (const enl_tseries_mx& v);
  enl_tseries_mx mean  (const enl_tseries_mx& v, const long& n);
  enl_tseries_mx stddev(const enl_tseries_mx& v, const long& n);
  enl_tseries_mx pow   (const enl_tseries_mx& v, const double& value);

  enl_tseries_mx ifover (const enl_tseries_mx& v, const enl_tseries_mx& t);
  enl_tseries_mx ifover (const enl_tseries_mx& v, const double& d);

  enl_tseries_mx ifover_or_equal (const enl_tseries_mx& v, const double& d);

  enl_tseries_mx ifunder(const enl_tseries_mx& v, const enl_tseries_mx& t);
  enl_tseries_mx ifunder(const enl_tseries_mx& v, const double& d);

  enl_tseries_mx ifequal(const enl_tseries_mx& v, const enl_tseries_mx& t, const enl_data& r1, const enl_data& r2);
  enl_tseries_mx ifequal(const enl_tseries_mx& v, const double& d, const double& r1, const double& r2);

  enl_tseries_mx ifisset(const enl_tseries_mx& v, const enl_tseries_mx& t);
  enl_tseries_mx ifover (const enl_tseries_mx& v, const double& d, const enl_tseries_mx& t1, const enl_tseries_mx& t2);

  enl_tseries_mx ifafter(const enl_tseries_mx& v, const int& n, const enl_data& d);

  enl_tseries_mx atoq		(const enl_tseries_mx& v);
  enl_tseries_mx atoq_planar(const enl_tseries_mx& v);

  double sum (const enl_tseries_mx& v);
  enl_tseries_mx sum (const enl_tseries_mx& v, const long& n );
  enl_tseries_mx join(const enl_tseries_mx& v1, const enl_tseries_mx& v2 );
  enl_tseries_mx ifAND(const enl_tseries_mx& Va, const double& a, const enl_tseries_mx& Vb, const double& b);

  enl_tseries_mx completeWith(enl_tseries_mx& v1, const enl_tseries_mx& v2);

#endif
