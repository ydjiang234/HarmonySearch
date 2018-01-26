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

    hms = 10;
    insRange << 0,100,
                0,100,
                0,100,
                0,100;
    unsigned int insNum = insRange.rows();
    fwRatio = ArrayXd::Ones(insNum,1) * 0.01;
    hmcr = ArrayXd::Ones(insNum,1) * 0.9;
    par = ArrayXd::Ones(insNum,1) * 0.3;

    HarmonySearch *hs = new HarmonySearch(insRange, hms, hmcr, par, fwRatio);
    //cout<<hs->randomPitch(0)<<' '<<hs->randomPitch(0)<<endl;
    //cout<<hs->randomPitch(0)<<' '<<hs->randomPitch(0)<<endl;
    //cout<<hs->fitness<<endl;
    unsigned int maxIter = 5000;
    double maxFit;
    ArrayXd maxVector;
    for (unsigned int i=0; i<maxIter; i++)
    {
        hs->next();
        maxFit = hs->OptimizedFitness();
        maxVector = hs->OptimizedSolution();
        printf("%0.4f %0.4f %0.4f %0.4f", maxVector(0), maxVector(1), maxVector(2), maxVector(3));
        cout<<endl;
    }
}
