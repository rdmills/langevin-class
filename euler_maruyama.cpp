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

EulerMaruyama::EulerMaruyama(opts_num opts1, double (*righthandside)(double, double))
{
    optsNum = opts1;
    mRhs = righthandside;

    SetInitialData(optsNum.initial_data);
    SetNumSteps(optsNum.num_steps);
    SetTmax(optsNum.t_max);
    
    double dt = optsNum.t_max/optsNum.num_steps;
    
    SetStepSize(dt);
    SetNumParticles(optsNum.num_particles);
    
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

double EulerMaruyama::RightHandSide(double y, double t)
{
    return -(*mRhs)(y,t);
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
        mpSolution[0][j] = GetInitialData();
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
            mpSolution[i][j] = mpSolution[i][j] + GetWiener();
        }
    }

}
