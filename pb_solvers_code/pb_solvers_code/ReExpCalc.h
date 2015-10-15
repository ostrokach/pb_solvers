//
//  ReExpCalc.h
//  pb_solvers_code
//
//  Created by David Brookes on 10/5/15.
//  Copyright © 2015 David Brookes. All rights reserved.
//

#ifndef ReExpCalc_h
#define ReExpCalc_h

#include <stdio.h>
#include "MyMatrix.h"
#include "Constants.h"
#include "util.h"
#include "BesselCalc.h"

using namespace std;

/*
 Class for pre-computing the constants in the re-expansion coefficne
// */
//class ReExpCoeffsConstants
//{
//protected:
//  MyMatrix<double> a_;  // first index is m, second is n
//  MyMatrix<double> b_;
//  MyMatrix<double> alpha_;
//  MyMatrix<double> beta_;
//  MyMatrix<double> nu_;
//  MyMatrix<double> mu_;
//  double lambda_; // uniform scaling factor (section 4.5 of Lotan 2006)
//  int p_;
//  double kappa_; //from Constants
//  
//  void calc_a_and_b();
//  void calc_alpha_and_beta();
//  void calc_nu_and_mu();
//
//public:
//  
//  /*
//   Initialize proper amount of memory in default constructor:
//   */
//  ReExpCoeffsConstants(int p=Constants::MAX_NUM_POLES)
//  :p_(p), a_(p, p), b_(p, p), alpha_(p, p+1), beta_(p, p+1)
//  ,nu_(2*p, p), mu_(2*p, p)
//  {
//  }
//  
//  ReExpCoeffsConstants(double kappa, double lambda,
//                       int p=Constants::MAX_NUM_POLES);
//  
//  const double get_a_val(int m, int n) const      { return a_(m, n); }
//  const double get_b_val(int m, int n) const      { return b_(m, n); }
//  const double get_alpha_val(int m, int n) const  { return alpha_(m, n+1); }
//  const double get_beta_val(int m, int n) const   { return beta_(m, n+1); }
//  const double get_nu_val(int m, int n) const     { return nu_(m+(p_-1), n); }
//  const double get_mu_val(int m, int n) const     { return mu_(m+(p_-1), n);}
//  
//};

/*
 Class representing one entry in the re-expansion coefficient matrix. So if 
 that matrix is T (as in Lotan 2006), then this class contains the info 
 for one T^(i,j)
 */
class ReExpCoeffs_IJ
{
protected:
  
  int p_; // max value of n when solving for A
  
  /*
   R_ contains rotation coefficients for this entry. R_ has three
   indices: R[n](m, s)
   And the range of each:  0 <= n <  poles
                          -n <= m <= n, but -m = conj(+m), so really just [0,p)
                          -n <= s <= n
   */
  MyVector<MyMatrix<cmplx> >  R_;
  /*
   S_ contains translation coefficients for this entry. S_ has three
   indices: S[m](n, l)
   */
  MyVector<MyMatrix<cmplx> >  S_;
//  ReExpCoeffsConstants*     _consts_;
  double kappa_; //from Constants
  double lambda_; // uniform scaling factor (section 4.5 of Lotan 2006)
  
  ShPt v_; //computing re-expansion along this vector
  
  /*
   Spherical harmonics for this v_:
   */
  const MyMatrix<cmplx>* Ytp_;
  const BesselCalc* _besselCalc_;
  
  void calc_r();  // calculate all the values for R_
  void calc_s(); // calculate all the values for S_
  
  // The below functions calculate constants required for R_ and S_
  const double calc_b(int m, int n);  // R_
  const double calc_a(int m, int n);  // R_
  const double calc_alpha(int m, int n);  // S_
  const double calc_beta(int m, int n);  // S_
  const double calc_nu(int m, int n);  // S_
  const double calc_mu(int m, int n); // S_
  
public:
  
//  ReExpCoeffs_IJ();
  ReExpCoeffs_IJ(int p, ShPt v, MyMatrix<cmplx>* Ytp, BesselCalc * BesselCalc,
                 double kappa, double lambda);
//  virtual ~ReExpCoeffs_IJ();
//  ReExpCoeffs_IJ& operator=(const ReExpCoeffs_IJ* other);

  const cmplx get_yval(int n, int s) const
  {
    if ( s < 0 ) return conj(Ytp_->operator()(n, -s));
    else         return Ytp_->operator()(n, s);
  }
  
  
  const cmplx get_rval(int n, int m, int s) const
  {
    if ( m < 0 ) return conj(R_[n](-m, -s+n));
    else         return R_[n](m, s+n);
  }
  //const cmplx get_sval(int m, int n, int l) const { return S_[m](n, l); }
  const cmplx get_sval(int n, int l, int m) const  { return S_[n](l, n+m); }
  

  void set_rval(int n, int m, int s, cmplx val)
  {
    if ( m < 0 ) R_[n].set_val(-m, s+n, conj( val ));
    else         R_[n].set_val( m, s+n, val );
  }
  
  void set_sval(int n, int l, int m, cmplx val) { S_[n].set_val(l, n+m, val); }
  
};

#endif /* ReExpCalc_hpp */