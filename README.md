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
                initialData[i] = initialData[i-1] + (hatMax-hatMin)/numParticles;![CodeCogsEqn](https://user-images.githubusercontent.com/28300876/154377967-afa2d347-82ab-4cf2-af9c-7e256473ae6c.svg)

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
![mk_gauss](https://user-images.githubusercontent.com/28300876/154377050-fcd849d1-d485-44f0-899a-6710b514b5b3.gif)


And general Langevin systems, e.g., diffusion in a multi-well potential: 

![langevin](https://user-images.githubusercontent.com/28300876/154381585-09cdaac4-5122-463c-8a12-d9b0fc2fc026.svg)

And Ornstein-Uhlenbeck processes:

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

![ou](https://user-images.githubusercontent.com/28300876/154378720-5797bdd4-3605-42e9-b778-dd926990ec4c.gif)

![lsde](https://user-images.githubusercontent.com/28300876/154381326-cb9feaee-652e-4e83-a1ee-ae37b53f9b6c.gif)

# Notes

- Supports periodic and no-flux boundary conditions.

- Abstracted numerical solver.
