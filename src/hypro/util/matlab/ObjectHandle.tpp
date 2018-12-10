/**
 * Implementation of the object handler for matlab/hypro wrapper.
 */

#include "ObjectHandle.h"

/**
 * Converts a Matlab interval into a HyPro interval
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 */
 std::vector<carl::Interval<double>>& ObjectHandle::mInterval2HyProInterval(const double* m_interval_list, const size_t& dim){
     std::vector<carl::Interval<double>> hyPro_interval_list;
     for(int i = 0; i < dim; i++){
        mxArray *m_int_ptr = m_interval_list[i];
        double *m_int = mxGetPr(m_int_ptr);    
        hyPro_interval_list.emplace_back(carl::Interval<double> interval(m_int[0], m_int[1]));
     }
    return hyPro_interval_list;
 }

/**
 * Converts a HyPro interval into a Matlab interval
 */
mxArray& ObjectHandle::hyProInterval2mInterval(std::vector<carl::Interval<double>> interval_list){
    size_t dim = interval_list.size();
    int dims[2] = {2,1};
    mxArray *m_interval_list_ptr = mxCreateNumericArray(dim, dims, mxUINT64_CLASS, mxREAL);
    double *m_interval = mxGetPr(m_interval_list_ptr);

    for(int i = 0; i < dim; i++){
        mxArray *interval_ptr = mxCreateDoubleMatrix(2,1,mxREAL);
        double *interval = mxGetPr(interval_ptr);
        //interval[0] =  TODO    
    }
}

/** 
 * Converts a Matlab matrix into a HyPro Matrix
 */
//?& ObjectHandle::mMatrix2HyProMatrix(double& matrix, const mwSize& dims){

}
/**
 * Converts a HyPro matrix into a Matlab matrix
 */
//mxArray& ObjectHandle::hyProInterval2mMatrix(double[]& matrix){

}