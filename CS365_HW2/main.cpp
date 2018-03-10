#include <iostream>
#include <vector>
#include "Bond.h"
#define BOND_H
using namespace std;

int main()
{

    Bond *bond = new Bond(5,100,1,2);
    /*This is the test for y=c and t0=0 I will do three to show it works no matter what T is*/
    cout <<"FV1: " << bond->FairValue(0,1) << endl;
    delete bond;

    cout << '\n';

    /*As we can see from this output FV is still 100 even with T as 10 */
    Bond *bond2 = new Bond(10,100,2,2);
    cout << "FV2: " << bond2->FairValue(0,2) << endl;
    delete bond2;

    cout << '\n';

    /*Even with T more higher it is once again still 100
      Therefore, we can see that as long as y=c the fair value will be 100
    */
    Bond *bond3 = new Bond(15,100,3,2);
    cout << "FV3: " << bond3->FairValue(0,3) << endl;
    delete bond3;

    cout << '\n';

    /*Straight Sum Of The Values Of The Cash Flows test I will compare answer by hand and show same result*/
    Bond *bond4 = new Bond(1,100,1,2);
    cout << "Straight sum of the values of the cash flows test: " << bond4->FairValue(0,0) << endl;
    delete bond4;

    cout << '\n';

    /*Zero Coupon Bond Test I will show same result by hand*/
    Bond *bond5 = new Bond(1,100,0,2);
    cout << "Zero Coupon Bond Test: " << bond5->FairValue(0,0) << endl;
    delete bond5;

    cout << '\n';

    /*Testing the yield function where y=c provide freq*t>1=*/
    Bond *bond6 = new Bond(2,100,4,2);
    double y1;
    int num_iter;
    bond6->yield(100,0.0001,100,0,y1,num_iter);
    cout << "Value of y=c: " << y1 << endl;
    delete bond6;

    cout << '\n';

    /*Testing the yield function where if B_target < 100 then y > c*/
    double y2;
    int num_iter2;
    Bond *bond7 = new Bond(2,100,2,2);
    bond7->yield(95,0.0001,100,0,y2,num_iter2);
    cout << "Value of y > c: " << y2 << endl;
    delete bond7;

    cout << '\n';

    /*Testing the yield function where if B_target > 100 then y < c*/
    double y3;
    int num_iter3;
    Bond *bond8 = new Bond(2,100,3,2);
    bond8->yield(101,0.0001,100,0,y3,num_iter3);
    cout << "Value of y < c: " << y3 << endl;
    delete bond8;

    cout << '\n';

    /*Testing the fact that B2 - B1 is equivalent to 1*/
    Bond *bond9 = new Bond(2,100,2,2);
    //value for the yield I chose is 3 for y1
    cout << "B1 FV is: " << bond9->FairValue(1,3) << endl;
    //It's B1 value is 99.5074
    double y5;
    int num_iter4;
    //Target is now B1 + 1 which is 100.5074
    bond9->yield(100.5074,0.0001,100,1,y5,num_iter4);
    //calculating the yield for y2 which really I say y5 not to confuse with the other y2 I used earlier
    cout << "yield for y5: " << y5 << endl;
    //Answer for y2 is 100.507 and now we need to calculate is fair value B2
    cout << "B2 FV is: " << bond9->FairValue(1,0.980377) << endl;
    //B2 is 100.507 we get B2 - B2 which is 100.507 - 99.5074 = 0.9996 which is equivalent to 1
    delete bond9;

    cout << '\n';

    /*Testing with worked examples from section 2.8 and 2.9*/
    std::vector<double> c = {4.1,4.2,4.3,4.4};
    Bond *bond10 = new Bond(2,100,0,2);
    bond10->set_coupons(c);
    double B, Macaulay_duration, modified_duration;
    bond10->FV_duration(0.0,6,B,Macaulay_duration,modified_duration);
    cout << "Bond price @ t0 = 0.0: " << B << endl;
    delete bond10;

    cout << '\n';

    std::vector<double> c1 = {4.1,4.2,4.3,4.4};
    Bond *bond11 = new Bond(2,100,0,2);
    bond11->set_coupons(c1);
    double B1, Macaulay_duration1, modified_duration1;
    bond11->FV_duration(0.1,6,B1,Macaulay_duration1,modified_duration1);
    cout << "Bond price @ t0 = 0.1: " << B1 << endl;
    delete bond11;

    cout << '\n';

    std::vector<double> c2 = {4.1,4.2,4.3,4.4};
    Bond *bond12 = new Bond(2,100,0,2);
    bond12->set_coupons(c2);
    double B2, Macaulay_duration2, modified_duration2;
    bond12->FV_duration(0.55,6,B2,Macaulay_duration2,modified_duration2);
    cout << "Bond price @ t0 = 0.55: " << B2 << endl;
    delete bond12;

    cout << '\n';

    std::vector<double> c3 = {4.1,4.2,4.3,4.4};
    Bond *bond13 = new Bond(2,100,0,2);
    bond13->set_coupons(c3);
    double B3, Macaulay_duration3, modified_duration3;
    bond13->FV_duration(0.0,6,B3,Macaulay_duration3,modified_duration3);
    cout << "Macaulay Duration @ t0 = 0.0: " << Macaulay_duration3 << endl;
    delete bond13;

    cout << '\n';

    std::vector<double> c4 = {4.1,4.2,4.3,4.4};
    Bond *bond14 = new Bond(2,100,0,2);
    bond14->set_coupons(c4);
    double B4, Macaulay_duration4, modified_duration4;
    bond14->FV_duration(0.1,6,B4,Macaulay_duration4,modified_duration4);
    cout << "Macaulay Duration @ t0 = 0.1: " << Macaulay_duration4 << endl;
    delete bond14;

    cout << '\n';

    std::vector<double> c5 = {4.1,4.2,4.3,4.4};
    Bond *bond15 = new Bond(2,100,0,2);
    bond15->set_coupons(c5);
    double B5, Macaulay_duration5, modified_duration5;
    bond15->FV_duration(0.55,6,B5,Macaulay_duration5,modified_duration5);
    cout << "Macaulay Duration @ t0 = 0.55: " << Macaulay_duration5 << endl;
    delete bond15;

    cout << '\n';

    std::vector<double> c6 = {4.1,4.2,4.3,4.4};
    Bond *bond16 = new Bond(2,100,0,2);
    bond16->set_coupons(c6);
    double B6, Macaulay_duration6, modified_duration6;
    bond16->FV_duration(0.0,6,B6,Macaulay_duration6,modified_duration6);
    cout << "Modified Duration @ t0 = 0.0: " << modified_duration6 << endl;
    delete bond16;

    cout << '\n';

    std::vector<double> c7 = {4.1,4.2,4.3,4.4};
    Bond *bond17 = new Bond(2,100,0,2);
    bond17->set_coupons(c7);
    double B7, Macaulay_duration7, modified_duration7;
    bond17->FV_duration(0.1,6,B7,Macaulay_duration7,modified_duration7);
    cout << "Modified Duration @ t0 = 0.1: " << modified_duration7 << endl;
    delete bond17;

    cout << '\n';

    std::vector<double> c8 = {4.1,4.2,4.3,4.4};
    Bond *bond18 = new Bond(2,100,0,2);
    bond18->set_coupons(c8);
    double B8, Macaulay_duration8, modified_duration8;
    bond18->FV_duration(0.55,6,B8,Macaulay_duration8,modified_duration8);
    cout << "Modified Duration @ t0 = 0.55: " << modified_duration8 << endl;
    delete bond18;

    return 0;
}
