/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_DB_OTL_H_
#define _ENL_DB_OTL_H_

class enl_db_otl : public enl_db {

  otl_connect db;

public:
  
  enl_db_otl(const char* dbname, const char* dbuser, const char* dbpass, const long& updateID,std::map<std::string,enl_tseries>* table_series);
  ~enl_db_otl();

  int isopen();

  enl_tseries get ( const char* cid, const char* sid, const long& freq );
  enl_tseries getData ( const char* cid, const char* sid, const long& freq, const char* tablename );
 
  int add   ( const enl_tseries& v,    const int& replace = 1 );
  int addmx ( const enl_tseries_mx& v, const int& replace = 1 );

  otl_connect* GetDatabase() { return &db; };

  int getparam ( const char* group, const char* name, double* value);
  int setparam ( const char* group, const char* name, double  value);

  int enl_db_otl::addSerie (const char seriesID[],const char seriesDescription[]="");

};

#endif
