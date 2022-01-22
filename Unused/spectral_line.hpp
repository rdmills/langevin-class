#ifndef SPECTRALLINEHEADERDEF
#define SPECTRALLINEHEADERDEF
#include <string>
#include <vector>

class SpectralLine
{
    public:
        // properties
        int N;
        std::vector<float> my_pts;
        
        float yMin;
        float yMax;
        std::string polar;

        // methods
        SpectralLine(int num_pts, float y_min, float y_max);
        void ChebyshevPts();
        
};

#endif 