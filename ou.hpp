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
  
class OU : public SDE
{

private:
    double mFriction;
    double mDrift;

public:
    // Force on RHS of SDE
    virtual double* Force(double* particles, double t);

    OU(opts_phys opts, 
       double* pfriction, 
       double* pdrift);
    
};
#endif