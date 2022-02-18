#ifndef OPTS_PHYS
#define OPTS_PHYS

// Optional physics for a 1d line.
// Example:
//      opts_phys optsPhys = {{-0.5,0.5}, 1000, 10.0}; 
struct opts_phys
    {
        double interval[2];  
        int num_particles;
        double beta;
    };    

#endif