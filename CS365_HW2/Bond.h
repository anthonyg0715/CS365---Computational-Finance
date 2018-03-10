#ifndef BOND_H
#define BOND_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class Bond
{
    public:
        Bond(double T, double F, double c = 0, int freq = 2);
        ~Bond() {};//clears coupons array and sets num_coupons to zero

			   // public methods
        int set_coupons(std::vector<double> & c);
        void set_flat_coupons(double c);
        int FV_duration(double t0, double y,
		double &B,
		double &Macaulay_duration,
		double &modified_duration) const;

        int yield(double B_target, double tol, int max_iter, double t0,
            double & y, int & num_iter) const;

        double FairValue(double t0, double y) const;
        double getT_maturity() const { return T_maturity; }

    private:
    std::vector<double> coupons;
	double face;
	double T_maturity;
	int cpn_freq;
	int num_coupons_periods;
};

#endif // BOND_H
