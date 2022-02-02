/*
    solver.hpp
    Solver abstract class for integrating langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF
#include "opts_num.hpp"

// Abstract Langevin base class.
class Solver
{
    private:
        double mStepSize;
        double mTmax;
        double mNumSteps;
        double mInitialData;

    public:
        friend class Langevin;
        opts_num optsNum;
        double* particles; 
                
    // construction
        // Solver(opts_num opts1, double (*righthandside)(double));
        // ~Solver();
        void SetNumSteps(int N);
        int GetNumSteps();
        void SetTmax(double T);
        double GetTmax();
        void SetInitialData(double y0);
        double GetInitialData();
        double GetStepSize();

        virtual double RightHandSide(double y, double t) = 0; 
        virtual void SolveEquation() = 0;
        virtual ~Solver() {};
};

#endif 