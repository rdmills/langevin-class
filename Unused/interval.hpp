#ifndef INTERVALHEADERDEF
#define INTERVALCLASSHEADERDEF
#include <string>

class Interval
{
    public:
        float pts;    
        
        float y_min;
        float y_max;
        std::string polar;
    
        // float pts;
        // float diff;
        // float integral;
        // int ind;
        // float interp;
        // float conv;
        // int N;
        // std::string polar;
};

#endif