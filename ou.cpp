/*
    ou.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "ou.hpp"

OU::OU(opts_phys opts, 
       double* pfriction, 
       double* pdrift) : SDE(opts)
{
    mFriction = *pfriction;
    mDrift = *pdrift;
}

void OU::SetFriction(double friction)
{
    mFriction = friction;
}

double OU::GetFriction()
{
    return mFriction;
}

double OU::GetDrift()
{
    return mDrift;
}

double* OU::Force(double* particles, double t)
{
   double* force = new double [mNumParticles];

   for (int j=0; j<mNumParticles; j++)
   {
       force[j] = mFriction*(mDrift-particles[j]);
   }

   return force;
}