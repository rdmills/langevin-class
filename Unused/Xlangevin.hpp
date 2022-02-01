/*
    langevin.hpp
    Langevin abstract class for langevin dynamics.
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
        double t_max;
    };

// Abstract Langevin base class.
class Langevin
{
    public:
    // properties
        int numParticles;
        std::vector<double> initParticles;
        std::vector< std::vector<double> > particles; 
        
        double tMax;
        double numSteps;
        double dt;

        opts_num optsNum;
    
    // construction
        Langevin(opts_num opts1);
    
    // methods  
        void SetIntegrator(std::string integrator);
        std::string GetIntegrator() const;
        
        virtual void InitialiseParticles() = 0; // dynamic binding
        
        virtual void DoLangevin() = 0;
        virtual void GenerateNoiseVector() = 0;
        virtual void PrintNoiseVector() = 0;

    protected:
    // properties
        std::string mIntegratorType;
    
};

#endif 