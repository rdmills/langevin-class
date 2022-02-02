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

EulerMaruyama::EulerMaruyama(opts_num opts, double (*righthandside)(double, double))
{
    optsNum = opts;
    mRhs = righthandside;
}

double EulerMaruyama::RightHandSide(double y,double t)
{
    return (*mRhs)(y,t);
}
double EulerMaruyama::SolveEquation()
{
    int N = GetNumSteps();
    
    double dt = GetStepSize();
    
    double y_sol[N], t_grid[N];

    t_grid[0] = 0.0; 
    y_sol[0] = GetInitialData();
    
    for (int i=1; i<N; i++)
    {
        t_grid[i] = t_grid[i-1] + dt;
        y_sol[i] = y_sol[i-1] + dt*RightHandSide(y_sol[i],t_grid[i]);
    }
    
    return 0.0;
}
