/*
    line1d.cpp
    Line1D class for langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "langevin.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include "line1d.hpp"

// Overridden constructor inheriting Langevin base constructor.
Line1D::Line1D(opts_num opts1, opts_phys opts2) : Langevin(opts1)
{

    yMin = opts2.interval[0];
    yMax = opts2.interval[1];

    for (int i=0; i<2; i++)
    {
        myMinyMax[i]=opts2.interval[i];
    }
}

// Setter for yMinyMax.
// @param interval : array of length 2.
void Line1D::SetyMinyMax(float interval[2])
{
    for (int i=0; i<2; i++)
    {
        myMinyMax[i] = interval[i];
    }
}

// Getter for yMinyMax.
// @return : myMinyMax class member pointer.
float* Line1D::GetyMinyMax() 
{
    return myMinyMax;
}

// Initialises particle positions and puts into initParticles.
void Line1D::InitialiseParticles() 
{     
    for (int i = 0; i < initParticles.size(); i++)
    {
        initParticles[i] = yMin + float(i)*(yMax-yMin)/float(numParticles);
    }    
}

// float Langevin::dW(float dt)
// {
//   float sigma = sqrt(dt);
//   std::default_random_engine generator;
//   std::normal_distribution<double> distribution(0.0,sigma);
//   float dw = distribution(generator);
//   return dw;
// }