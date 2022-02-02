#ifndef BVPSDEHEADERDEF
#define BVPSDEHEADERDEF

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
   std::vector<double>* mpSolVec;

   // Right-hand side vector
   std::vector<double>* mpRhsVec;

   // Allow user to specify the output file or
   // use a default name
   std::string mFilename;

   // // Methods for setting up linear system and solving it
   // void PopulateVector();
   void ApplyBoundaryConditions();

public:
   // Sole constructor
   Langevin(McKeanVlasov* pSde, 
            BoundaryConditions* pBcs, 
            Solver* pSolver,
            int numParticles);

   // As memory is dynamically allocated the destructor
   // is overridden
   ~Langevin();

   void SetFilename(const std::string& name)
   {
      mFilename = name;
   }
   void DoStochastics();
   void WriteSolutionFile();
};

#endif
