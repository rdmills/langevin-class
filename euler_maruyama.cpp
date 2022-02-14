/*
    euler_maryuama.cpp
    EulerMaruyama class for integrating langevin equation.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include "solver.hpp"
#include "euler_maruyama.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

EulerMaruyama::EulerMaruyama(opts_num opts1, BoundaryConditions* pBcs, int numParticles)
{
    optsNum = opts1;
    mpBconds = pBcs;
    // mGradV1 = righthandside;

    SetInitialData(optsNum.initial_data);
    SetNumSteps(optsNum.num_steps);
    SetTmax(optsNum.t_max);

    double dt = optsNum.t_max/optsNum.num_steps;
    SetStepSize(dt);
    SetNumParticles(numParticles);
    
    mpTime = new double [GetNumSteps()];
    mpSolutionStateNow = new double [GetNumSteps()];
    mpSolution = new double* [GetNumSteps()];
    for(int i = 0; i< GetNumSteps(); i++)
    {
        mpSolution[i] = new double [GetNumSteps()];
    }

    double sigma = sqrt(dt);
    std::normal_distribution<double> distribution (0.0, sigma);
    mDistribution = distribution;
}

int EulerMaruyama::DiracDelta(int i, int j)
{
    if (i==j)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// double EulerMaruyama::TwoBody(double* pParticles)
// {
//     double v2 = 0.0;
    
//     for (int i=0; i<GetNumParticles(); i++)
//     {
//         for (int j=0; j<GetNumParticles(); j++)
//             {
//                 if (i!=j)
//                 {
//                     double r = abs(pParticles[i]-pParticles[j]);
//                     v2 += 
//                 }
//             }

//     }
// }

double EulerMaruyama::RightHandSide(double y, double t)
{
    // return -(*mRhs)(y,t);
    return -Getkappa1()*(*mGradV1)(y,t);
}

double EulerMaruyama::GetWiener()
{
    return mDistribution(mGenerator);
}

// void EulerMaruyama::SolveEquation()
// {
//     double dt = GetStepSize();

//     mpTime[0] = 0.0; 

//     for (int i=1; i<GetNumSteps(); i++)
//     {
//         mpTime[i] = mpTime[i-1] + dt;
//     }
    
//     for (int j=0; j<GetNumParticles(); j++)
//     {
//         mpSolution[0][j] = GetInitialData()[j];
//     }

//     for (int i=1; i<GetNumSteps(); i++)
//     {
//         for (int j=0; j<GetNumParticles(); j++)    
//         {

//             mpSolution[i][j] = mpSolution[i-1][j] 
//                              + dt*RightHandSide(mpSolution[i-1][j],mpTime[i-1])
//                              + sqrt(2.0*GetBetaInv())*GetWiener();
//             mpSolution[i][j] = ApplyBoundaryConditions(mpSolution[i][j]);
//             // std::cout<<"mpSolution["<<i<<"]"<<"["<<j<<"] = "<< mpSolution[i][j]<<std::endl;
//         }
//     }
    
// }

double* EulerMaruyama::test(double* state, double t)
{
    double* force;
    force = new double [GetNumParticles()];
    for (int j=0; j<GetNumParticles(); j++)
    {
        force[j] = -Getkappa1()*(*mGradV1)(state[j],t);
        // std::cout<< "force["<<j<<"] = "<<force[j]<<std::endl;
    }

    double** v2;
    v2 = new double* [GetNumParticles()];
    for (int k = 0; k< GetNumParticles(); k++)
    {
        v2[k] = new double [GetNumParticles()];
    }

    for (int j=0; j<GetNumParticles(); j++)
    {
        for (int k=0; k<GetNumParticles(); k++)
        {
            if (k!=j)
            {
                // v2[j][k] = 1/float(GetNumParticles())
                //          *(-Getkappa2())*(*mGradV2)(state[j]-state[k]);
                v2[j][k] = (-Getkappa2())*(*mGradV2)(state[j]-state[k]);
            }
            else
            {
                v2[j][k] = 0.0;
            }
        }
    }

    double sum;
    
    for (int j=0; j<GetNumParticles(); j++)
    {
        sum = 0.0;
        for (int k=0; k<GetNumParticles(); k++)
        {
            sum = sum + v2[j][k];
        }
        force[j] = force[j] + sum;
        // std::cout<< "force["<<j<<"] = "<<force[j]<<std::endl;
    }

    for (int k = 0; k< GetNumParticles(); k++)
    {
        delete[] v2[k];
    }
    delete[] v2;

    // for (int j=0; j<GetNumParticles(); j++)
    // {
    //     std::cout<< "force["<<j<<"] = "<<force[j]<<std::endl;
    // }

    return force;
}

void EulerMaruyama::SolveEquation()
{
    double dt = GetStepSize();

    mpTime[0] = 0.0; 

    for (int i=1; i<GetNumSteps(); i++)
    {
        mpTime[i] = mpTime[i-1] + dt;
    }
    
    for (int j=0; j<GetNumParticles(); j++)
    {
        mpSolution[0][j] = GetInitialData()[j];
        mpSolutionStateNow[j] = mpSolution[0][j];
    }

    for (int i=1; i<GetNumSteps(); i++)
    {
        double* f = test(mpSolutionStateNow,mpTime[i-1]);
        for (int j=0; j<GetNumParticles(); j++)    
        {
            mpSolution[i][j] = mpSolution[i-1][j]
                             + dt*f[j]
                             + sqrt(2.0*GetBetaInv())*GetWiener();
            
            mpSolution[i][j] = ApplyBoundaryConditions(mpSolution[i][j]);
            // std::cout<<"mpSolution["<<i<<"]"<<"["<<j<<"] = "<< mpSolution[i][j]<<std::endl;
        }
        delete[] f;
        for (int j=0; j<GetNumParticles(); j++)
        {
            mpSolutionStateNow[j] = mpSolution[i][j];
        }
    }
    
}

double EulerMaruyama::ApplyBoundaryConditions(double particle)
{
    // std::cout<<"mpBconds->mBcIsPeriodic : "<<mpBconds->mBcIsPeriodic<<std::endl;
    if (mpBconds->mBcIsPeriodic)
    {
        if(particle<yMinyMax[0])
        {
            return yMinyMax[1] - (yMinyMax[0]-particle);
        }
        else if(particle>yMinyMax[1])
        {
            return yMinyMax[0] + (particle-yMinyMax[1]);
        }
        else 
        {
            return particle;
        }
    }

    if (mpBconds->mBcIsNoFlux)
    {
        if(particle<yMinyMax[0])
        {
            return yMinyMax[0] + (yMinyMax[0]-particle);
        }
        else if(particle>yMinyMax[1])
        {
            return yMinyMax[1] - (particle-yMinyMax[1]);
        }
        else 
        {
            return particle;
        }
    }

    else
    {
        return particle;
    }
}