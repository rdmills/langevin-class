/*
    solver.cpp
    Solver abstract class for sampling langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// Solver::Solver(opts_num opts1, double (*righthandside)(double))
// {
//     optsNum = opts1;

//     mNumSteps = opts1.num_steps;
//     mTmax = opts1.t_max;
//     mStepSize = mTmax/mNumSteps;
//     mR
    
// }

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

void Solver::SetInitialData(double y0)
{
    mInitialData = y0;
}

double Solver::GetInitialData()
{
    return mInitialData;
}

double Solver::GetStepSize()
{
    return mStepSize;
}