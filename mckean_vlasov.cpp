/*
    mckean_vlasov.cpp
    McKean_Vlasov class for langevin dynamics.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

McKeanVlasov::McKeanVlasov(double (*righthandSide)(double, double))
{
    mpRhsFunc = mGradV1External;
}

double McKeanVlasov::EvaluateRHS(double y, double t)    
{
    return -(*mpRhsFunc)(y,t);
}