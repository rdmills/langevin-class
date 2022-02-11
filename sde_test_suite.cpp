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

double V1Quart(double y, double t){return 1.0*(0.1*y*y*y*y-3.0*y*y);}

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y-6.0*y);}

double V2Gauss(double r, double a){return 0.5/sqrt(PI*a*a)*exp(-0.5*r*r/(a*a));}

double GradV2Gauss(double r, double a){return -0.5/sqrt(PI*a*a)*r/(a*a)*exp(-0.5*r*r/(a*a));}

int main(int argc, char* argv[])
{

    // int numParticles = 1000;
    // int numSteps = 2000;

    // opts_phys optsPhys = {{-0.5,0.5}, 
    //                       numParticles,
    //                       &V1Quad,
    //                       &GradV1Quad,
    //                       1.0, 
    //                       &V2Gauss, 
    //                       &GradV2Gauss, 
    //                       1.0};

    // opts_num optsNum = {numParticles, numSteps, 20.0, 1.0};
    
    // McKeanVlasov mkc_v(optsPhys, GradV1Quad);
    
    // BoundaryConditions bc_periodic;
    // bc_periodic.SetPeriodicBc();
    
    // Solver* p_solver = new EulerMaruyama(optsNum, GradV1Quad);
    // // Solver* p_solver = new EulerMaruyama(optsNum, GradV1Quad, &bc_periodic);
    
    // Langevin pl(&mkc_v, &bc_periodic, p_solver);
    
    // pl.SetFilename("mckean_vlasov_data.dat", "mckean_vlasov_num.dat", "mckean_vlasov_phys.dat");
    // pl.DoStochastics();

    // delete p_solver;

    
    int numParticles = 1000;
    int numSteps = 2000;

    opts_phys optsPhys = {{-0.5,0.5}, 
                    numParticles,
                    &V1Quart,
                    &GradV1Quart,
                    1.0, 
                    &V2Gauss, 
                    &GradV2Gauss, 
                    1.0,
                    0.1};                          

    // opts_num optsNum = {numParticles, numSteps, 20.0, 0.1};
    opts_num optsNum = {numParticles, numSteps, 20.0, -0.1};
    
    McKeanVlasov mkc_v(optsPhys, GradV1Quart);
    
    BoundaryConditions bc_periodic;
    bc_periodic.SetPeriodicBc();
    
    Solver* p_solver = new EulerMaruyama(optsNum, optsPhys, GradV1Quart);
    // Solver* p_solver = new EulerMaruyama(optsNum, GradV1Quad, &bc_periodic);
    
    Langevin pl(&mkc_v, &bc_periodic, p_solver);
    
    // pl.SetFilename("mckean_vlasov_data.dat", "mckean_vlasov_num.dat", "mckean_vlasov_phys.dat");
    pl.SetFilename("quart_data.dat", "quart_num.dat", "quart_phys.dat");
    pl.DoStochastics();

    delete p_solver;

    return 0;
}

