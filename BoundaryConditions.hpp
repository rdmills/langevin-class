#ifndef BOUNDARYCONDITIONSHEADERDEF
#define BOUNDARYCONDITIONSHEADERDEF

class BoundaryConditions
{
public:
   // The sde value class is able to
   // access boundary conditions.
   friend class BvpSde;
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

