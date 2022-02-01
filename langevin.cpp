#include <iostream>
#include <fstream>
#include <cassert>
#include "langevin.hpp"

Langevin::Langevin(MckeanVlasov* pSde, 
                   BoundaryConditions* pBcs, 
                   Solver* pSolver, 
                   int numParticles,
                   opts_num opts)
{
   mpMckeanVlasov = pSde;
   
   mpSolver = pSolver;

   mpBconds = pBcs;

   mNumParticles = numParticles;
   
   mpSolVec = new std::vector<double>;
   mpRhsVec = new std::vector<double>;

   mFilename = "ode_output.dat";
}

Langevin::~Langevin()
{
   // Deletes memory allocated in constructor
   delete mpSolVec;
   delete mpRhsVec;
   // delete mpSolver;
   
//    // Only delete if Solve has been called
//    if (mpLinearSystem)
//    {
//       delete mpLinearSystem;
//    }
}

void Langevin::DoStochastics()
{
//    PopulateMatrix();
//    PopulateVector();
   ApplyBoundaryConditions();
//    mpLinearSystem = new LinearSystem(*mpLhsMat, *mpRhsVec);
//    *mpSolVec = mpLinearSystem->Solve();
   WriteSolutionFile();
}

// void BvpOde::PopulateMatrix()
// {
//    for (int i=1; i<mNumNodes-1; i++)
//    {
//       // xm, x and xp are  x(i-1), x(i) and x(i+1) 
//       double xm = mpGrid->mNodes[i-1].coordinate;
//       double x = mpGrid->mNodes[i].coordinate;
//       double xp = mpGrid->mNodes[i+1].coordinate;
//       double alpha = 2.0/(xp-xm)/(x-xm);
//       double beta = -2.0/(xp-x)/(x-xm);
//       double gamma = 2.0/(xp-xm)/(xp-x);
//       (*mpLhsMat)(i+1,i) = (mpOde->mCoeffOfUxx)*alpha - 
//                       (mpOde->mCoeffOfUx)/(xp-xm);
//       (*mpLhsMat)(i+1,i+1) = (mpOde->mCoeffOfUxx)*beta + 
//                         mpOde->mCoeffOfU;
//       (*mpLhsMat)(i+1,i+2) = (mpOde->mCoeffOfUxx)*gamma + 
//                         (mpOde->mCoeffOfUx)/(xp-xm);
//    }
// }

// void BvpOde::PopulateVector()
// {
//    for (int i=1; i<mNumNodes-1; i++)
//    {
//       double x = mpGrid->mNodes[i].coordinate;
//       (*mpRhsVec)(i+1) = mpOde->mpRhsFunc(x);
//    }
// }

void Langevin::ApplyBoundaryConditions()
{
//    bool left_bc_applied = false;
//    bool right_bc_applied = false;

//    if (mpBconds->mLhsBcIsDirichlet)
//    {
//       (*mpLhsMat)(1,1) = 1.0;
//       (*mpRhsVec)(1) = mpBconds->mLhsBcValue;
//       left_bc_applied = true;
//    }

//    if (mpBconds->mRhsBcIsDirichlet)
//    {
//       (*mpLhsMat)(mNumNodes,mNumNodes) = 1.0;
//       (*mpRhsVec)(mNumNodes) = mpBconds->mRhsBcValue;
//       right_bc_applied = true;
//    }

//    if (mpBconds->mLhsBcIsNeumann)
//    {
//       assert(left_bc_applied == false);
//       double h = mpGrid->mNodes[1].coordinate - 
//                  mpGrid->mNodes[0].coordinate;
//       (*mpLhsMat)(1,1) = -1.0/h;
//       (*mpLhsMat)(1,2) = 1.0/h;
//       (*mpRhsVec)(1) = mpBconds->mLhsBcValue;
//       left_bc_applied = true;
//    }

//    if (mpBconds->mRhsBcIsNeumann)
//    {
//       assert(right_bc_applied == false);
//       double h = mpGrid->mNodes[mNumNodes-1].coordinate - 
//                  mpGrid->mNodes[mNumNodes-2].coordinate;
//       (*mpLhsMat)(mNumNodes,mNumNodes-1) = -1.0/h;
//       (*mpLhsMat)(mNumNodes,mNumNodes) = 1.0/h;
//       (*mpRhsVec)(mNumNodes) = mpBconds->mRhsBcValue;
//       right_bc_applied = true;
//    }

//    // Check that boundary conditions have been applied
//    // on both boundaries
//    assert(left_bc_applied);
//    assert(right_bc_applied);
}

void Langevin::WriteSolutionFile()
{
//    std::ofstream output_file(mFilename.c_str());
//    assert(output_file.is_open());
//    for (int i=0; i<mNumNodes; i++)
//    {
//       double x = mpGrid->mNodes[i].coordinate;
//       output_file << x << "  " << (*mpSolVec)(i+1) << "\n";
//    }
//    output_file.flush();
//    output_file.close();
//    std::cout<<"Solution written to "<<mFilename<<"\n";
}

