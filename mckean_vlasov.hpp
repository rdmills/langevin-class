#ifndef MCKEANVLASOVHEADERDEF
#define MCKEANVLASOVHEADERDEF

struct phys_consts
{
    double beta_inv;
    double kappa1;
    double kappa2;
};

class MckeanVlasov
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    friend class Solver;
private:
    // physical constants: K_BT, kappa_1, kappa_2
    double mbeta_inv;
    double mkappa1;
    double mkappa2;
    
    // Coefficients on RHS of SDE
    double (*mV1External)(double y);
    double (*mV2TwoBody)(double y, double yPrime);
    
    // Function on RHS of SDE
    double (*mpRhsFunc)(double y);

    // Interval for domain
    double mYmin;
    double mYmax;

public:
    MckeanVlasov(phys_consts phys, double (*pV1)(double), double (*pV2)(double,double), 
                  double (*righthandSide)(double),
                  double yMinimum, double yMaximum)
   {
        mbeta_inv = phys.beta_inv;       
        mkappa1 = phys.kappa1;       
        mkappa2 = phys.kappa2;       
        mV1External = pV1;
        mV2TwoBody = pV2;
        mpRhsFunc = righthandSide;
        mYmin = yMinimum;
        mYmax = yMaximum;
   }
};
#endif