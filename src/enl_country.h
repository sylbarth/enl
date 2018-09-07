/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_COUNTRY_H_
#define _ENL_COUNTRY_H_

struct enl_country {
  char cid[4];
  char name[100];
  char zone[100];
  char nameSQL[100];
  int  sample;
};

#endif
