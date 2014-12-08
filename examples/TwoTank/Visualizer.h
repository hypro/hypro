/* 
 * File:   Visualizer.h
 * Author: jongan
 *
 * Created on July 1, 2014, 6:50 PM
 */

#ifndef VISUALIZER_H
#define	VISUALIZER_H
#define BUFFER_SIZE 2048

#include "engine.h"
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <sstream>
#include <iostream>
#include "../../src/lib/representations/Zonotope/Zonotope.h"
#include "../../src/lib/algorithms/reachability/util.h"

template <typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> zonotope2Matrix(const Zonotope<Number>& z) {
    hypro::vector_t<Number> zcenter = z.center();
    hypro::matrix_t<Number> zgenerators = z.generators();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> center = hypro::convertVecToDouble(zcenter);
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generator_matrix = hypro::convertMatToDouble(zgenerators);
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> res;
    res.resize(center.rows(), generator_matrix.cols()+1);
    res << center, generator_matrix;
    return res;
}

class Visualizer {
public:
    Visualizer();
    Visualizer(const Visualizer& orig);
    virtual ~Visualizer();
    
    char buffer[BUFFER_SIZE+1];
    
    void sendVariable2Matlab(const char name[], const mxArray *var);
    
    void executeMatlabScript(const char name[]);
    
    mxArray * getVariablefromWorkspace(const char name[]);
    
    template<typename T>
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> mxArray2Eigen(mxArray* input_mx);
    
    template<typename T>
    T mxArray2Scalar(mxArray* input_mx);
    
    mxArray * createMatrix(int rows, int cols);
    
    mxArray * createCellArray(unsigned int ndim, const unsigned long dims[]);
    
    void setCellArray(mxArray *cell, mwIndex idx, mxArray *val);
    
    template <typename T>
    void matrix2mxArray(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& matrix, mxArray * res);
    
    template <typename Number>
    void draw2DZonotope(mxArray * res, const Zonotope<Number>& zonotope, unsigned d1, unsigned d2);
    
    template <typename Number>
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> arrayVectorsToMatrix(std::vector<Eigen::Matrix<Number, Eigen::Dynamic,1> >& vectorArray);
    
    Engine * getEngine();
    
private:
    Engine *ep_;
    
    
};

#endif	/* VISUALIZER_H */

