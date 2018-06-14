// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
///////////////////////////////////////////////////////////////
// DistNorm.cc
//
// Normal distributions
//
// Mike Dixon, EOL, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// June 2018
//
///////////////////////////////////////////////////////////////

#include <rapmath/DistPolynomial.hh>
#include <toolsa/mem.h>
#include <rapmath/usvd.h>
#include <iostream>
using namespace std;

// #define DEBUG_PRINT

////////////////////////////////////////////////////
// constructor

DistPolynomial::DistPolynomial() :
        Distribution()
        
{
  _init();
  setOrder(4);
}

////////////////////////////////////////////////////
// destructor

DistPolynomial::~DistPolynomial()
        
{
  _free();
}

//////////////////////////////////////////////////////////////////
// initialize the stats

void DistPolynomial::_clearStats()

{
  Distribution::_clearStats();
}

//////////////////////////////////////////////////////////////////
// set polynomial order

void DistPolynomial::setOrder(size_t order) 
{
  _nPoly = order;
  _nPoly1 = order + 1;
}

////////////////////////////////////////////////////
// perform a fit

int DistPolynomial::performFit()
  
{

  if (_nVals < 2) {
    _clearStats();
    return -1;
  }

  computeBasicStats();
  
  if (_histSize == 0) {
    computeHistogramSpecifyWidth(60, 3);
  }

  // perform polynomial fit
  
  _doPolyFit();

  // save the coefficients

  _coeffs.clear();
  for (size_t ii = 0; ii < _nPoly1; ii++) {
    _coeffs.push_back(_pp[ii]);
  }

  // load PDF vector

  _histPdf.clear();
  for (size_t jj = 0; jj < _histSize; jj++) {
    _histPdf.push_back(_yyEst[jj]);
  }

  _pdfAvail = true;

  computeHistCdf();

  return 0;

}

////////////////////////////////////////////////////
// get the pdf value for a given x
// a fit must have been performed

double DistPolynomial::getPdf(double xx)
  
{
  double pdf = 0.0;
  for (size_t ii = 0; ii < _coeffs.size(); ii++) {
    int jj = _nPoly1 - ii - 1;
    double term = _coeffs[jj] * pow(xx, (double) jj);
    pdf += term;
  }
  if (pdf < 0) {
    pdf = 0.0;
  }
  return pdf;
}

////////////////////////////////////////////////////
// get the cdf value for a given x
// a fit must have been performed

double DistPolynomial::getCdf(double xx)
  
{
  double cdf = 0.0;
  for (size_t ii = 0; ii < _coeffs.size(); ii++) {
    int jj = _nPoly1 - ii - 1;
    double term = (_coeffs[jj] * pow(xx, jj + 1.0)) / (jj + 1.0);
    cdf += term;
  }
  if (cdf < 0) {
    cdf = 0.0;
  }
  return cdf;
}

/////////////////////////////
// initialization

void DistPolynomial::_init()

{

  _xx = NULL;
  _yyEst = NULL;

  _vv = NULL;
  _vvT = NULL;
  _vvA = NULL;
  _vvB = NULL;
  _uu = NULL;
  _uuT = NULL;
  _ss = NULL;
  _ssInv = NULL;
  _ssVec = NULL;
  _ww = NULL;
  _wwT = NULL;

  _pp = NULL;
  _cc = NULL;
  _multa = NULL;
  _multb = NULL;

}

#ifdef JUNK

/////////////////////////////////////////////////////
// Perform adaptive filtering on a power spectrum
// Perform regression filtering on I,Q data
//
// Inputs:
//   rawIq: raw I,Q data
//
// Outputs:
//   filteredIq: filtered I,Q data
//
// Side effect:
//   polyfitIq is computed
//
// Note: assumes setup() has been successfully completed.

void DistPolynomial::apply(const RadarComplex_t *rawIq,
                           RadarComplex_t *filteredIq) const

{

  if (_histSize == 0) {
    cerr << "ERROR - DistPolynomial::apply" << endl;
    cerr << "  Number of samples has not been set" << endl;
    cerr << "  Call setup() before apply()" << endl;
    return;
  }

  // copy IQ data

  TaArray<double> rawI_, rawQ_;
  double *rawI = rawI_.alloc(_histSize);
  double *rawQ = rawQ_.alloc(_histSize);

  for (int ii = 0; ii < _histSize; ii++) {
    rawI[ii] = rawIq[ii].re;
    rawQ[ii] = rawIq[ii].im;
  }

  // poly fit to I

  polyFit(rawI);

  // compute the estimated I polynomial values
  
  _matrixVectorMult(_vv, _pp, _histSize, _nPoly1, _yyEst);

  // load residuals into filtered Iq
  
  for (int ii = 0; ii < _histSize; ii++) {
    filteredIq[ii].re = rawI[ii] - _yyEst[ii];
    _polyfitIq[ii].re = _yyEst[ii];
  }
  
  // poly fit to Q

  polyFit(rawQ);

  // compute the estimated Q polynomial values
  
  _matrixVectorMult(_vv, _pp, _histSize, _nPoly1, _yyEst);

  // load residuals into filtered Iq

  for (int ii = 0; ii < _histSize; ii++) {
    filteredIq[ii].im = rawQ[ii] - _yyEst[ii];
    _polyfitIq[ii].im = _yyEst[ii];
  }
  
}
#endif

/////////////////////////////////////////////////////
// Perform polynomial fit from observed data
// in histogram
//
// Input: _histDensity
//
// Result:
//   polynomial coefficients in _pp

void DistPolynomial::_doPolyFit()
  
{
  
  // allocate arrays
  
  _alloc();

  // load xx vector
  
  for (size_t jj = 0; jj < _histSize; jj++) {
    double xx = _histMin + jj * _histDelta;
    _xx[jj] = xx;
  }

  // compute CC matrix for later use

  _computeCc();
  
  for (size_t ii = 0; ii < _nPoly1; ii++) {
    double sum = 0;
    for (size_t jj = 0; jj < _histSize; jj++) {
      sum += _cc[ii][jj] * _histDensity[jj];
    }
    _pp[ii] = sum;
  }

  // compute the standard error of estimates of y
  
  _matrixVectorMult(_vv, _pp, _histSize, _nPoly1, _yyEst);
  
  double sumSq = 0.0;
  for (size_t ii = 0; ii < _histSize; ii++) {
    double error = _yyEst[ii] - _histDensity[ii];
    sumSq += error * error;
  }
  _stdErrEst = sqrt(sumSq / (double) _histSize);


#ifdef DEBUG_PRINT
  for (size_t ii = 0; ii < _nPoly1; ii++) {
    cerr << "ii, pp: " << ii << ", " << _pp[ii] << endl;
  }
  for (size_t ii = 0; ii < _histSize; ii++) {
    cerr << "ii, yyObserved, yyEst: " << ii
         << ", " << _histDensity[ii] << ", " << _yyEst[ii] << endl;
  }
  cerr << "===>> sdtErrEst: " << _stdErrEst << endl;
#endif

}

/////////////////////////////////////////////////////
// allocate space

void DistPolynomial::_alloc()

{
  
  _free();
  
  _xx = (double *) umalloc(_histSize * sizeof(double));
  _yyEst = (double *) umalloc(_histSize * sizeof(double));

  _vv = (double **) umalloc2(_histSize, _nPoly1, sizeof(double));
  _vvT = (double **) umalloc2(_nPoly1, _histSize, sizeof(double));
  _vvA = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _vvB = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));

  _uu = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _uuT = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));

  _ss = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _ssInv = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _ssVec = (double *) umalloc(_nPoly1 * sizeof(double));

  _ww = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _wwT = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));

  _pp = (double *) umalloc(_nPoly1 * sizeof(double));
  _cc = (double **) umalloc2(_nPoly1, _histSize, sizeof(double));
  _multa = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));
  _multb = (double **) umalloc2(_nPoly1, _nPoly1, sizeof(double));

}

/////////////////////////////////////////////////////
// free allocated space

void DistPolynomial::_free()

{
  
  _freeVec(_xx);
  _freeVec(_yyEst);
  _freeVec(_ssVec);
  _freeVec(_pp);

  _freeMatrix(_vv);
  _freeMatrix(_vvT);
  _freeMatrix(_vvA);
  _freeMatrix(_vvB);
  _freeMatrix(_uu);
  _freeMatrix(_uuT);
  _freeMatrix(_ss);
  _freeMatrix(_ssInv);
  _freeMatrix(_ww);
  _freeMatrix(_wwT);
  _freeMatrix(_cc);
  _freeMatrix(_multa);
  _freeMatrix(_multb);

}

void DistPolynomial::_freeVec(double* &vec)
{
  if (vec != NULL) {
    ufree(vec);
    vec = NULL;
  }
}

void DistPolynomial::_freeMatrix(double** &array)
{
  if (array != NULL) {
    ufree2((void **) array);
    array = NULL;
  }
}

/////////////////////////
// compute the CC matrix

void DistPolynomial::_computeCc()

{

  // compute vandermonde and transpose
  // this loads _vv, _vvT and _vvA
  
  _computeVandermonde();
  
  // compute SVD of vvA
  
  int iret = usvd(_vvA, _nPoly1, _nPoly1, _uu, _ww, _ssVec);
  if (iret) {
    cerr << "ERROR - DistPolynomial::_computeCc()" << endl;
    cerr << "  SVD returns error: " << iret << endl;
    cerr << "  Cannot compute SVD on Vandermonde matrix * transpose" << endl;
    return;
  }

  // fill out diagonal matrix and its inverse
  
  for (size_t ii = 0; ii < _nPoly1; ii++) {
    for (size_t jj = 0; jj < _nPoly1; jj++) {
      if (ii == jj) {
        _ss[ii][jj] = _ssVec[ii];
        _ssInv[ii][jj] = 1.0 / _ssVec[ii];
      } else {
        _ss[ii][jj] = 0.0;
        _ssInv[ii][jj] = 0.0;
      } 
    }
  }

  // compute transpose of _uu and _ww

  for (size_t ii = 0; ii < _nPoly1; ii++) {
    for (size_t jj = 0; jj < _nPoly1; jj++) {
      _uuT[ii][jj] = _uu[jj][ii];
      _wwT[ii][jj] = _ww[jj][ii];
    }
  }

  // check

  _matrixMult(_uu, _ss, _nPoly1, _nPoly1, _nPoly1, _multa);
  _matrixMult(_multa, _wwT, _nPoly1, _nPoly1, _nPoly1, _vvB);

  // compute cc
  
  _matrixMult(_ww, _ssInv, _nPoly1, _nPoly1, _nPoly1, _multa);
  _matrixMult(_multa, _uuT, _nPoly1, _nPoly1, _nPoly1, _multb);
  _matrixMult(_multb, _vvT, _nPoly1, _nPoly1, _histSize, _cc);

#ifdef DEBUG_PRINT
  _matrixPrint("_vvB", _vvB, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_uu", _uu, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_uuT", _uuT, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_ww", _ww, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_wwT", _wwT, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_ss", _ss, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_ssInv", _ssInv, _nPoly1, _nPoly1, stderr);
  _matrixPrint("_cc", _cc, _nPoly1, _histSize, stderr);
#endif
  
}

//////////////////////////////////////////////  
// compute Vandermonde matrix and transpose

void DistPolynomial::_computeVandermonde()

{

  // compute vandermonde and transpose

  for (size_t ii = 0; ii < _histSize; ii++) {
    double xx = _xx[ii];
    for (size_t jj = 0; jj < _nPoly1; jj++) {
      double vv = pow(xx, (double) jj);
      _vv[ii][jj] = vv;
      _vvT[jj][ii] = vv;
    }
  }

  // compute vvA = vvT * vv

  _matrixMult(_vvT, _vv, _nPoly1, _histSize, _nPoly1, _vvA);

  // debug print

#ifdef DEBUG_PRINT
  _matrixPrint("_vv", _vv, _histSize, _nPoly1, stderr);
  _matrixPrint("_vvT", _vvT, _nPoly1, _histSize, stderr);
  _matrixPrint("_vvA", _vvA, _nPoly1, _nPoly1, stderr);
#endif

}
  
//////////////////////////////////////////////  
// multiply two matrices
//
// xx = aa * bb
//
// Notes: nRowsBb = nColsAa
//        aa[nRowsAa][nColsAa]
//        bb[nColsAa][nColsBb]
//        xx[nRowsAa][nColsBb]

void DistPolynomial::_matrixMult(double **aa,
                                 double **bb,
                                 size_t nRowsAa,
                                 size_t nColsAa,
                                 size_t nColsBb,
                                 double **xx) const
  
{
  
  for (size_t ii = 0; ii < nRowsAa; ii++) {
    for (size_t jj = 0; jj < nColsBb; jj++) {
      double sum = 0.0;
      for (size_t kk = 0; kk < nColsAa; kk++) {
        sum += aa[ii][kk] * bb[kk][jj];
      }
      xx[ii][jj] = sum;
    }
  }

}
  
//////////////////////////////////////////////  
// multiply matrix and vector
//
// xx = aa * bb
//
//   aa[nRowsAa][nColsAa]
//   bb[nColsAa]
//   xx[nRowsAa]

void DistPolynomial::_matrixVectorMult(double **aa,
                                       double *bb,
                                       size_t nRowsAa,
                                       size_t nColsAa,
                                       double *xx) const
  
{
  
  for (size_t ii = 0; ii < nRowsAa; ii++) {
    double sum = 0.0;
    for (size_t kk = 0; kk < nColsAa; kk++) {
      sum += aa[ii][kk] * bb[kk];
    }
    xx[ii] = sum;
  }

}
  
//////////////////////////////////////////////  
// print matrix
//

void DistPolynomial::_matrixPrint(string name,
                                  double **aa,
                                  size_t nRowsAa,
                                  size_t nColsAa,
                                  FILE *out) const
  
{

  fprintf(out, "=========== %10s ===========\n", name.c_str());
  for (size_t ii = 0; ii < nRowsAa; ii++) {
    fprintf(out, "row %3d: ", (int) ii);
    for (size_t jj = 0; jj < nColsAa; jj++) {
      fprintf(out, " %8.2g", aa[ii][jj]);
    }
    fprintf(out, "\n");
  }
  fprintf(out, "==================================\n");

}
  
//////////////////////////////////////////////  
// print vector
//

void DistPolynomial::_vectorPrint(string name,
                                  double *aa,
                                  size_t sizeAa,
                                  FILE *out) const
  
{
  
  fprintf(out, "=========== %10s ===========\n", name.c_str());
  for (size_t ii = 0; ii < sizeAa; ii++) {
    fprintf(out, " %8.2g", aa[ii]);
  }
  fprintf(out, "\n");
  fprintf(out, "==================================\n");

}
  
