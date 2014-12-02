/* 
 * File:   Visualizer.cpp
 * Author: jongan
 * 
 * Created on July 1, 2014, 6:50 PM
 */

#include "Visualizer.h"

Visualizer::Visualizer() {
    ep_ = engOpen(NULL);
    buffer[BUFFER_SIZE] = '\0';
    engOutputBuffer(ep_, buffer, BUFFER_SIZE);
}

Visualizer::Visualizer(const Visualizer& orig) {
}

Visualizer::~Visualizer() {
    engClose(ep_);
}

void Visualizer::sendVariable2Matlab(const char name[], const mxArray *var)  
{ 
    engPutVariable(ep_, name, var);  
}

void Visualizer::executeMatlabScript(const char name[]) {
    engEvalString(ep_, name);
}

mxArray * Visualizer::getVariablefromWorkspace(const char name[]) {
    return engGetVariable(ep_, name);
}

template<> Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Visualizer::mxArray2Eigen<double>(mxArray* input_mx) {
    const int rows = mxGetM(input_mx), cols = mxGetN(input_mx);
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> res(rows, cols);
    double *input_mx_ptr = mxGetPr(input_mx);
    
    for (int i=0; i< rows*cols; i++) {
        res(i) = input_mx_ptr[i];
    }
    return res;
}

template<> double Visualizer::mxArray2Scalar<double>(mxArray* input_mx) {
    const int rows = mxGetM(input_mx), cols = mxGetN(input_mx);
    if (rows*cols != 1) {
        std::cout << "ERROR: mxArray2Scalar" << std::endl;
        return -1;
    }
    else {
        double *input_mx_ptr = mxGetPr(input_mx);
        return input_mx_ptr[0];
    }
    
}

Engine * Visualizer::getEngine() {
    return ep_;
}

mxArray * Visualizer::createMatrix(int rows, int cols) {
    return mxCreateDoubleMatrix(rows, cols, mxREAL);
}

mxArray * Visualizer::createCellArray(unsigned int ndim, const unsigned long dims[]) {
    mxArray * cell = mxCreateCellArray(ndim, dims);
    return cell;
}

void Visualizer::setCellArray(mxArray * cell, mwIndex idx, mxArray *val) {
    mxSetCell(cell, idx, val);
}

template<> void Visualizer::matrix2mxArray<double>(const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& matrix, mxArray * res) {
    double * temp_ptr = mxGetPr(res);
    for (unsigned int i=0; i<matrix.rows()*matrix.cols(); i++) {
        temp_ptr[i] = matrix(i);
    }
}

//template<typename Number> 
template<> void Visualizer::draw2DZonotope<double>(mxArray * res, const Zonotope<double>& zonotope, unsigned d1, unsigned d2) {
    Zonotope<double> z2(zonotope, d1, d2);
    
    std::vector<Eigen::Matrix<double, Eigen::Dynamic, 1> >  boundaries = z2.computeZonotopeBoundary();
    res = mxCreateDoubleMatrix(2, boundaries.size(), mxREAL);
    if (res==NULL) 
        std::cout << "Problem with allocating double matrix..." << std::endl;
    double * ptr = mxGetPr(res);
    
    for (unsigned i=0; i<boundaries.size(); i++) {
        ptr[2*i] = boundaries[i](0);
        ptr[2*i+1] = boundaries[i](1);
    }
    
    for (unsigned i=0; i<boundaries.size()*2; i++) {
        std::cout << ptr[i] << ", ";
    }
    std::cout << std::endl;
}

template<> Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Visualizer::arrayVectorsToMatrix<double>(std::vector<Eigen::Matrix<double, Eigen::Dynamic,1> >& vectorArray)
{
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> result;
    result.resize(vectorArray[0].rows(), vectorArray.size());
    for (unsigned i=0; i<vectorArray.size(); i++) {
        result.col(i) = vectorArray[i];
    }
    return result;
}
