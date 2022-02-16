/*
    sde.cpp
    Abstract SDE class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "sde.hpp"

SDE::SDE(opts_phys opts)
{
    optsPhys = opts;
    mbeta = opts.beta;
    myMinyMax[0] = opts.interval[0];
    myMinyMax[1] = opts.interval[1];
    mNumParticles = opts.num_particles;  
}

void SDE::SetNumParticles(int numParticles)
{
    mNumParticles = numParticles;   
}

int SDE::GetNumParticles()
{
    return mNumParticles;
}

void SDE::SetYminYmax(double interval[2])
{
    myMinyMax[0] = interval[0];
    myMinyMax[1] = interval[1];
}

double* SDE::GetYminYmax()
{
    return myMinyMax;
}

void SDE::SetBeta(double beta)
{
    mbeta = beta;   
}

double SDE::GetBeta()
{
    return mbeta;
}