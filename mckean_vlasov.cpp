/*
    mckean_vlasov.cpp
    Langevin problem definition including definitons of potential(s).
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "mckean_vlasov.hpp"

McKeanVlasov::McKeanVlasov(opts_phys opts, 
                           double (*pGradV1)(double, double),
                           double (*pGradV2)(double),
                           double* pkappa1,
                           double* pkappa2) : SDE(opts)
{
    mGradV1External = pGradV1;
    mGradV2TwoBody = pGradV2;    
    mkappa1 = *pkappa1;
    mkappa2 = *pkappa2;
}

double* McKeanVlasov::Force(double* particles, double t)
{
    double* force = new double [mNumParticles];

    for (int j=0; j<GetNumParticles(); j++)
    {
        force[j] = -Getkappa1()*(*mGradV1External)(particles[j],t);
    }

    for (int j=0; j<GetNumParticles(); j++)
    {
        double* p_v2;
        p_v2 = new double;
        *p_v2 = 0.0;
        for (int k=0; k<GetNumParticles(); k++)
        {
            if (k!=j)
            {
                *p_v2 += (-Getkappa2())*(*mGradV2TwoBody)(particles[j]-particles[k]);
            }
            else
            {
                *p_v2 += 0.0;
            }
        }
        force[j] += *p_v2;
        delete p_v2;
    }
    return force;  
}

void McKeanVlasov::SetKappa1(double kappa1)
{
    mkappa1 = kappa1;
}

double McKeanVlasov::Getkappa1()
{
    return mkappa1;
}

void McKeanVlasov::SetKappa2(double kappa2)
{
    mkappa2 = kappa2;
}

double McKeanVlasov::Getkappa2()
{
    return mkappa2;
}

