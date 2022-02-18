/*
    Langevin.hpp
    Langevin dynamics class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef BVPSDEHEADERDEF
#define BVPSDEHEADERDEF

#include <math.h>
#include <string>
#include <vector>
#include "ou.hpp"
#include "langevin_sde.hpp"
#include "mckean_vlasov.hpp"
#include "sde.hpp"
#include "solver.hpp"
#include "euler_maruyama.hpp"
#include "boundary_conditions.hpp"

class Langevin
{
private:
   // Only allow instance to be created from a SDE, boundary
   // conditions, and number of particles(the
   // copy constructor is private)
   Langevin(const Langevin& otherLangevin){}

   // Number of particles in in domain
   int mNumParticles;

   // Pointer to instance of an SDE
   SDE* mpSDE;

   // Initial data function pointer
   void (*mpInitialFun)(double* pInitData, double* yInit, int& numParticles);
   double* mpInitData;

   // // Pointer to an instance of boundary conditions
   // BoundaryConditions* mpBconds;
   std::string mBConds;

   // Pointer to instance of a solver
   Solver* mpSolver;

   // Pointer for solution to particle trajectories and time
   double** mpParticles;
   double* mpTime;

   // Allow user to specify the output file or
   // use a default name
   std::string mOutputData;
   std::string mNumList;
   std::string mPhysList;

   // // Methods for setting up langevin system and solving it
   void SetSDE();
   void SetConstants();
   void SetInitialData();

public:
   // Sole constructor
   Langevin(opts_num* opts1,
            SDE* pSde, 
            void (*pInitialData)(double*,double*, int&),
            std::string BC);

   // As memory is dynamically allocated the destructor
   // is overridden
   ~Langevin();

   opts_num optsNum;
   opts_phys optsPhys;

   void SetFilename(const std::string& dataName, 
                    const std::string& numName,
                    const std::string& physName)
   {
      mOutputData = dataName;
      mNumList    = numName;
      mPhysList   = physName;
   }
   
   void DoStochastics();
   void WriteSolutionFile();
};

#endif
