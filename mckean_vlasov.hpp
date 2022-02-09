/*
    mckean_vlasov.hpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef MCKEANVLASOVHEADERDEF
#define MCKEANVLASOVHEADERDEF

#include "opts_phys.hpp"
  
class McKeanVlasov
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    friend class Langevin;

private:
    // physical constants: K_BT, kappa_1, kappa_2
    double mbeta_inv;
    double mkappa1;
    // double mkappa2;
    
    // Coefficients on RHS of SDE
    double (*mV1External)(double y, double t);
    double (*mGradV1External)(double y, double t);
    
    double (*mpRhsFunc)(double y, double t);
    int mNumParticles;
    double myMinyMax [2];   

public:
    McKeanVlasov(opts_phys opts, double (*righthandSide)(double, double));
    double EvaluateRHS(double y, double t);
    double* GetYminYmax(); 
    int GetNumParticles(); 
    opts_phys optsPhys;
};
#endif