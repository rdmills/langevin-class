/*
    mckean_vlasov.hpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef SDEHEADERDEF
#define SDEHEADERDEF

#include "opts_phys.hpp"
// #include <iostream>
  
class SDE
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    friend class Langevin;

private:
    // physical constants: K_BT, kappa_1, kappa_2
    double mbeta_inv;
    double mkappa1;
    // double mkappa2;
    
    // Force on RHS of SDE
    double (*mForce)(double* particles, double t);
    
    int mNumParticles;
    double myMinyMax [2];   

public:
    opts_phys optsPhys; 
    void SetYminYmax(double interval [2]);
    double* GetYminYmax(); 
    void SetNumParticles(int numParticles);
    int GetNumParticles(); 
    
};
#endif