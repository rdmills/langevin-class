/*
    euler_maryuama.cpp
    EulerMaruyama class for sampling langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include "euler_maruyama.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

EulerMaruyama::EulerMaruyama(opts_num opts1, opts_phys opts2) : Solver(opts1)
{
    mV1 = opts2.pV1;
    mGradV1 = opts2.pGradV1;
    mV2 = opts2.pV2;
    mGradV2 = opts2.pGradV2;
}

double EulerMaruyama::RightHandSide(double y, double t)
{
    return (*mV1)(y);
}

// void Solver::SetStepSize(double dt)
// {
//     mStepSize = dt;
// }

// void Solver::SetTmax(double T)
// {
//     mTmax = T;
// }

// void Solver::SetInitialData(double y0)
// {
//     mInitialData = y0;
// }