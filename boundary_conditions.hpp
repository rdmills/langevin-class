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
   friend class Solver;
protected:
   bool mBcIsPeriodic;
   bool mBcIsNoFlux;
   bool mBcIsNone;
public:
   BoundaryConditions();
   void SetPeriodicBc();
   void SetNoFluxBc();
   void SetNoneBc();
};

#endif

