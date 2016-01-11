//
//  util.hpp
//  pb_solvers_code
//
//  Created by David Brookes on 9/24/15.
//  Copyright © 2015 David Brookes. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <math.h>
#include <complex>

#include "MyMatrix.h"

/*
 Right scalar multiplication of a matrix
*/
template<typename T>
MyMatrix<T> operator*(MyMatrix<T> mat, const T& rhs)
{
  MyMatrix<T> result = MyMatrix<T>(mat.get_nrows(), mat.get_ncols());
  int i, j;
  for (i = 0; i < mat.get_nrows(); i++)
  {
    for (j= 0; j < mat.get_ncols(); j++)
    {
        result.set_val(i, j, rhs * mat(i, j));
    }
  }
  return result;
}


/*
 lhs scalar multiplication of a matrix
 */
template<typename T>
MyMatrix<T> operator*(const T& lhs, MyMatrix<T> mat)
{
  MyMatrix<T> result = MyMatrix<T>(mat.get_nrows(), mat.get_ncols());
  int i, j;
  for (i = 0; i < mat.get_nrows(); i++)
  {
    for (j= 0; j < mat.get_ncols(); j++)
    {
        result.set_val(i, j, lhs * mat(i, j));
    }
  }
  return result;
}

/*
 Class for storing three dimensional points in spherical or
 euclidean coordinates
 Should note that THETA = polar angle [ 0 <= THETA <= PI ]
 and PHI = azimuthal angle [ 0 <= PHI <= 2*PI ]
 */
template<typename T>
class Point
{
protected:
  T p1_; // x or r
  T p2_; // y or theta
  T p3_; // z or phi
  bool sph_; // whether or not the point is in spherical coordinates
  
  // convert between coordinatre systems:
  void convert_to_spherical()
  {
    if (sph_)
      return; // do nothing if already spherical
    
    T theta, phi;
    T r = sqrt(p1_*p1_ + p2_*p2_ + p3_*p3_);
    
    if (r < fabs(p3_))
      r = fabs(p3_);
    
    if (r == 0.0)
      theta = 0.0;
    else
      theta = acos(p3_/r);
    
    if ((p1_ == 0.0) && (p2_ == 0.0))
      phi = 0.0;
    else
      phi = atan2(p2_, p1_);
    
    p1_ = r;
    p2_ = theta;
    p3_ = phi;
    sph_ = true;
  }
  
  void convert_to_euclidean()
  {
    if (!sph_)
      return; // do nothing if already euclidean
    
    T x, y, z;
    x = p1_ * cos(p2_) * sin(p3_);
    y = p1_ * sin(p2_) * sin(p3_);
    z = p1_ * cos(p3_);
    
    p1_ = x;
    p2_ = y;
    p3_ = z;
    sph_ = false;
  }
  
public:
  
  // constructor given three coordinate values and whether those are spherical
  // default is to assum euclidean
  Point(T p1=T(), T p2=T(), T p3=T(), bool sph=false)
  :p1_(p1), p2_(p2), p3_(p3), sph_(sph)
  {
  }
  
  //arithmetic operators:
  
  //scalar multiplication
  Point<T> operator*(T scalar)
  {
    Point<T> pout;
    if (sph_) convert_to_euclidean(); //for simplicity
    pout.p1_ = p1_ * scalar;
    pout.p2_ = p2_ * scalar;
    pout.p3_ = p3_ * scalar;
    return pout;
  }
  
  Point<T> operator+(Point<T>& other)
  {
    Point<T> pout;
    if (sph_) convert_to_euclidean();
    pout.p1_ = p1_ + other.p1_;
    pout.p2_ = p2_ + other.p2_;
    pout.p3_ = p3_ + other.p3_;
    return pout;
  }
  
  Point<T> operator-(Point<T>& other)
  {
    Point<T> pout;
    if (sph_) convert_to_euclidean(); //for simplicity
    pout.p1_ = p1_ - other.p1_;
    pout.p2_ = p2_ - other.p2_;
    pout.p3_ = p3_ - other.p3_;
    return pout;
  }
  
  // calculate the distance to another point
  double dist(Point<T>& other)
  {
    convert_to_euclidean();
    double d = pow(this->x() - other.x(), 2);
    d += pow(this->y() - other.y(), 2);
    d += pow(this->z() - other.z(), 2);
    d = sqrt(d);
    return d;
  }
  
  // Getter methods perform necessary conversions:
  const T& x()
  {
    if (sph_) convert_to_euclidean();
    return p1_;
  }
  const T& y()
  {
    if (sph_) convert_to_euclidean();
    return p2_;
  }
  const T& z()
  {
    if (sph_) convert_to_euclidean();
    return p3_;
  }
  const T& r()
  {
    if (!sph_) convert_to_spherical();
    return p1_;
  }
  const T& theta()
  {
    if (!sph_) convert_to_spherical();
    return p2_;
  }
  const T& phi()
  {
    if (sph_) convert_to_spherical();
    return p3_;
  }
  
};

typedef complex<double> cmplx;
typedef Point<double> Pt;



/*
 Calculate inner product of two matrices as defined in equation 29 of Lotan
 2006
 */
cmplx lotan_inner_prod(MyMatrix<cmplx> U, MyMatrix<cmplx> V, int p)
{
  cmplx ip;
  int n, m;
  for (n = 0; n < p; n++)
  {
    for (m = -n; m <= -n; m++)
    {
      ip += U(n, m+p) * conj(V(n, m+p));
    }
  }
  return ip;
}


#endif /* util_hpp */
