#ifndef HarmonySearch_h
#define HarmonySearch_h

#include <iostream>
#include <Dense>
#include <random>

class HarmonySearch
{
public:
    unsigned int  insNum;
    Eigen::ArrayXXd insRange;
    unsigned int  hms;
    Eigen::ArrayXd fwRatio;
    Eigen::ArrayXd hmcr;
    Eigen::ArrayXd par;

    Eigen::ArrayXd fw;
    Eigen::ArrayXXd HM;
    
    HarmonySearch(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio);
    ~HarmonySearch();

    bool bool_probability(double probability);
    std::uniform_int_distribution<int> distribution;
    


    




};


#endif
