/*
    euler_maruyama.hpp
    EulerMaruyama class for sampling langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef STRONGTAYLORHEADERDEF
#define STRONGTAYLORHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include "solver.hpp"



// Child class Line1D for langevin dynamics on an interval.
class StrongTaylor : public Solver
{       
    public: 
        StrongTaylor(opts_num opts1);

        virtual double RightHandSide(double y, double t); 
        virtual double SolveEquation();
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

};

#endif