#ifndef HarmonySearch_h
#define HarmonySearch_h

#include <iostream>
#include <Dense>
#include <random>

class HarmonySearch
{
public:
    //Input Parameters
    Eigen::ArrayXXd insRange;
    unsigned int  hms;
    Eigen::ArrayXd fwRatio;
    Eigen::ArrayXd hmcr;
    Eigen::ArrayXd par;
    
    Eigen::ArrayXd fw;
    Eigen::ArrayXXd HM;
    Eigen::ArrayXd fitness;
    unsigned int  insNum;
    bool isForceRange;
    
    //Other parameters
    std::random_device rd;
    std::mt19937 gen;
    
    
    
    HarmonySearch(Eigen::ArrayXXd insRange, unsigned int hms, Eigen::ArrayXd hmcr, Eigen::ArrayXd par, Eigen::ArrayXd fwRatio, bool isForceRange);
    HarmonySearch();
    ~HarmonySearch();
    virtual double objFun(Eigen::ArrayXd vector);
    
    //Generate the initail Harmony Memory
    void genHM();
    
    //Generate a new pitch of one instrument for the next step
    double selPitch(unsigned int insId);
    //Generate a new pitch vector for the next step
    Eigen::ArrayXd newPitchVector();
    //Update a the HM
    void updateHM(Eigen::ArrayXd newVector);
    //Next iteration
    void next();
    //Get the optimized fitness, vector of current iteration
    double OptimizedFitness();
    Eigen::ArrayXd OptimizedSolution();
    
    //Get bool when input a probability
    bool bool_probability(double probability);
    
    //random function
    std::uniform_real_distribution<double> dis01;
    std::uniform_real_distribution<double> dis1;
    std::uniform_int_distribution<unsigned int> disId;
    
    
    //Get random double from range 0~1
    double random01();
    //Get random double from range -1~1
    double random1();
    //Get random index from range 0~hms
    int randomId();
    //Get random pitch from the instrument range when input an instrument id
    double randomPitch(unsigned insId);
    
    //Change if an instrument is out of range
    double limitRange(double pitch, unsigned int insId);
};


#endif
