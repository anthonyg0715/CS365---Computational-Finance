#include "Bond.h"
#include <iostream>

using namespace std;

Bond::Bond(double T, double F, double c, int freq) {

	if (face >= 0) { face = F; }

	if (cpn_freq >= 1) { cpn_freq = freq; }

	if(cpn_freq < 1) { cpn_freq=2; }

	const double tol = 1.0e-6;

	num_coupons_periods = int(cpn_freq * T + tol);

	if (num_coupons_periods < 0) { num_coupons_periods = 0; }

	T_maturity = num_coupons_periods / cpn_freq;

	if (num_coupons_periods > 0) {
		if (c < 0.0) { c = 0.0; }
		coupons.resize(num_coupons_periods, c);
	}//here we are resizing coupons back to 0 if they are less than 0

};

int Bond::set_coupons(std::vector<double> &c) {

	if (c.size() < num_coupons_periods) return 1; //fail so exit

	for (int i = 0; i < num_coupons_periods; i++) {
		if (c[i] <= 0.0) {
			coupons[i] = 0.0;
		}
		else { coupons[i] = c[i]; }
	}
	return 0;//success aand exit
}

void Bond::set_flat_coupons(double c) {
	if (c < 0.0) c = 0.0;
	std::fill(coupons.begin(), coupons.end(), c);
}//modifying coupons to a new value

int Bond::FV_duration(double t0, double y, double &B, double &Macaulay_duration, double &modified_duration) const {

	B=0;
	Macaulay_duration=0;
	modified_duration=0;
	double y_decimal = 0.01 * y;//used to avoid factors of a 100 errors
	double temp1 = 1 + y_decimal / cpn_freq;
	const double tolerance = 1.0e-6;//guarding against floating point round off error aka tolerance parameter

	if ((num_coupons_periods <= 0) || (t0 >= T_maturity)) { return 1; }

	/* Working out the FV method */
	for (int i = 1; i <= num_coupons_periods; ++i) {

		double t_i = double(i) / double(cpn_freq);//coupon dates
		double temp2 = cpn_freq*(t_i - t0);
		double temp = coupons[i-1]/cpn_freq;
		double temp3 = face + coupons[i-1]/cpn_freq;
		double temp4 = (t_i - t0) * (coupons[i-1] / cpn_freq);
		double temp5 = (t_i - t0) * (face + coupons[i-1] / cpn_freq);

		if (t_i >= (t0+tolerance)) {
                //We are at the previous terms
			if (i <= num_coupons_periods-1) {

				B += ( (temp) / pow(temp1, temp2));

				Macaulay_duration += (temp4 / pow(temp1, temp2));
			}
			else {//we are at the last term

				B += ((temp3) / pow(temp1, temp2));

				Macaulay_duration += (temp5 / pow(temp1, temp2));
			}

		}//only include terms where ti - t0 > 0

	}//summing up all terms

	Macaulay_duration = Macaulay_duration*(1/B);//This is the final step to Macaulay duration * 1/B

	/*Working out the Modified Duration part of the method*/
	modified_duration = Macaulay_duration / temp1;

	return 0;//success and exit

}//FV_duration method

int Bond::yield(double B_target, double tol, int max_iter, double t0, double &y, int &num_iter) const {

	y = 0;
	num_iter = 0;//how many iterations were performed if the calculation converges

	if (B_target <= 0.0 || num_coupons_periods <= 0 || t0 >= T_maturity) { return 1; }//fail and exit

	double y_low = 0.0;
	double y_high = 100.0;

	double B_y_low = FairValue(t0, y_low);//calculating the bond price for y_low
	double diff_B_y_low = B_y_low - B_target;//needed for the next validation test

	if (fabs(diff_B_y_low) <= tol) {
		y = y_low;
		return 0;//success and exit
	}

	double B_y_high = FairValue(t0, y_high);//calculating the bond price for y_high
	double diff_B_y_high = B_y_high - B_target;// calculating the differnece for next validation test

	if (fabs(diff_B_y_high) <= tol) {
		y = y_high;
		return 0;//success and exit
	}

	if (diff_B_y_low * diff_B_y_high > 0) {//If yes, then the values of B(ylow) and B(yhigh) do not bracket B_target and we have failed.
		y = 0;
		return 1;//we have failed
	}

	/*If we have made it this far, then we know that we have bracketed the answer, and the true
	yield y lies between ylow and yhigh.
	•     Hence we now begin the main bisection iteration loop
	*/
	double B = 0;
	double diff_B = 0;
	for (num_iter = 1; num_iter < max_iter; ++num_iter) {
		y = (y_low + y_high) / 2.0;
		B = FairValue(t0, y);
		diff_B = B - B_target;
		//We have found a good enough value for the yield y
		if (fabs(diff_B) <= tol) {
			return 0;
		}
		//Check if B and B(ylow) are on the same side of Btarget.
		if (diff_B * diff_B_y_low > 0.0) {
			y_low = y;
		}
		else {
			y_high = y;
		}
		if (fabs(y_high - y_low) <= tol) {
			return 0;//the algorithm has converged success and exit
		}

	}//iterations
	//we exit the iteration loop after max iter steps and the calculation still has not converged,
	y=0;
	return 1;//fail and exit

	return 0;//otherwise success and exit

}//yield method

double Bond::FairValue(double t0, double y) const
{
	double B=0;
	double Macaulay_duration=0;
	double modified_duration=0;
	FV_duration(t0, y, B, Macaulay_duration, modified_duration);
	return B;
}
