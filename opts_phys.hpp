#ifndef OPTS_PHYS
#define OPTS_PHYS

// Optional physics for a 1d line.
// Example:
//      opts_phys optsPhys = {{-0.5,0.5}, &V1, &GradV1, 1.0}; 
struct opts_phys
    {
        double interval[2];  
        int numParticles;
        double (*pV1)(double, double);
        double (*pGradV1) (double, double); 
        double kappa1;
        // double (*pV2)(std::vector<double>);
        // double (*pGradV2)(std::vector<double>);
        // double kappa2;
    };    

#endif