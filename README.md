# langevin-class

Optimised Langevin dynamics class capable of simulating the meanfield dynamics of high dimensional particle systems, subject to complex many body interactions.

Capable of simulating McKean SDEs:

![CodeCogsEqn](https://user-images.githubusercontent.com/28300876/154377984-c0008ce5-9b50-4450-b82b-271cdda54f87.svg)


```C++
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double XI = 0.5;
const double ALPHA = 0.5; 

double Zero1(double y, double t){return 0.0;}

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
    int numParticles = 2000;
    double tMax = 2.0;  
    int numSteps = 1000;
    double yMin = -2, yMax = 2;    

    double kappa1 = 1.0;
    double kappa2 = 0.1;

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

![mkv_gauss](https://user-images.githubusercontent.com/28300876/154768181-9eb58013-c64e-4d4d-86d8-ab7d381d47ba.gif)

as well as general Langevin systems, e.g., particles subject to one body forces: 

![langevin](https://user-images.githubusercontent.com/28300876/154381585-09cdaac4-5122-463c-8a12-d9b0fc2fc026.svg)

in particular, Ornstein-Uhlenbeck processes:

![ou](https://user-images.githubusercontent.com/28300876/154378187-4ea06cd5-482a-4596-8a21-fba6841baabc.svg)


```C++
#include "langevin.hpp"
#include "opts_num.hpp"
#include "opts_phys.hpp"

const double XI = 0.5;
const double ALPHA = 0.5; 

double GradV1Quart(double y, double t){return 1.0*(0.4*y*y*y/(XI*XI*XI)-1.0*y/XI);}

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
    int numParticles = 2000;
    double tMax = 2.0;  
    int numSteps = 1000;
    double yMin = -2, yMax = 2;    

    double theta = 6.0;
    double mu = -1.0;
    double kappa1 = 10.0;


    opts_phys optsPhys = {.interval = {yMin, yMax}, 
                          .num_particles = numParticles,
                          .beta = 10.0};                          

    opts_num optsNum = {.num_steps = numSteps, 
                        .t_max = tMax};   

    SDE* p_test = new OU(optsPhys, &theta, &mu);
    Langevin pl1(&optsNum, p_test, Hat, "no_flux");    
    pl.SetFilename("ou_data.dat", "ou_num.dat", "ou_phys.dat");
    pl.DoStochastics();
    delete p_test;
    
    SDE* p_test = new LangevinSDE(optsPhys, GradV1Quart, &kappa1);
    Langevin pl2(&optsNum, p_test, Hat, "no_flux");    
    pl.SetFilename("lsde_data.dat", "lsde_num.dat", "lsde_phys.dat");
    pl.DoStochastics();
    delete p_test;
    
    return 0;
}
```

![lsde](https://user-images.githubusercontent.com/28300876/154767507-cedfbcad-b8d9-43c3-a6df-6d270aaf5e12.gif)

![ou](https://user-images.githubusercontent.com/28300876/154768785-29c2a617-9aa4-405f-b1c2-cbf91a171dac.gif)

# Notes

- Supports periodic and no-flux boundary conditions.

- Supports an abstracted solver for different numerical schemes, e.g. Euler-Maruyama, Order 1.5 Strong Taylor Scheme etc. (see, e.g., Kloeden, P.E., Platen, E. and Schurz, H., 2012. Numerical solution of SDE through computer experiments. Springer Science & Business Media.)
