/*********************************************************************
 * Project: Economic & Financial Numerical Library
 * Author : Sylvain BARTHELEMY (sylbarth@gmail.com)
 *********************************************************************/

#include "enl.h"

// --- Attention, ici nous utilisons >= pour mimer la fonction
//     CENTILE de Microsoft Excel, mais sans interpolations sur 
//     les percentiles multiples de 1/(n-1)
enl_data Centile(vectorD& sortedValues, const enl_data& percentile)
{
  int siz = sortedValues.size();
  for (int i=0; i<siz; i++)
    {
      enl_data s = 100.0 * enl_data(i+1) / enl_data(siz);
      if( s >= percentile )
	return sortedValues[i];
    }
  return 0.0;
}

enl_data getGrade(vectorD& sortedValues, const vectorG& grades, const enl_data& d)
{
  enl_data ret = 0.0;
  int siz = grades.size();
  for (int k=0; k<siz;k++)
    {
      enl_data threshold = Centile(sortedValues,grades[k].percentile);
      if( d > threshold ) 
	ret = grades[k].grade;
      else
	break;
    }
  return ret;
}

enl_tseries_mx percentiles(const enl_tseries_mx& ts, const vectorG& g)
{
  enl_tseries_mx m = ts;
  long i,j;

  // --- pour chaque colonne (année/trim)
  for(i=0; i<ts.ncols; i++)
    {

      // --- lecture des valeurs dans un tableau et tri
      std::vector<enl_data> sortedValues;
      for(j=0; j<ts.GetNSeries(); j++)
	{
	  if(ts[j].nrows()>i)
	    {
	      enl_data d = ts[j][i];
	      if( d.GetIsAvailable() ) 
		sortedValues.push_back(d.GetValue());
	    }
	}
      std::sort(sortedValues.begin(), sortedValues.end());

      // --- affectation des percentiles et conversion en notes
      for(j=0; j<ts.GetNSeries(); j++)
	{	  
	  if(ts[j].nrows()>i)
	    {
	      enl_data d = ts[j][i];
	      if( d.GetIsAvailable() ) 
		{
		  m[j][i] = getGrade( sortedValues, g, d.GetValue() );
		}
	    }
	}

    }

  return m;
}

enl_tseries percentiles_hist(const enl_tseries& tsInit, const vectorG& g, const long& year)
{
  long i;
  enl_tseries ts = tsInit;
  enl_tseries m  = tsInit;

  // --- on rebase sur l'année initiale
  long oldbyear = m.GetBaseYear();
  m.adjust_byear(year);
  ts.adjust_byear(year);
  m = na();

  // --- lecture des valeurs dans un tableau et tri
  std::vector<enl_data> sortedValues;
  for(i=0; i<ts.nrows(); i++)
    {
	      enl_data d = ts[i];
      if( d.GetIsAvailable() ) 
	sortedValues.push_back(d.GetValue());
    }
  std::sort(sortedValues.begin(), sortedValues.end());

  // --- affectation des percentiles et conversion en notes
  for(i=0; i<ts.nrows(); i++)
    {
      if( ts[i].GetIsAvailable() ) 
	{
	  m[i] = getGrade( sortedValues, g, ts[i].GetValue() );
	}
    }

  // --- on reprend tout l'historique
  m.adjust_byear(oldbyear);

  return m;
}

enl_tseries_mx percentiles_hist(const enl_tseries_mx& ts, const vectorG& g, const long& year)
{
  enl_tseries_mx m = ts;
  for(long i=0; i<ts.GetNSeries(); i++)
    {
      m[i] = percentiles_hist(ts[i],g,year);
    }
  return m;
}


