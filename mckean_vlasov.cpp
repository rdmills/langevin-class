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
}

double McKeanVlasov::EvaluateRHS(double y, double t)    
{
    return -(*mpRhsFunc)(y,t);
}