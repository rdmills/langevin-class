/*
    langevin.hpp
    Langevin abstract class for langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef LANGEVINHEADERDEF
#define LANGEVINHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>

// Numerical options for time integrator.
// Example:
//      struct opts_num optsNum = {12,"Euler–Maruyama", 10, 1.0};
struct opts_num
    {
        int num_steps;
        std::string integrator;
        int num_particles;
        float t_max;
    };

// Abstract Langevin base class.
class Langevin
{
    public:
    // properties
        int numParticles;
        std::vector<float> initParticles;
        std::vector< std::vector<float> > particles; 
        
        float tMax;
        float numSteps;
        float dt;

        opts_num optsNum;
    
    // construction
        Langevin(opts_num opts1);
    
    // methods  
        void SetIntegrator(std::string integrator);
        std::string GetIntegrator() const;
        virtual void InitialiseParticles() = 0; // dynamic binding

    protected:
    // properties
        std::string mIntegratorType;
    
};

#endif 