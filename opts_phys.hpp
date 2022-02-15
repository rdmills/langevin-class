#ifndef OPTS_PHYS
#define OPTS_PHYS

// Optional physics for a 1d line.
// Example:
//      opts_phys optsPhys = {{-0.5,0.5}, 1000, 1.0, 2.0, 10.0}; 
struct opts_phys
    {
        double interval[2];  
        int num_particles;
        double kappa1;
        double kappa2;
        double beta;
    };    

#endif