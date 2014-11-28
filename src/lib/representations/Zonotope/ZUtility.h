/* 
 * File:   Utility.h
 * Author: jongan
 *
 * Created on October 27, 2014, 11:53 AM
 */

#ifndef UTILITY_H
#define	UTILITY_H

#include <eigen3/Eigen/Dense>
#include <cmath>

namespace ZUtility {
// Options for checking for intersect
    typedef enum {
        ALAMO = 1,
        NDPROJECTION = 2,
        DICHOTOMIC2D = 3
    } IntersectionMethod_t;

    // Structure for Options used in running reachability analysis
    struct Options {
        IntersectionMethod_t intersectMethod;
        int testCase;
    };

    template<typename Number>
    bool compareVectors(Eigen::Matrix<Number, Eigen::Dynamic, 1> v1, Eigen::Matrix<Number, Eigen::Dynamic, 1> v2) {
        Number v1_sum = v1.array().abs().matrix().sum();
        Number v2_sum = v2.array().abs().matrix().sum();
        Number v1_inf = v1.array().abs().maxCoeff();
        Number v2_inf = v2.array().abs().maxCoeff();

        return (v1_sum-v1_inf) < (v2_sum-v2_inf);
    }




    template <typename Number>
    bool compareColumnVectors(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec1, 
                              const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec2) 
    {
        Number x1(colvec1(0)), x2(colvec2(0)), y1(colvec1(1)), y2(colvec2(1));

        Number ang1 = x1/sqrt(pow(x1,2) + pow(y1,2));
        Number ang2 = x2/sqrt(pow(x2,2) + pow(y2,2));

        return (ang1 < ang2);
    }

    template <typename Number> 
    bool compareYVal(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec1, 
                     const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec2)
    {
        return (colvec1(1) < colvec2(1));
    }

    template<typename Number>
    bool compareXVal(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec1, 
                     const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec2)
    {
        return (colvec1(0) < colvec2(0));
    }


    template <typename Number>
    struct Line_t {
        Line_t() {};
        Line_t(Eigen::Matrix<Number, 2,1> pt_,
             Eigen::Matrix<Number, 2,1> direction_) 
        {
            point = pt_;
            direction = direction_;
        }

        Eigen::Matrix<Number, 2,1> point;
        Eigen::Matrix<Number, 2,1> direction;
    };

}


#endif	/* UTILITY_H */

