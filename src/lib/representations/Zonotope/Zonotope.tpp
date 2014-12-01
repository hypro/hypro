#include "Zonotope.h"
#include <assert.h>
#include <Eigen/src/Core/PlainObjectBase.h>
#include <Eigen/LU>
#include <cmath>
#include <algorithm>


using namespace Parma_Polyhedra_Library;


/*****************************************************************************
 *                                                                           *
 *                          Non-member functions                             *                             
 *                                                                           *
 *****************************************************************************/

template <typename Number> 
bool comparePoint(Eigen::Matrix<Number, 2, 1>& p1, Eigen::Matrix<Number, 2, 1>& p2) {
    if (p1(0)!=p2(0))
        return (p1(0) < p2(0));
    else 
        return (p1(1) < p2(1));
}

template <typename Number>
void removeGenerator(unsigned int colToRemove, 
                    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& matrix) 
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;
    assert(matrix.cols()>1 && "cannot remove a generator from a one-generator generator");
    if( colToRemove < numCols ) {
        assert(numCols-colToRemove > 0);
        assert(numCols-colToRemove > 0);
        assert(colToRemove+1 <= matrix.cols() - 1);
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);
    }

    matrix.conservativeResize(Eigen::NoChange, numCols);
}

template <typename Number>
void removeEmptyGenerators(Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generatorMatrix)  {
    unsigned dim = generatorMatrix.rows();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> zero_vector; 
    zero_vector.resize(dim,1);
    zero_vector.setZero();
    
    std::vector<unsigned int> zeroIndex;
    for (unsigned int i=0; i<generatorMatrix.cols(); i++) {
        if(generatorMatrix.col(i)==zero_vector) {
            zeroIndex.push_back(i);
        }
    }

    for (std::vector<unsigned int>::reverse_iterator rit = zeroIndex.rbegin(); rit!=zeroIndex.rend(); ++rit) {
        removeGenerator<Number>(*rit, generatorMatrix);
    }
}

template <typename Number>
Eigen::Matrix<Number, 2, 1> computeLineIntersection(const ZUtility::Line_t<Number>& l1, const ZUtility::Line_t<Number>& l2) {
    Eigen::Matrix<Number,2,2> concatDirections;
    Eigen::Matrix<Number,2,1> a, resPt;
    
    concatDirections << l1.direction, -l2.direction;
    a = concatDirections.inverse()*(l2.point - l1.point);
    resPt = l1.point + a(0)*l1.direction;
    return resPt;
}



/*****************************************************************************
 *                                                                           *
 *            `         Member functions - Constructors                      *                             
 *                                                                           *
 *****************************************************************************/

template <typename Number>
Zonotope<Number>::Zonotope() : mDimension(0), mCenter(0,1), mGenerators(0,0)
{
}

template <typename Number>
Zonotope<Number>::Zonotope(unsigned int dimension) {
    assert(dimension!=0 && "Zonotope cannot have dimension 0.");
    mDimension = dimension;
    mCenter.resize(mDimension,1);
    mCenter.setZero();
    mGenerators.resize(mDimension,1);
    mGenerators.setZero();
}

template <typename Number>
Zonotope<Number>::Zonotope(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center, 
                            const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators) {
    assert(center.rows()==generators.rows() && "Center and generators have to have same dimensionality.");
    mDimension = center.rows();
    mCenter = center;
    mGenerators = generators;
}

template <typename Number>
Zonotope<Number>::Zonotope(const Zonotope<Number>& other) {
    assert(other.mDimension!=0 && "Cannot copy an empty zonotope (dimension=0).");
    mDimension = other.mDimension;
    mCenter = other.mCenter;
    mGenerators = other.mGenerators;
}


template <typename Number>
Zonotope<Number>::Zonotope(const Zonotope<Number>& other, unsigned d1, unsigned d2) {
    assert(other.mDimension!=0 && d1 >= 0 && d1 < other.mDimension && d2 >= 0 && d1 < other.mDimension && d1!=d2 &&
            "d1 and d2 have to be in range of copied zonotope.");
    
    
    Eigen::Matrix<Number, 2, 1> center;
    Eigen::Matrix<Number, 2, Eigen::Dynamic> generators;
    center = {other.center()(d1), other.center()(d2)};
    
    generators.resize(Eigen::NoChange, other.numGenerators());
    generators << other.generators().row(d1), other.generators().row(d2);
    
    mDimension = 2;
    mCenter = center;
    mGenerators = generators;
}

template <typename Number>
Zonotope<Number>::~Zonotope() {

}


/*****************************************************************************
 *                                                                           *
 *      Member functions - Getters, Setters and non-algorithm functions      *                             
 *                                                                           *
 *****************************************************************************/


template <typename Number>
unsigned int Zonotope<Number>::dimension() const {
	return mDimension;
}

template <typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, 1> Zonotope<Number>::center() const  {
    return mCenter;
}

template <typename Number>
Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> Zonotope<Number>::generators() const {
    return mGenerators;
}



template <typename Number>
void Zonotope<Number>::setCenter(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& center) {
    if (mDimension==0) {
        mDimension = center.rows();
        mGenerators.resize(mDimension,1);
        mGenerators.setZero();
    }
    assert(center.rows()==mDimension && "Center has to have same dimensionality as zonotope.");
    mCenter = center;
}

template <typename Number>
void Zonotope<Number>::setGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& new_generators) {
    if (mDimension==0) {
        mDimension = new_generators.rows();
        mCenter.resize(mDimension,1);
        mCenter.setZero();
    }
    assert(new_generators.rows()==mDimension && "Generators have to have same dimensionality as zonotope");
    mGenerators = new_generators;
}

template <typename Number>
bool Zonotope<Number>::addGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& generators) {
    if (mDimension==0) {
        mDimension = generators.rows();
    }
    
    assert(generators.rows()==mDimension && "Added generators has to have same dimensionality as zonotope");
    if (mGenerators.rows()!=generators.rows()) {
        setGenerators(generators);
    }
    else {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmp = mGenerators;
        mGenerators.resize(tmp.rows(), generators.cols()+tmp.cols());
        mGenerators << tmp, generators;
    }
    removeEmptyGenerators();
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
    assert(new_dim!=0 && "Cannot change dimensionality of zonotope to zero") ;
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

template <typename Number>
void Zonotope<Number>::clear() {
    mGenerators.resize(0,0);
    mCenter.resize(0,1);
    mDimension = 0;
}


/*****************************************************************************
*                                                                           *
*                           Algorithm Functions                             *                             
*                                                                           *
*****************************************************************************/


template <typename Number>
bool Zonotope<Number>::minkowskiSum(Zonotope<Number>& result, const Zonotope<Number>& rhs) {
    assert(mDimension==rhs.dimension() && "Zonotope on RHS must have same dimensionality as current.");
    
    result.setCenter(this->mCenter + rhs.mCenter);
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> tmp;
    tmp.resize(mDimension, rhs.numGenerators()+numGenerators());
    tmp << mGenerators, rhs.generators();
    result.setGenerators(tmp);
    result.removeEmptyGenerators();
    return true;
    
}

template <typename Number>
bool Zonotope<Number>::linearTransformation(Zonotope<Number>& result, const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A) {
    assert(A.cols()==mCenter.rows() && "Matrix's dimensionality is different from zonotope's center's dimensionality.");
    assert(A.cols()==mGenerators.rows() && "Matrix's dimensionality is different from zonotope's generators' dimensionality.");
    
    result.setCenter(A*this->mCenter);
    result.setGenerators(A*this->mGenerators);
    
    return true;
    
}

template <typename Number>
std::vector< Eigen::Matrix<Number, Eigen::Dynamic,1> > Zonotope<Number>::computeZonotopeBoundary() {
    assert(mDimension==2 && "Computing Zonotope boundaries only possible for Dim 2");
    
    this->removeEmptyGenerators();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generators = this->mGenerators;
    
    unsigned i;
    std::vector< Eigen::Matrix<Number, Eigen::Dynamic,1> > sortArray, verticesArray;
    
    
    // Reflect generators if y-value is negative
    Eigen::Matrix<Number, 1, Eigen::Dynamic> yValsRow = generators.row(1); 
    
    for (i=0; i<yValsRow.cols(); i++) {
        if (yValsRow(i) < 0) {
            generators.col(i) = -1*generators.col(i);
        }
    }
    
    
    // Sort generators


    for (i=0; i<generators.cols(); i++) {
        sortArray.push_back(generators.col(i));
    }
    
    std::sort(sortArray.begin(), sortArray.end(), ZUtility::compareColumnVectors<Number>);
    
    Eigen::Matrix<Number, Eigen::Dynamic,1> pm = mCenter - generators.rowwise().sum();
    
    verticesArray.push_back(pm);
    
    // Finding vertices of Zonotope
    for (i=0; i<sortArray.size(); i++) {
        verticesArray.push_back(verticesArray.back() + 2*sortArray[i]);
    }
    for (i=0; i<sortArray.size(); i++) {
        verticesArray.push_back(verticesArray.back() - 2*sortArray[i]);
    }
    
    return verticesArray;
}

template <typename Number>
Number intersect2d(const Zonotope<Number>& input, const Hyperplane<Number>& hp, int minOrMax) {
    assert(input.dimension() == hp.dimension() && input.dimension() == 2 && "zonotope dimension must be of same dimension (only dim 2 accepted) as hyperplane");
    unsigned numGenerators = input.numGenerators();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> g1, g2, generators = input.generators();
    Eigen::Matrix<Number, 2, 1> s, s1, pmNext, pm = input.center();
    
    for (unsigned i=0; i<numGenerators; i++) {
        if ((generators(1,i) > 0 || (generators(1,i) == 0 && generators(0,i) > 0)) && minOrMax == 1) 
            generators.col(i) = -1*generators.col(i);
        else if ((generators(1,i) < 0 || (generators(1,i) == 0 && generators(0,i) < 0)) && minOrMax == 0)
            generators.col(i) = -1*generators.col(i);
        
        pm = pm - generators.col(i);
    }
    
    std::vector<unsigned> indexToRemove;
    if (pm(0) <= hp.scalar()) {
        for (unsigned i=0; i<generators.cols(); i++) {
            if (generators.col(i)(0) <= 0) 
                indexToRemove.push_back(i);
        }
    }
    else {
        for (unsigned i=0; i<generators.cols(); i++) {
            if (generators.col(i)(0) >= 0) 
                indexToRemove.push_back(i);
        }
    }
    

    for (std::vector<unsigned>::reverse_iterator rit = indexToRemove.rbegin(); rit!=indexToRemove.rend(); ++rit) {
        removeGenerator<Number>(*rit, generators);
    }
    
    s = 2*generators.rowwise().sum();
        
    std::vector<unsigned> idx_a1, idx_a2;
    while (generators.cols() > 1) {
        
        // collecting indices to delete
        for (unsigned i=0; i<generators.cols(); i++) {
            Number angle = atan(generators(1,i)/generators(0,i));
            if (angle - atan(s(1)/s(0)) <= 0) 
                idx_a1.push_back(i);
            else if (angle - atan(s(1)/s(0)) >= 0) 
                idx_a2.push_back(i);
        }
        
        // clear generators of certain rows
        for (std::vector<unsigned>::reverse_iterator rit = idx_a1.rbegin(); rit!=idx_a1.rend(); ++rit) {
            g1 = generators;
            removeGenerator<Number>(*rit, g1);
        }
        for (std::vector<unsigned>::reverse_iterator rit = idx_a2.rbegin(); rit!=idx_a2.rend(); ++rit) {
            g2 = generators;
            removeGenerator<Number>(*rit, g2);
        }
        
        
        if (pm(0) < hp.scalar()) 
            s1 = (minOrMax==1) ? 2*g1.rowwise().sum() : 2*g2.rowwise().sum();
           
        else
            s1 = (minOrMax==1) ? 2*g2.rowwise().sum() : 2*g1.rowwise().sum();
        
        pmNext = pm + s1;
        if ((pm(0) <= hp.scalar() &&  pmNext(0) >= hp.scalar()) || (pm(0) >= hp.scalar() && pmNext(0) <= hp.scalar())) {
            generators = (minOrMax==1) ? g2 : g1;
            s = s1;
        }
        else {
            generators = (minOrMax==1) ? g1 : g2;
            s = s - s1;
            pm = pmNext;
        }
    }
    pmNext = pm + s;
    Number m = pm(1) + (hp.scalar()-pm(0)) * (pmNext(1)-pm(1))/(pmNext(0)-pm(0));
    return m;
    
}

template<typename Number> 
void intersectZonogoneHyperplaneDSearch(Zonotope<Number>& inputZonotope,
                                             const Hyperplane<Number>& hp,
                                             Zonotope<Number>& result)
{
    assert(inputZonotope.dimension() == hp.dimension() && inputZonotope.dimension() == 2 && 
            "zonotope dimension must be of same dimension (only dim 2 accepted) as hyperplane");
    Number p1 = intersect2d<Number>(inputZonotope, hp, 1);
    Eigen::Matrix<Number, 2, 1> p1Vec = {0, p1};
    Number p2 = intersect2d<Number>(inputZonotope, hp, 0);
    Eigen::Matrix<Number, 2, 1> p2Vec = {0, p2};
    
    Zonotope<Number> res((p1Vec+p2Vec)/2, (p1Vec-p2Vec)/2);
    result = res;
}

template <typename Number>
void intersectZonogoneHyperplane(Zonotope<Number>& inputZonotope,
                                             const Hyperplane<Number>& hp,
                                             Zonotope<Number>& result,
                                             Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& minMaxOfLine) 
{
    assert(inputZonotope.dimension()==hp.dimension() && "Zonotope and Hyperplane have to be of similar dimensions");
    std::vector< Eigen::Matrix<Number, Eigen::Dynamic ,1> > vertices = inputZonotope.computeZonotopeBoundary();
    vertices.pop_back();
    
    unsigned numPts = vertices.size();
    Eigen::Matrix<Number, 2,2> xhp;
        
    // Compute hyperplane points xhp
    if (hp.vector()(1)==0) {
        Eigen::Matrix<Number, 2, 1> minVecY, maxVecY;
        minVecY = *std::min_element(vertices.begin(), vertices.end(), ZUtility::compareYVal<Number>);
        maxVecY = *std::max_element(vertices.begin(), vertices.end(), ZUtility::compareYVal<Number>);

        xhp.row(1) << (minVecY(1) - std::abs(maxVecY(1)-minVecY(1))/10), 
                      (maxVecY(1) + std::abs(maxVecY(1)-minVecY(1))/10);
        Eigen::Matrix<Number, 1, 2> eVec = {hp.scalar(), hp.scalar()};
        xhp.row(0) = (eVec - hp.vector()(1)*xhp.row(1))/hp.vector()(0);
    }
    else {
        Eigen::Matrix<Number, 2, 1> minVecX, maxVecX;
        minVecX = *std::min_element(vertices.begin(), vertices.end(), ZUtility::compareXVal<Number>);
        maxVecX = *std::max_element(vertices.begin(), vertices.end(), ZUtility::compareXVal<Number>);
        
        xhp.row(0) << (minVecX(0) - std::abs(maxVecX(0)-minVecX(0))/10), 
                      (maxVecX(0) + std::abs(maxVecX(0)-minVecX(0))/10);
        Eigen::Matrix<Number, 1, 2> eVec = {hp.scalar(), hp.scalar()};
        xhp.row(1) = (eVec - hp.vector()(0)*xhp.row(0))/hp.vector()(1);
    }
    // Real algorithm starts here
        
    ZUtility::Line_t<Number> lnhp(xhp.col(0),(xhp.col(1) - xhp.col(0)));
    
    // Naming variables: dzbme is used for sorting vertices nearest to the line
    //                   dzb is used to keep track of d'*zb values
    std::valarray<Number> dzbme(vertices.size()), dzb(vertices.size());
    unsigned minIdx = 0, i;
    for (i=0; i<vertices.size(); i++) {
        dzbme[i] = (hp.vector().transpose()*vertices[i] - hp.scalar());
        dzb[i] = (hp.vector().transpose()*vertices[i]);
    }
    
    
    std::vector<int> ltZeroIdxArray, mtZeroIdxArray;
    for (i=0; i<dzbme.size(); i++) {
        if (std::abs(dzbme[i]) < std::abs(dzbme[minIdx])) {
            minIdx = i;
        }
        if (dzbme[i] < 0) ltZeroIdxArray.push_back(i);
        if (dzbme[i] > 0) mtZeroIdxArray.push_back(i);
        
    }
    
    //TODO: circshift vertices vector
    dzb = dzb.cshift(minIdx);
    dzbme = dzbme.cshift(minIdx);
    
    
    // Essentially create a temporary val array to do cshift operation 
    // and copy back value into vertices std::vector
    std::valarray< Eigen::Matrix<Number, Eigen::Dynamic ,1> > verticesValArray(vertices.data(), vertices.size());
    verticesValArray = verticesValArray.cshift(minIdx);
    vertices.assign(std::begin(verticesValArray), std::end(verticesValArray));
    
    unsigned nil,il1p2, il2p1, il2p2; 
    if (dzbme[0] < 0) {
        nil = ltZeroIdxArray.size();
        if (dzbme[1] < 0) {
            il1p2 = numPts;
            il2p1 = nil;
        }
        else {
            il1p2 = 2;
            il2p1 = numPts-nil+1;
        }
    }
    else {
        nil = mtZeroIdxArray.size();
        if (dzbme[1] > 0) {
            il1p2 = numPts;
            il2p1 = nil;
        }
        else {
            il1p2 = 2;
            il2p1 = numPts-nil+1;
        }
    }
    
    if (nil==1) il2p2 = 1;
    else il2p2 = il2p1+1;
    
    ZUtility::Line_t<Number> ln(vertices[0], vertices[il1p2-1]-vertices[0]);
    // TODO: compute line intersection
    Eigen::Matrix<Number, 2, 1> p1 = computeLineIntersection(ln, lnhp);
    
    ln.point = vertices[il2p1-1];
    ln.direction = vertices[il2p2-1] - vertices[il2p1-1];
    // TODO: compute line intersection
    Eigen::Matrix<Number, 2, 1> p2 = computeLineIntersection(ln, lnhp);
    
    Zonotope<Number> resZonotope((p1+p2)/2, (p1-p2)/2);
    
    minMaxOfLine.resize(2,2);
    minMaxOfLine.row(0) = (comparePoint(p1, p2)) ? p1.transpose() : p2.transpose(); // min [x,y] here
    minMaxOfLine.row(1) = (comparePoint(p1, p2)) ? p2.transpose() : p1.transpose(); // max [x,y] here
    
    result = resZonotope;
}

template<typename Number>
void intersectAlamo(const Zonotope<Number>& inputZonotope, const Hyperplane<Number>& hp, 
            Zonotope<Number>& resultZonotope)
{
    
    assert(inputZonotope.dimension()==hp.dimension());
     // Determine intersect as Zonotope, according to Tabatabaeipour et al., 2013 
    Number sgm = 0; // could be redundant
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> H = inputZonotope.generators();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> HHT = H*H.transpose();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> center = inputZonotope.center();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> lambda = (HHT*hp.vector())/(hp.vector().transpose()*HHT*hp.vector()+sgm*sgm);

    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> new_gen, identity;
    Zonotope<Number> zg(inputZonotope.dimension());

    zg.setCenter(center+lambda*(hp.scalar()-hp.vector().transpose()*center));  


    identity.resize(inputZonotope.dimension(), inputZonotope.dimension());

    identity.setIdentity();


    new_gen =(identity - lambda*(hp.vector().transpose()))*H;    
    zg.setGenerators(new_gen);

    resultZonotope = zg;
}

template<typename Number>
void intersectNDProjection(const Zonotope<Number>& inputZonotope, const Hyperplane<Number>& hp, 
                            Zonotope<Number>& resultZonotope, Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& minMaxOfLine)
{
    assert(hp.dimension()==inputZonotope.dimension() && "Intersect ND: input zonotope and input hyperplane must have same dimensionality");
    Eigen::Matrix<Number, Eigen::Dynamic, 1> dVec;
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> kernel;
    dVec = hp.vector();
    Eigen::JacobiSVD<Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> > svd(dVec.transpose(), 
                                                                                Eigen::ComputeFullU | Eigen::ComputeFullV);
    // Using SVD to calculate nullspace (kernel)
    kernel = svd.matrixV().block(0,1,svd.matrixV().rows(), svd.matrixV().cols()-1);
    
    unsigned nd, dim;
    nd = kernel.cols();
    dim = inputZonotope.dimension();
    
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> dpQg, resultGenerators;
    Number dpQc;
    minMaxOfLine.resize(2,nd);
    resultGenerators.resize(dim, nd);
    dpQc = dVec.dot(inputZonotope.center());
    dpQg = dVec.transpose()*inputZonotope.generators();

    for (unsigned i=0; i<nd; i++) {
        // construct 2 dimensional Zonotope
        Eigen::Matrix<Number, 2, 1> projCenter;
        Eigen::Matrix<Number, 2, Eigen::Dynamic> projGenerators;
        
        projCenter << dpQc, kernel.col(i).dot(inputZonotope.center());
        projGenerators.resize(2,dpQg.cols());
        projGenerators << dpQg, kernel.col(i).transpose() * inputZonotope.generators();
        
        Zonotope<Number> projZonotope(projCenter, projGenerators), tempResZonotope;
        
        // Upon projection, the hyperplane now has a d vector of [1;0] but retains its e scalar
        Eigen::Matrix<Number, 2, 1> lgDVector(1,0);
        Hyperplane<Number> lg(lgDVector, hp.scalar());
                
//        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> dummyMinMax;
        intersectZonogoneHyperplaneDSearch(projZonotope, lg, tempResZonotope);
        
        Eigen::Matrix<Number, 2, 1> p1, p2;
        p1 = tempResZonotope.center() + tempResZonotope.generators();
        p2 = tempResZonotope.center() - tempResZonotope.generators();
        
        
        // find min and max points of intersect between zonogone and hyperplane
        // we only consider the y axis owing to the [1;0] property of the projected space as mentioned earlier
        minMaxOfLine(0,i) = (p1(1) < p2(1)) ? p1(1) : p2(1);
        minMaxOfLine(1,i) = (p1(1) > p2(1)) ? p1(1) : p2(1);
        
        
        resultGenerators.conservativeResize(dim, i+1);
        resultGenerators.col(i) << ((minMaxOfLine(1,i) - minMaxOfLine(0,i))/2) * kernel.col(i); 
    }
    
    resultZonotope.setCenter(kernel * ((minMaxOfLine.row(1)+minMaxOfLine.row(0))/2).transpose() + hp.scalar()*dVec);
    resultZonotope.setGenerators(resultGenerators);
    
    
}

template<typename Number> 
bool Zonotope<Number>::intersect(Zonotope<Number>& result,
                                 const Hyperplane<Number>& hp,
                                 int method) 
{
    Eigen::Matrix<Number , Eigen::Dynamic, Eigen::Dynamic> EMPTY_MATRIX(0,0);
    return this->intersect(result, hp, EMPTY_MATRIX, method);
}

template <typename Number>
bool Zonotope<Number>::intersect(Zonotope<Number>& result, 
                                const Hyperplane<Number>& hp, 
                                Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& minMaxOfLine,
                                int method) 
{
    assert(hp.dimension()==mDimension && "Zonotope's dimensionality must be same as Hyperplane's dimensionality.");
    
    // Determine if intersection is found, according to Girard, Guernic, 2008
    Number emdc = hp.scalar()-hp.vector().transpose()*mCenter;
    Number zs = (hp.vector().transpose()*mGenerators).array().abs().sum();
    
    bool hasIntersect = (emdc > -zs && zs > emdc);
    if (hasIntersect) {

        switch (method) {
            case ZUtility::ALAMO:
//                std::cout << "Using Alamo's method with dimension " << mDimension << std::endl;
                intersectAlamo(*this, hp, result);
                break;
            case ZUtility::NDPROJECTION:
            {
                if (mDimension==2) {
//                    std::cout << "Using Girard's method with dimension 2 " << std::endl;
                    intersectZonogoneHyperplane(*this, hp, result, minMaxOfLine);
                    
                }
                else {
//                    std::cout << "Using Girard's method with dimension " << mDimension << std::endl;
                    intersectNDProjection<Number>(*this, hp, result, minMaxOfLine);
                }
                break;
            }
//            case DICHOTOMIC2D:
//                assert(mDimension==2);
//                intersectZonogoneHyperplaneDSearch(*this, hp, result);
//                break;
            default: break;
        }   
        return true;
    }
    else
        return false;
}

template<typename Number>
bool Zonotope<Number>::intersect(Zonotope<Number>& result, const Constraint& halfspace) {
    assert(halfspace.space_dimension() == this->mDimension);
    Number e = halfspace.inhomogeneous_term().get_d();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> dVec;
    
    dVec.resize(halfspace.space_dimension(), Eigen::NoChange);
    
    for (unsigned i=0; i<halfspace.space_dimension(); i++) {
        dVec(i) = -1*halfspace.coefficient(Variable(i)).get_d();
    }
    
    Number zs = (dVec.transpose()*this->mGenerators).array().abs().sum();
    Number dc = dVec.dot(this->mCenter);
    Number qu = dc + zs,
           qd = dc -zs;
    
    if (qd <= e) {
        if (qu <= e) {
            
        }
        else {
            Number sigma = (e-qd)/2,
                    d = (qd+e)/2;
            Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> HHT = this->mGenerators*this->mGenerators.transpose();
            Eigen::Matrix<Number, Eigen::Dynamic, 1> lambda = HHT * dVec / ((dVec.transpose() * HHT * dVec) + sigma*sigma);
            result.setCenter(this->mCenter + lambda*(d - dc));
            Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> identity;
            identity.resize(mDimension, mDimension);
            identity.setIdentity();
            result.setGenerators((identity - lambda * dVec.transpose())*this->mGenerators);
            result.addGenerators(sigma*lambda);
        }
    }
    else return false;
    
    return true;
}

template<typename Number>
bool Zonotope<Number>::intersect(Zonotope<Number>& result, const C_Polyhedron& rhs) {
    // Get set of half spaces
    const Constraint_System& cs = rhs.constraints();
    unsigned int dim = rhs.space_dimension();
    Zonotope<Number> cur_zonotope(mCenter, mGenerators);
    
    // Iterate through all constraints of the polyhedron
    for (Constraint constr : cs) {
        Zonotope<Number> intermediateResult;
//        Eigen::Matrix<Number, Eigen::Dynamic, 1> d_vector;
//        Number e;
//        d_vector.resize(dim,1);
//        
//        // PPL represents constraints in the form of a*x1 + b*x2 + ... {>,>=} q
//        // Note: e does not need to be negated 'cause PPL returns value of inhomogenous_term on the LHS of inequality
//        e = constr.inhomogeneous_term().get_d();
//        for (unsigned i=0; i<constr.space_dimension(); i++) {
//            // each coefficient has to be negated due to >= in PPL instead of <=
//            d_vector(i) = -1*constr.coefficient(Variable(i)).get_d();
//        }
//        
//        // zs is ||H^t * n || _ 1
//        Number zs = (d_vector.transpose()*cur_zonotope.generators()).array().abs().sum();
//        Number dc = d_vector.transpose()*cur_zonotope.center();
//        Number qu = dc + zs, qd = dc - zs;
//        
//        if (qd<=e) {
//            if (qu<=e) { 
//                // do nothing
//            }
//            else {
//                Number sgm = (e-qd)/2, d = (qd+e)/2;
//                Eigen::Matrix<Number, Eigen::Dynamic, 1> lambda = ((cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector)/
//                                (d_vector.transpose()*(cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector+sgm*sgm);
//                
//                Zonotope<Number> new_zonotope;
//                new_zonotope.setCenter(cur_zonotope.center()+lambda*(d-dc));
//                
//                Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> new_gen1, new_gen2, identity;
//                identity.resize(dim, dim);
//                identity.setIdentity();
//                new_gen1 = (identity-lambda*d_vector.transpose())*cur_zonotope.generators();
//                new_gen2 = sgm*lambda;
//                new_zonotope.setGenerators(new_gen1);
//                new_zonotope.addGenerators(new_gen2);
//                cur_zonotope = new_zonotope;
//            }
//        }
//        else {
//            return false;
//        }
        bool intersectFound = this->intersect(intermediateResult, constr);
        if (!intersectFound) return false;
        
    }
    return true;
    // TODO: QUESTION! If one iteration yields empty set, should we break out of loop?
}

template<typename Number>
bool Zonotope<Number>::convexHull(Zonotope<Number>& result, const Zonotope<Number>& other) 
{
    assert(mDimension == other.mDimension && "Zonotopes must be of same dimension in order to carry out convex hull operations.");
    unsigned numGenCurrent, numGenOther;
    Zonotope<Number> temp;
    numGenCurrent = this->numGenerators();
    numGenOther = other.numGenerators();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> R1, R2;
    Eigen::Matrix<Number, Eigen::Dynamic, 1> c1, c2;
    R1 = this->mGenerators;
    R2 = other.mGenerators;
    c1 = this->mCenter;
    c2 = other.mCenter;
    
    // common traits of center and generators for all two zonotopes
    temp.setCenter((c1+c2)*0.5);

    if (numGenCurrent > numGenOther) {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> R11, R12;        
        R11 = R1.block(0, 0, mDimension, numGenOther);
        R12 = R1.block(0, numGenOther, mDimension, numGenCurrent-numGenOther);
        
        temp.setGenerators((R2 + R11)*0.5);
        temp.addGenerators((c1-c2)*0.5);
        temp.addGenerators((R11-R2)*0.5);
        temp.addGenerators(R12);   
    }
    else if (numGenCurrent < numGenOther) {
        Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> R21, R22;
        
        R21 = R2.block(0, 0, mDimension, numGenCurrent);
        R22 = R2.block(0, numGenCurrent, mDimension, numGenOther-numGenCurrent);
        
        temp.setGenerators((R1 + R21)*0.5);
        temp.addGenerators((c2-c1)*0.5);
        temp.addGenerators((R21-R1)*0.5);
        temp.addGenerators(R22);
    }
    else {
        
        temp.setGenerators((R1 + R2)*0.5);
        temp.addGenerators((c1-c2)*0.5);
        temp.addGenerators((R1 - R2)*0.5);
    }
    result = temp;
    return true;
}


template<typename Number>
bool Zonotope<Number>::intervalHull(Zonotope<Number>& result) 
{
    Eigen::Matrix<Number, Eigen::Dynamic, 1> imax, imin, sumOfGenerators, center = this->mCenter;
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generators = this->mGenerators;
    Zonotope<Number> temp;
    
    sumOfGenerators = generators.cwiseAbs().rowwise().sum();
    
    imax = center + sumOfGenerators;
    imin = center - sumOfGenerators;
    
    temp.setCenter((imax+imin)*0.5);

    temp.setGenerators( ((imax-imin)*0.5).cwiseAbs().asDiagonal() );
    
    result = temp;
    return true;
}