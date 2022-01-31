/*
    euler_maryuama.cpp
    EulerMaruyama class for sampling langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include "strong_taylor.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// StrongTaylor::StrongTaylor(opts_num opts1, opts_phys opts2) : Solver(opts1)
// {
//     mV1 = opts2.pV1;
//     mGradV1 = opts2.pGradV1;
//     mV2 = opts2.pV2;
//     mGradV2 = opts2.pGradV2;
// }

double StrongTaylor::RightHandSide(double y, double t)
{
    return -(*mGradV1)(y);
}

double StrongTaylor::SolveEquation()
{
    // int N = GetNumSteps();
    
    // double dt = GetStepSize();
    
    // double y_sol[N], t_grid[N];

    // t_grid[0] = 0.0; 
    // y_sol[0] = GetInitialData();
    
    // for (int i=1; i<N; i++)
    // {
    //     t_grid[i] = t_grid[i-1] + dt;
    //     y_sol[i] = y_sol[i-1] + dt*RightHandSide(y_sol[i],t_grid[i]);
    // }
    
    return 0.0;
}
