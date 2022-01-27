#include <cassert>
#include "BoundaryConditions.hpp"

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
