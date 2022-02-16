/*
    langevin_sde.hpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef LANGEVINSDEHEADERDEF
#define LANGEVINSDEHEADERDEF

#include "opts_phys.hpp"
#include "sde.hpp"
#include <iostream>
  
class LangevinSDE : public SDE
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    // friend class Langevin;

private:
    // physical constants: kappa_1
    double mkappa1;
    
    // Coefficients on RHS of SDE
    double (*mGradV1External)(double y, double t);

public:
    
    LangevinSDE(opts_phys opts, 
                double (*pGradV1)(double, double), 
                double* pkappa1);

    virtual ~LangevinSDE(){};

    void SetGradV1(double (*pGradV1)(double, double));

    void SetKappa1(double kappa1);
    double Getkappa1();

    virtual double* Force(double* particles, double t);
};
#endif