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
#include <algorithm>

Langevin::Langevin(opts_num* pOpts,
                   SDE* pSde, 
                   double* (*pInitialData)(double*, int),
                   std::string BC)
{
   mpInitialData  = pInitialData;
   optsNum        = *pOpts;
   mpSDE = pSde;
   mBConds        = BC;
   mNumParticles  = mpSDE->GetNumParticles();
   
   mpTime      = new double [optsNum.num_steps];
   mpParticles = new double* [optsNum.num_steps];
   
   for (int i=0; i<optsNum.num_steps; i++)
   {
      mpParticles[i]  = new double [mpSDE->GetNumParticles()];
   }
   optsPhys  = mpSDE->optsPhys;
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
   BoundaryConditions bc;

   if (mBConds == "periodic")
   {
      bc.SetPeriodicBc();
      mpSolver = new EulerMaruyama(optsNum, &bc, mpSDE->GetNumParticles());
   }
   else if (mBConds == "no_flux")
   {
      bc.SetNoFluxBc();
      mpSolver = new EulerMaruyama(optsNum, &bc, mpSDE->GetNumParticles());

   }
   else if (mBConds == "none")
   {
      bc.SetNoneBc();
      mpSolver = new EulerMaruyama(optsNum, &bc, mpSDE->GetNumParticles());
   }

   if (!mpSolver)
   {
      std::cout<<"Solver with BC = "<< mBConds<<" unavailable."<<std::endl;
   }
   assert(mpSolver);
   
   std::cout<<"Made new Langevin solver with BC = "<<mBConds<< "."<<std::endl;

   SetSDE();
   SetConstants();
   SetInitialData();

   time_t tstart, tend; 
   std::cout<<"Sampling dynamics..."<<std::endl;
   tstart = time(0);
   mpSolver->SolveEquation();
   tend = time(0); 
   std::cout<<"\n...done."<<std::endl;
   std::cout<<"Computation time : "<< difftime(tend, tstart) <<" second(s)."<< std::endl;
   
   for (int i = 0; i<mpSolver->GetNumSteps(); i++)
   {
      for (int j=0; j<mpSolver->GetNumParticles(); j++)   
      {
         mpParticles[i][j] = mpSolver->mpSolution[i][j];
         // std::cout<<"mpParticles["<<i<<"]"<<"["<<j<<"] = "<< mpParticles[i][j]<<std::endl;
      }
   }
   
   std::cout<<"******************"<<std::endl;
   std::cout<<"Writing data to file "<<mOutputData<<"..."<<std::endl;
   WriteSolutionFile();
   std::cout<<"...done"<<std::endl;
   std::cout<<"******************"<<std::endl;
}

void Langevin::SetSDE()
{
   mpSolver->SetSDE(mpSDE);
}

void Langevin::SetConstants()
{
   mpSolver->SetBetaInv(1/float(mpSDE->mbeta));
   mpSolver->SetYMinYMax(mpSDE->myMinyMax);
}

void Langevin::SetInitialData()
{
   double* initial_data = mpInitialData(optsPhys.interval, mNumParticles);
   
   double* min = std::min_element( initial_data, initial_data + mNumParticles );
   double* max = std::max_element( initial_data, initial_data + mNumParticles );
   
   if (!(optsPhys.interval[0] < *min && *max < optsPhys.interval[1]))
   {
      std::cout<<"Particles initialised outside of finite domain:"<<std::endl;
      std::cout<<"y_init_min = "<<*min<<std::endl;
      std::cout<<"y_init_max = "<<*max<<std::endl;
   }
   
   assert(optsPhys.interval[0] < *min && *max < optsPhys.interval[1]);
   
   mpSolver->SetInitialData(initial_data);
   delete[] initial_data;
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

   phys_file << mpSDE->GetYminYmax()[0]<< " ";
   phys_file << mpSDE->GetYminYmax()[1]<< " ";
   phys_file << mpSDE->GetNumParticles()<< " ";
   
   phys_file.flush();
   phys_file.close();
   std::cout<<"Physical parameters written to "<<mPhysList<<"\n";
}

