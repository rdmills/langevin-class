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

Solver::Solver(opts_num opts1)
{
    optsNum = opts1;
}

void Solver::SetStepSize(double dt)
{
    mStepSize = dt;
}

void Solver::SetTmax(double T)
{
    mTmax = T;
}

void Solver::SetInitialData(double y0)
{
    mInitialData = y0;
}