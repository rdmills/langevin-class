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
   mLhsBcIsNeumann = false;
   mRhsBcIsNeumann = false;
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

void BoundaryConditions::SetLhsNeumannBc(double lhsDerivValue)
{
   assert(!mBcIsPeriodic);
   assert(!mBcIsNoFlux);
   assert(!mBcIsNone);
   mLhsBcIsNeumann = true;
   mLhsBcValue = lhsDerivValue;
}

void BoundaryConditions::SetRhsNeumannBc(double rhsDerivValue)
{
   assert(!mBcIsPeriodic);
   assert(!mBcIsNoFlux);
   assert(!mBcIsNone);
   mRhsBcIsNeumann = true;
   mRhsBcValue = rhsDerivValue;
}
