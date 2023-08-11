/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Zonotope.h"

namespace hypro {

/*****************************************************************************
 *                                                                           *
 *                          Non-member functions                             *
 *                                                                           *
 *****************************************************************************/

    template<typename Number>
    bool comparePoint(Eigen::Matrix<Number, 2, 1> &p1, Eigen::Matrix<Number, 2, 1> &p2) {
        if (p1(0) != p2(0))
            return (p1(0) < p2(0));
        else
            return (p1(1) < p2(1));
    }

    template<typename Number>
    void removeGenerator(unsigned colToRemove, matrix_t<Number> &matrix) {
        Eigen::Index numRows = matrix.rows();
        Eigen::Index numCols = matrix.cols() - 1;
        if (matrix.cols() == 1 && colToRemove == 0) {
            matrix.conservativeResize(Eigen::NoChange, 0);
        } else {
            if (colToRemove < numCols) {
                assert(numCols - colToRemove > 0);
                assert(colToRemove + 1 <= matrix.cols() - 1);
                matrix.block(0, colToRemove, numRows, numCols - colToRemove) =
                        matrix.block(0, colToRemove + 1, numRows, numCols - colToRemove);
            }
            matrix.conservativeResize(Eigen::NoChange, numCols);
        }
    }

    template<typename Number>
    void removeEmptyGenerators(matrix_t<Number> &generatorMatrix) {
        Eigen::Index dim = generatorMatrix.rows();
        vector_t<Number> zero_vector;
        zero_vector.resize(dim, 1);
        zero_vector.setZero();

        std::vector<Eigen::Index> zeroIndex;
        for (Eigen::Index i = 0; i < generatorMatrix.cols(); i++) {
            if (generatorMatrix.col(i) == zero_vector) {
                zeroIndex.push_back(i);
            }
        }

        for (std::vector<Eigen::Index>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit) {
            removeGenerator<Number>(*rit, generatorMatrix);
        }
    }

    template<typename Number>
    Eigen::Matrix<Number, 2, 1> computeLineIntersection(const ZUtility::Line_t<Number> &l1,
                                                        const ZUtility::Line_t<Number> &l2) {
        Eigen::Matrix<Number, 2, 2> concatDirections;
        Eigen::Matrix<Number, 2, 1> a, resPt;

        concatDirections << l1.direction, -l2.direction;
        a = concatDirections.inverse() * (l2.point - l1.point);
        resPt = l1.point + a(0) * l1.direction;
        return resPt;
    }

/*****************************************************************************
 *                                                                           *
 *            `         Member functions - Constructors                      *
 *                                                                           *
 *****************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::ZonotopeT()
            : mDimension(0), mCenter(0, 1), mGenerators(0, 0) {}

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::ZonotopeT(std::size_t dimension)
            : mDimension(dimension), mCenter(vector_t<Number>::Zero(dimension)),
              mGenerators(matrix_t<Number>::Zero(dimension, 1)) {
        assert(dimension != 0 && "Zonotope cannot have dimension 0.");
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::ZonotopeT(const matrix_t<Number>& _constraints, const vector_t<Number>& _constants) {
        assert(matrix.rows() == vector.rows() && "Matrix and vector have to have same dimensionality.");

        // converts source object into a v-polytope
        auto temp = VPolytopeT<Number, Converter, Setting>(_constraints, _constants);

        // conversion is from here done just like V -> Zonotope
        *this = Converter::toZonotope(temp);
        std::cout << "I was called " << std::endl;

        uniteEqualVectors();
        removeEmptyGenerators();
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::ZonotopeT(std::size_t dimension, const vector_t<Number> &center, const matrix_t<Number> &generators) 
        : mDimension(dimension), mCenter(center), mGenerators(generators) {
        assert(center.rows() == generators.rows() && "Center and generators have to have same dimensionality.");
        uniteEqualVectors();
        removeEmptyGenerators();
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::ZonotopeT(const ZonotopeT<Number, Converter, Setting> &other, unsigned d1,
                                                     unsigned d2) {
        assert(other.mDimension != 0 && d1 >= 0 && d1 < other.mDimension && d2 >= 0 && d1 < other.mDimension &&
               d1 != d2 &&
               "d1 and d2 have to be in range of copied zonotope.");

        Eigen::Matrix<Number, 2, 1> center;
        Eigen::Matrix<Number, 2, Eigen::Dynamic> generators;
        center = {other.center()(d1), other.center()(d2)};

        generators.resize(Eigen::NoChange, other.size());
        generators << other.generators().row(d1), other.generators().row(d2);

        mDimension = 2;
        mCenter = center;
        mGenerators = generators;
        uniteEqualVectors();
        removeEmptyGenerators();
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>::~ZonotopeT() {
    }

/*****************************************************************************
 *                                                                           *
 *      Member functions - Getters, Setters and non-algorithm functions      *
 *                                                                           *
 *****************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    std::size_t ZonotopeT<Number, Converter, Setting>::dimension() const {
        return mDimension;
    }

    template<typename Number, typename Converter, typename Setting>
    Number ZonotopeT<Number, Converter, Setting>::supremum() const {
        // evaluate center first to obtain a basic value
        Number supremum = mCenter(0);
        for (unsigned d = 1; d < mCenter.rows(); ++d) {
            supremum = mCenter(d) > supremum ? mCenter(d) : supremum;
        }
        // take generators into consideration (only consider the positive ones, as we are looking for the "largest point")
        vector_t<Number> ones = vector_t<Number>::Ones(this->dimension());
        Number zs = (ones.transpose() * this->mGenerators).array().abs().sum();

        return supremum + zs;
    }

    template<typename Number, typename Converter, typename Setting>
    bool ZonotopeT<Number, Converter, Setting>::empty() const {
        if (mEmptyState == SETSTATE::UNKNOWN) {
            mEmptyState = mGenerators.cols() == 0 ? SETSTATE::EMPTY : SETSTATE::NONEMPTY;
        }
        assert(mEmptyState != SETSTATE::UNIVERSAL);
        return mEmptyState == SETSTATE::EMPTY;
    }

    template<typename Number, typename Converter, typename Setting>
    const vector_t<Number> &ZonotopeT<Number, Converter, Setting>::center() const {
        return mCenter;
    }

    template<typename Number, typename Converter, typename Setting>
    const matrix_t<Number> &ZonotopeT<Number, Converter, Setting>::generators() const {
        return mGenerators;
    }

    template<typename Number, typename Converter, typename Setting>
    Number ZonotopeT<Number, Converter, Setting>::order() const {
        // object empty.
        if (mGenerators.rows() == 0) {
            return Number(0);
        }
        return Number(mGenerators.cols()) / Number(mGenerators.rows());
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::setCenter(const vector_t<Number> &center) {
        if (mDimension == 0) {
            mDimension = center.rows();
            mGenerators = matrix_t<Number>::Zero(mDimension, 1);
        }
        assert((std::size_t) center.rows() == mDimension && "Center has to have same dimensionality as zonotope.");
        mCenter = center;
        uniteEqualVectors();
        removeEmptyGenerators();
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::setGenerators(const matrix_t<Number> &new_generators) {
        if (mDimension == 0) {
            mDimension = new_generators.rows();
            mCenter = vector_t<Number>::Zero(mDimension);
        }
        assert((std::size_t) new_generators.rows() == mDimension &&
               "Generators have to have same dimensionality as zonotope");
        mGenerators = new_generators;
        uniteEqualVectors();
        removeEmptyGenerators();
    }

    template<typename Number, typename Converter, typename Setting>
    bool ZonotopeT<Number, Converter, Setting>::addGenerators(const matrix_t<Number> &generators) {
        if (mDimension == 0) {
            mDimension = generators.rows();
        }

        assert((std::size_t) generators.rows() == mDimension &&
               "Added generators has to have same dimensionality as zonotope");
        if (mGenerators.rows() != generators.rows()) {
            setGenerators(generators);
        } else {
            matrix_t<Number> tmp = mGenerators;
            mGenerators.resize(tmp.rows(), generators.cols() + tmp.cols());
            mGenerators << tmp, generators;
        }
        uniteEqualVectors();
        removeEmptyGenerators();
        return true;
    }

    template<typename Number, typename Converter, typename Setting>
    std::size_t ZonotopeT<Number, Converter, Setting>::size() const {
        return mGenerators.cols();
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::removeGenerator(unsigned colToRemove) {
        Eigen::Index numRows = mGenerators.rows();
        Eigen::Index numCols = mGenerators.cols() - 1;

        if (colToRemove < numCols) {
            mGenerators.block(0, colToRemove, numRows, numCols - colToRemove) =
                    mGenerators.block(0, colToRemove + 1, numRows, numCols - colToRemove);
        }

        mGenerators.conservativeResize(numRows, numCols);
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::removeEmptyGenerators() {
        // TODO
        vector_t<Number> zero_vector = vector_t<Number>::Zero(mDimension);

        std::vector<unsigned> zeroIndex;
        for (unsigned i = 0; i < mGenerators.cols(); i++) {
            if (mGenerators.col(i) == zero_vector) {
                zeroIndex.push_back(i);
            }
        }

        for (std::vector<unsigned>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit) {
            removeGenerator(*rit);
        }
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::uniteEqualVectors() {
        vector_t<Number> zero_vector = vector_t<Number>::Zero(mDimension);

        std::vector<unsigned> zeroIndex;

        for (unsigned i = 0; i < mGenerators.cols(); i++) {
            for (unsigned j = (i + 1); j < mGenerators.cols(); j++) {
                if (mGenerators.col(i) == mGenerators.col(j) ||
                    linearDependent(vector_t<Number>(mGenerators.col(i)), vector_t<Number>(mGenerators.col(j))).first) {
                    zeroIndex.push_back(j);
                }
            }
            for (std::vector<unsigned>::reverse_iterator rit = zeroIndex.rbegin(); rit != zeroIndex.rend(); ++rit) {
                mGenerators.col(i) += mGenerators.col(*rit);

                removeGenerator(*rit);
            }
            zeroIndex.clear();
        }
    }

    template<typename Number, typename Converter, typename Setting>
    bool ZonotopeT<Number, Converter, Setting>::changeDimension(std::size_t new_dim) {
        assert(new_dim != 0 && "Cannot change dimensionality of zonotope to zero");
        if (new_dim == mDimension) {
            return false;
        } else {
            mCenter.conservativeResize(new_dim, Eigen::NoChange);
            mGenerators.conservativeResize(new_dim, Eigen::NoChange);

            // If new dim > old dim, initialize all new rows to zero
            for (unsigned i = mDimension; i < new_dim; i++) {
                mCenter.row(i).setZero();
                mGenerators.row(i).setZero();
            }

            mDimension = new_dim;
            return true;
        }
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::clear() {
        mGenerators.resize(0, 0);
        mCenter.resize(0, 1);
        mDimension = 0;
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::reduceOrder(unsigned limit) {
        // std::cout << __func__ << ": Current order: " << this->order() << std::endl;
        while (this->order() > limit) {
            matrix_t<Number> generators = mGenerators;
            Eigen::Index dim = mGenerators.rows();

            // create duplicates of generators to sort them
            std::vector<hypro::vector_t<Number>> sortedGenerators;
            for (Eigen::Index i = 0; i < generators.cols(); i++) {
                sortedGenerators.push_back(generators.col(i));
            }

            // Sort generators according to the difference between 1-norm and infty-norm
            // (i.e.: How suitable are the generators to
            // be overapproximated by an interval hull)
            std::sort(sortedGenerators.begin(), sortedGenerators.end(), ZUtility::compareVectors<Number>);

            // Row-wise sum of all 2*dim chosen generators (absolute value)
            vector_t<Number> sumVector = vector_t<Number>::Zero(dim);
            for (unsigned i = 0; i < 2 * (dim); i++) {
                sumVector += sortedGenerators[i].array().abs().matrix();
            }

            Eigen::Index numRemainingGenerators = Eigen::Index(sortedGenerators.size() - (2 * dim));

            matrix_t<Number> remainingGenerators = matrix_t<Number>(dim, numRemainingGenerators);

            // inserts the original remaining vectors
            for (Eigen::Index i = 0; i < numRemainingGenerators; i++) {
                remainingGenerators.col(i) = sortedGenerators[i + (2 * dim)];
            }

            // calculate interval hull of first 2n generators
            matrix_t<Number> intervalHull = sumVector.asDiagonal();

            matrix_t<Number> reducedGenerators = matrix_t<Number>(dim, remainingGenerators.cols() + dim);

            reducedGenerators << intervalHull, remainingGenerators;
            mGenerators = reducedGenerators;
        }
        // std::cout << __func__ << ": Reduced order: " << this->order() << std::endl;
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::reduceNumberRepresentation() {
        /*
        std::vector<vector_t<Number>> tmpGenerators;
        for(unsigned i = 0; i < mGenerators.cols(); ++i) {
            vector_t<Number> tmp = hypro::reduceNumberRepresentation(vector_t<Number>(mGenerators.col(i)));
            tmpGenerators.push_back( tmp );
        }
        for(unsigned i = 0; i < mGenerators.cols(); ++i) {
            mGenerators.col(i) = tmpGenerators[i];
        }
        */
    }

    template<typename Number, typename Converter, typename Setting>
    EvaluationResult<Number> ZonotopeT<Number, Converter, Setting>::evaluate(const vector_t<Number> &) const {
        // TODO
        return EvaluationResult<Number>();
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<EvaluationResult<Number>>
    ZonotopeT<Number, Converter, Setting>::multiEvaluate(const matrix_t<Number> &, bool) const {
        // TODO
        return std::vector<EvaluationResult<Number>>();
    }

/*****************************************************************************
 *                                                                           *
 *                           Algorithm Functions                             *
 *                                                                           *
 *****************************************************************************/

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::minkowskiSum(const ZonotopeT<Number, Converter, Setting> &rhs) const {
        assert(mDimension == rhs.dimension() && "Zonotope on RHS must have same dimensionality as current.");
        ZonotopeT<Number, Converter, Setting> result;
        result.setCenter(this->mCenter + rhs.mCenter);
        matrix_t<Number> tmp;
        tmp.resize(mDimension, rhs.size() + size());
        tmp << mGenerators, rhs.generators();
        result.setGenerators(tmp);
        result.uniteEqualVectors();
        result.removeEmptyGenerators();
        result.reduceOrder();
        return result;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::projectOn(const std::vector<std::size_t> &dimensions) const {
        if (dimensions.empty()) {
            return Empty();
        }

        matrix_t<Number> projectedGenerators = matrix_t<Number>::Zero(dimensions.size(), mGenerators.cols());

        for (unsigned generatorIndex = 0; generatorIndex < mGenerators.cols(); ++generatorIndex) {
            for (unsigned i = 0; i < dimensions.size(); ++i) {
                if (dimensions.at(i) < this->dimension()) {
                    projectedGenerators(i, generatorIndex) = mGenerators(dimensions.at(i), generatorIndex);
                }
            }
        }

        auto newCenter = hypro::projectOn(mCenter, dimensions);
        ZonotopeT<Number, Converter, Setting> res = ZonotopeT<Number, Converter, Setting>(newCenter.rows(),
                newCenter, projectedGenerators);
        res.reduceOrder();

        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::linearTransformation(const matrix_t<Number> &A) const {
        assert(A.cols() == mCenter.rows() &&
               "Matrix's dimensionality is different "
               "from zonotope's center's "
               "dimensionality.");
        assert(A.cols() == mGenerators.rows() &&
               "Matrix's dimensionality is "
               "different from zonotope's "
               "generators' dimensionality.");
        ZonotopeT<Number, Converter, Setting> result;
        result.setCenter(A * this->mCenter);
        result.setGenerators(A * this->mGenerators);
        return result;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::affineTransformation(const matrix_t<Number> &A,
                                                                const vector_t<Number> &b) const {
        assert(A.cols() == mCenter.rows() &&
               "Matrix's dimensionality is different "
               "from zonotope's center's "
               "dimensionality.");
        assert(A.cols() == mGenerators.rows() &&
               "Matrix's dimensionality is "
               "different from zonotope's "
               "generators' dimensionality.");
        ZonotopeT<Number, Converter, Setting> result;
        result.setCenter(A * this->mCenter + b);
        result.setGenerators(A * this->mGenerators);

        return result;
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<vector_t<Number>> ZonotopeT<Number, Converter, Setting>::computeZonotopeBoundary() {
        assert(mDimension == 2 && "Computing Zonotope boundaries only possible for Dim 2");

        this->removeEmptyGenerators();
        matrix_t<Number> generators = this->mGenerators;

        unsigned i;
        std::vector<vector_t<Number>> sortArray, verticesArray;

        // Reflect generators if y-value is negative
        Eigen::Matrix<Number, 1, Eigen::Dynamic> yValsRow = generators.row(1);

        for (i = 0; i < yValsRow.cols(); i++) {
            if (yValsRow(i) < 0) {
                generators.col(i) = -1 * generators.col(i);
            }
        }

        // Sort generators

        for (i = 0; i < generators.cols(); i++) {
            sortArray.push_back(generators.col(i));
        }

        std::sort(sortArray.begin(), sortArray.end(), ZUtility::compareColumnVectors<Number>);

        vector_t<Number> pm = mCenter - generators.rowwise().sum();

        verticesArray.push_back(pm);

        // Finding vertices of Zonotope
        for (i = 0; i < sortArray.size(); i++) {
            verticesArray.push_back(verticesArray.back() + 2 * sortArray[i]);
        }
        for (i = 0; i < sortArray.size(); i++) {
            verticesArray.push_back(verticesArray.back() - 2 * sortArray[i]);
        }

        return verticesArray;
    }

    template<typename Number, typename Converter, typename Setting>
    std::vector<Point<Number>> ZonotopeT<Number, Converter, Setting>::vertices(const matrix_t<Number> &) const {
        // uniteEqualVectors();

        // removeEmptyGenerators();

        // vector_t<Number> init = vector_t<Number>::Zero( this->dimension() );

        vector_t<Number> init = mCenter;

        std::vector<vector_t<Number>> possibleCorners = ZUtility::getCornersRecursive(mGenerators, init);
        std::vector<Point<Number>> res;

        for (const auto &coord: possibleCorners) {
            res.emplace_back(coord);
        }

        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    Number intersect2d(const ZonotopeT<Number, Converter, Setting> &input, const Halfspace<Number> &hp, int minOrMax) {
        assert(input.dimension() == hp.dimension() && input.dimension() == 2 &&
               "zonotope dimension must be of same dimension (only dim 2 accepted) "
               "as Halfspace");
        Eigen::Index size = Eigen::Index(input.size());
        matrix_t<Number> gUpper, gLower, generators = input.generators();
        matrix_t<Number> s, s1, pmNext, pm = input.center();

        // ensure that all generators are pointing either upwards or all downwards (depends on minOrMax)
        // minOrMax == 0 -> start from smallest point (cf. Algorithm Girard HSCC'08)
        for (Eigen::Index i = 0; i < size; i++) {
            // point downwards
            if ((generators(1, i) > 0 || (generators(1, i) == 0 && generators(0, i) > 0)) && minOrMax == 1) {
                generators.col(i) = -1 * generators.col(i);
            }  // point upwards
            else if ((generators(1, i) < 0 || (generators(1, i) == 0 && generators(0, i) < 0)) && minOrMax == 0) {
                generators.col(i) = -1 * generators.col(i);
            }
            // set pm successively to be the largest or lowest point starting from the center
            pm = pm - generators.col(i);
        }

        // Determine x-direction to forward - "we should look left or right", delete all generators pointing in the wrong direction.
        std::vector<unsigned> indexToRemove;
        if (pm(0) <= hp.offset()) {
            for (unsigned i = 0; i < generators.cols(); i++) {
                if (generators.col(i)(0) <= 0) indexToRemove.push_back(i);
            }
        } else {
            for (unsigned i = 0; i < generators.cols(); i++) {
                if (generators.col(i)(0) >= 0) indexToRemove.push_back(i);
            }
        }
        for (std::vector<unsigned>::reverse_iterator rit = indexToRemove.rbegin(); rit != indexToRemove.rend(); ++rit) {
            removeGenerator<Number>(*rit, generators);
        }

        s = 2 * generators.rowwise().sum();

        while (generators.cols() > 1) {
            std::vector<unsigned> gLowerIndices, gUpperIndices;
            // splitting the generators according to trigonometric order (angle) in relation to s
            // TODO: check if atan is available for FLOAT_T types
            Number sAngle = atan((Number) s(1) / (Number) s(0));
            for (unsigned i = 0; i < generators.cols(); i++) {
                Number angle = atan((Number) generators(1, i) / (Number) generators(0, i));
                if (angle - sAngle <= 0) {
                    gLowerIndices.push_back(i);
                } else if (angle - sAngle >= 0) {
                    gUpperIndices.push_back(i);
                }
            }

            // after splitting, establish two sets gUpper, gLower holding the splitting result.
            gUpper = generators;
            gLower = generators;

            // std::cout << "MinOrMax: " << minOrMax << std::endl;
            // std::cout << " S is: " << s << std::endl;
            // std::cout << " PM is: " << pm << std::endl;
            // std::cout << "Generators: "<< std::endl << generators << std::endl;
            // std::cout << "Indices gLowerIndices: " << gLowerIndices << " and gUpperIndices: " << gUpperIndices << std::endl;

            for (std::vector<unsigned>::reverse_iterator rit = gLowerIndices.rbegin();
                 rit != gLowerIndices.rend(); ++rit) {
                removeGenerator<Number>(*rit, gUpper);
            }
            for (std::vector<unsigned>::reverse_iterator rit = gUpperIndices.rbegin();
                 rit != gUpperIndices.rend(); ++rit) {
                removeGenerator<Number>(*rit, gLower);
            }
            assert(gUpper.cols() + gLower.cols() == generators.cols());  // Verify correct splitting.

            // Advance from pm to s1 (Line 17). The case distinction is necessary, as the trigonometric ordering is inverted
            // when advancing towards the negative direction ( pm(0) > hp.offset() ).
            if (pm(0) < hp.offset()) {
                s1 = (minOrMax == 1) ? 2 * gUpper.rowwise().sum() : 2 * gLower.rowwise().sum();
            } else {
                s1 = (minOrMax == 1) ? 2 * gLower.rowwise().sum() : 2 * gUpper.rowwise().sum();
            }

            // pmNext is the end of the line segment [p, p+s1]. Verify intersection.
            pmNext = pm + s1;
            if ((pm(0) <= hp.offset() && pmNext(0) >= hp.offset()) ||
                (pm(0) >= hp.offset() && pmNext(0) <= hp.offset())) {
                // TODO: Check, if this is still independent from the direction we are advancing to (left/right).
                generators = (minOrMax == 1) ? gLower : gUpper;

                // if there is no update, exit the loop -> copes with numeric problems regarding atan and linear dependence
                // of generators
                if (s == s1) {
                    break;
                }

                s = s1;
                // This should not happen, otherwise we have an infinite loop.
                assert(minOrMax != 1 || !gUpperIndices.empty());
                assert(minOrMax != 0 || !gLowerIndices.empty());
            } else {
                // TODO: Check, if this is still independent from the direction we are advancing to (left/right).
                generators = (minOrMax == 1) ? gUpper : gLower;
                s = s - s1;
                pm = pmNext;

                // If there is no progress we can end the algorithm - it is an over-approximation, thus correct.
                if (s == s - s1) {
                    break;
                }
            }
        }
        pmNext = pm + s;
        Number m = pm(1) + (hp.offset() - pm(0)) * (pmNext(1) - pm(1)) / (pmNext(0) - pm(0));
        return m;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    intersectZonotopeHalfspaceDSearch(const ZonotopeT<Number, Converter, Setting> &inputZonotope,
                                      const Halfspace<Number> &hp) {
        assert(inputZonotope.dimension() == hp.dimension() && inputZonotope.dimension() == 2 &&
               "zonotope dimension must be of same "
               "dimension (only dim 2 accepted) as "
               "Halfspace");
        ZonotopeT<Number, Converter, Setting> res(inputZonotope);
        res.uniteEqualVectors();

        Number p1 = intersect2d<Number>(res, hp, 1);
        Eigen::Matrix<Number, 2, 1> p1Vec = {0, p1};
        Number p2 = intersect2d<Number>(res, hp, 0);
        Eigen::Matrix<Number, 2, 1> p2Vec = {0, p2};

        res = ZonotopeT<Number, Converter, Setting>(p1Vec.rows(), (p1Vec + p2Vec) / 2, (p1Vec - p2Vec) / 2);
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    static ZonotopeT<Number, Converter, Setting>
    intersectZonotopeHalfspace(ZonotopeT<Number, Converter, Setting> &inputZonotope, const Halfspace<Number> &hp,
                               matrix_t<Number> &minMaxOfLine) {
        assert(inputZonotope.dimension() == hp.dimension() &&
               "Zonotope and Halfspace have to be of similar dimensions");
        std::vector<vector_t<Number>> vertices = inputZonotope.computeZonotopeBoundary();
        vertices.pop_back();

        std::size_t numPts = vertices.size();
        Eigen::Matrix<Number, 2, 2> xhp;

        // Compute Halfspace points xhp
        if (hp.normal()(1) == 0) {
            Eigen::Matrix<Number, 2, 1> minVecY, maxVecY;
            minVecY = *std::min_element(vertices.begin(), vertices.end(), ZUtility::compareYVal<Number>);
            maxVecY = *std::max_element(vertices.begin(), vertices.end(), ZUtility::compareYVal<Number>);

            xhp.row(1) << (minVecY(1) - carl::abs(Number(maxVecY(1) - minVecY(1))) / 10),
                    (maxVecY(1) + carl::abs(Number(maxVecY(1) - minVecY(1))) / 10);
            Eigen::Matrix<Number, 1, 2> eVec = {hp.offset(), hp.offset()};
            xhp.row(0) = (eVec - hp.normal()(1) * xhp.row(1)) / hp.normal()(0);
        } else {
            Eigen::Matrix<Number, 2, 1> minVecX, maxVecX;
            minVecX = *std::min_element(vertices.begin(), vertices.end(), ZUtility::compareXVal<Number>);
            maxVecX = *std::max_element(vertices.begin(), vertices.end(), ZUtility::compareXVal<Number>);

            xhp.row(0) << (minVecX(0) - carl::abs(Number(maxVecX(0) - minVecX(0))) / 10),
                    (maxVecX(0) + carl::abs(Number(maxVecX(0) - minVecX(0))) / 10);
            Eigen::Matrix<Number, 1, 2> eVec = {hp.offset(), hp.offset()};
            xhp.row(1) = (eVec - hp.normal()(0) * xhp.row(0)) / hp.normal()(1);
        }
        // Real algorithm starts here

        ZUtility::Line_t<Number> lnhp(xhp.col(0), (xhp.col(1) - xhp.col(0)));

        // Naming variables: dzbme is used for sorting vertices nearest to the line
        //                   dzb is used to keep track of d'*zb values
        std::valarray<Number> dzbme(vertices.size()), dzb(vertices.size());
        unsigned minIdx = 0, i;
        for (i = 0; i < vertices.size(); i++) {
            assert(hp.normal().rows() == vertices[i].rows());
            matrix_t<Number> res = hp.normal().transpose() * vertices[i];
            assert(res.rows() == 1 && res.cols() == 1);
            dzbme[i] = (res(0, 0) - hp.offset());
            dzb[i] = (res(0, 0));
        }

        std::vector<unsigned> ltZeroIdxArray, mtZeroIdxArray;
        for (i = 0; i < dzbme.size(); i++) {
            if (carl::abs(dzbme[i]) < carl::abs(dzbme[minIdx])) {
                minIdx = i;
            }
            if (dzbme[i] < 0) ltZeroIdxArray.push_back(i);
            if (dzbme[i] > 0) mtZeroIdxArray.push_back(i);
        }

        // TODO: circshift vertices vector
        dzb = dzb.cshift(minIdx);
        dzbme = dzbme.cshift(minIdx);

        // Essentially create a temporary val array to do cshift operation
        // and copy back value into vertices std::vector
        std::valarray<vector_t<Number>> verticesValArray(vertices.data(), vertices.size());
        verticesValArray = verticesValArray.cshift(minIdx);
        vertices.assign(std::begin(verticesValArray), std::end(verticesValArray));

        std::size_t nil, il1p2, il2p1, il2p2;
        if (dzbme[0] < 0) {
            nil = ltZeroIdxArray.size();
            if (dzbme[1] < 0) {
                il1p2 = numPts;
                il2p1 = nil;
            } else {
                il1p2 = 2;
                il2p1 = numPts - nil + 1;
            }
        } else {
            nil = mtZeroIdxArray.size();
            if (dzbme[1] > 0) {
                il1p2 = numPts;
                il2p1 = nil;
            } else {
                il1p2 = 2;
                il2p1 = numPts - nil + 1;
            }
        }

        if (nil == 1)
            il2p2 = 1;
        else
            il2p2 = il2p1 + 1;

        ZUtility::Line_t<Number> ln(vertices[0], vertices[il1p2 - 1] - vertices[0]);
        // TODO: compute line intersection
        Eigen::Matrix<Number, 2, 1> p1 = computeLineIntersection(ln, lnhp);

        ln.point = vertices[il2p1 - 1];
        ln.direction = vertices[il2p2 - 1] - vertices[il2p1 - 1];
        // TODO: compute line intersection
        Eigen::Matrix<Number, 2, 1> p2 = computeLineIntersection(ln, lnhp);

        ZonotopeT<Number, Converter, Setting> resZonotope(p1.rows(), (p1 + p2) / 2, (p1 - p2) / 2);

        minMaxOfLine.resize(2, 2);
        minMaxOfLine.row(0) = (comparePoint(p1, p2)) ? p1.transpose() : p2.transpose();  // min [x,y] here
        minMaxOfLine.row(1) = (comparePoint(p1, p2)) ? p2.transpose() : p1.transpose();  // max [x,y] here

        return resZonotope;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    intersectAlamo(const ZonotopeT<Number, Converter, Setting> &inputZonotope, const Halfspace<Number> &hp) {
        assert(inputZonotope.dimension() == hp.dimension());
        // Determine intersect as Zonotope, according to Tabatabaeipour et al., 2013
        Number sgm = 0;     // could be redundant
        matrix_t<Number> H = inputZonotope.generators();
        matrix_t<Number> HHT = H * H.transpose();
        vector_t<Number> center = inputZonotope.center();
        vector_t<Number> lambda =
                (HHT * hp.normal()) / ((hp.normal().transpose() * HHT * hp.normal())(0, 0) + sgm * sgm);

        matrix_t<Number> new_gen, identity;
        ZonotopeT<Number, Converter, Setting> zg(inputZonotope.dimension());

        zg.setCenter(center + lambda * (hp.offset() - (hp.normal().transpose() * center)(0, 0)));

        identity.resize(inputZonotope.dimension(), inputZonotope.dimension());

        identity.setIdentity();

        new_gen = (identity - lambda * (hp.normal().transpose())) * H;
        zg.setGenerators(new_gen);

        return zg;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    intersectNDProjection(const ZonotopeT<Number, Converter, Setting> &inputZonotope, const Halfspace<Number> &hp,
                          matrix_t<Number> &minMaxOfLine) {
        assert(hp.dimension() == inputZonotope.dimension() &&
               "Intersect ND: input zonotope and input Halfspace must have same "
               "dimensionality");
        ZonotopeT<Number, Converter, Setting> resultZonotope;
        vector_t<double> dVec;
        matrix_t<double> kernel;
        dVec = convert<Number, double>(hp.normal());
        Eigen::JacobiSVD<matrix_t<double>> svd(dVec.transpose(), Eigen::ComputeFullU | Eigen::ComputeFullV);
        // Using SVD to calculate nullspace (kernel)
        kernel = svd.matrixV().block(0, 1, svd.matrixV().rows(), svd.matrixV().cols() - 1);

        Eigen::Index nd;
        std::size_t dim;
        nd = kernel.cols();
        dim = inputZonotope.dimension();

        matrix_t<double> dpQg;
        matrix_t<Number> resultGenerators;
        double dpQc;
        minMaxOfLine.resize(2, nd);
        resultGenerators.resize(dim, nd);
        vector_t<double> inCenterD = convert<Number, double>(inputZonotope.center());
        dpQc = dVec.dot(inCenterD);
        dpQg = dVec.transpose() * convert<Number, double>(inputZonotope.generators());

        for (Eigen::Index i = 0; i < nd; i++) {
            // construct 2 dimensional Zonotope
            Eigen::Matrix<double, 2, 1> projCenter;
            Eigen::Matrix<double, 2, Eigen::Dynamic> projGenerators;

            projCenter << dpQc, kernel.col(i).dot(inCenterD);
            projGenerators.resize(2, dpQg.cols());
            projGenerators << dpQg, kernel.col(i).transpose() * convert<Number, double>(inputZonotope.generators());

            ZonotopeT<double, Converter, Setting> projZonotope(projCenter.rows(), projCenter, projGenerators), tempResZonotope;

            // Upon projection, the Halfspace now has a d vector of [1;0] but retains
            // its e scalar
            Eigen::Matrix<double, 2, 1> lgDVector(1, 0);
            Halfspace<double> lg(lgDVector, toDouble(hp.offset()));

            //        matrix_t<Number> dummyMinMax;
            tempResZonotope = intersectZonotopeHalfspaceDSearch(projZonotope, lg);

            Eigen::Matrix<Number, 2, 1> p1, p2;
            p1 = convert<double, Number>(tempResZonotope.center()) +
                 convert<double, Number>(tempResZonotope.generators());
            p2 = convert<double, Number>(tempResZonotope.center()) -
                 convert<double, Number>(tempResZonotope.generators());

            // find min and max points of intersect between zonogone and Halfspace
            // we only consider the y axis owing to the [1;0] property of the projected
            // space as mentioned earlier
            minMaxOfLine(0, i) = (p1(1) < p2(1)) ? p1(1) : p2(1);
            minMaxOfLine(1, i) = (p1(1) > p2(1)) ? p1(1) : p2(1);

            resultGenerators.conservativeResize(dim, i + 1);
            resultGenerators.col(i)
                    << Number((minMaxOfLine(1, i) - minMaxOfLine(0, i)) / 2) * convert<double, Number>(kernel.col(i));
        }

        resultZonotope.setCenter(
                convert<double, Number>(kernel) * ((minMaxOfLine.row(1) + minMaxOfLine.row(0)) / 2).transpose() +
                hp.offset() * hp.normal());
        resultZonotope.setGenerators(resultGenerators);

        return resultZonotope;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::intersect(const Halfspace<Number> &hp, int method) {
        matrix_t<Number> EMPTY_MATRIX(0, 0);
        return this->intersect(hp, EMPTY_MATRIX, method);
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::intersect(const Halfspace<Number> &hp, matrix_t<Number> &minMaxOfLine,
                                                     int method) {
        assert(hp.dimension() == mDimension && "Zonotope's dimensionality must be same as Halfspace's dimensionality.");

        ZonotopeT<Number, Converter, Setting> result;

        // Determine if intersection is found, according to Girard, Guernic, 2008
        matrix_t<Number> emdcTmp = hp.normal().transpose() * mCenter;
        assert(emdcTmp.rows() == 1 && emdcTmp.cols() == 1);
        Number emdc = hp.offset() - emdcTmp(0, 0);
        Number zs = (hp.normal().transpose() * mGenerators).array().abs().sum();

        bool hasIntersect = (emdc > -zs && zs > emdc);
        if (hasIntersect) {
            switch (method) {
                case ZUtility::ALAMO:
                    // std::cout << "Using Alamo's method with dimension " << mDimension << std::endl;
                    result = intersectAlamo(*this, hp);
                    break;
                case ZUtility::NDPROJECTION: {
                    if (mDimension == 2) {
                        // std::cout << "Using Girard's method with dimension 2 " << std::endl;
                        result = intersectZonotopeHalfspace(*this, hp, minMaxOfLine);
                    } else {
                        // std::cout << "Using Girard's method with dimension " << mDimension << std::endl;
                        result = intersectNDProjection<Number>(*this, hp, minMaxOfLine);
                    }
                    break;
                }
                    //            case DICHOTOMIC2D:
                    //                assert(mDimension==2);
                    //                result = intersectZonotopeHalfspaceDSearch(*this, hp);
                    //                break;
                default:
                    break;
            }
        }

        return result;
    }

#ifdef HYPRO_USE_PPL
    template <typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting> ZonotopeT<Number, Converter, Setting>::intersect( const Parma_Polyhedra_Library::Constraint& halfspace ) const {
        assert( halfspace.space_dimension() == this->mDimension );
        Number e = halfspace.inhomogeneous_term().get_d();
        vector_t<Number> dVec;

        dVec.resize( halfspace.space_dimension(), Eigen::NoChange );

        for ( unsigned i = 0; i < halfspace.space_dimension(); i++ ) {
            dVec( i ) = -1 * halfspace.coefficient( Parma_Polyhedra_Library::Variable( i ) ).get_d();
        }

        return this->intersectHalfspace( Halfspace<Number>( dVec, e ) );
    }
#endif

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::intersectHalfspace(const Halfspace<Number> &rhs) const {
        if (this->empty()) {
            return *this;
        }
        ZonotopeT<Number, Converter, Setting> result;
        /* zs holds the 1-norm (Manhattan-Norm) of the direction projected onto the
         * generators
         *  -> we sum the projections of the direction onto the generators (take only
         * positive ones to prevent from
         * canceling)
         * -> this holds the farest we can go without leaving the zonotope
         */
        Number zs = (rhs.normal().transpose() * this->mGenerators).array().abs().sum();
        // projection of normal on center -> offset induced by the center vector.
        Number dc = rhs.normal().dot(this->mCenter);
        // qu holds the maximal value one can go into direction of the Halfspace ->
        // if this is less than the scalar, the
        // zonotope is fully contained
        Number qu = dc + zs, qd = dc - zs;    // qd holds the minimal value of the zonotope generators
        // evaluated into the direction of the
        // Halfspace (with respect to the center)
        // Qu and Qd are the offsets of the supporting hyperplanes in direction of the normal vector of the half-space
        if (qd <= rhs.offset()) {         // the zonotope is below the Halfspace -> there is an
            // intersection
            if (qu <= rhs.offset()) {     // the zonotopes maximal evaluation is also below the
                // Halfspace -> it is fully contained
                result = *this;
            } else {  // partly contained
                // sigma is half the distance between the Halfspace and the "lowest"
                // point of the zonotope.
                Number sigma = (rhs.offset() - qd) / 2, d = (qd + rhs.offset()) /
                                                            2;  // d is half the distance between the lowest point and the center and the offset
                matrix_t<Number> HHT = this->mGenerators * this->mGenerators.transpose();
                vector_t<Number> lambda =
                        HHT * rhs.normal() / ((rhs.normal().transpose() * HHT * rhs.normal())(0, 0) + sigma * sigma);
                result.setCenter(this->mCenter + lambda * (d - dc));
                matrix_t<Number> identity = matrix_t<Number>::Identity(mDimension, mDimension);
                result.setGenerators((identity - lambda * rhs.normal().transpose()) * this->mGenerators);
                result.addGenerators(sigma * lambda);
            }
        }
        result.reduceOrder();
        return result;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::intersectHalfspaces(const matrix_t<Number> &mat,
                                                               const vector_t<Number> &vec) const {
        if (this->empty()) {
            return *this;
        }
        assert(mat.rows() == vec.rows());
        ZonotopeT<Number, Converter, Setting> res = *this;

        // first, detect intersections with lines modeled as intersections with two halfspaces -> improve precision by using line intersection
        std::vector<std::pair<unsigned, unsigned>> linePairs;
        std::set<unsigned> lineConstraints;
        for (unsigned firstHalfspaceIndex = 0; firstHalfspaceIndex < mat.rows(); ++firstHalfspaceIndex) {
            for (unsigned secondHalfspaceIndex = firstHalfspaceIndex + 1;
                 secondHalfspaceIndex < mat.rows(); ++secondHalfspaceIndex) {
                // check condition for a line intersection - the 2nd normal is the negated 1st and the constants are the same, except the sign.
                if (mat.row(firstHalfspaceIndex) == -mat.row(secondHalfspaceIndex) &&
                    vec(firstHalfspaceIndex) == -vec(secondHalfspaceIndex)) {
                    linePairs.emplace_back(firstHalfspaceIndex, secondHalfspaceIndex);
                    lineConstraints.insert(firstHalfspaceIndex);
                    lineConstraints.insert(secondHalfspaceIndex);
                }
            }
        }

        // perform line intersection first TODO: What is more precise?
        for (unsigned lineIndex = 0; lineIndex < linePairs.size(); ++lineIndex) {
            unsigned firstConstraintIndex = linePairs.at(lineIndex).first;
            res = res.intersect(
                    Halfspace<Number>(vector_t<Number>(mat.row(firstConstraintIndex)), vec(firstConstraintIndex)),
                    ZUtility::NDPROJECTION);
        }

        if (res.empty()) {
            return res;
        }

        for (unsigned constraintIndex = 0; constraintIndex < mat.rows(); ++constraintIndex) {
            // just intersect with constraints not being part of a line
            if (lineConstraints.find(constraintIndex) == lineConstraints.end()) {
                res = res.intersectHalfspace(
                        Halfspace<Number>(vector_t<Number>(mat.row(constraintIndex)), vec(constraintIndex)));
                if (res.empty()) {
                    return res;
                }
            }
        }
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    std::pair<CONTAINMENT, ZonotopeT<Number, Converter, Setting>>
    ZonotopeT<Number, Converter, Setting>::satisfiesHalfspace(const Halfspace<Number> &rhs) const {
        if (this->empty()) {
            return std::make_pair(CONTAINMENT::NO, *this);
        }
        ZonotopeT<Number, Converter, Setting> result;
        /* zs holds the 1-norm (Manhattan-Norm) of the direction projected onto the
         * generators
         *  -> we sum the projections of the direction onto the generators (take only
         * positive ones to prevent from
         * canceling)
         * -> this holds the farest we can go without leaving the zonotope
         */
        Number zs = (rhs.normal().transpose() * this->mGenerators).array().abs().sum();
        // projection of normal on center -> offset induced by the center vector.
        Number dc = rhs.normal().dot(this->mCenter);
        bool limited = false;
        // qu holds the maximal value one can go into direction of the Halfspace ->
        // if this is less than the scalar, the
        // zonotope is fully contained
        Number qu = dc + zs, qd = dc - zs;    // qd holds the minimal value of the zonotope generators
        // evaluated into the direction of the
        // Halfspace (with respect to the center)
        if (qd <= rhs.offset()) {            // the zonotope is below the Halfspace -> there is an
            // intersection
            if (qu <= rhs.offset()) {        // the zonotopes maximal evaluation is also below the
                // Halfspace -> it is fully contained
                result = *this;
            } else {  // partly contained
                // sigma is half the distance between the Halfspace and the "lowest"
                // point of the zonotope.
                limited = true;
                Number sigma = (rhs.offset() - qd) / 2, d = (qd + rhs.offset()) / 2;  // d holds ?
                matrix_t<Number> HHT = this->mGenerators * this->mGenerators.transpose();
                vector_t<Number> lambda =
                        HHT * rhs.normal() / ((rhs.normal().transpose() * HHT * rhs.normal())(0, 0) + sigma * sigma);
                result.setCenter(this->mCenter + lambda * (d - dc));
                matrix_t<Number> identity;
                identity.resize(mDimension, mDimension);
                identity.setIdentity();
                result.setGenerators((identity - lambda * rhs.normal().transpose()) * this->mGenerators);
                result.addGenerators(sigma * lambda);
            }
            result.reduceOrder();
            if (limited) {
                return std::make_pair(CONTAINMENT::PARTIAL, std::move(result));
            } else {
                return std::make_pair(CONTAINMENT::FULL, std::move(result));
            }
        }
        return std::make_pair(CONTAINMENT::NO, std::move(result));
    }

    template<typename Number, typename Converter, typename Setting>
    std::pair<CONTAINMENT, ZonotopeT<Number, Converter, Setting>>
    ZonotopeT<Number, Converter, Setting>::satisfiesHalfspaces(const matrix_t<Number> &mat,
                                                               const vector_t<Number> &vec) const {
        if (this->empty()) {
            return std::make_pair(CONTAINMENT::NO, *this);
        }
        assert(mat.rows() == vec.rows());
        std::pair<CONTAINMENT, ZonotopeT<Number, Converter, Setting>> resultPair = std::make_pair(CONTAINMENT::NO,
                                                                                                  *this);

        resultPair.second = resultPair.second.intersectHalfspaces(mat, vec);
        if (!resultPair.second.empty()) {
            // Check whether *this is contained fully or partially:
            // Sum up all generators in one vector
            vector_t<Number> summedGenerators = vector_t<Number>::Zero(mDimension);
            for (int k = 0; k < mGenerators.rows(); k++) {
                summedGenerators(k) = mGenerators.row(k).array().abs().sum();
            }

            // For every halfspace:
            for (int i = 0; i < mat.rows(); i++) {
                // Build extreme point according to coefficients of halfspace
                vector_t<Number> extremum = vector_t<Number>::Zero(mDimension);
                for (int j = 0; j < mat.cols(); j++) {
                    extremum(j) = mat(i, j) > 0 ? summedGenerators(j) : Number(-1) * summedGenerators(j);
                }
                extremum += mCenter;

                // Check if extreme point is contained in current halfspace, if yes, then zonotope is fully contained
                // else zonotope is only partially contained
                Halfspace<Number> hs = Halfspace<Number>(mat.row(i), vec(i));
                bool containsExtremum = hs.contains(extremum);
                if (!containsExtremum) {
                    resultPair.first = CONTAINMENT::PARTIAL;
                    return resultPair;
                }
            }
            resultPair.first = CONTAINMENT::FULL;
        } else {
            resultPair.first = CONTAINMENT::NO;
        }

        /*
        for(unsigned constraintIndex = 0; constraintIndex < mat.rows(); ++constraintIndex) {
            resultPair = resultPair.second.satisfiesHalfspace(Halfspace<Number>(vector_t<Number>(mat.row(constraintIndex)), vec(constraintIndex)));
            if(resultPair.first == false) {
                return resultPair;
            }
        }
        */
        return resultPair;
    }

#ifdef HYPRO_USE_PPL
    template <typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting> ZonotopeT<Number, Converter, Setting>::intersect( const Parma_Polyhedra_Library::C_Polyhedron& rhs ) const {
        // Get set of half spaces
        const Parma_Polyhedra_Library::Constraint_System& cs = rhs.constraints();
        ZonotopeT<Number, Converter, Setting> curZonotope( *this );

        // Iterate through all constraints of the polyhedron
        for ( const auto& constr : cs ) {
            //        vector_t<Number> d_vector;
            //        Number e;
            //        d_vector.resize(dim,1);
            //
            //        // PPL represents constraints in the form of a*x1 + b*x2 + ...
            //        {>,>=} q
            //        // Note: e does not need to be negated 'cause PPL returns value of
            //        inhomogenous_term on the LHS of
            //        inequality
            //        e = constr.inhomogeneous_term().get_d();
            //        for (unsigned i=0; i<constr.space_dimension(); i++) {
            //            // each coefficient has to be negated due to >= in PPL instead
            //            of <=
            //            d_vector(i) = -1*constr.coefficient(Variable(i)).get_d();
            //        }
            //
            //        // zs is ||H^t * n || _ 1
            //        Number zs =
            //        (d_vector.transpose()*cur_zonotope.generators()).array().abs().sum();
            //        Number dc = d_vector.transpose()*cur_zonotope.center();
            //        Number qu = dc + zs, qd = dc - zs;
            //
            //        if (qd<=e) {
            //            if (qu<=e) {
            //                // do nothing
            //            }
            //            else {
            //                Number sgm = (e-qd)/2, d = (qd+e)/2;
            //                vector_t<Number> lambda =
            //                ((cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector)/
            //                                (d_vector.transpose()*(cur_zonotope.generators()*cur_zonotope.generators().transpose())*d_vector+sgm*sgm);
            //
            //                ZonotopeT<Number,Converter,Setting> new_zonotope;
            //                new_zonotope.setCenter(cur_zonotope.center()+lambda*(d-dc));
            //
            //                matrix_t<Number> new_gen1, new_gen2, identity;
            //                identity.resize(dim, dim);
            //                identity.setIdentity();
            //                new_gen1 =
            //                (identity-lambda*d_vector.transpose())*cur_zonotope.generators();
            //                new_gen2 = sgm*lambda;
            //                new_zonotope.setGenerators(new_gen1);
            //                new_zonotope.addGenerators(new_gen2);
            //                cur_zonotope = new_zonotope;
            //            }
            //        }
            //        else {
            //            return false;
            //        }
            curZonotope = curZonotope.intersect( constr );

            bool intersectFound = curZonotope.empty();
            if ( !intersectFound ) return curZonotope;
        }
        return curZonotope;
        // TODO: QUESTION! If one iteration yields empty set, should we break out of
        // loop?
    }
#endif

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::unite(const ZonotopeT<Number, Converter, Setting> &other) const {
        assert(mDimension == other.mDimension &&
               "Zonotopes must be of same "
               "dimension in order to carry out "
               "convex hull operations.");
        TRACE("hypro.representations", "Union.");
        std::size_t numGenCurrent, numGenOther;
        ZonotopeT<Number, Converter, Setting> temp;
        numGenCurrent = this->size();
        numGenOther = other.size();
        matrix_t<Number> R1, R2;
        vector_t<Number> c1, c2;
        R1 = this->mGenerators;
        R2 = other.mGenerators;
        c1 = this->mCenter;
        c2 = other.mCenter;

        // common traits of center and generators for all two zonotopes
        temp.setCenter((c1 + c2) * Number(Number(1) / Number(2)));

        if (numGenCurrent > numGenOther) {
            matrix_t<Number> R11, R12;
            R11 = R1.block(0, 0, mDimension, numGenOther);
            R12 = R1.block(0, numGenOther, mDimension, numGenCurrent - numGenOther);

            temp.setGenerators((R2 + R11) * Number(Number(1) / Number(2)));
            temp.addGenerators((c1 - c2) * Number(Number(1) / Number(2)));
            temp.addGenerators((R11 - R2) * Number(Number(1) / Number(2)));
            temp.addGenerators(R12);
        } else if (numGenCurrent < numGenOther) {
            matrix_t<Number> R21, R22;

            R21 = R2.block(0, 0, mDimension, numGenCurrent);
            R22 = R2.block(0, numGenCurrent, mDimension, numGenOther - numGenCurrent);

            temp.setGenerators((R1 + R21) * Number(Number(1) / Number(2)));
            temp.addGenerators((c2 - c1) * Number(Number(1) / Number(2)));
            temp.addGenerators((R21 - R1) * Number(Number(1) / Number(2)));
            temp.addGenerators(R22);
        } else {
            temp.setGenerators((R1 + R2) * Number(Number(1) / Number(2)));
            temp.addGenerators((c1 - c2) * Number(Number(1) / Number(2)));
            temp.addGenerators((R1 - R2) * Number(Number(1) / Number(2)));
        };
        TRACE("hypro.representations", "Number generators after union: " << temp.generators().cols());
        return temp;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting>
    ZonotopeT<Number, Converter, Setting>::unite(const std::vector<ZonotopeT<Number, Converter, Setting>> &sets) {
        ZonotopeT<Number, Converter, Setting> res = sets.begin();
        for (auto zonoIt = ++(sets.begin()); zonoIt != sets.end(); ++zonoIt) {
            res = res.unite(*zonoIt);
        }
        return res;
    }

    template<typename Number, typename Converter, typename Setting>
    ZonotopeT<Number, Converter, Setting> ZonotopeT<Number, Converter, Setting>::intervalHull() const {
        ZonotopeT<Number, Converter, Setting> result;
        vector_t<Number> imax, imin, sumOfGenerators, center = this->mCenter;
        matrix_t<Number> generators = this->mGenerators;
        ZonotopeT<Number, Converter, Setting> temp;

        sumOfGenerators = generators.cwiseAbs().rowwise().sum();

        imax = center + sumOfGenerators;
        imin = center - sumOfGenerators;

        temp.setCenter((imax + imin) * carl::rationalize<Number>(0.5));

        temp.setGenerators(((imax - imin) * carl::rationalize<Number>(0.5)).cwiseAbs().asDiagonal());

        result = temp;
        return result;
    }

    template<typename Number, typename Converter, typename Setting>
    bool ZonotopeT<Number, Converter, Setting>::contains(const Point<Number> &point) const {
        // create system of generators bounded by -1 and 1. We need to test whether the point can be
        // described by a linear combination of the generators with coefficients -1 to 1. Each generator
        // is modeled as a bounded variable. Do not forget the influence of the center.

        std::size_t dim = this->dimension();
        matrix_t<Number> constraints = matrix_t<Number>::Zero(4 * dim, this->mGenerators.cols());
        vector_t<Number> constants = vector_t<Number>::Ones(4 * dim);

        // set generators
        constraints.block(0, 0, dim, this->mGenerators.cols()) = mGenerators;
        constraints.block(dim, 0, dim, this->mGenerators.cols()) = -mGenerators;
        // set bounds for the generators
        constraints.block(2 * dim, 0, dim, dim) = matrix_t<Number>::Identity(dim, dim);
        constraints.block(3 * dim, 0, dim, dim) = -matrix_t<Number>::Identity(dim, dim);

        // set point
        constants.block(0, 0, dim, 1) = point.rawCoordinates() - this->mCenter;
        constants.block(dim, 0, dim, 1) = -(point.rawCoordinates() - this->mCenter);

        // check containment
        Optimizer<Number> opt(constraints, constants);
        return opt.checkConsistency();
    }

    template<typename Number, typename Converter, typename Setting>
    void ZonotopeT<Number, Converter, Setting>::print() const {
        std::cout << this->mCenter << std::endl;
        std::cout << this->mGenerators << std::endl;
    }
}  // namespace hypro
