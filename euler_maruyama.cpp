/*
    euler_maryuama.cpp
    EulerMaruyama class for integrating langevin equation.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include "euler_maruyama.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

EulerMaruyama::EulerMaruyama(opts_num opts1, int numParticles)
{
    optsNum = opts1;
    // mGradV1 = righthandside;

    SetInitialData(optsNum.initial_data);
    SetNumSteps(optsNum.num_steps);
    SetTmax(optsNum.t_max);

    double dt = optsNum.t_max/optsNum.num_steps;
    SetStepSize(dt);
    SetNumParticles(numParticles);
    
    mpTime = new double [GetNumSteps()];
    mpSolution = new double* [GetNumSteps()];
    for(int i = 0; i< GetNumSteps(); i++)
    {
        mpSolution[i] = new double [GetNumSteps()];
    }

    double sigma = sqrt(dt);
    std::normal_distribution<double> distribution (0.0, sigma);
    mDistribution = distribution;
}

int EulerMaruyama::DiracDelta(int i, int j)
{
    if (i==j)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// double EulerMaruyama::TwoBody(double* pParticles)
// {
//     double v2 = 0.0;
    
//     for (int i=0; i<GetNumParticles(); i++)
//     {
//         for (int j=0; j<GetNumParticles(); j++)
//             {
//                 if (i!=j)
//                 {
//                     double r = abs(pParticles[i]-pParticles[j]);
//                     v2 += 
//                 }
//             }

//     }
// }

double EulerMaruyama::RightHandSide(double y, double t)
{
    // return -(*mRhs)(y,t);
    return -Getkappa1()*(*mGradV1)(y,t);
}

double EulerMaruyama::GetWiener()
{
    return mDistribution(mGenerator);
}

void EulerMaruyama::SolveEquation()
{
    double dt = GetStepSize();

    mpTime[0] = 0.0; 

    for (int i=1; i<GetNumSteps(); i++)
    {
        mpTime[i] = mpTime[i-1] + dt;
    }
    
    for (int j=0; j<GetNumParticles(); j++)
    {
        mpSolution[0][j] = GetInitialData()[j];
    }

    for (int j=0; j<GetNumParticles(); j++)
    {
        for (int i=1; i<GetNumSteps(); i++)
        {
            mpSolution[i][j] = mpSolution[i-1][j] + dt*RightHandSide(mpSolution[i-1][j],mpTime[i-1]);
        }
    }

    for (int j=0; j<GetNumParticles(); j++)
    {
        for (int i=1; i<GetNumSteps(); i++)
        {
            mpSolution[i][j] = mpSolution[i][j] + sqrt(2.0*GetBetaInv())*GetWiener();
            // std::cout<<"mpSolution["<<i<<"]"<<"["<<j<<"] = "<< mpSolution[i][j]<<std::endl;
        }
    }

}
