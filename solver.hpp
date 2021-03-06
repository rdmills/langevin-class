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
#include "sde.hpp"

class Solver
{
    private:
        double mStepSize;
        double mTmax;
        int mNumSteps;
        double mNumParticles;
        double mBetaInv;
    
    protected:
        double yMinyMax [2];   
        double* mInitialData;
        double** mpSolution;
        double* mpSolutionStateNow;
        double* mpTime;
        double* (*mForce)(double* particle, double t);
        
        SDE* mpSDE;
        BoundaryConditions* mpBconds;    
        
    public:
        // The Langevin value class is able to
        // access Solver.
        friend class Langevin;
        opts_num optsNum;
                
        void SetNumSteps(int N);
        int GetNumSteps();
        void SetTmax(double T);
        double GetTmax();
        void SetStepSize(double dt);
        double GetStepSize();
        void SetNumParticles(int N);
        int GetNumParticles();
        
        void SetInitialData(const double* initialData);
        double* GetInitialData();

        void SetSDE(SDE* pSDE);

        void SetBetaInv(double betaInv);
        double GetBetaInv();

        void SetYMinYMax(double interval [2]);
        
        double ApplyBoundaryConditions(double particle_new, double particle_old);

        virtual double* RightHandSide(double* state, double t) = 0;
        virtual double GetWiener() = 0;
        virtual void SolveEquation() = 0;
        
        virtual ~Solver() {};
};

#endif 