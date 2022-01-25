/*
    line1d.hpp
    Line1D class for langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef LINE1DHEADERDEF
#define LINE1DHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include "langevin.hpp"

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
class Line1D : public Langevin
{       
    public: 
        double yMin;
        double yMax;

        opts_phys optsPhys;

        Line1D(opts_num opts1, opts_phys opts2);
        void SetyMinyMax(double interval[2]);
        double* GetyMinyMax();
        virtual void InitialiseParticles();
        
        virtual void DoLangevin();
        virtual void GenerateNoiseVector();
        virtual void PrintNoiseVector();

    
    private:
        double myMinyMax [2];
        double* mNoiseVector;    
};

#endif