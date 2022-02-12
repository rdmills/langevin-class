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
#include <cmath>
#include <ctime>

Langevin::Langevin(opts_num* pOpts,
                   McKeanVlasov* pSde, 
                   BoundaryConditions* pBcs)
{
   optsNum        = *pOpts;
   mpMcKeanVlasov = pSde;
   mpBconds       = pBcs;
   mNumParticles  = mpMcKeanVlasov->GetNumParticles();

   mpTime      = new double [optsNum.num_steps];
   mpParticles = new double* [optsNum.num_steps];
   
   for (int i=0; i<optsNum.num_steps; i++)
   {
      mpParticles[i]  = new double [mpMcKeanVlasov->GetNumParticles()];
   }
   optsPhys  = mpMcKeanVlasov->optsPhys;
}

Langevin::~Langevin()
{
   // Deletes memory allocated in constructor
   delete [] mpTime;
   for (int i=0; i<optsNum.num_steps; i++)
   {
      delete[]  mpParticles[i];
   }
   
   // Only delete if DoStochastics() has been called
   if (mpSolver)
   {
      delete mpSolver;
   }
}

void Langevin::DoStochastics()
{
   // ApplyBoundaryConditions();
   // mpSolver = new EulerMaruyama(optsNum, optsPhys, mpMcKeanVlasov->mGradV1External);
   mpSolver = new EulerMaruyama(optsNum, optsPhys);
   SetCoefficients();

   time_t tstart, tend; 
   std::cout<<"Sampling dynamics..."<<std::endl;
   tstart = time(0);
   mpSolver->SolveEquation();
   tend = time(0); 
   std::cout<<"...done."<<std::endl;
   std::cout<<"Computation time : "<< difftime(tend, tstart) <<" second(s)."<< std::endl;
   
   for (int j=0; j<mpSolver->GetNumParticles(); j++)
   {
      for (int i = 0; i<mpSolver->GetNumSteps(); i++)
      {
         mpParticles[i][j] = mpSolver->mpSolution[i][j];
         // std::cout<<"mpParticles["<<i<<"]"<<"["<<j<<"] = "<< mpParticles[i][j]<<std::endl;
      }
   }
   
   std::cout<<"*********"<<std::endl;
   std::cout<<"Writing data to file "<<mOutputData<<"..."<<std::endl;
   WriteSolutionFile();
   std::cout<<"...done"<<std::endl;
   std::cout<<"*********"<<std::endl;
}

void Langevin::SetCoefficients()
{
   mpSolver->SetGradV1(mpMcKeanVlasov->mGradV1External);
   // for (int i=1; i<mNumNodes-1; i++)
   // {
   //    // xm, x and xp are  x(i-1), x(i) and x(i+1) 
   //    double xm = mpGrid->mNodes[i-1].coordinate;
   //    double x = mpGrid->mNodes[i].coordinate;
   //    double xp = mpGrid->mNodes[i+1].coordinate;
   //    double alpha = 2.0/(xp-xm)/(x-xm);
   //    double beta = -2.0/(xp-x)/(x-xm);
   //    double gamma = 2.0/(xp-xm)/(xp-x);
   //    (*mpLhsMat)(i+1,i) = (mpOde->mCoeffOfUxx)*alpha - 
   //                    (mpOde->mCoeffOfUx)/(xp-xm);
   //    (*mpLhsMat)(i+1,i+1) = (mpOde->mCoeffOfUxx)*beta + 
   //                      mpOde->mCoeffOfU;
   //    (*mpLhsMat)(i+1,i+2) = (mpOde->mCoeffOfUxx)*gamma + 
   //                      (mpOde->mCoeffOfUx)/(xp-xm);
   // }
}

void Langevin::SetConstants()
{
   // for (int i=1; i<mNumNodes-1; i++)
   // {
   //    double x = mpGrid->mNodes[i].coordinate;
   //    (*mpRhsVec)(i+1) = mpOde->mpRhsFunc(x);
   // }
}

void Langevin::ApplyBoundaryConditions()
{

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
   num_file << mpSolver->GetInitialData() << " ";

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

