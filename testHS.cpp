#include <iostream>
#include <random>
#include <Dense>
#include "HarmonySearch.h"

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXXd;

int main()
{
    ArrayXXd insRange(4,2);
    unsigned int  hms;
    ArrayXd fwRatio;
    ArrayXd hmcr;
    ArrayXd par;

    hms = 100;
    insRange << 0,100,
                0,100,
                0,100,
                0,100;
    unsigned int insNum = insRange.rows();
    fwRatio = ArrayXd::Ones(insNum,1) * 0.01;
    hmcr = ArrayXd::Ones(insNum,1) * 0.9;
    par = ArrayXd::Ones(insNum,1) * 0.3;

    HarmonySearch *hs = new HarmonySearch(insRange, hms, hmcr, par, fwRatio);
    default_random_engine generator;
    cout<<hs->distribution(generator)<<endl;
}
