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

EulerMaruyama::EulerMaruyama(opts_num opts1, BoundaryConditions* pBcs, int numParticles)
{
    optsNum = opts1;
    mpBconds = pBcs;

    SetInitialData(optsNum.initial_data);
    SetNumSteps(optsNum.num_steps);
    SetTmax(optsNum.t_max);

    double dt = optsNum.t_max/optsNum.num_steps;
    SetStepSize(dt);
    SetNumParticles(numParticles);
    
    mpTime = new double [GetNumSteps()];
    mpSolutionStateNow = new double [GetNumSteps()];
    mpSolution = new double* [GetNumSteps()];
    for(int i = 0; i< GetNumSteps(); i++)
    {
        mpSolution[i] = new double [GetNumSteps()];
    }

    double sigma = sqrt(dt);
    std::normal_distribution<double> distribution (0.0, sigma);
    mDistribution = distribution;
}

double EulerMaruyama::GetWiener()
{
    return mDistribution(mGenerator);
}

double* EulerMaruyama::RightHandSide(double* state, double t)
{
    double* force;
    force = new double [GetNumParticles()];
    for (int j=0; j<GetNumParticles(); j++)
    {
        force[j] = -Getkappa1()*(*mGradV1)(state[j],t);
        // std::cout<< "force["<<j<<"] = "<<force[j]<<std::endl;
    }
    
    for (int j=0; j<GetNumParticles(); j++)
    {
        double* p_v2;
        p_v2 = new double;
        *p_v2 = 0.0;
        for (int k=0; k<GetNumParticles(); k++)
        {
            if (k!=j)
            {
                *p_v2 += (-Getkappa2())*(*mGradV2)(state[j]-state[k]);
            }
            else
            {
                *p_v2 += 0.0;
            }
        }
        // std::cout<<"*p_v2 = "<<*p_v2<<std::endl;
        force[j] += *p_v2;
        delete p_v2;
    }

    return force;
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
        mpSolutionStateNow[j] = mpSolution[0][j];
    }

    for (int i=1; i<GetNumSteps(); i++)
    {
        double* force = RightHandSide(mpSolutionStateNow,mpTime[i-1]);
        
        for (int j=0; j<GetNumParticles(); j++)    
        {
            mpSolution[i][j] = mpSolution[i-1][j]
                             + dt*force[j]
                             + sqrt(2.0*GetBetaInv())*GetWiener();
            mpSolution[i][j] = ApplyBoundaryConditions(mpSolution[i][j]);
        }
        
        delete[] force;
        
        for (int j=0; j<GetNumParticles(); j++)
        {
            mpSolutionStateNow[j] = mpSolution[i][j];
        }
    
    }
    
}