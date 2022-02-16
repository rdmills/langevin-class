/*
    sde.hpp
    Abstract SDE class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef SDEHEADERDEF
#define SDEHEADERDEF

#include "opts_phys.hpp"
// #include <iostream>
  
class SDE
{
protected:
    // physical constants: K_BT etc
    double mbeta;
    int mNumParticles;
    double myMinyMax [2];
    
public:
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    friend class Langevin; 

    opts_phys optsPhys; 
    void SetBeta(double beta);
    double GetBeta(); 
    void SetNumParticles(int numParticles);
    int GetNumParticles(); 
    void SetYminYmax(double interval [2]);
    double* GetYminYmax();
    void SET(double* (*pForce)(double*, double));
    virtual double* Force(double* particles, double t) = 0;
    
    SDE(opts_phys opts);
    virtual ~SDE() {};
};
#endif