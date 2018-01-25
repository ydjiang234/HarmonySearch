#include <iostream>
#include <Dense>
#include "HarmonySearch.h"


HarmonySearch::HarmonySearch(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio)
{
    this->insRange = insRange;
    this->hms = hms;
    this->hmcr = hmcr;
    this->par = par;
    this->fwRatio = fwRatio;
    //Initial
    this->insNum = this->insRange.rows();
    this->fw = this->fwRatio * (this->insRange.col(1) - this->insRange.col(0));
}

HarmonySearch::~HarmonySearch() {};

bool HarmonySearch::bool_probability(double probability)
{
   return false; 
}
