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
        // EulerMaruyama(opts_num opts, 
        //               double (*mRightHandSide)(double, double), 
        //               BoundaryConditions* pBcs);        
        EulerMaruyama(opts_num opts1, 
                      opts_phys opts2);
                    //   double (*mRightHandSide)(double, double));        
        
        void SetBetaInv();
        double GetBetaInv();
        void SetKappa1();
        double GetKappa1();

        int DiracDelta(int i, int j);
        
        virtual double RightHandSide(double y, double t); 
        virtual double GetWiener();
        virtual void SolveEquation();
        virtual ~EulerMaruyama() 
        { 
            delete [] mpTime;
            for (int i = 0; i<GetNumSteps(); i++)
            {
                delete [] mpSolution[i]; 
            }
        };
    private:
        opts_phys mOptsPhys;
        double mBetaInv;
        double mKappa1;
        double mKappa2;

        // double (*mV1)(double y, double t); 
        // double (*mGradV1)(double y, double t);
        // double (*mV2)(double y, double yPrime); 
        // double (*mGradV2)(double y, double yPrime);

        double (*mRhs)(double y, double t);
        std::default_random_engine mGenerator;
        std::normal_distribution<double> mDistribution;
};

#endif