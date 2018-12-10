#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <mex.h>

class ObjectHandle{
    public:
        std::vector<carl::Interval<double>>& mInterval2HyProInterval(const double*, int);
        mxArray& hyProInterval2mInterval(const std::vector<carl::Interval<double>>);
        //?& mMatrix2HyProMatrix(double&, size_t&);
        //mxArray& hyProInterval2mMatrix(?);
    private:
};

/**
 * Converts a Matlab interval into a HyPro interval
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 */
 std::vector<carl::Interval<double>>& ObjectHandle::mInterval2HyProInterval(const double* interval_list, int dim){
     std::vector<carl::Interval<double>> hyPro_interval_list;

     for(int i = 0; i < dim; i++){
        double lower = interval_list[i];
        double upper = interval_list[i+1];
        i++;
        hyPro_interval_list.emplace_back(carl::Interval<double>(lower, upper));
     }
    return hyPro_interval_list;
 }

/**
 * Converts a HyPro interval into a Matlab interval
 */
mxArray& ObjectHandle::hyProInterval2mInterval(std::vector<carl::Interval<double>> interval_list){
    // Create the output array for the interval list
    const size_t rows = interval_list.size();
    const size_t cols = 2;
    mxArray *m_interval_list_ptr = mxCreateDoubleMatrix((mwSize) rows, (mwSize) cols, mxREAL);
    double *m_interval = mxGetPr(m_interval_list_ptr);

    for(int i = 0; i < rows; i++){
        m_interval[i] = interval_list[i].lower();
        m_interval[i+1] = interval_list[i].upper();
        i++;
    }
   // return m_interval_list_ptr;
}

