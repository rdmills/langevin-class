/*
    sde_test_suite.cpp
    Entry point for running langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include "langevin.hpp"
// #include "solver.hpp"

const double PI = 3.14159265359;

double V1Quad(double y, double t){return 0.5*y*y;}

double GradV1Quad(double y, double t){return y;}

double V2Gauss(double r, double a){return 0.5/sqrt(PI*a*a)*exp(-0.5*r*r/(a*a));}

double GradV2Gauss(double r, double a){return -0.5/sqrt(PI*a*a)*r/(a*a)*exp(-0.5*r*r/(a*a));}

int main(int argc, char* argv[])
{
    opts_phys optsPhys = {{-0.5,0.5}, &V1Quad, &GradV1Quad, 1.0};
    opts_num optsNum = {12, 1.0};
    phys_consts phys = {1.0};
    
    MckeanVlasov mkc_v(optsPhys, V1Quad);
    
    BoundaryConditions bc_periodic;
    bc_periodic.SetPeriodicBc();

    Solver* p_solver = new EulerMaruyama(optsNum,V1Quad);
    
    Langevin pl(&mkc_v, &bc_periodic, p_solver, 101, optsNum);

    delete p_solver;
 
    return 0;
}

// Langevin(MckeanVlasov* pSde, 
//             BoundaryConditions* pBcs, 
//             Solver* pSolver,
//             int numParticles,
//             opts_num opts);


// #include <cmath>
// #include <string>
// #include "BvpOde.hpp"

// double model_prob_1_rhs(double x){return 1.0;}
// double model_prob_2_rhs(double x){return 34.0*sin(x);}

// int main(int argc, char* argv[])
// {
//    SecondOrderOde ode_mp1(-1.0, 0.0, 0.0, 
//                          model_prob_1_rhs, 
//                          0.0, 1.0);
//    BoundaryConditions bc_mp1;
//    bc_mp1.SetLhsDirichletBc(0.0);
//    bc_mp1.SetRhsDirichletBc(0.0);

//    BvpOde bvpode_mp1(&ode_mp1, &bc_mp1, 101);
//    bvpode_mp1.SetFilename("model_problem_results1.dat");
//    bvpode_mp1.Solve();

//    SecondOrderOde ode_mp2(1.0, 3.0, -4.0, 
//                          model_prob_2_rhs, 
//                          0.0, M_PI);
//    BoundaryConditions bc_mp2;
//    bc_mp2.SetLhsNeumannBc(-5.0);
//    bc_mp2.SetRhsDirichletBc(4.0);

//    BvpOde bvpode_mp2(&ode_mp2, &bc_mp2, 1001);
//    bvpode_mp2.SetFilename("model_problem_results2.dat");
//    bvpode_mp2.Solve();

//    return 0;
// }

