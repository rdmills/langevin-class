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

EulerMaruyama::EulerMaruyama(opts_num opts1) : Solver(opts1)
{

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