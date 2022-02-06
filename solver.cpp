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

void Solver::SetInitialData(double y0)
{
    mInitialData = y0;
}

double Solver::GetInitialData()
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