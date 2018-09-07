/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"

enl_db_otl::enl_db_otl(const char* dbname, const char* dbuser, const char* dbpass, const long& updateID,std::map<std::string,enl_tseries>* table_series) :
  enl_db(updateID,table_series)
{
  char connect_str[255];
  sprintf(connect_str, "%s/%s@%s", dbuser, dbpass, dbname);
  db.rlogon(connect_str);
}

enl_db_otl::~enl_db_otl()
{
  db.logoff();
}

int enl_db_otl::isopen() 
{
  return db.connected;
}

enl_tseries enl_db_otl::get( const char* cid, const char* sid, const long& freq )
{
	enl_tseries v = getData (cid,sid,freq,"dataest");
	if(v.avail() <= 0) v = getData (cid,sid,freq,"dataimf");
	if(v.avail() <= 0) v = getData (cid,sid,freq,"data");
	return v;
}

enl_tseries enl_db_otl::getData ( const char* cid, const char* sid, const long& freq, const char* tablename )
{
  enl_tseries tsempty(0,freq,1980,na());
  tsempty.SetCountryID(cid);  
  tsempty.SetSeriesID (sid);  
  tsempty.SetUpdateID (m_updateID);

  // --- recherche d'abord si déjà extrait
  
  
  enl_tseries oldv = enl_db::get(cid,sid,freq);
  if(oldv.avail()){return oldv;}

  // --- recherche des données dans la base Oracle
  char sql    [1024];
  char szWhere[1024];

  // --- prépare le where
  sprintf(szWhere, "cid='%s' AND sid='%s' AND uid=%i AND freq=%i", cid, sid, m_updateID, freq);    

  // --- compte le nombre de lignes
  long ndata;
  sprintf(sql, "SELECT count(*) FROM %s WHERE %s", tablename, szWhere);
  otl_stream stcount(50,sql,db);
  stcount >> ndata;
  if(ndata==0) return tsempty;

  // --- lecture des lignes
//  sprintf(sql,"SELECT dataYear,dataSubp,seriesBaseYear,recodID,dataValue FROM data,series");
//  sprintf(sql, "%s WHERE (data.seriesID=series.seriesID) AND %s ", sql, szWhere);
//  sprintf(sql, "%s ORDER BY dataYear,dataSubp", sql);

  sprintf(sql, "SELECT year,subp,value FROM %s WHERE %s ORDER BY year,subp", tablename, szWhere);
  otl_stream strows(50,sql,db);

  // --- init du vecteur
  long byear;
  long bsubp;
  strows >> byear;
  strows >> bsubp;

  bool trouve=true;
  enl_tseries v1;
  while(trouve){
	trouve=false;
	 // --- déclaration de la série
	enl_tseries v(ndata+bsubp-1,freq,byear,na());
	v.SetCountryID(cid);
	v.SetSeriesID (sid);
	v.SetUpdateID (m_updateID);

	// --- lecture des valeurs
	int i = 0;
	long yearNew;
	long yearOld=byear;
	long subpNew;
	long subpOld=bsubp;
	strows.rewind();
	while ( !strows.eof() ) {
	    double dataValue;
		strows >> yearNew;
		strows >> subpNew;
		strows >> dataValue;
		//permet de vérifier si des années ont été sautées
		i=i+(yearNew-yearOld)*freq+subpNew-subpOld;
		if(!strows.is_null()){
			if( (i+bsubp-1)<ndata ) {
				v[i+bsubp-1] = dataValue;
				  
			}
		}	  
		yearOld=yearNew;
		subpOld=subpNew;

	}				
	if(i!=ndata-1){
	  trouve=true;
	  ndata=i+1;
	}
	v1=v;
  }
  // --- ajuste l'année de base
  long seriesBaseYear;
  sprintf(sql,"SELECT baseyear FROM series WHERE sid='%s'", sid);
  otl_stream stSeriesBaseYear(50,sql,db);
  stSeriesBaseYear >> seriesBaseYear;
  v1.adjust_byear(seriesBaseYear); 
  enl_db::add(v1);
  return v1;
}


int enl_db_otl::add ( const enl_tseries& v, const int& replace )
{
  char   sql[1024];

  enl_db::add(v,replace);

  // --- recherche si la série est déjà répertoriée
  sprintf(sql,"SELECT * FROM series WHERE sid='%s'", v.GetSeriesID());
  otl_stream series(50,sql,db);
  if( series.eof() ) return 1;

  // --- efface la version précédente
  sprintf(sql,"DELETE FROM data WHERE cid='%s' AND sid='%s' AND uid=%i AND freq=%i", 
	  v.GetCountryID(), v.GetSeriesID(), v.GetUpdateID(),v.GetDataFreq());
  otl_cursor::direct_exec( db, sql, otl_exception::disabled );

  // --- debut de la transaction
  //  odb.BeginTrans();
  //  set_commit(0);

  // --- ajout des éléments
  for(int i=0; i<v.nrows(); i++)
    {
	
	  if( v[i].GetIsAvailable() ) 
	  {
		sprintf(sql,"INSERT INTO data(cid,sid,uid,freq,year,subp,value) ");
		sprintf(sql,"%s VALUES('%s','%s',%i,%i,%i,%i,%f)", sql,
			v.GetCountryID(),
			v.GetSeriesID(),
			v.GetUpdateID(),
			v.GetDataFreq(),
			v.GetYear(i),
			v.GetSubp(i),
			v[i].GetValue() );
	  }
	  else
	  {
		sprintf(sql,"INSERT INTO data(cid,sid,uid,freq,year,subp) ");
		sprintf(sql,"%s VALUES('%s','%s',%i,%i,%i,%i)", sql,
			v.GetCountryID(),
			v.GetSeriesID(),
			v.GetUpdateID(),
			v.GetDataFreq(),
			v.GetYear(i),
			v.GetSubp(i));
	  }

	  otl_cursor::direct_exec( db, sql, otl_exception::disabled );

    }

  // --- fin de la transaction
  //  odb.CommitTrans();
  //  set_commit(0);


  return 0;
}

int enl_db_otl::addmx ( const enl_tseries_mx& v, const int& replace )
{
  long i;

  // --- efface la version précédente
  const char* sid = NULL;
  long  uid = 0;

  for(i=0; i<v.GetNSeries(); i++)
    {
      if( sid == NULL )
	if ( v[i].GetSeriesID() != NULL )
	  sid = v[i].GetSeriesID();
      if( uid == 0 )
	if ( v[i].GetUpdateID() != 0 )
	  uid = v[i].GetUpdateID();
      if( (sid!=NULL) && (uid!=0) )
	break;

    }
  if( (sid!=NULL) && (uid!=0) )
    {
      char sql[1024];
      sprintf(sql,"DELETE FROM data WHERE seriesID='%s' AND updateID=%i", sid, uid);
      otl_cursor::direct_exec( db, sql, otl_exception::disabled );
    }

  // --- ajoute les séries
  for(i=0; i<v.GetNSeries(); i++)
    {
      add(v[i],replace);
    }

  return 1;

}

int enl_db_otl::getparam ( const char* group, const char* name, double* value)
{
  char   sql[1024];
  if ( !group || !name ) return 0;

  sprintf(sql,"SELECT pvalue FROM params WHERE pgroup='%s' AND pname='%s'", group, name);
  otl_stream params(50,sql,db);
  if( params.eof() ) return 0;

  double v;
  params >> v;
  *value = v;
  
  return 1;
}

int enl_db_otl::setparam (const char* group, const char* name, double value)
{
  char   sql[1024];
  if ( !group || !name ) return 0;

  sprintf(sql,"DELETE FROM params WHERE pgroup='%s' AND pname='%s'", group, name);
  otl_cursor::direct_exec( db, sql, otl_exception::disabled );

  sprintf(sql,"INSERT INTO params VALUES('%s','%s',%f)",group,name,value);
  otl_cursor::direct_exec( db, sql, otl_exception::disabled );
  
  return 1;
}


int enl_db_otl::addSerie (const char seriesID[],const char seriesDescription[])
{
  char   sql[1024];

  // --- recherche si la série est déjà répertoriée
  sprintf(sql,"select * from series where sid='%s'",seriesID);
  otl_stream series(50,sql,db);

  if(series.eof()){
	sprintf(sql, "INSERT INTO series(sid,desc) VALUES ('%s','%s')", seriesID,seriesDescription);
	otl_stream series(50,sql,db);
  }

  return 0;
}
