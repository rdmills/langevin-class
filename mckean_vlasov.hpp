#ifndef MCKEANVLASOVHEADERDEF
#define MCKEANVLASOVHEADERDEF

struct phys_consts
    {
        double kappa1;
        // double kappa2;
    };

// Numerical options for time integrator.
// Example:
//      opts_num optsNum = {12,"Euler–Maruyama", 10, 1.0};
// struct opts_num
//     {
//         int num_steps;
//         std::string integrator;
//         int num_particles;
//         double t_max;
//     };

// Optional physics for a 1d line.
// Example:
//      opts_phys optsPhys = {{-0.5,0.5}}; 
struct opts_phys
    {
        double interval[2];  
        double (*pV1)(double, double);
        double (*pGradV1) (double, double); 
        double kappa1;
        // double (*pV2)(std::vector<double>);
        // double (*pGradV2)(std::vector<double>);
        // double kappa2;
    };    

class MckeanVlasov
{
    // The boundary value class is able to
    // access the coefficients etc. of this equation
    friend class Langevin;

private:
    // physical constants: K_BT, kappa_1, kappa_2
    double mbeta_inv;
    double mkappa1;
    // double mkappa2;
    
    // Coefficients on RHS of SDE
    double (*mV1External)(double y, double t);
    double (*mGradV1External)(double y, double t);
    // double (*mV2TwoBody)(std::vector<double> yParticles);
    // double (*mGradV2TwoBody)(std::vector<double> yParticles);

    // double (*mV2Conv)(double y);
    // double (*mGradV2Conv)(double y);
    
    // Function on RHS of SDE
    double (*mpRhsFunc)(double y, double t);

    // Interval for domain
    double mYmin;
    double mYmax;

public:
    MckeanVlasov(opts_phys phys, double (*righthandSide)(double, double));
    double EvaluateRHS(double y, double t);
   
};
#endif