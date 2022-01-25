/*
    mckean_vlasov.cpp
    Entry point for running langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include "langevin.hpp"
#include "line1d.hpp"

const double PI = 3.14159265359;

double V1Quad(double y)
{
    return 0.5*y*y;
}

double GradV1Quad(double y)
{
    return y;
}

double V2Gauss(double r, double a)
{
    return 0.5/sqrt(PI*a*a)*exp(-0.5*r*r/(a*a));
}

double GradV2Gauss(double r, double a)
{
    return -0.5/sqrt(PI*a*a)*r/(a*a)*exp(-0.5*r*r/(a*a));
}

int main(int argc, char* argv[])
{
    // Choose numerical and physical options.
    struct opts_num optsNum   = {12,"Euler–Maruyama", 10, 1.0};
    struct opts_phys optsPhys = {{-0.5,0.5}, 
                                &V1Quad, 
                                &GradV1Quad,
                                1.0, 
                                &V2Gauss, 
                                &GradV2Gauss,
                                1.0};

    // Make a 1d line.
    Line1D aLine(optsNum,optsPhys);

    std::cout<<"V1 : 0.5*y*y @y=3.0 =  "<<(*aLine.optsPhys.pV1)(3.0)<<std::endl;
    std::cout<<"yMin = "<<*(aLine.GetyMinyMax()+1)<<std::endl;
    std::cout<<"Integrator type = "<<aLine.GetIntegrator()<<std::endl;

    aLine.GenerateNoiseVector();
    aLine.PrintNoiseVector();


    // Langevin pl(optsNum);

    // pl.InitialUniformParticles();

    // for (int i = 0; i < pl.particles.size(); i++)
    // {
    //     for (int j = 0; j < pl.particles[i].size(); j++)
    //     {
    //         pl.particles[i][j] = 1.0;
    //     }   
    // }

    // for (int i = 0; i < pl.particles.size(); i++)
    //     {
    //         for (int j = 0; j < pl.particles[i].size(); j++)
    //         {
    //             std::cout << pl.particles[i][j] << " ";
    //         }   
    //         std::cout << std::endl;
    //     }


    // std::cout << pl.dW(0.1);
    // std::cout << pl.dW(0.1);


    return 0;
}