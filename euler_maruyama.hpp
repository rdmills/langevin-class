/*
    euler_maruyama.hpp
    EulerMaruyama class for integrating langevin equation.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef EULERMARYAMAHEADERDEF
#define EULERMARYAMAHEADERDEF

#include "solver.hpp"

// Child class EulerMaryuama for langevin dynamics on an interval.
class EulerMaruyama : public Solver
{       
    public: 
        EulerMaruyama(opts_num opts, double (*mRightHandSide)(double, double));
        
        virtual double RightHandSide(double y, double t); 
        virtual double SolveEquation();
        virtual ~EulerMaruyama() {};
    private:
        double (*mV1)(double y); 
        double (*mGradV1)(double y);
        // double (*mV2)(double y, double yPrime); 
        // double (*mGradV2)(double y, double yPrime);

        double (*mRhs)(double y, double t);
        double myMinyMax [2];
};

#endif