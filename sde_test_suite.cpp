/*
    sde_test_suite.cpp
    Entry point for running langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double PI = 3.14159265359;

double V1Quad(double y, double t){return 0.5*y*y;}

double GradV1Quad(double y, double t){return y;}

double V2Gauss(double r, double a){return 0.5/sqrt(PI*a*a)*exp(-0.5*r*r/(a*a));}

double GradV2Gauss(double r, double a){return -0.5/sqrt(PI*a*a)*r/(a*a)*exp(-0.5*r*r/(a*a));}

int main(int argc, char* argv[])
{
    opts_phys optsPhys = {{-0.5,0.5}, 100, &V1Quad, &GradV1Quad, 1.0};
    opts_num optsNum = {12, 1.0};
    
    McKeanVlasov mkc_v(V1Quad);
    
    BoundaryConditions bc_periodic;
    bc_periodic.SetPeriodicBc();

    Solver* p_solver = new EulerMaruyama(V1Quad);
    
    Langevin pl(&mkc_v, &bc_periodic, p_solver, 101);
    pl.SetFilename("overdamped_langevin.dat");

    delete p_solver;
    
    return 0;
}

