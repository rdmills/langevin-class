#ifndef BVPSDEHEADERDEF
#define BVPSDEHEADERDEF

#include <string>
#include <vector>
#include "mckean_vlasov.hpp"
#include "solver.hpp"
#include "BoundaryConditions.hpp"

// struct phys_consts
// {
//     double beta_inv;
//     double gamma;
//     double mass;
// };

// Optional physics for a 1d line.
// Example:
//      struct opts_phys optsPhys = {{-0.5,0.5}}; 
// struct opts_phys
//     {
//         double interval[2];  
//         double (*pV1)(double);
//         double (*pGradV1) (double); 
//         double kappa1;
//         double (*pV2)(double, double);
//         double (*pGradV2)(double, double);
//         double kappa2;
//     };

// Numerical options for time integrator.
// Example:
//      struct opts_num optsNum = {12,"Euler–Maruyama", 10, 1.0};
struct opts_num
    {
        int num_steps;
        std::string integrator;
        int num_particles;
        double t_max;
    };    

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
   MckeanVlasov* mpMckeanVlasov;

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
   Langevin(MckeanVlasov* pSde, 
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
