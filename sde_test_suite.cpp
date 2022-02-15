/*
    sde_test_suite.cpp
    Entry point for running langevin dynamics in 1D.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double PI = 3.14159265359;
const double XI = 2.0;
const double ALPHA = 0.5; 

// One body

double Zero1(double y, double t){return 0.0;}

double V1Quad(double y, double t){return 0.5*(y*y-4);}

double GradV1Quad(double y, double t){return y-4;}

double V1Quart(double y, double t){return 1.0*(0.1*y*y*y*y-3.0*y*y);}

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y-6.0*y);}

// Two body kernels

double Zero2(double y){return 0.0;}

double V2Gauss(double r){return exp(-0.5*r*r/(XI*XI));}

double GradV2Gauss(double r){return -1/(XI*XI)*r*exp(-0.5*r*r/(XI*XI));}

// initial data

double* Hat(double* yInit, int numParticles)
        {
            double* initialData;
            initialData = new double [numParticles]; // gets deleted in Langevin::SetInitialData()
            double hatMin = ALPHA*yInit[0];
            double hatMax = ALPHA*yInit[1];
            initialData[0] = hatMin;
            
            for (int i=1; i<numParticles; i++)
            {
                initialData[i] = initialData[i-1] + (hatMax-hatMin)/numParticles;
            }
            return initialData;
        }

double* Uniform(double* yInit, int numParticles)
        {
            double* initialData;
            initialData = new double [numParticles]; // gets deleted in Langevin::SetInitialData()
            initialData[0] = yInit[0];
            
            for (int i=1; i<numParticles; i++)
            {
                initialData[i] = initialData[i-1] + (yInit[1]-yInit[0])/numParticles;
            }
            return initialData;
        }        

int main(int argc, char* argv[])
{
    int numParticles = 1000;
    double tMax = 2.0;  
    int numSteps = 2000;
    double yMin = -4, yMax = 4;    

    opts_phys optsPhys = {.interval = {yMin, yMax}, 
                          .num_particles = numParticles,
                          .kappa1 = 1.0, 
                          .kappa2 = 1.0,
                          .beta = 10.0};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax};   
    
    McKeanVlasov mkc_v(optsPhys, Zero1, GradV2Gauss);
    // McKeanVlasov mkc_v(optsPhys, Zero1, Zero2);
    // McKeanVlasov mkc_v(optsPhys, GradV1Quart, Zero2);
    
    Langevin pl(&optsNum, &mkc_v, Hat, "no_flux");    
    // Langevin pl(&optsNum, &mkc_v, Uniform, "no_flux");    
    // Langevin pl(&optsNum, &mkc_v, Uniform, "periodic");
    // Langevin pl(&optsNum, &mkc_v, Uniform, "none");
    
    pl.SetFilename("gauss_data.dat", "gauss_num.dat", "gauss_phys.dat");
    pl.DoStochastics();

    return 0;
}

