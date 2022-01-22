#include "spectral_line.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

const float PI = 3.14159;

SpectralLine::SpectralLine(int num_pts, float y_min, float y_max)
{
    yMin = y_min;
    yMax = y_max;
    N    = num_pts;
}

void SpectralLine::ChebyshevPts()
{       
    std::vector<float> theta;
    theta.resize(N);
    my_pts.resize(N);

    for(int i = 0; i < theta.size(); i++)
    {
        theta[i] = PI*float(i)/float(N);
    }

    for(int i = 0; i < my_pts.size(); i++)
    {
        my_pts[my_pts.size()-(i+1)] = cos(theta[i]);
    }
    
}
