/*
    solver.hpp
    Solver abstract class for integrating langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef SOLVERHEADERDEF
#define SOLVERHEADERDEF
#include "opts_num.hpp"
#include "opts_phys.hpp"
#include <random>
#include "boundary_conditions.hpp"

// Abstract Langevin base class.
class Solver
{
    private:
        double mStepSize;
        double mTmax;
        double mNumSteps;
        double mInitialData;
        double mNumParticles;

        double mBetaInv;
        double mkappa1;
        double mkappa2;

        // Pointer to an instance of boundary conditions
        BoundaryConditions* mpBconds;

    public:
        friend class Langevin;
        opts_num optsNum;
        double** mpSolution;
        double* mpTime;
                
        void SetNumSteps(int N);
        int GetNumSteps();
        void SetTmax(double T);
        double GetTmax();
        void SetInitialData(double y0);
        double GetInitialData();
        void SetStepSize(double dt);
        double GetStepSize();
        void SetNumParticles(int N);
        int GetNumParticles();

        // double (*mV1)(double y, double t); 
        double (*mGradV1)(double y, double t);
        void SetGradV1(double (*pGradV1)(double, double));

        // double (*mV2)(double y, double t); 
        double (*mGradV2)(double r);
        void SetGradV2(double (*pGradV2)(double));

        void SetBetaInv(double betaInv);
        double GetBetaInv();

        void SetKappa1(double kappa1);
        double Getkappa1();
        
        void SetKappa2(double kappa1);
        double Getkappa2();

        virtual double RightHandSide(double y, double t) = 0; 
        virtual double GetWiener() = 0;
        virtual void SolveEquation() = 0;
        virtual ~Solver() {};
};

#endif 