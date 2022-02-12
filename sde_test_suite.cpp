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
const double XI = 1.0;

double V1Quad(double y, double t){return 0.5*y*y;}

double GradV1Quad(double y, double t){return y;}

double V1Quart(double y, double t){return 1.0*(0.1*y*y*y*y-3.0*y*y);}

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y-6.0*y);}

double V2Gauss(double r){return exp(-0.5*r*r/(XI*XI));}

double GradV2Gauss(double r){return -1/(XI*XI)*r*exp(-0.5*r*r/(XI*XI));}

int main(int argc, char* argv[])
{
    int numParticles = 1000;
    int numSteps = 2000;                         

    opts_phys optsPhys = {{-0.5,0.5}, 
                    numParticles,
                    1.0, 
                    1.0,
                    0.1};                          

    opts_num optsNum = {numSteps, 
                        20.0,
                        -0.1};     
    
    McKeanVlasov mkc_v(optsPhys, GradV1Quart, GradV2Gauss);
    
    BoundaryConditions bc_periodic;
    bc_periodic.SetPeriodicBc();
    
    Langevin pl(&optsNum, &mkc_v, &bc_periodic);
    
    pl.SetFilename("quart_data.dat", "quart_num.dat", "quart_phys.dat");
    pl.DoStochastics();

    return 0;
}

