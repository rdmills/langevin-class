/*
    Langevin.cpp
    Langevin dynamics class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include <fstream>
#include <cassert>
#include "langevin.hpp"

Langevin::Langevin(McKeanVlasov* pSde, 
                   BoundaryConditions* pBcs, 
                   Solver* pSolver)
{
   mpMcKeanVlasov = pSde;
   mpSolver       = pSolver;
   mpBconds       = pBcs;
   mNumParticles  = mpSolver->GetNumParticles();
   
   mpTime      = new double [mpSolver->GetNumSteps()];
   mpParticles = new double* [mpSolver->GetNumSteps()];
   
   for (int i=0; i<mpSolver->GetNumSteps(); i++)
   {
      mpParticles[i]  = new double [mpSolver->GetNumParticles()];
   }
   
   optsNum   = mpSolver->optsNum;
   optsPhys  = mpMcKeanVlasov->optsPhys;
   // mOutputData = "langevin_output.dat";
}

Langevin::~Langevin()
{
   // Deletes memory allocated in constructor
   delete [] mpTime;
   for (int i=0; i<mpSolver->GetNumSteps(); i++)
   {
      delete[]  mpParticles[i];
   }
   
//    // Only delete if Solve has been called
//    if (mpLinearSystem)
//    {
//       delete mpLinearSystem;
//    }
}

void Langevin::DoStochastics()
{
   // ApplyBoundaryConditions();
   mpSolver->SolveEquation();
   
   for (int j=0; j<mpSolver->GetNumParticles(); j++)
   {
      for (int i = 0; i<mpSolver->GetNumSteps(); i++)
      {
         mpParticles[i][j] = mpSolver->mpSolution[i][j];
      }
   }
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
   // Solution data written here
   std::ofstream data_file(mOutputData.c_str());
   assert(data_file.is_open());

   for (int j=0; j<mpSolver->GetNumParticles(); j++)
   {
      for (int i=0; i<mpSolver->GetNumSteps(); i++)
      {
        data_file << mpParticles[i][j] << " ";
      }
      data_file <<"\n";
   }

   for (int i=0; i<mpSolver->GetNumSteps(); i++)
   {
      double t = mpSolver->mpTime[i];
      data_file << t <<" ";
   }

   data_file.flush();
   data_file.close();
   std::cout<<"Solution data written to "<<mOutputData<<"\n";

   // Numerical options written here
   std::ofstream num_file(mNumList.c_str());
   assert(num_file.is_open());

   num_file << mpSolver->GetTmax() << " ";
   num_file << mpSolver->GetNumSteps() << " ";
   num_file << mpSolver->GetStepSize() << " ";

   num_file.flush();
   num_file.close();
   std::cout<<"Numerical parameters written to "<<mNumList<<"\n";

   // Physical options written here
   std::ofstream phys_file(mPhysList.c_str());
   assert(phys_file.is_open());

   phys_file << mpMcKeanVlasov->GetYminYmax()[0]<< " ";
   phys_file << mpMcKeanVlasov->GetYminYmax()[1]<< " ";
   phys_file << mpMcKeanVlasov->GetNumParticles()<< " ";
   
   phys_file.flush();
   phys_file.close();
   std::cout<<"Physical parameters written to "<<mPhysList<<"\n";
}

