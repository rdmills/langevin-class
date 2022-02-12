/*
    mckean_vlasov.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

McKeanVlasov::McKeanVlasov(opts_phys opts, 
                           double (*pGradV1)(double, double),
                           double (*pGradV2)(double))
{
    mGradV1External = pGradV1;
    mGradV2TwoBody = pGradV2;
    optsPhys = opts;
    myMinyMax[0] = opts.interval[0];
    myMinyMax[1] = opts.interval[1];
    mNumParticles = opts.numParticles;
//    std::cout<<"mNumParticles = "<<mNumParticles<<std::endl;
    
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