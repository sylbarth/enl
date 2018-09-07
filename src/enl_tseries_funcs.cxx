/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"
#include "iostream.h"

enl_tseries pow(const enl_tseries& v, const double& d)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ )
    ets[i] = pow(v[i], d);
  return ets;
}

 
enl_tseries sqrt(const enl_tseries& v)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ )
    ets[i] = sqrt(v[i]);
  return ets;
}

 
enl_tseries log(const enl_tseries& v)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ )
    ets[i] = log(v[i]);
  return ets;
}

 
enl_tseries exp(const enl_tseries& v)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ )
    ets[i] = exp(v[i]);
  return ets;
}

enl_tseries logit(const enl_tseries& v,const double& a, const double& b)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ )
    ets[i] = exp(a*v[i]+b)/(1+exp(a*v[i]+b));
  return ets;
}

 
enl_tseries ifover(const enl_tseries& v, const enl_tseries& t)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if(i<t.nrows()) 
	{
	  if ( v[i] > t[i] ) 
	    ets[i] = 1;
	  else
	    ets[i] = 0;
	}
    }
  return ets;
}

 
enl_tseries ifover(const enl_tseries& v, const double& d)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if( v[i].GetIsAvailable() ) {
	if ( v[i] < d ) 
	  ets[i] = 1;
	else
	  ets[i] = 0;
      }
    }
  return ets;
}

 
enl_tseries ifover_or_equal(const enl_tseries& v, const double& d)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if( v[i].GetIsAvailable() ) {
	if ( v[i] >= d ) 
	  ets[i] = 1;
	else
	  ets[i] = 0;
      }
    }
  return ets;
}

 
enl_tseries ifunder(const enl_tseries& v, const enl_tseries& t)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if(i<t.nrows()) 
	{
	  if ( v[i] < t[i] ) 
	    ets[i] = 1;
	  else
	    ets[i] = 0;
	}
    }
  return ets;
}

 
enl_tseries ifunder(const enl_tseries& v, const double& d)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if( v[i].GetIsAvailable() ) {
	if ( v[i] < d ) 
	  ets[i] = 1;
	else
	  ets[i] = 0;
      }
    }
  return ets;
}

 
enl_tseries ifequal(const enl_tseries& v, const enl_tseries& t, const enl_data& r1, const enl_data& r2)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if(i<t.nrows()) 
	{
	  if ( v[i] == t[i] ) 
	    ets[i] = r1;
	  else
	    ets[i] = r2;
	}
    }
  return ets;
}

 
enl_tseries ifequal(const enl_tseries& v, const double& d, const enl_data& r1, const enl_data& r2)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if( v[i].GetIsAvailable() ) {
	if ( v[i] == d ) 
	  ets[i] = r1;
	else
	  ets[i] = r2;
      }
    }
  return ets;
}

 
enl_tseries ifisset(const enl_tseries& v, const enl_tseries& t)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if(i<t.nrows()) 
	{
	  if ( t[i] != 1 ) 
	    ets[i] = na();
	}
    }
  return ets;
}

 
enl_tseries ifover(const enl_tseries& v, const double& d, const enl_tseries& t1, const enl_tseries& t2)
{
  enl_tseries ets = v;
  ets = na();
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if( (i<t1.nrows()) && (i<t2.nrows()) ) 
	{
	  if( v[i].GetIsAvailable() ) {
	    if ( v[i] > d ) 
	      ets[i] = t1[i];
	    else
	      ets[i] = t2[i];
	  }
	}
    }
  return ets;
}

 
enl_tseries ifafter(const enl_tseries& v, const int& n, const enl_data& d)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) 
    {
      if(v[i] >= 1)
	{
	  while(v[i]>=1)
	    {
	      if(i<v.nrows()) 
		i++;
	      else
		break;
	    }
	  for(long k=i; (k<(i+n)) && k<(v.nrows()); k++)
	    ets[k] = d;
	}
    }
  return ets;
}

 
enl_tseries over(const enl_tseries& v, const double& dThr)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) {
    ets[i] = v[i];
    if( v[i].GetIsAvailable() ) {
      if ( v[i] < dThr )
	ets[i] = dThr;
    } else
      ets[i] = na();
  }
  return ets;
}


 
enl_tseries greater_else(const enl_tseries& v, const double& dThr, const enl_data& other)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) {
    ets[i] = v[i];
    if( v[i].GetIsAvailable() ) {
      if ( v[i] <= dThr )
	ets[i] = other;
    } else
      ets[i] = na();
  }
  return ets;
}

 
enl_tseries under(const enl_tseries& v, const double& dThr)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) {
    ets[i] = v[i];
    if( v[i].GetIsAvailable() ) {
      if ( v[i] > dThr )
	ets[i] = dThr;
    } else
      ets[i] = na();
  }
  return ets;
}

 
enl_tseries over_abs(const enl_tseries& v, const double& dThr)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) {
    ets[i] = v[i];
    if( v[i].GetIsAvailable() ) {
      if ( fabs(v[i]) < dThr )
	ets[i] = enl_data(0);
    } else
      ets[i] = na();
  }
  return ets;
}

 
enl_tseries under_abs(const enl_tseries& v, const double& dThr)
{
  enl_tseries ets = v;
  for ( long i=0; i<v.nrows(); i++ ) {
    ets[i] = v[i];
    if( v[i].GetIsAvailable() ) {
      if ( fabs(v[i]) > dThr )
	ets[i] = enl_data(0);
    } else
      ets[i] = na();
  }
  return ets;
}

 
enl_tseries fabs (const enl_tseries& v)
{
  enl_tseries ret = v;
  for ( long i=0; i<v.nrows(); i++ )
    ret[i] = fabs(v[i]);
  return ret;
}

enl_tseries mob_2m1_c(const enl_tseries& v, const std::vector<double> coef)
{
  long i,c;
  long nobs  = v.nrows();
  long ncoef = coef.size();

  enl_tseries ets = v;
  ets.fill_na();

  // --- vérif ncoef<nobs
  if(ncoef>nobs) return ets;

  // --- vérif somme des coefs == 1
  double sum = 0.0;
  for(c=0; c<ncoef; c++)
    sum+=coef[c];
  // --- on aurorise une erreur de précision
  // ex: moyenne de henderson non toujours==1.0 strictement
  if(sum > 1.0000001) return ets;
  if(sum < 0.9999999) return ets;

  // --- vérif nombre impair de coefs
  if( (ncoef%2) == 0) return ets;

  // --- calcul mob centrée
  int m = (ncoef-1)/2;
  for(i=m; i<(nobs-m); i++) {
    ets[i] = 0.0;
    for(c=0; c<ncoef; c++) {
      if( v[i-m+c].GetIsAvailable() )
	ets[i] = ets[i].GetValue() + v[i-m+c].GetValue()*coef[c];
      else {
	ets[i].SetIsAvailable(0);
	break; // on passe au suivant car une donnée NA
      }
    }
  }
  return ets;
}

std::vector<double> hender(const long& n)
{
  long i = 0;
  long j = 0;
  long m = (n+1)/2;
  std::vector<double> v(n);
 
  double y  = ((double)n+3.0)/2.0;
  double y1 = (y-1.0)*(y-1.0);
  double y2 = y*y;
  double y3 = (y+1.0)*(y+1.0);
  double y4 = 3.0*y2-16.0;
  double y5 = 4.0*y2;
  double denomi=8.0*y*(y2-1.0)*(y5-1.0)*(y5-9.0)*(y5-25.0)/315.0;

  // --- calcul des coefs
  for(i=0; i<m; i++) {
    double x=(double)i*(double)i;
    v[m-1-i] = (y1-x)*(y2-x)*(y3-x)*(y4-11.0*x)/denomi;
  }
  // --- les autes sont symétriques autour de m-1
  for(i=m,j=(m-2); (i<n) && (j>=0); i++,j--)
    v[i] = v[j];

  return v;
}

enl_tseries mob_hender(const enl_tseries& v, const long& m)
{
  std::vector<double> coef;
  enl_tseries        ets;

  coef = hender (2*m+1);
  ets  = mob_2m1_c(v,coef);

  return ets;
}

enl_tseries seasadj_hender(const enl_tseries& v, const long& m)
{
  if(v.GetDataFreq()!=ENL_QUARTERLY) {
    enl_tseries e;
    return e;
  }
  // --- lissage de henderson
  enl_tseries ets = mob_hender(v,m);

  // --- lissage 4321 pour les points terminaux
  enl_tseries vm = mean4321(v);
  enl_tseries tv = yoy(vm);

  // --- remplissages des derniers points avec yoy(v)
  for(long i=4; i<ets.nrows(); i++) {
    if( (ets[i]  .GetIsAvailable()==0) &&
	(ets[i-4].GetIsAvailable()==1) &&
	(tv[i]   .GetIsAvailable()==1) ) {
      ets[i] = (1.0+tv[i].GetValue()/100.0)*ets[i-4].GetValue();
    }
  }
  return ets;
}

enl_tseries atoq(const enl_tseries& v, const bool hender)
{
  enl_tseries ets = atoq_planar(v);
  ets = mean4321(ets);
  if(hender==true) ets = seasadj_hender(ets,4);

  return ets;
}

enl_tseries atoq_planar(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_QUARTERLY);

  if ( v.nr == 0 )              return ets;
  if ( v.m_freq != ENL_ANNUAL ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_QUARTERLY);

  // --- opération
  ets.resize(v.nr * 4);
  for ( long i=0; i<v.nr; i++ )
    for ( long j=0; j<4; j++ )
      ets[k++] = v[i];

  return ets;
}
 
enl_tseries qtoa_s(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_ANNUAL);

  if ( v.nrows() == 0 )                 return ets;
  if ( v.GetDataFreq() != ENL_QUARTERLY ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_ANNUAL);

  // --- opération
  enl_tseries vs = sum4(v);
  ets.resize(v.nrows()/4);
  ets = na();

  for ( long i=3; i<v.nrows(); i+=4 )
    ets[k++] = vs[i];

  return ets;
}

 
enl_tseries qtoa_m(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_ANNUAL);

  if ( v.nrows() == 0 )                 return ets;
  if ( v.GetDataFreq() != ENL_QUARTERLY ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_ANNUAL);

  // --- opération
  enl_tseries vm = mean4(v);
  ets.resize(v.nrows()/4);
  ets = na();

  for ( long i=3; i<v.nrows(); i+=4 )
    ets[k++] = vm[i];

  return ets;
}

 
enl_tseries qtoa_eop(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_ANNUAL);

  if ( v.nrows() == 0 )                 return ets;
  if ( v.GetDataFreq() != ENL_QUARTERLY ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_ANNUAL);

  // --- opération
  enl_tseries vm = v;
  ets.resize(v.nrows()/4);
  ets = na();

  for ( long i=0; i<v.nrows(); i++ )
    if(ets.GetSubp(i)==4)
      ets[k++] = vm[i];

  return ets;
}

enl_tseries mtoa_m(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_ANNUAL);

  if ( v.nrows() == 0 )                 return ets;
  if ( v.GetDataFreq() != ENL_MONTHLY ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_ANNUAL);

  // --- opération
  enl_tseries vm = mean(v,12);
  ets.resize(v.nrows()/12);
  ets = na();

  for ( long i=11; i<v.nrows(); i+=12 )
    ets[k++] = vm[i];

  return ets;
}

enl_tseries mtoq_m(const enl_tseries& v)
{
  enl_tseries ets;
  long      k = 0;

  ets.SetDataFreq(ENL_QUARTERLY);

  if ( v.nrows() == 0 )                 return ets;
  if ( v.GetDataFreq() != ENL_MONTHLY ) return ets;

  ets = v;
  ets.SetDataFreq(ENL_QUARTERLY);

  // --- opération
  enl_tseries vm = mean(v,3);
  ets.resize(v.nrows()/3);
  ets = na();

  for ( long i=2; i<v.nrows(); i+=3 )
    ets[k++] = vm[i];

  return ets;
}
 
enl_tseries base(const enl_tseries& v, const long& year, const long& subp)
{
  enl_tseries ets = v;
  if ( v.nrows()==0 ) return enl_tseries();

  // --- recherche de la valeur de base
  long idx  = v.GetIndex(year,subp);

  // --- opération
  for (long i=0; i<v.nrows(); i++ ){
	ets[i] = 100.0*v[i]/v[idx];
  }
  return ets;
}


enl_tseries sum( const enl_tseries& v, const long& n )
{
  enl_tseries ets;

  if ( v.nrows() == 0 ) return ets;
  if ( v.nrows() <  n ) return ets;

  ets = v;
  ets = na();
  
  for ( long i=(n-1); i<v.nrows(); i++ ) {
    ets[i] = 0.0;
    for ( int j=(i-n+1); j<=i; j++ )
       ets[i] += v[j];
  }
  return ets;
}

 
enl_tseries mean (const enl_tseries& v, const long& n)
{
  return sum(v,n)/double(n);
}

 
enl_tseries sd (const enl_tseries& v, const long& n)
{
  if ( v.nrows() == 0 ) return enl_tseries();
  if ( v.nrows() <  n ) return enl_tseries();

  enl_tseries vv = pow(v,2);
  enl_tseries a  = double(n) * sum(vv, n);
  enl_tseries b  = pow(sum(v,n),2);  

  enl_tseries ret = sqrt( (a-b)/double(n*n) );

  return ret;
}

 
enl_tseries sde (const enl_tseries& v, const long& n)
{
  if(n<=1) return enl_tseries();
  return sd(v,n) * ::sqrt(double(n))/::sqrt(double(n-1));
}


 
enl_tseries trend (const enl_tseries& v, const double& c)
{
  enl_tseries t = v;
  for(long i=1; i<v.nrows(); i++)
    t[i] = t[i-1] + c;
  return t;
}

 
enl_tseries trend_exp(const enl_tseries& v, const double& c)
{
  enl_tseries t = v;
  for(long i=1; i<v.nrows(); i++)
    t[i] = t[i-1] * c;
  return t;
}

 
enl_tseries mean4321 (const enl_tseries& v)
{
  enl_tseries ets = 0.4*v + 0.3*v(1) + 0.2*v(2) + 0.1*v(3);
  return ets;
}

 
enl_tseries mean4 (const enl_tseries& v)
{
  enl_tseries ets = mean(v,4);
  return ets;
}

 
enl_tseries sum4 (const enl_tseries& v)
{
  enl_tseries ets = sum(v,4);
  return ets;
}

 
 
enl_tseries yoy (const enl_tseries& v)
{
  enl_tseries ets;

  if ( v.nrows() == 0 ) return ets;

  ets = v;

  switch ( v.GetDataFreq() ) {
  case ENL_ANNUAL:    ets = ets/ets(1) - 1.0;  break;
  case ENL_QUARTERLY: ets = ets/ets(4) - 1.0;  break;
  case ENL_MONTHLY:   ets = ets/ets(12) - 1.0; break;
  }

  return 100.0*ets;
}

 
enl_tseries lint(const enl_tseries& v)
{
  long i,j,k;
  long start = 0;
  enl_tseries ets;

  if ( v.nrows() == 0 ) return ets;

  ets = v;

  // --- on recherche la première donnée dispo
  for ( start=0; start<ets.nrows(); start++) {
    if ( ets[start].GetIsAvailable() )
      break;
  }
  // --- sortie si pas de premier point
  if ( start > (ets.nrows()-1) )
    return ets;

  // --- interpolation
  for ( i=(start+1); i<ets.nrows(); i++ ) {

    // --- si une donnée manque
    if ( !ets[i].GetIsAvailable() ) {
			
      if( ets[i] == ets.last() ) break;

      // --- calcul du nombre obs NA consécutives
      enl_data size = 0.0;
      for ( k = i; k<ets.nrows(); k++ ) {
	if ( ets[k].GetIsAvailable() ) break;
	size += 1.0;
      }
      
      if ( k >= ets.nrows() ) break;

      // --- création du vecteur
      enl_data first= ets[i-1].GetValue();
      enl_data last = ets[  k].GetValue();
      for ( j=i; j<k; j++ ) {
	enl_data step  = (last - first)/(size+1.0);
	enl_data count = j-i+1;
	ets[j] = (step*count) + first;
	ets[j].SetIsEstimate(true);
      }
    }
  }
  return ets;
}



 
 enl_data maxval(const enl_tseries& v)
{
  enl_data dMax = DBL_MIN;

  for ( long i = 0; i < v.nrows(); i++) {
      if ( ( v[i].GetIsAvailable() ) && 
	   ( v[i].GetValue() > dMax) )
	dMax = v[i].GetValue();
  }

  return dMax;
}

 
 enl_data minval(const enl_tseries& v)
{
  enl_data dMin = DBL_MAX;

  for ( long i = 0; i < v.nrows(); i++) {
      if ( ( v[i].GetIsAvailable() ) && 
	   ( v[i].GetValue() < dMin) )
	dMin = v[i].GetValue();
  }

  return dMin;
}

 
enl_tseries max_sized(const enl_tseries& v, const long& n)
{
  enl_tseries ret = v;

  ret = na();
  if ( n < 2 ) return ret;

  long _fobs = n-1;

  for ( long i=_fobs; i<v.nrows(); i++) {

    double dMax = DBL_MIN;

    for (int j=(i-n+1); j<=i; j++) {
      if ( v[j] > dMax )
	dMax = v[j].GetValue();
    }

    if ( dMax > DBL_MIN ) {
      if ( v[i].GetIsAvailable() ) {
	ret[i].SetValue(dMax);
	ret[i].SetIsAvailable(1);
      }
    } 

  }
  return ret;
}

 
enl_tseries min_sized(const enl_tseries& v, const long& n)
{
  enl_tseries ret = v;

  ret = na();
  if ( n < 2 ) return ret;

  long _fobs = n-1;

  for ( long i=_fobs; i<v.nrows(); i++) {

    double dMin = DBL_MAX;

    for (int j=(i-n+1); j<=i; j++) {
      if ( v[j] < dMin )
	dMin = v[j].GetValue();
    }

    if ( dMin < DBL_MAX ) {
      if ( v[i].GetIsAvailable() ) {
	ret[i].SetValue(dMin);
	ret[i].SetIsAvailable(1);
      }
    }
 
  }
  return ret;
}

 
 enl_data maxval(const enl_tseries& v, const long& year)
{
  enl_data dMax = DBL_MIN;

  for ( long i = 0; i < v.nrows(); i++) {
    if ( ( v[i].GetIsAvailable() ) && 
	 ( v[i].GetValue() > dMax) &&
	 ( v.GetYear(i)>=year) )
      dMax = v[i].GetValue();
  }

  return dMax;
}

 
 enl_data minval(const enl_tseries& v, const long& year)
{
  enl_data dMin = DBL_MAX;

  for ( long i = 0; i < v.nrows(); i++) {
    if ( ( v[i].GetIsAvailable() ) && 
	 ( v[i].GetValue() < dMin) &&
	 ( v.GetYear(i)>=year) )
      dMin = v[i].GetValue();
  }

  return dMin;
}

 
enl_tseries join(const enl_tseries& v1, const enl_tseries& v2)
{
  enl_tseries ets = v1;
  ets = na();
  for ( long i=0; i<v1.nrows(); i++ ) 
  {
    if ( v2.nrows() > i ) 
	{
		if(!ets[i].GetIsAvailable())
			ets[i] = v2[i];
	}
  }
  return ets;
}

 
enl_tseries ifAND(const enl_tseries& Va, const double& a, const enl_tseries& Vb, const double& b)
{
  enl_tseries ets = Va;
  ets = na();
  for ( long i=0; i<ets.nrows(); i++ ) 
  {
	  if( (i<Va.nrows()) && (i<Vb.nrows()) ) 
	  {
	  if( Va[i].GetIsAvailable() && Vb[i].GetIsAvailable() ) {
    if ( (Va[i] == a) &&  (Vb[i] == b) ) 
		ets[i] = 1;
	else
		ets[i] = 0;
	  }
	  }
  }
  return ets;
}


double sum( const enl_tseries& v )
{
  double s = 0.0;
  for ( long i=0; i<v.nrows(); i++ )
  {
	  if(v[i].GetIsAvailable())
       s += v[i].GetValue();
  }
  return s;
}

double mean( const enl_tseries& v )
{
  if( v.nrows()==0 ) return -999999.0;
  return sum(v)/v.nrows();
}

double sd( const enl_tseries& v )
{
  if( v.nrows()==0 ) return -999999.0;

  double n = double(v.nrows());
  double a = n * sum( pow(v,2) );
  double b = pow( sum(v),2 );  

  return sqrt( (a-b)/(n*n) );
}

double cov( const enl_tseries& v1, const enl_tseries& v2 )
{
  if( v1.nrows()==0 ) return 0.0;
  if( v2.nrows()==0 ) return 0.0;

  double mv1 = mean(v1);
  double mv2 = mean(v2);

  return mean( (v1-mv1) * (v2-mv2) );
}


double cor( const enl_tseries& v1, const enl_tseries& v2 )
{
  if( v1.nrows()==0 ) return 0.0;
  if( v2.nrows()==0 ) return 0.0;

  double sdv1 = sd(v1);
  double sdv2 = sd(v2);
  if( sdv1==0.0 ) return 0.0;
  if( sdv1==0.0 ) return 0.0;

  return cov(v1,v2)/(sdv1*sdv2);
}

