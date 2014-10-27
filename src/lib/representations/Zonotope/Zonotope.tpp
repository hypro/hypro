#include "Zonotope.h"
#include <assert.h>
#include <Eigen/src/Core/PlainObjectBase.h>
#include <Eigen/LU>
#include <cmath>
#include <algorithm>


using namespace Parma_Polyhedra_Library;

// Options for checking for intersect
enum {
    ALAMO = 1,
    NDPROJECTION = 2
};


/**
 * Non-member functions
 */

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

template <typename Number>
void removeGenerator(unsigned int colToRemove, 
                    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& matrix) 
{
    unsigned int numRows = matrix.rows();
    unsigned int numCols = matrix.cols()-1;

    if( colToRemove < numCols )
        matrix.block(0,colToRemove,numRows,numCols-colToRemove) = matrix.block(0,colToRemove+1,numRows,numCols-colToRemove);

    matrix.conservativeResize(numRows,numCols);
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
Eigen::Matrix<Number, 2, 1> computeLineIntersection(const Line_t<Number>& l1, const Line_t<Number>& l2) {
    Eigen::Matrix<Number,2,2> concatDirections;
    Eigen::Matrix<Number,2,1> a, resPt;
    
    concatDirections << l1.direction, -l2.direction;
    a = concatDirections.inverse()*(l2.point - l1.point);
    resPt = l1.point + a(0)*l1.direction;
    return resPt;
}

template <typename Number>
bool compareColumnVectors(const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec1, 
                          const Eigen::Matrix<Number, Eigen::Dynamic, 1>& colvec2) 
{
    Number x1(colvec1(0)), x2(colvec2(0)), y1(colvec2(1)), y2(colvec2(1));
    
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


/**
 * Member functions of Zonotope class
 */

template <typename Number>
Zonotope<Number>::Zonotope() : mDimension(0)
{
}

template <typename Number>
Zonotope<Number>::Zonotope(unsigned int dimension) {
    assert(dimension!=0);
    mDimension = dimension;
    mCenter.resize(2,1);
    mCenter.setZero();
    mGenerators.resize(2,1);
    mGenerators.setZero();
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
    assert(A.cols()==mCenter.rows());
    assert(A.cols()==mGenerators.rows());
    
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
    
    std::sort(sortArray.begin(), sortArray.end(), compareColumnVectors<Number>);
    
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
void intersectZonogoneHyperplane(Zonotope<Number>& inputZonotope,
                                             const Hyperplane<Number>& hp,
                                             Zonotope<Number>& result) 
{
    assert(inputZonotope.dimension()==hp.dimension() && "Zonotope and Hyperplane have to be of similar dimensions");
    std::vector< Eigen::Matrix<Number, Eigen::Dynamic ,1> > vertices = inputZonotope.computeZonotopeBoundary();
    vertices.pop_back();
    
    unsigned numPts = vertices.size();
    Eigen::Matrix<Number, 2,2> xhp;
        
    // Compute hyperplane points xhp
    if (hp.vector()(1)==0) {
        Eigen::Matrix<Number, 2, 1> minVecY, maxVecY;
        minVecY = *std::min_element(vertices.begin(), vertices.end(), compareYVal<Number>);
        maxVecY = *std::max_element(vertices.begin(), vertices.end(), compareYVal<Number>);

        xhp.row(1) << (minVecY(1) - std::abs(maxVecY(1)-minVecY(1))/10), 
                      (maxVecY(1) + std::abs(maxVecY(1)-minVecY(1))/10);
        Eigen::Matrix<Number, 1, 2> eVec = {hp.scalar(), hp.scalar()};
        xhp.row(0) = (eVec - hp.vector()(1)*xhp.row(1))/hp.vector()(0);
    }
    else {
        Eigen::Matrix<Number, 2, 1> minVecX, maxVecX;
        minVecX = *std::min_element(vertices.begin(), vertices.end(), compareXVal<Number>);
        maxVecX = *std::max_element(vertices.begin(), vertices.end(), compareXVal<Number>);
        
        xhp.row(0) << (minVecX(0) - std::abs(maxVecX(0)-minVecX(0))/10), 
                      (maxVecX(0) + std::abs(maxVecX(0)-minVecX(0))/10);
        Eigen::Matrix<Number, 1, 2> eVec = {hp.scalar(), hp.scalar()};
        xhp.row(1) = (eVec - hp.vector()(0)*xhp.row(0))/hp.vector()(1);
    }
    // Real algorithm starts here
        
    Line_t<Number> lnhp(xhp.col(0),(xhp.col(1) - xhp.col(0)));
    
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
    
    Line_t<Number> ln(vertices[0], vertices[il1p2-1]-vertices[0]);
    // TODO: compute line intersection
    Eigen::Matrix<Number, 2, 1> p1 = computeLineIntersection(ln, lnhp);
    
    ln.point = vertices[il2p1-1];
    ln.direction = vertices[il2p2-1] - vertices[il2p1-1];
    // TODO: compute line intersection
    Eigen::Matrix<Number, 2, 1> p2 = computeLineIntersection(ln, lnhp);
    
    Zonotope<Number> resZonotope((p1+p2)/2, (p1-p2)/2);
    
    result = resZonotope;
}

template<typename Number>
void intersectAlamo(const Zonotope<Number>& inputZonotope, const Hyperplane<Number>& hp, 
            Zonotope<Number>& resultZonotope)
{
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
    kernel = dVec.transpose().fullPivLu().kernel();
        
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
        
        intersectZonogoneHyperplane(projZonotope, lg, tempResZonotope);
        
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
    assert(hp.dimension()==mDimension);
    
    // Determine if intersection is found, according to Girard, Guernic, 2008
    Number emdc = hp.scalar()-hp.vector().transpose()*mCenter;
    Number zs = (hp.vector().transpose()*mGenerators).array().abs().sum();
    
    bool hasIntersect = (emdc > -zs && zs > emdc);
    if (hasIntersect) {
        if (mDimension==2)
            intersectZonogoneHyperplane(*this, hp, result);
        else {
            switch (method) {
                case ALAMO:
                    intersectAlamo(*this, hp, result);
                    break;
                case NDPROJECTION:
                default:
                    intersectNDProjection<Number>(*this, hp, result, minMaxOfLine);
                    break;
            }
            
        }
        return true;
    }
    else {
        return false;
    }
}

template<typename Number>
bool Zonotope<Number>::intersect(Zonotope<Number>& result, const C_Polyhedron& rhs) {
    // Get set of half spaces
    const Constraint_System& cs = rhs.constraints();
    unsigned int dim = rhs.space_dimension();
    Zonotope<Number> cur_zonotope(mCenter, mGenerators);
    
    // Iterate through all constraints of the polyhedron
    for (Constraint constr : cs) {
        Eigen::Matrix<Number, Eigen::Dynamic, 1> d_vector;
        Number e;
        d_vector.resize(dim,1);
        
        // PPL represents constraints in the form of a*x1 + b*x2 + ... {>,>=} q
        // Note: e does not need to be negated 'cause PPL returns value of inhomogenous_term on the LHS of inequality
        e = constr.inhomogeneous_term().get_d();
        for (unsigned i=0; i<constr.space_dimension(); i++) {
            // each coefficient has to be negated due to >= in PPL instead of <=
            d_vector(i) = -1*constr.coefficient(Variable(i)).get_d();
        }
        
        // zs is ||H^t * n || _ 1
        Number zs = (d_vector.transpose()*cur_zonotope.generators()).array().abs().sum();
        Number dc = d_vector.transpose()*cur_zonotope.center();
        Number qu = dc + zs, qd = dc - zs;
        
        if (qd<=e) {
            if (qu<=e) { 
                // do nothing
            }
            else {
                Number sgm = (e-qd)/2, d = (qd+e)/2;
                Eigen::Matrix<Number, Eigen::Dynamic, 1> lambda = ((cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector)/
                                (d_vector.transpose()*(cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector+sgm*sgm);
                
                Zonotope<Number> new_zonotope;
                new_zonotope.setCenter(cur_zonotope.center()+lambda*(d-dc));
                
                Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> new_gen1, new_gen2, identity;
                identity.resize(dim, dim);
                identity.setIdentity();
                new_gen1 = (identity-lambda*d_vector.transpose())*cur_zonotope.generators();
                new_gen2 = sgm*lambda;
                new_zonotope.setGenerators(new_gen1);
                new_zonotope.addGenerators(new_gen2);
                cur_zonotope = new_zonotope;
            }
        }
        else {
            return false;
        }
        
    }
    return true;
    // TODO: QUESTION! If one iteration yields empty set, should we break out of loop?
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
    assert(center.rows()==mDimension);
    mCenter = center;
}

template <typename Number>
void Zonotope<Number>::setGenerators(const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& new_generators) {
    if (mDimension==0) {
        mDimension = new_generators.rows();
        mCenter.resize(mDimension,1);
        mCenter.setZero();
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

template <typename Number>
void Zonotope<Number>::clear() {
    mGenerators.resize(0,0);
    mCenter.resize(0,1);
    mDimension = 0;
}
