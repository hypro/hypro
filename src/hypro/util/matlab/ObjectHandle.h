#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <mex.h>

class ObjectHandle{
    public:
        std::vector<carl::Interval<double>>& mInterval2HyProInterval(mxArray*, int, int);
        void hyProInterval2mInterval(const std::vector<carl::Interval<double>>, double*, int, int);
        //?& mMatrix2HyProMatrix(double&, size_t&);
        //mxArray& hyProInterval2mMatrix(?);
    private:
};

/**
 * Converts a Matlab interval into a HyPro interval
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 */
 std::vector<carl::Interval<double>>& ObjectHandle::mInterval2HyProInterval(mxArray* m_intervals, int dimx, int dimy){
    std::vector<carl::Interval<double>> *hyPro_interval_list = new std::vector<carl::Interval<double>>;
    double *in = mxGetPr(m_intervals);
    int counter = 0;
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            hyPro_interval_list->emplace_back(carl::Interval<double>(in[i*dimy+j], in[(i + 1)*dimy+j]));
        }
        i++;
    }
    return *hyPro_interval_list;
 }

/**
 * Converts a HyPro interval into a Matlab interval
 */
void ObjectHandle::hyProInterval2mInterval(std::vector<carl::Interval<double>> interval_list, double *out, int dimx, int dimy){
    for(int i = 0; i < interval_list.size(); i++){
            out[i] = interval_list[i].lower();
            out[i + dimx] = interval_list[i].upper();
        }
}

