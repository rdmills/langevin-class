#ifndef INTERVALHEADERDEF
#define INTERVALCLASSHEADERDEF
#include <string>

class Interval
{
    public:
        double pts;    
        
        double y_min;
        double y_max;
        std::string polar;
    
        // double pts;
        // double diff;
        // double integral;
        // int ind;
        // double interp;
        // double conv;
        // int N;
        // std::string polar;
};

#endif