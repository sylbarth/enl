/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#ifndef _ENL_DB_H_
#define _ENL_DB_H_


class enl_db {

protected:

  long m_updateID;
  std::map<std::string,enl_tseries> *m_table_series;

  std::string getKey(const enl_tseries& v);
  std::string getKey(const char* cid, const char* sid, const long& freq);

public:
  enl_db(const long& updateID,std::map<std::string, enl_tseries>* table_series);
  virtual ~enl_db();

  // --- add / get by values
  virtual int add ( const enl_tseries& v, const int& replace = 1 ) = 0;
  virtual enl_tseries get ( const char*  cid, const char* sid, const long& freq) = 0;

  virtual int addmx ( const enl_tseries_mx& v, const int& replace = 1 );
  virtual enl_tseries_mx getmx ( const char** cid, const long& n, const char* sid, const long& freq);

  virtual int getparam ( const char* group, const char* name, double* value);
  virtual int saveparams ( );

};


#endif
