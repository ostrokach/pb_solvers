//
//  main.cpp
//  pb_solvers_test
//
//  Created by Marielle Soniat on 10/5/15.
//  Copyright (c) 2015 David Brookes. All rights reserved.
//

#include <iostream>

#include <limits.h>
#include "gtest/gtest.h"

#include "Constants.h"
#include "util.h"

double preclim = 1.0e-4;    //! precision limit
const int nvals = 10 ;      //! standard number of poles for testing

#include "BesselCalcUnitTest.h"
//#include "ConstantsUnitTest.h"
//#include "MyMatrixTest.h"
//#include "SHCalcUnitTest.h"
//#include "ASolverUnitTest.h"

#include "tester.h"


using namespace std ;

int main(int argc, char * argv[])
{
  
  bool test = true;
  if (test)
  {
    cout << "Welcome to test suite" << endl;
    CTester allTest = CTester();
    allTest.unitTest( argc, argv );
  }
  
  cout << "Now for Google Tests." << endl ;
    
  bool gtest = false;
  if (gtest)
  {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }
}
