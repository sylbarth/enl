/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"
#include "iostream.h"

enl_tseries::enl_tseries() : mat(0), nr(0), init(0),
    m_updateID(0), m_recodID(0), m_freq(1), m_byear(ENL_DEFAULT_BYEAR)
  {
    m_countryID[0] = '\0';
    m_seriesID[0]  = '\0';
  }

  enl_tseries::enl_tseries(const long& r, const long& f , const long& b, const enl_data& t) : mat(0), nr(r), init(0),
    m_updateID(0), m_recodID(0), m_freq(f), m_byear(b)
  {
  if( nr==0 ) return;
  mat = new enl_data[nr];
  for (long i=0; i<nr; i++) {
     mat[i] = t;
  }

  }

  enl_tseries::enl_tseries(const enl_tseries& v) :   mat (0),  nr (v.nr), init(v.init),
    m_updateID(v.m_updateID), m_recodID(v.m_recodID),
    m_freq(v.m_freq), m_byear(v.m_byear) 
  {
    strcpy(m_countryID, v.m_countryID);
    strcpy(m_seriesID,  v.m_seriesID);
    if( nr==0 ) return;
    mat = new enl_data[nr];
    for(long i=0; i<nr; i++)
      mat[i] = v.mat[i];
  }

  enl_tseries::~enl_tseries() 
  {
	    empty();
  }

  // --- opérateurs d'affectation
  enl_tseries& enl_tseries::operator=(const enl_tseries& v)
  {
    if ( mat == v.mat ) return *this;
    
    init = v.init;
    
    strcpy(m_countryID, v.m_countryID);
    strcpy(m_seriesID,  v.m_seriesID);
    m_updateID = v.m_updateID;
    m_recodID  = v.m_recodID;
    m_freq     = v.m_freq;
    m_byear    = v.m_byear;

    resize(v.nr);

    for (long i=0; i<nr; i++)
	mat[i] = v.mat[i];

    return *this;
  }

  enl_tseries& enl_tseries::operator=(const enl_data& t)
  {
    for ( long i=0; i<nr; i++ )
      mat[i] = t;
    return *this;
  }

    // --- empty/resize
	void enl_tseries::empty()
	{ 
	if(mat) delete[] mat;
	mat = 0;
	 nr  = 0;
	}
  
//  reallocation method
void enl_tseries::resize (const long& r)
{
  if ( r==nr ) return;

  // --- alloc nouvelle mat
  enl_data* mat1 = new enl_data[r];

  // --- copie ancienne mat
  if( nr>0 ) {
    long min_nr = MIN(nr,r);
    if(mat) {
		for (long i=0; i<min_nr; i++)
		mat1[i] = mat[i];
		delete[] mat;
	}
  }

  //--- affectation nouvelle mat
  mat = mat1;
  nr  = r;

  return;
}

  // --- opérateurs arithmétiques
  enl_tseries enl_tseries::operator+(const enl_tseries& v) const
  {
    enl_tseries ets;
    if( MakeFields(&ets,this,&v)==false ) return ets;

    // --- opération
    long nobs = MIN(nr,v.nr);
    ets.resize(nobs);

    for ( long i=0; i<nobs; i++ )
      ets.mat[i] = mat[i] + v.mat[i];

    return ets;
  }

  enl_tseries enl_tseries::operator-(const enl_tseries& v) const
  {
    enl_tseries ets;
    if( MakeFields(&ets,this,&v)==false ) return ets;
  
    // --- opération
    long nobs = MIN(nr,v.nr);
    ets.resize(nobs);

    for ( long i=0; i<nobs; i++ )
      ets.mat[i] = mat[i] - v.mat[i];

    return ets;
  }

  enl_tseries enl_tseries::operator*(const enl_tseries& v) const
  {
    enl_tseries ets;
    if( MakeFields(&ets,this,&v)==false ) return ets;
  
    // --- opération
    long nobs = MIN(nr,v.nr);
    ets.resize(nobs);

    for ( long i = 0; i < nobs; i++ )
      ets.mat[i] = mat[i] * v.mat[i];

    return ets;
  }

  enl_tseries enl_tseries::operator/(const enl_tseries& v) const
  {
    enl_tseries ets;
    if( MakeFields(&ets,this,&v)==false ) return ets;
  
    // --- opération
    long nobs = MIN(nr,v.nr);
    ets.resize(nobs);

    for ( long i = 0; i < nobs; i++ )
      ets.mat[i] = mat[i] / v.mat[i];

    return ets;
  }

  enl_tseries enl_tseries::operator+= (const enl_tseries& v) { *this = *this + v; return *this; }
  enl_tseries enl_tseries::operator-= (const enl_tseries& v) { *this = *this - v; return *this; }
  enl_tseries enl_tseries::operator*= (const enl_tseries& v) { *this = *this * v; return *this; }
  enl_tseries enl_tseries::operator/= (const enl_tseries& v) { *this = *this / v; return *this; }


  // --- opérateurs arithmétiques double
  enl_tseries enl_tseries::operator+= (const double& d) { *this = *this + d; return *this; }
  enl_tseries enl_tseries::operator-= (const double& d) { *this = *this - d; return *this; }
  enl_tseries enl_tseries::operator*= (const double& d) { *this = *this * d; return *this; }
  enl_tseries enl_tseries::operator/= (const double& d) { *this = *this / d; return *this; }


// --- opérateurs arithmétiques double friends
enl_tseries operator+(const enl_tseries& v, const double& d)
{
  enl_tseries ets(v);
  for ( long i=0; i<v.nr; i++ )
    ets[i] = v[i] + d;
  return ets;
}

enl_tseries operator-(const enl_tseries& v, const double& d)
{
  enl_tseries ets(v);
  for ( long i=0; i<v.nr; i++ )
    ets[i] = v[i] - d;
  return ets;
}

enl_tseries operator*(const enl_tseries& v, const double& d)
{
  enl_tseries ets(v);
  for ( long i=0; i<v.nr; i++ )
    ets[i] = v[i] * d;
  return ets;
}

enl_tseries operator/(const enl_tseries& v, const double& d)
{
  enl_tseries ets(v);
  for ( long i=0; i<v.nr; i++ )
    ets[i] = v[i] / d;
  return ets;
}

enl_tseries operator+ (const double& d, const enl_tseries& v) { return v+d; }
enl_tseries operator- (const double& d, const enl_tseries& v) { return d+(-1.0*v); }
enl_tseries operator* (const double& d, const enl_tseries& v) { return v*d; }

enl_tseries operator/ (const double& d, const enl_tseries& v) 
{ 
  enl_tseries t = v;
  t = pow(t,-1) * d;
  return t;
}
  // --- opérateurs d'accès
  enl_tseries enl_tseries::operator()(const long n) const
  {
    enl_tseries ets(*this);
    ets.resize(ets.nrows()+n);
    ets = na();

    if ( n>=nr ) return ets;

    for ( long i=n; i<ets.nrows(); i++ )
      ets[i] = mat[i-n];

    return ets;
  }

  enl_tseries enl_tseries::forward(const long n) const
  {
    long i;
    enl_tseries ets(*this);
    //    ets.resize();
    //    ets = na();

    if ( n>=nr ) return ets;

    for ( i=0; i<(ets.nrows()-n); i++ )
      ets[i] = mat[i+n];
    for ( i=(ets.nrows()-n); i<ets.nrows(); i++ )
      ets[i] = na();

    return ets;
  }

  enl_data& enl_tseries::operator[](const long n)       
  { 
	  return mat[n]; 
  }

  const enl_data& enl_tseries::operator[](const long n) const 
  { 
	  return mat[n]; 
  }

  
  // to transform to get() / add() / getval()
  void enl_tseries::add( const enl_data& ed )
  {
    resize(nr+1);
    mat[nr-1] = ed;
  }
  void enl_tseries::fill_na() {
    for(long i=0; i<nr; i++)
		  mat[i]= enl_data();
  }

  enl_data enl_tseries::get(const long& year, const long& subp)
  {
    long index = GetIndex(year,subp); 
    if(index>=nr) return na();
    return mat[index];
  }

  long enl_tseries::avail()
  {
    long count = 0;
    for ( long i=0; i<nr; i++ )
      if ( mat[i].GetIsAvailable() ) count++;
    return count;
  }

  enl_data enl_tseries::first() const
  {
    enl_data e;
    if ( nr <= 0 ) return e;

    for ( long i=0; i<nr; i++ ) {
      if ( mat[i].GetIsAvailable() ) 
	return mat[i];
    }
    return e;
  }

  enl_data enl_tseries::last() const
  {
    enl_data e;
    if ( nr <= 0 ) return e;

    for ( long i=(nr-1); i!=0; i-- ) {
      if ( mat[i].GetIsAvailable() ) 
	return mat[i];
    }
    return e;
  }


  bool enl_tseries::adjust_byear(const long& byear)
  {
    long i;
    long   diff = (m_byear-byear)*m_freq;

    // --- test diff
    if ( diff==0 ) return true;

    // --- nobs
    long nobs = nrows();

    // --- sauvegarde de l'actuel
    enl_tseries m(*this);

    // --- ajuste le nouveau sur la nouvelle base
    nobs += diff;
    empty();
    m_byear = byear;
    if(nobs<0) 
      {
	nobs=0;
	return true;
      }
    resize(nobs);
    for(i=0; i<nobs; i++)
      mat[i] = na();

    // --- recopie des anciennes données
    if(diff>0) {
      for(i=0; i<m.nr; i++)
	if( (i+diff)<nr) mat[i+diff] = m.mat[i];
    } else {
      for(i=-diff; i<m.nr; i++)
	if( (i+diff)<nr) mat[i+diff] = m.mat[i];
    }
    return true;
  }

  // --- Get/Set sur les membres privés
  long enl_tseries::GetIndex(const long& year, const long& subp) const 
  { 
	  return ((year-m_byear)*m_freq+subp-1); 
  }
  
  long enl_tseries::GetYear (const long& n) const 
  { 
    long debug = (n/m_freq)+m_byear;
    return (n/m_freq)+m_byear; 
  }
  
  long enl_tseries::GetSubp (const long& n) const 
  { 
    long debug = (n%m_freq)+1;
    return (n%m_freq)+1; 
  }

  long enl_tseries::last_indice() const
  {
	for(long i=nr-1;i>=0;i--)
    if ( mat[i].GetIsAvailable() ) 
      return i;
	return 0;
  }
  
  const char*  enl_tseries::GetCountryID()     const { return m_countryID; }
  const char*  enl_tseries::GetSeriesID()      const { return m_seriesID; }
  const int    enl_tseries::GetUpdateID()      const { return m_updateID; }
  const int    enl_tseries::GetRecodID()       const { return m_recodID;  }
  const int    enl_tseries::GetDataFreq()      const { return m_freq; }
  const int    enl_tseries::GetBaseYear()      const { return m_byear; }
  const enl_data enl_tseries::GetInit()		   const { return init; }

  void enl_tseries::SetCountryID  (const char* s) { strcpy(m_countryID, s);}
  void enl_tseries::SetSeriesID   (const char* s) { strcpy(m_seriesID,  s); }
  void enl_tseries::SetUpdateID   (const long& n) { m_updateID = n; }
  void enl_tseries::SetRecodID    (const long& n) { m_recodID = n; }
  void enl_tseries::SetDataFreq   (const long& n) { m_freq = n; }
  void enl_tseries::SetBaseYear   (const long& n) { m_byear = n; }

bool enl_tseries::MakeFields ( enl_tseries* ret, const enl_tseries* t1, const enl_tseries* t2 ) const
{
  // --- tests
  if ( t1->nr == 0 || t2->nr == 0 ) return false;
  if ( t1->m_byear != t2->m_byear ) return false;
  if ( t1->m_freq  != t2->m_freq  ) return false;

  // --- affectation des champs
  if( strcmp(t1->m_countryID,t2->m_countryID)==0 ) 
    strcpy(ret->m_countryID,t1->m_countryID);

  if( strcmp(t1->m_seriesID,t2->m_seriesID)==0 ) 
    strcpy(ret->m_seriesID,t1->m_seriesID);

  if ( t1->m_updateID == t2->m_updateID ) 
    ret->m_updateID = t1->m_updateID;

  if ( t1->m_recodID == t2->m_recodID ) 
    ret->m_recodID = t1->m_recodID;

  ret->SetDataFreq(t1->m_freq);
  ret->SetBaseYear(t1->m_byear);
      
  return true;


}

enl_tseries base_from(const enl_tseries& v, const long& year, const long& subp)
{
  enl_tseries ets = v;
  if ( v.nrows()==0 ) return enl_tseries();

  // --- recherche de la valeur de base
	long idx  = v.GetIndex(year,subp);

  // --- opération
  for (long i=idx; i<v.nrows(); i++ )
    ets[i] = 100.0*v[i]/v[idx];

  return ets;
}

enl_tseries basev(const enl_tseries& v, const std::vector<enl_date> by)
{
  long i,k;
  enl_tseries ets;
  enl_tseries vinit;

  if ( v.nrows() <= 0 ) return ets;
  if ( v.GetYear(0) != by[0].year ) return ets;
  if ( v.GetSubp(0) != by[0].subp ) return ets;

  // --- première base: on recherche le premier indice
  //     vinit ne sert à rien
  int f_year = v.GetBaseYear();
  int l_year = v.GetYear(v.nrows()-1);
  for (k=0; (k<v.nrows()) && (k<by.size()) && (vinit.avail()<=0); k++ ) {
    if(by[k].avail) {
		vinit = base(v,by[k].year,by[k].subp);
		}
  }
  if(vinit.avail()<=0) return ets;

  // --- tout ce qui est avant k est estimé car on ne connait par la base
  //  for(i=0; (i<k) && (i<vinit.nrows()); i++)
  //    vinit[i].SetIsEstimate(1);

  ets   = vinit;

  // --- on base toute la suite à partir de k
  int year_c = 0;
  int subp_c = 0;
  int year_p = by[k].year;
  int subp_p = by[k].subp;
  for ( i=(k+1); (i<v.nrows()) && (i<by.size()); i++ ) {
    if ( by[i].avail ) {
      year_c = by[i].year;
      subp_c = by[i].subp;
      // --- rebase que si la base change
      if( (year_c!=year_p) || (subp_c!=subp_p) ) {
	enl_tseries newets = base_from(ets,year_c,subp_c);
	if ( newets.avail() > 0 ) 
	  ets = newets;
      }
      year_p = year_c;
      subp_p = subp_c;
    }
  }

  return ets;
}

bool enl_tseries::adjust_lyear(const long& lyear)
{
  long n = nr-1;
  long y = GetYear(n);
  long s = GetSubp(n);

  if(y==lyear) return true;

  // --- cas 1: ajout
  if(lyear>y) {
    for(;;) {
      add(enl_data());
      n = nr-1;
      y = GetYear(n);
      s = GetSubp(n);
      if( (y==lyear) && (s==m_freq) ) break; 
    }
  } 
  // --- cas 2: retrait
  else {
    long idx = GetIndex(lyear,m_freq);
    resize(idx+1);
  }

  return true;
}

void enl_tseries::dump(ostream& os)
{
  if(m_countryID) os << "country : " << m_countryID << endl;
  if(m_seriesID ) os << "series  : " << m_seriesID  << endl;

  switch(m_freq) {
  case ENL_ANNUAL:    os << "per    : A\n";  break;
  case ENL_QUARTERLY: os << "per    : Q\n";  break;
  case ENL_MONTHLY:   os << "per    : M\n";  break;
  default:            os << "per    : NA\n";
  }

  os << "byear  : " << m_byear << endl;
  os << "nobs   : " << nr  << endl;

  for(long i=0; i<nr; i++) {

    char s[256];
    s[0] = '\0';
    switch(m_freq) {
    case ENL_ANNUAL:    sprintf(s, "%i",      GetYear(i));	break;
    case ENL_QUARTERLY: sprintf(s, "%i.%i",   GetYear(i), GetSubp(i));break;
    case ENL_MONTHLY:   sprintf(s, "%i.%02i", GetYear(i), GetSubp(i));	break;
    default:            sprintf(s, "%i",      GetYear(i));	break;
    }

	if( mat[i].GetIsAvailable() )
		os << s << "\t" << mat[i].GetValue() << endl;
	else
		os << s << "\t" << "n.a." << endl;
  }

  os << endl;

}

