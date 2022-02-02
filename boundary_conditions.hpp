/*
    boundary_conditions.hpp
    Boundary conditions class.
    @author Rory Mills-Williams
    @version 1.0 20/01/2022
*/

#ifndef BOUNDARYCONDITIONSHEADERDEF
#define BOUNDARYCONDITIONSHEADERDEF

class BoundaryConditions
{
public:
   // The sde value class is able to
   // access boundary conditions.
   friend class Langevin;
private:
   bool mBcIsPeriodic;
   bool mLhsBcIsNeumann;
   bool mRhsBcIsNeumann;
   double mLhsBcValue;
   double mRhsBcValue;
public:
   BoundaryConditions();
   void SetPeriodicBc();
   void SetLhsNeumannBc(double lhsDerivValue);
   void SetRhsNeumannBc(double rhsDerivValue);
};

#endif

