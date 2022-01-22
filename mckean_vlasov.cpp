/*
    mckean_vlasov.cpp
    Entry point for running langevin dynamics on a finite interval.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <iostream>
#include "langevin.hpp"
#include "line1d.hpp"

int main(int argc, char* argv[])
{
    // Choose numerical and physical options.
    struct opts_num optsNum   = {12,"Euler–Maruyama", 10, 1.0};
    struct opts_phys optsPhys = {{-0.5,0.5}};

    // Make a 1d line.
    Line1D aLine(optsNum,optsPhys);

    std::cout<<*(aLine.GetyMinyMax()+1)<<std::endl;
    std::cout<<aLine.GetIntegrator()<<std::endl;

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