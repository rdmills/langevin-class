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

double V1Quad(double y, double t){return 0.5*(y*y-4);}

double GradV1Quad(double y, double t){return y-4;}

double V1Quart(double y, double t){return 1.0*(0.1*y*y*y*y-3.0*y*y);}

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y-6.0*y);}

double V2Gauss(double r){return exp(-0.5*r*r/(XI*XI));}

double GradV2Gauss(double r){return -1/(XI*XI)*r*exp(-0.5*r*r/(XI*XI));}

int main(int argc, char* argv[])
{
    int numParticles = 1000;
    double tMax = 20.0;  
    int numSteps = 2000;

    double yMin = -0.5, yMax = 0.5;    

    double* initialData;
    initialData = new double [numParticles];
    initialData[0] = yMin;
    
    for (int i=1; i<numParticles; i++)
    {
        initialData[i] = initialData[i-1] + (yMax-yMin)/numParticles;
    }

    opts_phys optsPhys = {.interval = {yMin,yMax}, 
                          .num_particles = numParticles,
                          .kappa1 = 2.0, 
                          .kappa2 = 1.0,
                          .beta = 0.1};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax,
                        .initial_data = initialData};     
    
    McKeanVlasov mkc_v(optsPhys, GradV1Quart, GradV2Gauss);
    
    BoundaryConditions bc_periodic;
    bc_periodic.SetPeriodicBc();
    
    // Langevin pl(&optsNum, &mkc_v, &bc_periodic);
    Langevin pl(&optsNum, &mkc_v, "periodic");
    
    pl.SetFilename("quart_data.dat", "quart_num.dat", "quart_phys.dat");
    pl.DoStochastics();

    delete [] initialData;

    return 0;
}

