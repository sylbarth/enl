/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/


#ifndef _ENL_H_
#define _ENL_H_

#ifdef WIN32
  #pragma warning(disable:4786)
#endif

#define SQR(x) ((x)*(x))
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

const long ENL_DEFAULT_BYEAR = 1970;
const long ENL_ANNUAL    = 1;
const long ENL_QUARTERLY = 4;
const long ENL_MONTHLY   = 12;

// --- librairie standard
#include <math.h>
#include <float.h>

#define ENL_SQLLEN 2048

// --- MySQL via OTL
#define OTL_ANSI_CPP 
#define OTL_ORA_TEXT_ON
#define OTL_ODBC_MYSQL 
#undef OTL_ORA8I

#include "otlv4.h"
/*
#ifdef WIN32
  #pragma comment(lib, "c:\\oracle\\ora81\\oci\\lib\\msvc\\oci.lib")
#endif 
*/
#ifdef WIN32
  #pragma comment(lib, "C:\\oracle\\product\\11.2.0\\client_1\\oo4o\\CPP\\LIB\\ORACLM32.LIB")
#endif

// --- STL
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <string>
#define vectorD std::vector<enl_data>
#define vectorG std::vector<enl_grade>
#include "enl_country.h"
#include "enl_date.h"
#include "enl_data.h"

#include "enl_tseries.h"
#include "enl_tseries_funcs.h"

#include "enl_tseries_mx.h"
#include "enl_tseries_mx_funcs.h"

#include "enl_percentiles.h"

#include "enl_db.h"
#include "enl_db_otl.h"

#include "enl_ols.h"

#endif
