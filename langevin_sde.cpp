/*
    langevin_sde.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "langevin_sde.hpp"

LangevinSDE::LangevinSDE(opts_phys opts, 
                           double (*pGradV1)(double, double),
                           double* pkappa1) : SDE(opts)
{
    mGradV1External = pGradV1;
    mkappa1 = *pkappa1;
}

double* LangevinSDE::Force(double* particles, double t)
{
    double* force = new double [mNumParticles];

    for (int j=0; j<GetNumParticles(); j++)
    {
        force[j] = -Getkappa1()*(*mGradV1External)(particles[j],t);
    }
    return force;  
}

void LangevinSDE::SetKappa1(double kappa1)
{
    mkappa1 = kappa1;
}

double LangevinSDE::Getkappa1()
{
    return mkappa1;
}

