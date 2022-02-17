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
        EulerMaruyama(opts_num opts1, BoundaryConditions* pBcs, int numParticles);

        int DiracDelta(int i, int j);
        virtual double* RightHandSide(double* state, double t);
        virtual double GetWiener();
        virtual void SolveEquation();
        virtual ~EulerMaruyama() 
        { 
            delete [] mpTime;
            delete [] mpSolutionStateNow;
            delete [] mInitialData;
            for (int i = 0; i<GetNumSteps(); i++)
            {
                delete [] mpSolution[i]; 
            }
        };
    private:
        double (*mRhs)(double y, double t);
        std::default_random_engine mGenerator;
        std::normal_distribution<double> mDistribution;
};

#endif