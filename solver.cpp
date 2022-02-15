/*
    solver.cpp
    Solver abstract class for integrating langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

void Solver::SetNumSteps(int N)
{
    mNumSteps = N;
}

int Solver::GetNumSteps()
{
    return mNumSteps;
}

void Solver::SetTmax(double T)
{
    mTmax = T;
}

double Solver::GetTmax()
{
    return mTmax;
}

void Solver::SetInitialData(double* y0)
{
    mInitialData = y0;
}

double* Solver::GetInitialData()
{
    return mInitialData;
}

void Solver::SetStepSize(double dt)
{
    mStepSize = dt;
}

double Solver::GetStepSize()
{
    return mStepSize;
}

void Solver::SetNumParticles(int N)
{
    mNumParticles = N;
}

int Solver::GetNumParticles()
{
    return mNumParticles;
}

void Solver::SetBetaInv(double betaInv)
{
    mBetaInv = betaInv;
}

double Solver::GetBetaInv()
{
    return mBetaInv;
}

void Solver::SetKappa1(double kappa1)
{
    mkappa1 = kappa1;
}

double Solver::Getkappa1()
{
    return mkappa1;
}

void Solver::SetKappa2(double kappa2)
{
    mkappa2 = kappa2;
}

double Solver::Getkappa2()
{
    return mkappa2;
}

void Solver::SetYMinYMax(double interval [2])
{
    yMinyMax[0] = interval[0];
    yMinyMax[1] = interval[1];
}

void Solver::SetGradV1(double (*pGradV1)(double, double))
{
    mGradV1 = pGradV1;
}

void Solver::SetGradV2(double (*pGradV2)(double))
{
    mGradV2 = pGradV2;
}

double Solver::ApplyBoundaryConditions(double particle)
{
    // std::cout<<mpBconds->mBcIsPeriodic<<std::endl;
    if (mpBconds->mBcIsPeriodic)
    {
        if(particle<yMinyMax[0])
        {
            return yMinyMax[1] - (yMinyMax[0]-particle);
        }
        else if(particle>yMinyMax[1])
        {
            return yMinyMax[0] + (particle-yMinyMax[1]);
        }
        else 
        {
            return particle;
        }
    }
    
    if (mpBconds->mBcIsNoFlux)
    {
        if(particle<yMinyMax[0])
        {
            return yMinyMax[0] + (yMinyMax[0]-particle);
            // return yMinyMax[0];
        }
        else if(particle>yMinyMax[1])
        {
            return yMinyMax[1] - (particle-yMinyMax[1]);
            // return yMinyMax[1];
        }
        else 
        {
            return particle;
        }
    }

    else
    {
        return particle;
    }
}