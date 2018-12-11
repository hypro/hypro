#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <mex.h>

class ObjectHandle{
    public:
        static std::vector<carl::Interval<double>>& mIntervals2HyProIntervals(double*, int, int);
        static void hyProIntervals2mIntervals(const std::vector<carl::Interval<double>>, double*, int, int);
        static std::vector<carl::Interval<double>>& mPoints2HyProIntervals(double*);
        static carl::Interval<double>& mInterval2HyproInterval(double*);
        static carl::Interval<double>& mInterval2Point(double*); // Makas it sense?
    private:
};

/**
 * @brief Converts Matlab intervals (in form of a matrix) into a vector of HyPro intervals
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 **/
 std::vector<carl::Interval<double>>& ObjectHandle::mIntervals2HyProIntervals(double* intervals, int dimx, int dimy){
    std::vector<carl::Interval<double>> *hyPro_intervals = new std::vector<carl::Interval<double>>;
    int counter = 0;
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            hyPro_intervals->emplace_back(carl::Interval<double>(intervals[i*dimy+j], intervals[(i + 1)*dimy+j]));
        }
        i++;
    }
    return *hyPro_intervals;
 }


/**
 *  @brief Converts a single Matlab interval into a HyPro interval
 *  @param Pointer to the matlab input interval
 **/
carl::Interval<double>& ObjectHandle::mInterval2HyproInterval(double* interval){
    carl::Interval<double> *hyPro_interval = new carl::Interval<double>(interval[0], interval[1]);
    return *hyPro_interval;
}


/**
 *  @brief Converts a HyPro interval into a Matlab interval
 *  @param interval_list A list of HyPro intervals
 *  @param out A pointer to the output Matlab matrix
 *  @param dimx Number of rows
 *  @parma dimy Number of columns
 **/
void ObjectHandle::hyProIntervals2mIntervals(std::vector<carl::Interval<double>> interval_list, double *out, int dimx, int dimy){
    for(int i = 0; i < interval_list.size(); i++){
        out[i] = interval_list[i].lower();
        out[i + dimy] = interval_list[i].upper();
    }
}

/**
 *  @brief Converts a pair of points defined in matlab into hyPro intervals
 *  @param points A pointer to the input Matlab matrix
 **/
std::vector<carl::Interval<double>>& ObjectHandle::mPoints2HyProIntervals(double* points){
    std::vector<carl::Interval<double>> *hyPro_intervals = new std::vector<carl::Interval<double>>;
    hyPro_intervals->emplace_back(carl::Interval<double>(points[0], points[2]));
    hyPro_intervals->emplace_back(carl::Interval<double>(points[1], points[3]));
    return *hyPro_intervals;
}


 
 

