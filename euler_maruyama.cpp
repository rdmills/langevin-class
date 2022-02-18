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

const int BARWIDTH = 70;

void UpdateProgressBar(double progress)
{
    int pos = BARWIDTH * progress;
    for (int i = 0; i < BARWIDTH; ++i) 
    {
        if (i < pos) std::cout << "\u2588";
        else std::cout << " ";
    }   
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

EulerMaruyama::EulerMaruyama(opts_num opts1, BoundaryConditions* pBcs, int numParticles)
{
    optsNum = opts1;
    mpBconds = pBcs;

    SetNumSteps(optsNum.num_steps);
    SetTmax(optsNum.t_max);

    double dt = optsNum.t_max/optsNum.num_steps;
    SetStepSize(dt);
    SetNumParticles(numParticles);
    
    double sigma = sqrt(dt);
    std::normal_distribution<double> distribution (0.0, sigma);
    mDistribution = distribution;

    mpTime = new double [GetNumSteps()];
    mpSolutionStateNow = new double [GetNumParticles()];
    mpSolution = new double* [GetNumSteps()];
    for(int i = 0; i< GetNumSteps(); i++)
    {
        mpSolution[i] = new double [GetNumParticles()];
    }
    mInitialData = new double [GetNumParticles()];
}

double EulerMaruyama::GetWiener()
{
    return mDistribution(mGenerator);
}

double* EulerMaruyama::RightHandSide(double* state, double t)
{
    return mpSDE->Force(state,t);
}

void EulerMaruyama::SolveEquation()
{   
    // for (int j=0; j<GetNumParticles(); j++)
    // {
    //     std::cout<<"mInitialData[j] = "<< GetInitialData()[j]<<std::endl;
    // }

    // std::cout<< "GetStepSize() = "<<GetStepSize()<<std::endl;
    // std::cout<< "GetTmax() = "<<GetTmax()<<std::endl;
    // std::cout<< "GetNumSteps() = "<<GetNumSteps()<<std::endl;
    
    double dt = GetStepSize();
    double tMax = GetTmax();

    mpTime[0] = 0.0; 

    for (int i=1; i<GetNumSteps(); i++)
    {
        mpTime[i] = mpTime[i-1] + dt;
        // std::cout<<"mpTime[i] = "<< mpTime[i]<<std::endl;
    }
    
    for (int j=0; j<GetNumParticles(); j++)
    {
        // mpSolution[0][j] = GetInitialData()[j];
        mpSolution[0][j] = mInitialData[j];
        mpSolutionStateNow[j] = mInitialData[j];
        // std::cout<<"mpSolution[0][j] = "<< mpSolution[0][j]<<std::endl;
        // std::cout<<"mpSolutionStateNow[j] = "<< mpSolutionStateNow[j]<<std::endl;
    }

    // for (int j=0; j<GetNumParticles(); j++)
    // {
    //     // std::cout<<"mpSolution[0][j] = "<< mpSolution[0][j]<<std::endl;
    //     std::cout<<"mpSolutionStateNow[j] = "<< mpSolutionStateNow[j]<<std::endl;
    // }
    
    double progress = 0.0;
    std::cout << "[";
    
    for (int i=1; i<GetNumSteps(); i++)
    {    
        UpdateProgressBar(progress);

        double* force = RightHandSide(mpSolutionStateNow,mpTime[i-1]);
        
        for (int j=0; j<GetNumParticles(); j++)    
        {
            // std::cout<<"mpSolutionStateNow[j] = "<< mpSolutionStateNow[j]<<std::endl;    
            // mpSolution[i][j] = mpSolutionStateNow[j];
            // mpSolution[i][j] = 0.5;
            mpSolution[i][j] = mpSolutionStateNow[j]
                             + dt*force[j]
                             + sqrt(2.0*GetBetaInv())*GetWiener();
            mpSolution[i][j] = ApplyBoundaryConditions(mpSolution[i][j], mpSolutionStateNow[j]);
            // std::cout<<"mpSolution["<<i<<"]"<<"["<<j<<"] = "<< mpSolution[i][j]<<std::endl;                             
        }
        
        delete[] force;
        
        for (int j=0; j<GetNumParticles(); j++)
        {
            mpSolutionStateNow[j] = mpSolution[i][j];
        }

        progress = i*dt/tMax;
    }

    // for (int j=0; j<GetNumParticles(); j++)
    // {
    //     std::cout<<"mInitialData[j] = "<< GetInitialData()[j]<<std::endl;
    // }
    
}