/*
    solver.hpp
    Solver abstract class for langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>
// #include "langevin.hpp"

// Numerical options for time integrator.
// Example:
//      opts_num optsNum = {12, 1.0};
struct opts_num
    {
        int num_steps;
        double t_max;
    };

// Abstract Langevin base class.
class Solver
{
    public:
    friend class Langevin;
    // properties
        // std::vector< std::vector<double> > particles; 
        std::vector< double > particles; 
        opts_num optsNum;

    // construction
        // Solver(opts_num opts1, double (*righthandside)(double));
        // ~Solver();
    
    // methods  
        void SetNumSteps(int N);
        int GetNumSteps();
        void SetTmax(double T);
        double GetTmax();
        void SetInitialData(double y0);
        double GetInitialData();
        double GetStepSize();

        virtual double RightHandSide(double y, double t) = 0; 
        virtual double SolveEquation() = 0;
        virtual ~Solver() {};
    // protected:
    // properties
        
    private:
        double mStepSize;
        double mTmax;
        double mNumSteps;
        double mInitialData;
        

};

#endif 