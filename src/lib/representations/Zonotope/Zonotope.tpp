#include "Zonotope.h"
#include <assert.h>
#include <Eigen/src/Core/PlainObjectBase.h>



template <typename Number>
Zonotope<Number>::Zonotope() : mDimension(0)
{
}

template <typename Number>
Zonotope<Number>::Zonotope(unsigned int dimension) {
    assert(dimension!=0);
    mDimension = dimension;
}

template <typename Number>
Zonotope<Number>::Zonotope(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center, 
                            const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators) {
    assert(center.rows()==generators.rows());
    mDimension = center.rows();
    mCenter = center;
    mGenerators = generators;
}

template <typename Number>
Zonotope<Number>::~Zonotope() {

}




template <typename Number>
unsigned int Zonotope<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
bool Zonotope<Number>::minkowskiSum(Zonotope<Number>& result, const Zonotope<Number>& rhs) {
    assert(mDimension==rhs.dimension());
    
    result.mCenter = this->mCenter + rhs.mCenter;
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmp;
    tmp.resize(mDimension, rhs.numGenerators()+this->numGenerators());
    tmp << this->mGenerators, rhs.getGenerators();
    result.setGenerators(tmp);
    return true;
    
}

template <typename Number>
bool Zonotope<Number>::linearTransformation(Zonotope<Number>& result, const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A) {
    assert(A.rows()==mDimension);
    
    result.mCenter = A*this->mCenter;
    result.mGenerators = A*this->mGenerators;
    return true;
    
}

template <typename Number>
bool Zonotope<Number>::intersect(Zonotope<Number>& result, const Hyperplane<Number>& hp) {
    assert(hp.dimension()==mDimension);
    
    // Determine if intersection is found, according to Girard, Guernic, 2008
    Number emdc = hp.getEValue()-hp.getDVector().transpose()*mCenter;
    Number zs = (hp.getDVector().transpose()*mGenerators).array().abs().sum();
    
    bool hasIntersect = (emdc > -zs && zs > emdc);
    if (hasIntersect) {
        // Determine intersect as Zonotope, according to Tabatabaeipour et al., 2013 
        Number sgm = 0; // could be redundant
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> H = mGenerators;
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> HHT = H*H.transpose();
        
        Eigen::Matrix<Number, Eigen::Dynamic, 1> lambda = (HHT*hp.getDVector())/(hp.getDVector().transpose()*HHT*hp.getDVector()+sgm*sgm);
        
        Zonotope<Number> zg(mDimension);

        zg.setCenter(mCenter+lambda*(hp.getEValue()-hp.getDVector().transpose()*mCenter));  
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> new_gen, identity;

        identity.resize(mDimension, mDimension);

        identity.setIdentity();

        
        new_gen =(identity - lambda*(hp.getDVector().transpose()))*H;    
        zg.setGenerators(new_gen);
        
        result = zg;
        return true;
    }
    else {
        return false;
    }
}

template <typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, 1> Zonotope<Number>::getCenter() const  {
    return mCenter;
}

template <typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> Zonotope<Number>::getGenerators() const {
    return mGenerators;
}



template <typename Number>
void Zonotope<Number>::setCenter(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center) {
    if (mDimension==0) {
        mDimension = center.rows();
    }
    assert(center.rows()==mDimension);
    mCenter = center;
}

template <typename Number>
void Zonotope<Number>::setGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& new_generators) {
    if (mDimension==0) {
        mDimension = new_generators.rows();
    }
    assert(new_generators.rows()==mDimension);
    mGenerators = new_generators;
}

template <typename Number>
bool Zonotope<Number>::addGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators) {
    if (mDimension==0) {
        mDimension = generators.rows();
    }
    
    assert(generators.rows()==mDimension);
    if (mGenerators.rows()!=generators.rows()) {
        this->setGenerators(generators);
    }
    else {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmp = mGenerators;
        mGenerators.resize(tmp.rows(), generators.cols()+tmp.cols());
        mGenerators << tmp, generators;
    }
    return true;
}

template <typename Number>
unsigned int Zonotope<Number>::numGenerators() const {
    return mGenerators.cols();
}




template <typename Number>
void Zonotope<Number>::removeGenerator(unsigned int colToRemove) {
    unsigned int numRows = mGenerators.rows();
    unsigned int numCols = mGenerators.cols()-1;

    if( colToRemove < numCols )
        mGenerators.block(0,colToRemove,numRows,numCols-colToRemove) = mGenerators.block(0,colToRemove+1,numRows,numCols-colToRemove);

    mGenerators.conservativeResize(numRows,numCols);
}

template <typename Number>
void Zonotope<Number>::removeEmptyGenerators() {
// TODO
    Eigen::Matrix<Number, Eigen::Dynamic, 1> zero_vector; 
    zero_vector.resize(mDimension,1);
    zero_vector.setZero();
    
    std::vector<unsigned int> zeroIndex;
    for (unsigned int i=0; i<mGenerators.cols(); i++) {
        if(mGenerators.col(i)==zero_vector) {
            zeroIndex.push_back(i);
        }
    }

    for (std::vector<unsigned int>::reverse_iterator rit = zeroIndex.rbegin(); rit!=zeroIndex.rend(); ++rit) {
        removeGenerator(*rit);
    }
}

template <typename Number>
bool Zonotope<Number>::changeDimension(unsigned int new_dim) {
    assert(new_dim!=0);
    if(new_dim==mDimension) {
        return false;
    }
    else {
        mCenter.conservativeResize(new_dim, Eigen::NoChange);
        mGenerators.conservativeResize(new_dim, Eigen::NoChange);
        
        // If new dim > old dim, initialize all new rows to zero
        for (unsigned int i=mDimension; i<new_dim; i++) {
            mCenter.row(i).setZero();
            mGenerators.row(i).setZero();
        }
        
        mDimension = new_dim;
        return true;
    }
}
