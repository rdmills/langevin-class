/*
    langevin.cpp
    Langevin abstract class for langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "langevin.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

Langevin::Langevin(opts_num opts1)
{
    optsNum = opts1;

    numSteps       = opts1.num_steps;
    tMax           = opts1.t_max;
    dt             = tMax/numSteps;
    this->SetIntegrator(opts1.integrator);
    numParticles   = opts1.num_particles;
    

    initParticles.resize(numParticles);
    particles.resize(numParticles);

    for (int i=0; i < particles.size(); i++)
    {
        particles[i].resize(numSteps);
    }
}

void Langevin::SetIntegrator(std::string integrator)
{
    mIntegratorType = integrator;
}

std::string Langevin::GetIntegrator() const
{
    return mIntegratorType;
}