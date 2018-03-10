#include <iostream>
#include "math.h"
using namespace std;

double future_value(double F0, double t0, double t1, double r)
{
	double r_decimal = 0.01*r;
	double F1 = F0 * exp(r_decimal*(t1 - t0));
	return F1;
}

 /*This function does the inverse meaning the discount factor*/
int df_and_r(double F0, double F1, double t0, double t1, double & df, double & r)
{
	if (t1 - t0 == 0.0) {
		df = 0;
		r = 0;
		return -1;//exit with return value -1 if t1 - t0 = 0
	}
	else if ((F0 <= 0.0) || (F1 <= 0.0)) {
		df = 0;
		r = 0;
		return -2;//exit with return value -2 if F0 <= 0 or F1 <= 0
	}
	else {//else everything is fine do calculations
		df = F0 / F1;
		r = -( log(df) / (t1 - t0) )*100;//this is what I did to solve for r
		//I took the natural log of both sides and get r = -( ln(d) / (t1-t0) ) where d is F_today/F_future
	}

	return 0; // and exit with return value 0
}

int main()
{
	/* This is the test for the future value function */

	double fv, fv1, fv2;
	fv = future_value(100.5, 0.0, 0.75, 5.5);//test 1 where t0 equals t1
	fv1 = future_value(100.0, 0.0, 0.5, 0.5);//test 2 where t1 > t0
	fv2 = future_value(100.0, 0.0, -0.5, 0.5);//test 3 where t1 < t0
	cout << "Test Case Value1: " << fv << '\n';
	cout << "test Case Value2: " << fv1 << '\n';
	cout << "Test Case Value3: " << fv2 << '\n';

	/* testing df and r function here */

	double df_r, df, r;
	df_r = df_and_r(95, 105, 0, 0.75, df, r);
	cout << "Test df_and_r: " << r << '\n';

	return 0;
}
