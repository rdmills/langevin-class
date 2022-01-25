#ifndef SPECTRALLINEHEADERDEF
#define SPECTRALLINEHEADERDEF
#include <string>
#include <vector>

class SpectralLine
{
    public:
        // properties
        int N;
        std::vector<double> my_pts;
        
        double yMin;
        double yMax;
        std::string polar;

        // methods
        SpectralLine(int num_pts, double y_min, double y_max);
        void ChebyshevPts();
        
};

#endif 