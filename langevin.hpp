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
#include "mckean_vlasov.hpp"
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
   McKeanVlasov* mpMcKeanVlasov;

   // Pointer to an instance of boundary conditions
   BoundaryConditions* mpBconds;

   // Pointer to instance of a solver
   Solver* mpSolver;

   // Vector for solution to particle trajectories
   // std::vector<double>* mpParticles;
   double** mpParticles;
   double* mpTime;

   // Right-hand side vector
   // std::vector<double>* mpRhsVec;

   // Allow user to specify the output file or
   // use a default name
   std::string mOutputData;
   std::string mNumList;
   std::string mPhysList;

   // // Methods for setting up linear system and solving it
   // void PopulateVector();
   void ApplyBoundaryConditions();

public:
   // Sole constructor
   Langevin(McKeanVlasov* pSde, 
            BoundaryConditions* pBcs, 
            Solver* pSolver);

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
