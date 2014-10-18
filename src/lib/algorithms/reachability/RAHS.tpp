#include "RAHS.h"


// Non-class function
template<typename Number>
bool compareVectors(Eigen::Matrix<Number, Eigen::Dynamic, 1> v1, Eigen::Matrix<Number, Eigen::Dynamic, 1> v2) {
    Number v1_sum = v1.array().abs().matrix().sum();
    Number v2_sum = v2.array().abs().matrix().sum();
    Number v1_inf = v1.array().abs().maxCoeff();
    Number v2_inf = v2.array().abs().maxCoeff();

    return (v1_sum-v1_inf) < (v2_sum-v2_inf);
}



/*
 * Public Functions - Constructors
 */


template<typename Number>
RAHS<Number>::RAHS(unsigned int dimension) : mInitialized() , mDimension(dimension)
{}

//template<typename Number>
//RAHS<Number>::RAHS(unsigned int dimension,
//                        const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& A,
//                        const Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic>& bigB,
//                        const Eigen::Matrix<Number, Eigen::Dynamic, 1>& smallb, 
//                        Number r, 
//                        const Zonotope<Number>& U, 
//                        const Zonotope<Number>& Q  ) 
//{
//    assert(dimension==A.rows() && A.rows()==bigB.rows() && 
//            bigB.rows()==smallb.rows() && smallb.rows() == Q.dimension());
//    mInitialized = true;
//    mDimension = dimension;
//    A_ = A;
//    bigB_ = bigB;
//    smallb_ = smallb;
//    r_ = r;
//    U_ = U;
//    Q_ = Q;
//}

template<typename Number>
RAHS<Number>::~RAHS() {
    
}



/*
 * Public Functions - Operations
 */


template<typename Number>
unsigned int RAHS<Number>::dimension() const {
    return mDimension;
}

template<typename Number>
void RAHS<Number>::loadHybridAutomaton(hypro::HybridAutomaton<Number>* hybridAutomaton_) {
    mHybridAutomaton = hybridAutomaton_;
    // pick first init state
    mCurrentLoc = (hybridAutomaton_->initialLocations()->begin());
    A_ = mCurrentLoc.activityMat();
    bigB_ = mCurrentLoc.activityInputMat();
    smallb_ = mCurrentLoc.activityVec();
    Q_ = hybridAutomaton_->valuation();
    mInitialized = true;
}


template<typename Number>
void RAHS<Number>::approxReachDiscrete(unsigned int numIterations, unsigned int order_reduction_threshold) 
{
    assert(mInitialized);
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> null_vector;
    null_vector.resize(mDimension, 1);
    null_vector.setZero();
    
    

    
    sequence_zonQ_.push_back(Q_); // Pushing back Q0
    
    bool mRestartFlag = true;
    unsigned int i=0;
    Zonotope<Number>* intersect_zonotope;
    
    while (i<numIterations) {
        if (mRestartFlag) {
            mRestartFlag = false;
            if (i>0)
                loadNewState(&mCurrentLoc, intersect_zonotope);
            
            if(smallb_!=null_vector) {
                readjust();
            }
            
            initializeRAHSComputation();
            sequence_zonQ_.push_back(Q_); // push back Q1
            

        }
        else {
            computeNextZonotope_RACS(i-1, order_reduction_threshold);
            checkGuardJumpCondition(intersect_zonotope);
            sequence_zonQ_.push_back(Q_);
        }
        i++;
        
    }


}

/*
 * Private Functions
 */


template<typename Number>
void RAHS<Number>::readjust() {
    unsigned int origAdim = A_.rows(), origBdim = bigB_.rows();
    
    // Append b into new A matrix and hereby changing dimension of A matrix
    A_.conservativeResize(Eigen::NoChange,origAdim+1);
    A_.col(origAdim) = smallb_;
    
    // Append null row to A matrix
    A_.conservativeResize(origAdim+1, Eigen::NoChange);
    A_.row(origAdim).setZero();
    // Append null vector to B matrix
    bigB_.conservativeResize(origBdim+1, Eigen::NoChange);
    bigB_.row(origBdim).setZero();
    
    // Change dimension of Q Zonotope
    Q_.changeDimension(origAdim+1);
    Eigen::Matrix<Number, Eigen::Dynamic, 1> temp_center = Q_.getCenter();
    temp_center(Q_.dimension()-1) = 1;
    Q_.setCenter(temp_center);
}

template<typename Number>
void RAHS<Number>::initializeRAHSComputation() {
    // Variable declaration
    unsigned int dimA = A_.rows(), dimB = bigB_.cols();
    Eigen::Matrix<Number, Eigen::Dynamic, 1> I_center = Q_.getCenter();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> I_generators = Q_.getGenerators();
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> C_matrix, C_null, exp_rC, phiU, identity;
    
    // Resizing dynamic matrices
    identity.resize(dimA, dimA);
    identity.setIdentity();
    phiU.resize(dimA, dimB);
    C_null.resize(dimB, dimA+dimB);
    C_null.setZero();
    C_matrix.resize(dimA+dimB, dimA+dimB);
    
    // forming C matrix for matrix exponential
    C_matrix << A_, bigB_,
                C_null;
    
    exp_rC = (r_* C_matrix).exp();
    

    exp_rA_ = exp_rC.block(0, 0, dimA, dimA);
    phiU = exp_rC.block(0, dimA, dimA, dimB);
    

    
    Number mxx;
    if(Q_.numGenerators()==0) 
        mxx = I_center.norm();
    else {
        Eigen::Matrix<Number, Eigen::Dynamic, 1> result;
        result.resize(dimA, 1);
        result = I_center + I_generators.array().abs().matrix().rowwise().sum();
        mxx = result.norm();
    }
    

    
    // Compute alpha_r

    Number rnA = r_*A_.norm();
    Number ar = (exp(rnA)-1-rnA)*mxx;

    // Start RA algorithm: Omega0


    Zonotope<Number> MG(dimA);
    MG.setCenter((I_center+exp_rA_*I_center)/2);
    if(Q_.numGenerators()==0) {
        MG.addGenerators((I_center-exp_rA_*I_center)/2);
        MG.addGenerators(ar*identity);

    }
    else {
        MG.addGenerators((Q_.getGenerators()+exp_rA_*Q_.getGenerators())/2);
        MG.addGenerators((Q_.getCenter()-exp_rA_*Q_.getCenter())/2);
        MG.addGenerators((Q_.getGenerators()-exp_rA_*Q_.getGenerators())/2);
        MG.addGenerators(ar*identity);    

    }

    MG.removeEmptyGenerators();

    Q_ = MG;
    V_.setCenter(phiU*U_.getCenter());
    V_.addGenerators(phiU*U_.getGenerators());

    Eigen::Matrix<Number, Eigen::Dynamic, 1> c;
    c.resize(dimA,1);
    c.setZero();
    
    S_.setCenter(c);
                
}

template<typename Number>
void RAHS<Number>::computeNextZonotope_RACS(unsigned int i, unsigned int order_reduction_threshold) {
    
    Zonotope<Number> X, Q_previous = sequence_zonQ_[i];
    Q_previous.setCenter(exp_rA_*Q_previous.getCenter());
    Q_previous.setGenerators(exp_rA_*Q_previous.getGenerators());
    X = Q_previous;
    
    V_.setCenter(exp_rA_*V_.getCenter());
    V_.setGenerators(exp_rA_*V_.getGenerators());
    
    S_.setCenter(S_.getCenter() + V_.getCenter());
    S_.addGenerators(V_.getGenerators());
    
    Q_.setCenter(X.getCenter() + S_.getCenter());
    Q_.setGenerators(X.getGenerators());
    Q_.addGenerators(S_.getGenerators());
    
    
    // Order reduction on Q
    if (Q_.numGenerators() > order_reduction_threshold) {
        overapproximateZonotope(Q_);
    }
}

template<typename Number>
void RAHS<Number>::overapproximateZonotope(Zonotope<Number>& z) {
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generators = z.getGenerators();
    unsigned int z_rows = z.dimension();
    std::vector<Eigen::Matrix<Number, Eigen::Dynamic, 1> > vectOfGenerators;

    for (unsigned int i=0; i<generators.cols(); i++) {
        vectOfGenerators.push_back(generators.col(i));
    }

    // Sort generators
    std::sort(vectOfGenerators.begin(), vectOfGenerators.end(), compareVectors<Number>);
    
    // Rowwise sum of all generators (absolute value)
    Eigen::Matrix<Number, Eigen::Dynamic, 1> sumVector;
    for (unsigned int i=0; i<2*(z_rows); i++) {
        if (i==0) {
            sumVector.resize(z_rows, 1);
            sumVector << vectOfGenerators[i];
        }
        else {
            sumVector += vectOfGenerators[i].array().abs().matrix();
        }
    }

    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> remaining_vectors;
    unsigned int numRemainingVectors = vectOfGenerators.size()-(2*z_rows+1);
    remaining_vectors.resize(z_rows, numRemainingVectors);
    
    for (unsigned int i=0; i<numRemainingVectors; i++) {
        remaining_vectors.col(i) = vectOfGenerators[i+(2*z_rows+1)];
    }
    
//    for (unsigned int i=2*z_rows+1; i<vectOfGenerators.size(); i++) {
//        if (i==2*z_rows+1) {
//            remaining_vectors.resize(z_rows, 1);
//            remaining_vectors << vectOfGenerators[i];
//        }
//        else {
//            Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> temp = remaining_vectors;
//            remaining_vectors.resize(z_rows, remaining_vectors.cols()+1);
//            remaining_vectors << temp, vectOfGenerators[i];
//        }
//    }
    
    // calculate interval hull of first 2n generators
    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> interval_hull = sumVector.asDiagonal();

    Eigen::Matrix<Number, Eigen::Dynamic, Eigen::Dynamic> generators_new;
    generators_new.resize(z_rows, remaining_vectors.cols()+z_rows);

    generators_new << interval_hull, remaining_vectors;
    z.setGenerators(generators_new);
}

template<typename Number>
void RAHS<Number>::checkGuardJumpCondition(Zonotope<Number>* intersect_zonotope) {
    std::set< hypro::Transition<Number>* > possibleTransitions = mCurrentLoc.transitions();
    
    for (hypro::Transition<Number>* trans : possibleTransitions) 
    {
        Hyperplane<Number> hp(trans->guard().mat.row(1).transpose(), trans->guard().vec(1));
        if(Q_.intersect(*intersect_zonotope, hp)) {
            mCurrentLoc = (*trans->targetLoc());
            mRestartFlag = true;
            break;
        }  
    }
}


template<typename Number>
void RAHS<Number>::loadNewState(hypro::Location<Number>* newLocation, Zonotope<Number>* intersect_zonotope) {
    smallb_ = newLocation->activityVec();
    bigB_ = newLocation->activityInputMat();
    A_ = newLocation->activityMat();
    Q_ = *intersect_zonotope;
    
}