#ifndef OPTS_NUM
#define OPTS_NUM

// Numerical options for time integrator.
// Example:
//      opts_num optsNum = {12, 1.0};
struct opts_num
    {   
        // int num_particles;
        int num_steps;
        double t_max;
        double* initial_data;
    };
#endif