/*
    mckean_vlasov.cpp
    McKean_Vlasov class for langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

MckeanVlasov::MckeanVlasov(opts_phys phys, double (*righthandSide)(double, double))
{
    mkappa1 = phys.kappa1;       
    // mkappa2 = phys.kappa2;       
    mV1External = phys.pV1;
    mGradV1External = phys.pGradV1;
    // mV2TwoBody = phys.pV2;
    // mGradV2TwoBody = phys.pGradV2;
    
    mpRhsFunc = mGradV1External;
    // mpRhsFunc = -(mkappa1*mGradV1External + mkappa2*mGradV2TwoBody);
    
    mYmin = phys.interval[0];
    mYmax = phys.interval[1];
}

double MckeanVlasov::EvaluateRHS(double y, double t)    
{
    return -(*mpRhsFunc)(y,t);
}