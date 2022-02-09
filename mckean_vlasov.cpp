/*
    mckean_vlasov.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

McKeanVlasov::McKeanVlasov(opts_phys opts, double (*righthandside)(double, double))
{
    mpRhsFunc = righthandside;
    optsPhys = opts;
    myMinyMax[0] = opts.interval[0];
    myMinyMax[1] = opts.interval[1];
    mNumParticles = opts.numParticles;
}

double McKeanVlasov::EvaluateRHS(double y, double t)    
{
    return -(*mpRhsFunc)(y,t);
}

int McKeanVlasov::GetNumParticles()
{
    return mNumParticles;
}

double* McKeanVlasov::GetYminYmax()
{
    return myMinyMax;
}