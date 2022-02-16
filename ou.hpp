/*
    ou.hpp
    Ornstein-Uhlenbeck class definition.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef OUHEADERDEF
#define OUHEADERDEF

#include "opts_phys.hpp"
#include "sde.hpp"
#include <iostream>
  
class OU : public SDE
{

private:
    // physical constants
    double mFriction;
    double mDrift;

    // // Coefficients on RHS of SDE
    // double (*Friction)(double y);
    // double (*mDrift)(double y);

public:
    
    OU(opts_phys opts, 
       double* pFriction,
       double* pDrift);

    void SetFriction(double friction);
    void SetDrift(double drift);

    double GetFriction();
    double GetDrift();

    virtual ~OU(){};

    // Force on RHS of SDE
    virtual double* Force(double* particles, double t);
    
};
#endif

