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
    // double (*mV2TwoBody)(std::vector<double> yParticles);
    // double (*mGradV2TwoBody)(std::vector<double> yParticles);

    // double (*mV2Conv)(double y);
    // double (*mGradV2Conv)(double y);
    
    // Function on RHS of SDE
    double (*mpRhsFunc)(double y, double t);

    // Interval for domain
    double mYmin;
    double mYmax;

public:
    McKeanVlasov(double (*righthandSide)(double, double));
    double EvaluateRHS(double y, double t);
   
};
#endif