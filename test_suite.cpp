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
const double XI = 0.5;
const double ALPHA = 0.5; 

// One body

double Zero1(double y, double t){return 0.0;}

double GradV1Quad(double y, double t){return y-4;}

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y-1.11*y);}

// Two body kernels

double Zero2(double y){return 0.0;}

double GradV2Gauss(double r){return -1/(XI*XI)*r*exp(-0.5*r*r/(XI*XI));}

// initial data

// double* Hat(double* yInit, int numParticles)
//         {
//             double* initialData;
//             initialData = new double [numParticles]; // gets deleted in Langevin::SetInitialData()
//             double hatMin = ALPHA*yInit[0];
//             double hatMax = ALPHA*yInit[1];
//             initialData[0] = hatMin;
            
//             for (int i=1; i<numParticles; i++)
//             {
//                 initialData[i] = initialData[i-1] + (hatMax-hatMin)/numParticles;
//             }
//             return initialData;
//         }

// double* Uniform(double* yInit, int numParticles)
//         {
//             double* initialData;
//             initialData = new double [numParticles]; // gets deleted in Langevin::SetInitialData()
//             initialData[0] = yInit[0];
            
//             for (int i=1; i<numParticles; i++)
//             {
//                 initialData[i] = initialData[i-1] + (yInit[1]-yInit[0])/numParticles;
//             }
//             return initialData;
//         }  

void Hat(double* pInitData , double* yInit, int& numParticles)
        {
            double hatMin = ALPHA*yInit[0];
            double hatMax = ALPHA*yInit[1];
            pInitData[0] = hatMin;
            
            for (int i=1; i<numParticles; i++)
            {
                pInitData[i] = pInitData[i-1] + (hatMax-hatMin)/numParticles;
            }
            
        }


int main(int argc, char* argv[])
{
    int numParticles = 2000;
    double tMax = 2.0;  
    int numSteps = 1000;
    double yMin = -2, yMax = 2;    

    double kappa1 = 1.0;
    double kappa2 = 0.5;

    double theta = 1.0;
    double mu = -1.0;

    opts_phys optsPhys = {.interval = {yMin, yMax}, 
                          .num_particles = numParticles,
                          .beta = 10.0};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax};   

    // SDE* p_test = new OU(optsPhys, &theta, &mu);
    SDE* p_test = new McKeanVlasov(optsPhys, Zero1, GradV2Gauss, &kappa1, &kappa2);
    // SDE* p_test = new LangevinSDE(optsPhys, GradV1Quart, &kappa1);
    
    Langevin pl(&optsNum, p_test, Hat, "no_flux");    
    // Langevin pl(&optsNum, p_test, Hat, "no_flux");    
    // Langevin pl(&optsNum, p_test, Hat, "periodic");
    // Langevin pl(&optsNum, p_test, Hat, "none");
    
    pl.SetFilename("lsde_data.dat", "lsde_num.dat", "lsde_phys.dat");
    pl.DoStochastics();

    delete p_test;
    return 0;
}

