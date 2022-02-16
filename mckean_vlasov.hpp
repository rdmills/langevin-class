/*
    mckean_vlasov.hpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef MCKEANVLASOVHEADERDEF
#define MCKEANVLASOVHEADERDEF

#include "opts_phys.hpp"
#include "sde.hpp"
#include <iostream>
  
class McKeanVlasov : public SDE
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    // friend class Langevin;

private:
    // physical constants: kappa_1, kappa_2
    double mkappa1;
    double mkappa2;
    
    // Coefficients on RHS of SDE
    double (*mGradV1External)(double y, double t);
    double (*mGradV2TwoBody)(double r);

public:
    
    McKeanVlasov(opts_phys opts, 
                double (*pGradV1)(double, double), 
                double (*pGradV2)(double),
                double* pkappa1,
                double* pkappa2);

    virtual ~McKeanVlasov(){};

    void SetGradV1(double (*pGradV1)(double, double));
    void SetGradV2(double (*pGradV2)(double));

    void SetKappa1(double kappa1);
    double Getkappa1();
    
    void SetKappa2(double kappa1);
    double Getkappa2();

    virtual double* Force(double* particles, double t);
};
#endif