/*
    ou.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "ou.hpp"

OU::OU(opts_phys opts, 
       double* pfriction,
       double* pdrift)
{
    optsPhys = opts;
    
    mFriction = *pfriction;
    mDrift = *pdrift;
    
    mbeta = opts.beta;
    myMinyMax[0] = opts.interval[0];
    myMinyMax[1] = opts.interval[1];
    mNumParticles = opts.num_particles;  
}

double* OU::Force(double* particles, double t)
{
   double* force = new double [mNumParticles];

   for (int j=0; j<mNumParticles; j++)
   {
       force[j] = -mFriction*(mDrift-particles[j]);
   }

   return force;
}