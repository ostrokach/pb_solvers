//  pb_solvers_code
//
//  Created by Marielle Soniat on 10/5/15.
//  Copyright (c) 2015 David Brookes. All rights reserved.
//

#ifndef BesselCalcTest_h
#define BesselCalcTest_h

#include <stdio.h>
#include <math.h>
#include "BesselCalc.h"

const int nPol = 10 ;
double precLim = 1.0e-4;

BesselConstants bConst = BesselConstants( nPol );
BesselCalc bCalc = BesselCalc( nPol,  &bConst );

class BesselConstantsTest : public ::testing::Test
{
    protected :
    
    double kPreFactors[10] = { -1.0, 0.33333333,
        0.06666667, 0.02857143, 0.01587302,
        0.01010101, 0.00699301, 0.00512821,
        0.00392157, 0.00309598 } ;
    
    virtual void SetUp() {}
    virtual void TearDown() {}
};

class BesselCalcTest : public ::testing::Test
{
    protected :
    
    // for z = 1.0 and z = 10.0, calculated from python pbam_unit_test.py
    double i1[nPol] = {1.17520119e+00,   1.10363832e+00,   1.07344305e+00,
        1.05683451e+00,   1.04633846e+00,   1.03910889e+00,
        1.03382786e+00,   1.02980185e+00,   1.02663135e+00,
        1.02407006e+00};
    double i10[nPol] = {1.10132329e+03,   2.97357289e+02,   1.20594900e+02,
        6.18668362e+01,   3.69986800e+01,   2.46194746e+01,
        1.77022637e+01,   1.34885612e+01,   1.07449415e+01,
        8.86189182e+00};
    double k1[nPol] = {1.00000000e+00,   2.00000000e+00,   2.33333333e+00,
        2.46666667e+00,   2.53333333e+00,   2.57248677e+00,
        2.59807600e+00,   2.61606542e+00,   2.62938888e+00,
        2.63964796e+00 };
    double k10[nPol] = {1.00000000e+00,   1.10000000e+01,   4.43333333e+01,
        1.17666667e+02,   2.44333333e+02,   4.31105820e+02,
        6.77907167e+02,   9.79379768e+02,   1.32702447e+03,
        1.71109497e+03};
    
    virtual void SetUp() {}
    virtual void TearDown() {}
};


 
TEST_F(BesselConstantsTest, first10)
{
    ASSERT_EQ( nPol , bConst.get_n() ) ;
    for (int i = 0; i < nPol; i++)
    {
        double calculated = bConst.get_kconst_val( i ) ;
        double difference = kPreFactors[i] - calculated ;
        EXPECT_NEAR(bConst.get_kconst_val(i), kPreFactors[i], precLim) ;
    }
}


TEST_F(BesselCalcTest, first10)
{
    const vector<double> mBFI10 = bCalc.calc_mbfI( nPol, 10.0 );
    const vector<double> mBFK10 = bCalc.calc_mbfK( nPol, 10.0 );
    const vector<double> mBFI1 = bCalc.calc_mbfI( nPol, 1.0 );
    const vector<double> mBFK1 = bCalc.calc_mbfK( nPol, 1.0 );
    
    for (int iter = 0; iter < mBFI1.size(); iter++)
    {
        EXPECT_NEAR( mBFI1[iter],  i1[iter], precLim) ;
        EXPECT_NEAR(mBFI10[iter], i10[iter], precLim) ;
        EXPECT_NEAR( mBFK1[iter],  k1[iter], precLim) ;
        EXPECT_NEAR(mBFK10[iter], k10[iter], precLim) ;
    }
}


#endif
