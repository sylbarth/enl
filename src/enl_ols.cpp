/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include <cmath>

#include "enl.h"

enl_ols::enl_ols(): 
  maty(0,0,enl_data()), 
  matx(0,0,enl_data()), 
  matbeta(0,0,enl_data()), 
  matstud(0,0,enl_data()),
  matiss(0,0,enl_data()),
  matvarcov(0,0,enl_data())
{
}

enl_ols::~enl_ols()
{
}

int enl_ols::addy(const enl_vector<enl_data>& v)
{
  maty.empty();
  maty << v;
  return 1;
}

int enl_ols::addy(const enl_matrix<enl_data>& m)
{
  maty = m;
  return 1;
}

int enl_ols::addx(const enl_matrix<enl_data>& m)
{
  matx = m;
  return 1;
}


int enl_ols::addy(const enl_tseries& ts)
{
  byear = ts.GetBaseYear();
  maty.empty();
  maty << ts;
  return 1;
}

int enl_ols::addx(const enl_tseries& ts)
{
  if(ts.GetBaseYear()!=byear) return 0;
  matx << ts;
  return 1;
}

void enl_ols::remove()
{
  maty.empty();
  matx.empty();
  byear = 0;
}

int enl_ols::estimate(const size_t& start, const size_t& end)
{
  size_t i,j;
  size_t fr = start;
  size_t lr = end;
  size_t nr = lr-fr+1;
  size_t nc = matx.ncols();

  enl_matrix<enl_data> X(0,0,enl_data());
  enl_matrix<enl_data> Y(0,0,enl_data());

  if ( fr >=lr ) return 0;

  // --- transfert des matrices
  nobs = nr;
  nreg = nc;
  df   = nobs - nreg;

  Y.resize(nr, 1 );
  X.resize(nr, nc);

  for(i=fr; i<=lr; i++) {
    Y[i-fr][0] = maty[i][0];
    for(j=0; j<nc; j++) {
      X[i-fr][j] = matx[i][j];
    }
  }
  // --- les transposées
  enl_matrix<enl_data> tX = enl_transpose(X);
  enl_matrix<enl_data> tY = enl_transpose(Y);

  // --- enl_ols estimates
  matiss  = tX*X;
  matiss  = enl_invert(matiss);
  matbeta = matiss * tX * Y;

  enl_matrix<enl_data> tb = enl_transpose(matbeta);
  
  // --- correction moy
  enl_data meany = 0;
  for ( i=0; i<nobs; i++ )
    meany += Y[i][0];
  meany /= double(nobs);
  enl_data meanc = double(nobs) * meany * meany;

  // --- tss = ess + rss
  enl_matrix<enl_data> yy   = tY * Y;
  enl_matrix<enl_data> bxy  = tb * tX * Y;
  enl_matrix<enl_data> _tss = yy   - meanc;
  enl_matrix<enl_data> _ess = bxy  - meanc;	

  tss = _tss[0][0]; // conv en scalaires
  ess = _ess[0][0]; // idem
  rss = tss - ess;

  // --- R2, R2adj
  R2   = ess / tss;
  R2adj= 1.0 - (1.0 - R2) * (nobs - 1.0) / df;

  // --- var-cov enl_matrix<enl_data>
  vres	 = rss / df;
  matvarcov = matiss * vres;

  // --- matsigma
  matsigma = matbeta;
  for ( i=0; i<matsigma.nrows(); i++ )
    matsigma[i][0] = sqrt(matvarcov[i][i]);

  // --- matstudent
  matstud = matbeta;
  for ( i=0; i<matstud.nrows(); i++ )
    matstud[i][0] /= sqrt(matvarcov[i][i]);

  return 1;
}

// --- estimations en chaine
int enl_olsv ( enl_ols*           e, 
	       enl_tseries*       matbeta, 
	       enl_tseries*       matstud, 
	       enl_tseries*       R2, 
	       enl_tseries*	  nobs,
	       const char*        prefix, 
	       const enl_tseries& _vinit,
	       const int          size)
{

  size_t k,i;
  
  // --- nom des séries
  char prefixB[256];
  char prefixT[256];
  char prefixR[256];
  char prefixN[256];

  memset(prefixB, 0, 256);
  memset(prefixT, 0, 256);
  memset(prefixR, 0, 256);
  memset(prefixN, 0, 256);

  strcpy(prefixB, prefix);
  strcpy(prefixT, prefix);
  strcpy(prefixR, prefix);
  strcpy(prefixN, prefix);

  strcat(prefixB, "_b_");
  strcat(prefixT, "_t_");
  strcat(prefixR, "_r");
  strcat(prefixN, "_n");

  // --- nb variables à estimer
  int nCount = e->matx.ncols();

  // --- init matbeta/matstud
  for ( k = 0; k < nCount; k++ ) {
    char _szIndice[256];
    char _prefixB [256];
    char _prefixT [256];

    memset(_szIndice, 0, 256);
    memset(_prefixB,  0, 256);
    memset(_prefixT,  0, 256);

    strcpy(_prefixB, prefixB);
    strcpy(_prefixT, prefixT);

    itoa( k, _szIndice, 10);

    strcat(_prefixB, _szIndice);
    strcat(_prefixT, _szIndice);

    matbeta[k] = _vinit; // init
    matstud[k] = _vinit; // init
    matbeta[k].SetSeriesID(_prefixB);
    matstud[k].SetSeriesID(_prefixT);
    matbeta[k].fill_na();	
    matstud[k].fill_na();
  }

  // --- init r2
  R2[0] = _vinit; // init
  R2->fill_na();
  R2->SetSeriesID(prefixR);
  
  nobs[0] = _vinit; // init
  nobs->fill_na();
  nobs->SetSeriesID(prefixN);
  
  // --- estimate
  size_t nry = e->maty.nrows();
  size_t nrx = e->matx.nrows();
  size_t nr  = (nry<nrx)?nry:nrx;

	// --- pour chaque année
  for ( i = (size-1); i<nr; i++ ) {

    int rep = e->estimate(i-size+1,i);
    if (rep == 0) continue;

    for ( k = 0; k < nCount; k++ ) {
      if ( i<matbeta[k].nrows() ) {
	enl_tseries* m1 = &matbeta[k];
	enl_tseries* m2 = &matstud[k];
	(*m1)[i] = e->matbeta[k][0];
	(*m2)[i] = e->matstud[k][0];
      }
      (*R2)  [i] = e->R2;
      (*nobs)[i] =(double) e->nobs;
    }

  }

  return 1;
}
