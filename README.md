# langevin-class

Optimised Langevin dynamics class capable of simulating the meanfield dynamics of high dimensional particle systems, subject to complex many body interactions.

Capable of simulating McKean SDEs:

```C++
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double XI = 0.5;
const double ALPHA = 0.5; 

double GradV2Gauss(double r){return -1/(XI*XI)*r*exp(-0.5*r*r/(XI*XI));}

double* Hat(double* yInit, int numParticles)
        {
            double* initialData;
            initialData = new double [numParticles]; 
            double hatMin = ALPHA*yInit[0];
            double hatMax = ALPHA*yInit[1];
            initialData[0] = hatMin;
            
            for (int i=1; i<numParticles; i++)
            {
                initialData[i] = initialData[i-1] + (hatMax-hatMin)/numParticles;
            }
            return initialData;
        }   

int main(int argc, char* argv[])
{
    int numParticles = 1000;
    double tMax = 2.0;  
    int numSteps = 2000;
    double yMin = -2, yMax = 2;    

    double kappa1 = 1.0;
    double kappa2 = 0.5;

    opts_phys optsPhys = {.interval = {yMin, yMax}, 
                          .num_particles = numParticles,
                          .beta = 10.0};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax};   

    SDE* p_test = new McKeanVlasov(optsPhys, Zero1, GradV2Gauss, &kappa1, &kappa2);
    
    Langevin pl(&optsNum, p_test, Hat, "no_flux");    
    
    pl.SetFilename("mkv_gauss_data.dat", "mkv_gauss_num.dat", "mkv_gauss_phys.dat");
    pl.DoStochastics();

    delete p_test;
    return 0;
}
```

And simple(r) Langevin systems, e.g., Ornstein-Uhlenbeck processes:

```C++
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double ALPHA = 0.5; 

double* Hat(double* yInit, int numParticles)
        {
            double* initialData;
            initialData = new double [numParticles]; 
            double hatMin = ALPHA*yInit[0];
            double hatMax = ALPHA*yInit[1];
            initialData[0] = hatMin;
            
            for (int i=1; i<numParticles; i++)
            {
                initialData[i] = initialData[i-1] + (hatMax-hatMin)/numParticles;
            }
            return initialData;
        }

int main(int argc, char* argv[])
{
    int numParticles = 1000;
    double tMax = 2.0;  
    int numSteps = 2000;
    double yMin = -2, yMax = 2;    

    double theta = 1.0;
    double mu = -1.0;

    opts_phys optsPhys = {.interval = {yMin, yMax}, 
                          .num_particles = numParticles,
                          .beta = 10.0};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax};   

    SDE* p_test = new OU(optsPhys, &theta, &mu);
    
    Langevin pl(&optsNum, p_test, Hat, "no_flux");    
    
    pl.SetFilename("ou_data.dat", "ou_num.dat", "ou_phys.dat");
    pl.DoStochastics();

    delete p_test;
    return 0;
}
```

# Notes

Supports periodic and no-flux boundary conditions.
