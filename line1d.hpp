/*
    line1d.hpp
    Line1D class for langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef LINE1DHEADERDEF
#define LINE1DHEADERDEF
#include <string>
#include <vector>
#include <random>
#include <math.h>
#include "langevin.hpp"

// Optional physics for a 1d line.
// Example:
//      struct opts_phys optsPhys = {{-0.5,0.5}}; 
struct opts_phys
    {
        float interval[2];    
    };

// Child class Line1D for langevin dynamics on an interval.
class Line1D : public Langevin
{       
    public: 
        float yMin;
        float yMax;

        Line1D(opts_num opts1, opts_phys opts2);
        void SetyMinyMax(float interval[2]);
        float* GetyMinyMax();
        virtual void InitialiseParticles();
    
    private:
        float myMinyMax [2];    
};

#endif