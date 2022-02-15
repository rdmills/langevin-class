/*
    boundary_conditions.cpp
    Boundary conditions class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#include <cassert>
#include "boundary_conditions.hpp"

BoundaryConditions::BoundaryConditions()
{
   mBcIsPeriodic = false;
   mBcIsNoFlux = false;
   mBcIsNone = false;
}

void BoundaryConditions::SetNoneBc()
{
   assert(!mBcIsNoFlux);
   assert(!mBcIsPeriodic);
   mBcIsNone = true;
}

void BoundaryConditions::SetPeriodicBc()
{
   assert(!mBcIsNoFlux);
   assert(!mBcIsNone);
   mBcIsPeriodic = true;
}

void BoundaryConditions::SetNoFluxBc()
{
   assert(!mBcIsPeriodic);
   assert(!mBcIsNone);
   mBcIsNoFlux = true;
}
