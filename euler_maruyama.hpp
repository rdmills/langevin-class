/*
    euler_maruyama.hpp
    EulerMaruyama class for sampling langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef EULERMARYAMAHEADERDEF
#define EULERMARYAMAHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include "solver.hpp"

// Optional physics for a 1d line.
// Example:
//      struct opts_phys optsPhys = {{-0.5,0.5}}; 
struct opts_phys
    {
        double interval[2];  
        double (*pV1)(double);
        double (*pGradV1) (double); 
        double kappa1;
        double (*pV2)(double, double);
        double (*pGradV2)(double, double);
        double kappa2;

    };

// Child class Line1D for langevin dynamics on an interval.
class EulerMaruyama : public Solver
{       
    public: 
        EulerMaruyama(opts_num opts1, opts_phys opts2);

        virtual double RightHandSide(double y, double t); 

        // void SetyMinyMax(double interval[2]);
        // double* GetyMinyMax();
        // virtual void InitialiseParticles();
        
        // virtual void DoLangevin();
        // virtual void GenerateNoiseVector();
        // virtual void PrintNoiseVector();

    
    private:
        double (*mV1)(double y); 
        double (*mGradV1)(double y);
        double (*mV2)(double y, double yPrime); 
        double (*mGradV2)(double y, double yPrime);

        double myMinyMax [2];
        double* mNoiseVector;

        int numSteps;    
};

#endif