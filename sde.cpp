/*
    sde.cpp
    Abstract SDE class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "sde.hpp"

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