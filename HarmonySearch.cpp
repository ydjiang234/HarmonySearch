#include <iostream>
#include <Dense>
#include <random>
#include "HarmonySearch.h"


HarmonySearch::HarmonySearch(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange) : dis01(0.0, 1.0),dis1(-1.0,1.0),disId(0,hms-1)
{
    this->insRange = insRange;
    this->hms = hms;
    this->hmcr = hmcr;
    this->par = par;
    this->fwRatio = fwRatio;
    this->isForceRange = isForceRange;
    //Initial
    this->insNum = this->insRange.rows();
    this->fw = this->fwRatio * (this->insRange.col(1) - this->insRange.col(0));
    
    //random generator
    this->gen = std::mt19937(this->rd());
    
    //generate the initial HM
    this->genHM();
}

HarmonySearch::~HarmonySearch() {};

bool HarmonySearch::bool_probability(double probability)
{
    return (this->random01() < probability);
}


double HarmonySearch::random01()
{
    return this->dis01(this->gen);
}

double HarmonySearch::random1()
{
    return dis1(this->gen);
}

int HarmonySearch::randomId()
{
    return disId(this->gen);
}

double HarmonySearch::randomPitch(unsigned insId)
{
    std::uniform_real_distribution<double> disTemp(this->insRange(insId, 0), this->insRange(insId, 1));
    return disTemp(this->gen);
}

void HarmonySearch::genHM()
{
    this->HM = Eigen::ArrayXXd(this->hms, this->insNum);
    this->fitness = Eigen::ArrayXd(this->hms);
    for (int rowId=0; rowId<this->hms; rowId++)
    {
        for (int insId=0; insId<this->insNum; insId++)
        {
            this->HM(rowId, insId) = this->randomPitch(insId);
        }
        this->fitness(rowId) = this->objFun(this->HM.row(rowId));
    }
}

void HarmonySearch::updateHM(Eigen::ArrayXd newVector)
{
    double newFitness = this->objFun(newVector);
    unsigned int  minId;
    this->fitness.minCoeff(&minId);
    double minFitness = this->fitness(minId);
    if (newFitness > minFitness)
    {
        this->fitness(minId) = newFitness;
        this->HM.row(minId) = newVector;
    }
}

void HarmonySearch::next()
{
    Eigen::ArrayXd newVector = this->newPitchVector();
    this->updateHM(newVector);
}

double HarmonySearch::OptimizedFitness()
{
    unsigned int maxId;
    this->fitness.maxCoeff(&maxId);
    return this->fitness(maxId);
}

Eigen::ArrayXd HarmonySearch::OptimizedSolution()
{
    unsigned int maxId;
    this->fitness.maxCoeff(&maxId);
    return this->HM.row(maxId);
}


double HarmonySearch::selPitch(unsigned int insId)
{
    double newPitch;
    if (this->bool_probability(this->hmcr(insId)))
    {
        newPitch = this->HM.col(insId)(this->randomId());
        if (this->bool_probability(this->par(insId)))
        {
            newPitch = newPitch + this->random1() * this->fw(insId);
            newPitch = this->limitRange(newPitch, insId);
        }
    } else {
        newPitch = this->randomPitch(insId);
    }
    return newPitch;
}

Eigen::ArrayXd HarmonySearch::newPitchVector()
{
    Eigen::ArrayXd PitchVector = Eigen::ArrayXd(this->insNum);
    for (int insId=0; insId<this->insNum; insId++)
    {
        PitchVector(insId) = this->selPitch(insId);
    }
    
    return PitchVector;
}

double HarmonySearch::objFun(Eigen::ArrayXd vec)
{
    double x = vec(0);
    double y = vec(1);
    double m = vec(2);
    double n = vec(3);
    
    double out = (x-2.0)*(x-2.0) + (y-30.0)*(y-30.0) + (m-15.0)*(m-15.0) + (n-101.0)*(n-101.0);
    return out * -1;
}

double  HarmonySearch::limitRange(double pitch, unsigned int insId)
{
    double newPitch;
    if (this->isForceRange)
    {
        if (pitch > this->insRange(insId, 1))
        {
            newPitch = insRange(insId, 1);
        } else if (pitch < this->insRange(insId, 0))
        {
            newPitch = insRange(insId, 0);
        } else {
            newPitch = pitch;
        }
                
    } else {
        newPitch = pitch;
    }
    return newPitch;
}