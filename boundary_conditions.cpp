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
   mLhsBcIsNeumann = false;
   mRhsBcIsNeumann = false;
}

void BoundaryConditions::SetPeriodicBc()
{
   assert(!mRhsBcIsNeumann);
   mBcIsPeriodic = true;
}

void BoundaryConditions::SetLhsNeumannBc(double lhsDerivValue)
{
   assert(!mBcIsPeriodic);
   mLhsBcIsNeumann = true;
   mLhsBcValue = lhsDerivValue;
}

void BoundaryConditions::SetRhsNeumannBc(double rhsDerivValue)
{
   assert(!mBcIsPeriodic);
   mRhsBcIsNeumann = true;
   mRhsBcValue = rhsDerivValue;
}
