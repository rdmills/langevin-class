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
    
    p_particleSolution = new double [optsNum.num_steps];
    p_time             = new double [optsNum.num_steps];
    
    this->SetInitialData(optsNum.initial_data);
    this->SetNumSteps(optsNum.num_steps);
    this->SetTmax(optsNum.t_max);
}

double EulerMaruyama::RightHandSide(double y,double t)
{
    return (*mRhs)(y,t);
}
void EulerMaruyama::SolveEquation()
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

    for (int i=1; i<N; i++)
    {
        p_particleSolution[i] = y_sol[i];
        p_time[i] = t_grid[i];
    }

}
