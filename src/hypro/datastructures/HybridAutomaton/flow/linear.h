#pragma once
#include "../../../types.h"

namespace hypro {

template<typename Number>
class linearFlow {
public:
protected:
    matrix_t<Number> mFlowMatrix;
    mutable TRIBOOL mIsIdentity = TRIBOOL::NSET;
    mutable TRIBOOL mNoFlow = TRIBOOL::NSET;
public:
    linearFlow() = default;
    linearFlow(const linearFlow& in) = default;
    linearFlow(const matrix_t<Number> A) : mFlowMatrix(A) {}
    virtual ~linearFlow() {}

    static DynamicType type() { return DynamicType::linear; }
    std::size_t dimension() const { return mFlowMatrix.cols(); }

    void setFlowMatrix(const matrix_t<Number>& newA) {
        mFlowMatrix = newA;
        mIsIdentity = TRIBOOL::NSET;
        mNoFlow = TRIBOOL::NSET;
    }
    const matrix_t<Number>& getFlowMatrix() const { return mFlowMatrix;}

    bool isIdentity() const {
        if(mIsIdentity == TRIBOOL::NSET) {
            if(mFlowMatrix.rows() == 0) {
                mIsIdentity = TRIBOOL::FALSE;
                mNoFlow = TRIBOOL::FALSE;
                return false;
            } else {
                mIsIdentity = mFlowMatrix == matrix_t<Number>::Identity(mFlowMatrix.rows(), mFlowMatrix.cols()) ? TRIBOOL::TRUE : TRIBOOL::FALSE;
                if(mIsIdentity == TRIBOOL::TRUE) {
                    mNoFlow = TRIBOOL::FALSE;
                }
            }
        }
        return mIsIdentity == TRIBOOL::TRUE;
    }

    bool hasNoFlow() const {
        if(mNoFlow == TRIBOOL::NSET) {
            if(mFlowMatrix.rows() == 0) {
                mNoFlow = TRIBOOL::FALSE;
                mIsIdentity = TRIBOOL::FALSE;
                return false;
            } else {
                mNoFlow = mFlowMatrix == matrix_t<Number>::Zero(mFlowMatrix.rows(), mFlowMatrix.cols()) ? TRIBOOL::TRUE : TRIBOOL::FALSE;
                if(mNoFlow == TRIBOOL::TRUE) {
                    mIsIdentity = TRIBOOL::FALSE;
                }
            }
        }
        return mNoFlow == TRIBOOL::TRUE;
    }

    bool isTimed() const {
        TRACE("hypro.decisionEntity","Flowmatrix: " << mFlowMatrix);
        Eigen::Index rows = mFlowMatrix.rows();
        if(mFlowMatrix.block(0,0,rows-1,rows-1) == matrix_t<Number>::Zero(rows-1,rows-1)){
            if(mFlowMatrix.block(0,rows-1,rows-1,1) == vector_t<Number>::Ones(rows-1)){
                return true;
            }
        }
        return false;
    }

    bool isDiscrete() const {
        return hasNoFlow();
    }

    friend bool operator==(const linearFlow<Number>& lhs, const linearFlow<Number>& rhs) {
        return lhs.getFlowMatrix() == rhs.getFlowMatrix();
    }

    friend bool operator!=(const linearFlow<Number>& lhs, const linearFlow<Number>& rhs) {
        return !(lhs == rhs);
    }

    friend ostream& operator<<(ostream& out, const linearFlow<Number>& in) {
        return out << in.mFlowMatrix;
    }
};

} // hypro

namespace std {

    template<typename Number>
    struct hash<hypro::linearFlow<Number>> {
        std::size_t operator()(const hypro::linearFlow<Number>& f) const
        {
            std::size_t seed = 0;
            carl::hash_add(seed, std::hash<hypro::matrix_t<Number>>()(f.getFlowMatrix()));
            return seed;
        }
    };

}  // namespace std
