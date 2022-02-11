/*
    mckean_vlasov.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

McKeanVlasov::McKeanVlasov(opts_phys opts, 
                           double (*pV1)(double, double),
                           double (*pV2)(double))
{
    mGradV1External = pV1;
    mGradV2TwoBody = pV2;
    optsPhys = opts;
    myMinyMax[0] = opts.interval[0];
    myMinyMax[1] = opts.interval[1];
    mNumParticles = opts.numParticles;
}

double McKeanVlasov::EvaluateRHS(double y, double t)    
{
    return -(*mGradV1External)(y,t);
}

void McKeanVlasov::SetNumParticles(int numParticles)
{
    mNumParticles = numParticles;   
}

int McKeanVlasov::GetNumParticles()
{
    return mNumParticles;
}

void McKeanVlasov::SetYminYmax(double interval[2])
{
    myMinyMax[0] = interval[0];
    myMinyMax[1] = interval[1];
}

double* McKeanVlasov::GetYminYmax()
{
    return myMinyMax;
}