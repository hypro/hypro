/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2016-03-17
 */

#include "Converter.h"

#ifndef INCL_FROM_CONVERTERHEADER
static_assert( false, "This file may only be included indirectly by Converter.h" );
#endif

namespace hypro {

/**
 * Is the caller function for the recursive method that computes exactly one boundary point for each direction that it gets (via support function)
 */
    template<typename Number, typename Converter, typename inSetting>
    std::vector<Point<Number>> computeBoundaryPointsExpensive(const SupportFunctionT<Number, Converter, inSetting> &sf,
                                                              const matrix_t<Number> &directions) {
        // determines how many directions need to be checked
        Eigen::Index numberOfDirections = directions.rows();
        // gets dimension in which is currently computed
        Eigen::Index dim = directions.cols();
        // only continue if directions and object match dimensionwise
        assert(dim == Eigen::Index(sf.dimension()));
        // generates an empty PointVector for the return value
        std::vector<Point<Number>> res;
        // if the function has an object that is not yet certainly a singleton (i.e. dimension is greater than zero)
        if (dim > 0) {
            // generates an empty PointVector for the return values of the recursive calls
            std::vector<Point<Number>> recursiveSolutions;
            for (Eigen::Index i = 0; i < numberOfDirections; ++i) {
                // determines current evaluation direction
                vector_t<Number> curNormal = directions.row(i);

                // lets the support function evaluate the offset of the halfspace for the current direction
                EvaluationResult<Number> offset = sf.evaluate(curNormal);
                // if result is infinity, try the next direction
                if (offset.errorCode == SOLUTION::INFTY) {
                    continue;
                }
                Number constant = offset.supportValue;

                // creates a Halfspacevector containing only the recently created Halfspace
                std::vector<Halfspace<Number>> curPlaneVector;
                curPlaneVector.emplace_back(curNormal, constant);
                curPlaneVector.emplace_back(-curNormal, -constant);
                assert(curPlaneVector.size() == 2);

                // intersects the current support function with the Halfspace
                SupportFunctionT<Number, Converter, inSetting> curPlaneSup = SupportFunctionT<Number, Converter, inSetting>(
                        curPlaneVector);
                // std::cout << "current supportplane:" << std::endl;
                curPlaneSup.print();
                SupportFunctionT<Number, Converter, inSetting> curFace = sf.intersect(curPlaneSup);
                // std::cout << "current face:" << std::endl;
                curFace.print();
                // only continue if face has still the same dimension as the source object (although it is technically now a dim-1 object at most)
                assert(Eigen::Index(curFace.dimension()) == dim);

                // call of the recursive sub-function for the current face
                recursiveSolutions.push_back(
                        computeBoundaryPointsExpensiveRecursive(curFace, directions, std::size_t(dim - 1)));
            }
            // removes duplicate points in order to enable the arithmetic mean to yield best possible results
            recursiveSolutions = Point<Number>::removeDuplicatePoints(recursiveSolutions);
            res = recursiveSolutions;
            // kickoff function gets called with a point for some reason
        } else {  // dim == 0
            // evaluates the object in the first direction (any direction produces the same result)
            EvaluationResult<Number> point = sf.evaluate(directions.row(1));
            // there needs to be a result here, otherwise something went terribly wrong
            assert(point.errorCode != SOLUTION::INFEAS && point.errorCode != SOLUTION::UNKNOWN);
            res.emplace_back(point.optimumValue);
            assert(sf.contains(Point<Number>(point.optimumValue)));
        }
        return res;
    }

/*
 *Recursively computes some boundary points that lie relatively central for each face of the object, this function is constructed to only be called by computeBoundaryPoints
 */
    template<typename Number, typename Converter, typename inSetting>
    Point<Number> computeBoundaryPointsExpensiveRecursive(const SupportFunctionT<Number, Converter, inSetting> &sf,
                                                          const matrix_t<Number> &directions, std::size_t curDim) {
        // determines how many directions need to be checked
        Eigen::Index numberOfDirections = directions.rows();
        // only continue if directions and object match dimensionwise
        assert(std::size_t(directions.cols()) == sf.dimension());
        // generates an empty Point for the return value
        Point<Number> res;
        // if the function has an object that is not yet certainly a singleton (i.e. dimension is greater than zero)
        if (curDim > 0) {
            // generates an empty PointVector for the return values of the recursive calls
            std::vector<Point<Number>> recursiveSolutions;
            for (Eigen::Index i = 0; i < numberOfDirections; ++i) {
                // determines current evaluation direction
                vector_t<Number> curNormal = directions.row(i);

                // lets the support function evaluate the offset of the halfspace for the current direction
                EvaluationResult<Number> offset = sf.evaluate(curNormal);
                // if result is infinity, try the next direction
                if (offset.errorCode == SOLUTION::INFTY) {
                    continue;
                }
                Number constant = offset.supportValue;

                // creates a Halfspacevector containing only the recently created Halfspace
                std::vector<Halfspace<Number>> curPlaneVector;
                curPlaneVector.emplace_back(curNormal, constant);
                curPlaneVector.emplace_back(-curNormal, -constant);
                assert(curPlaneVector.size() == 2);

                // intersects the current support function with the Halfspace
                SupportFunctionT<Number, Converter, inSetting> curPlaneSup = SupportFunctionT<Number, Converter, inSetting>(
                        curPlaneVector);
                // std::cout << "current supportplane:" << std::endl;
                curPlaneSup.print();
                SupportFunctionT<Number, Converter, inSetting> curFace = sf.intersect(curPlaneSup);
                // std::cout << "current face:" << std::endl;
                curFace.print();
                // only continue if face has still the same dimension as the source object (although it is technically now a dim-1 object at most)
                assert(curFace.dimension() == unsigned(directions.cols()));

                // recursive call of this function for the current face
                recursiveSolutions.push_back(computeBoundaryPointsExpensiveRecursive(curFace, directions, curDim - 1));
                assert(recursiveSolutions.back().rawCoordinates().rows() > 0);
            }
            // removes duplicate points in order to enable the arithmetic mean to yield best possible results
            recursiveSolutions = Point<Number>::removeDuplicatePoints(recursiveSolutions);
            assert(!recursiveSolutions.empty());

            // computes the arithmetic mean as an approximation of the centroid
            res = Point<Number>(computeArithmeticMeanPoint(recursiveSolutions));
            // std::cout << "merged point:" << res << std::endl;
            // call has only a point as source object (deepest recursion layer)
        } else {  // curDim == 0
            // evaluates the object in the first direction (any direction produces the same result)
            EvaluationResult<Number> point = sf.evaluate(directions.row(1));
            // there needs to be a result here, otherwise something went terribly wrong
            assert(point.errorCode != SOLUTION::INFEAS && point.errorCode != SOLUTION::UNKNOWN);
            res = Point<Number>(point.optimumValue);
            assert(sf.contains(point.optimumValue));
            // std::cout << "deepest floor point:" << point.optimumValue << std::endl;
        }
        return res;
    }

// conversion from V-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const VPolytopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return _source;
    }

    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const ConstraintSetT<Number, inSetting> &_source, const CONV_MODE) {
        return VPolytopeT<Number, Converter, VPolySetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename VPolySetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const Ellipsoid &_source, const CONV_MODE) {
        vector_t<Number> l(_source.dimension());
        l.setZero();
        vector_t<Number> evaluation;
        std::vector<vector_t<Number>> constraints;
        vector_t<Number> b;
        for (std::size_t i = 0; i < _source.dimension(); i++) {
            for (std::size_t j = i + 1; j < _source.dimension(); j++) {
                // Evaluation in 8 directions for each pair of dimensions
                // only compute 4 directions, as E is symmetric. Comments denote the combination of i,j
                // (1,0)
                l(i) = 1;
                evaluation = _source.evaluate(l);
                constraints.push_back(evaluation);
                constraints.push_back(-evaluation);
                // (1,1)
                l(j) = 1;
                evaluation = _source.evaluate(l);
                constraints.push_back(evaluation);
                constraints.push_back(-evaluation);
                // (-1,1)
                l(i) = -1;
                evaluation = _source.evaluate(l);
                constraints.push_back(evaluation);
                constraints.push_back(-evaluation);
                // (0,1)
                l(i) = 0;
                evaluation = _source.evaluate(l);
                constraints.push_back(evaluation);
                constraints.push_back(-evaluation);
                l(j) = 0;
            }
        }
        b.setOnes(constraints.size());
        matrix_t<Number> constraintMatrix(constraints.size(), _source.dimension());
        for (std::size_t i = 0; i < constraints.size(); i++) {
            constraintMatrix.row(i) = constraints.at(i);
        }
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(constraintMatrix, b);
    }

// conversion from H-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const HPolytopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        // exact conversion
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(_source.matrix(), _source.vector());
    }

// conversion from Box to V-Polytope (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const BoxT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(_source.vertices());
    }

// conversion from Zonotope to V-Polytope (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const ZonotopeT<Number, Converter<Number>, inSetting> &_source, const CONV_MODE) {
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(_source.vertices());
    }

// TODO verification of alternative underapproximation (yields only one point for some reason)
//  conversion from Support Function to V-Polytope (OVER, UNDER or ALTERNATIVE)
// ALTERNATIVE mode gives an underapproximation that is probably better but costs a lot more to compute
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const SupportFunctionT<Number, Converter<Number>, inSetting> &_source,
                                   const CONV_MODE mode, std::size_t numberOfDirections) {
        VPolytopeT<Number, Converter<Number>, VPolySetting> target;
        if (mode == OVER) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();
            // std::cout << "toVPolytope::over" << std::endl;
            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }

            // lets the support function evaluate the offset of the halfspaces for each direction
            std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
            assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
            std::vector<std::size_t> boundedConstraints;
            for (std::size_t offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex) {
                if (offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                    boundedConstraints.push_back(offsetIndex);
            }
            // builds halfspaces with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
            matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), dim);
            vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
            std::size_t pos = boundedConstraints.size() - 1;
            while (!boundedConstraints.empty()) {
                constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
                constants(pos) = offsets[boundedConstraints.back()].supportValue;
                boundedConstraints.pop_back();
                --pos;
            }

            // constructs a V-Polytope out of the computed halfspaces (implicit conversion H->V)
            target = VPolytopeT<Number, Converter, VPolySetting>(constraints, constants);
        }
        if (mode == UNDER) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();
            // std::cout << "toVPolytope::over" << std::endl;
            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }

            // lets the support function evaluate the offset of the halfspaces for each direction
            std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
            assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
            std::vector<std::size_t> boundedConstraints;
            for (std::size_t offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex) {
                if (offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                    boundedConstraints.push_back(offsetIndex);
            }

            // builds a pointVector from boundary points with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
            std::vector<Point<Number>> points = std::vector<Point<Number>>(boundedConstraints.size());
            std::size_t pos = boundedConstraints.size() - 1;
            while (!boundedConstraints.empty()) {
                points[pos] = offsets[boundedConstraints.back()].optimumValue;
                boundedConstraints.pop_back();
                --pos;
            }

            // constructs a V-Polytope out of the computed points
            target = VPolytopeT<Number, Converter, VPolySetting>(points);
        }

        if (mode == ALTERNATIVE) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();

            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }
            // computes some central boundary points based on the directions (pretty precise but expensive)
            std::vector<Point<Number>> boundaryPoints = computeBoundaryPointsExpensive(_source,
                                                                                       templateDirectionMatrix);

            target = VPolytopeT<Number, Converter, VPolySetting>(boundaryPoints);
        }
        return target;
    }

#ifdef HYPRO_USE_PPL
    template <typename Number>
    template <typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting> Converter<Number>::toVPolytope( const PolytopeT<Number, Converter<Number>, inSetting>& source, const CONV_MODE ) {
        return VPolytopeT<Number, Converter<Number>, VPolySetting>( source.vertices() );
    }
#endif

    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const DifferenceBoundsT<Number, Converter<Number>, inSetting> &_source,
                                   const CONV_MODE mode) {
        return toVPolytope(toHPolytope(_source, mode));
    }

// conversion from H-Polytope to V-Polytope (no differentiation between conversion modes - always EXACT)
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const CarlPolytopeT<Number, Converter<Number>, inSetting> &_source,
                                   const CONV_MODE) {
        // exact conversion
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(_source.matrix(), _source.vector());
    }

    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const TemplatePolyhedronT<Number, Converter<Number>, inSetting> &_source,
                                   const CONV_MODE) {
        return VPolytopeT<Number, Converter<Number>, VPolySetting>(_source.matrix(), _source.vector());
    }

// template<typename Number>
// template<typename VPolytopeSetting, typename inSetting>
// VPolytopeT<Number,Converter<Number>,VPolytopeSetting> Converter<Number>::toVPolytope( const OrthoplexT<Number,Converter<Number>,inSetting>& source, const CONV_MODE ) {
//	return VPolytopeT<Number,Converter<Number>,VPolytopeSetting>();
// }

/**
 * Is the caller function for the recursive method that computes exactly one boundary point for each direction that it gets (via support function)
 * Note that the next three functions are all copies of the functions above, but for SupportFunctionNews instead of SupportFunctions.
 */

    template<typename Number, typename Converter, typename inSetting>
    std::vector<Point<Number>>
    computeBoundaryPointsExpensive(const SupportFunctionNewT<Number, Converter, inSetting> &sf,
                                   const matrix_t<Number> &directions) {
        // determines how many directions need to be checked
        Eigen::Index numberOfDirections = directions.rows();
        // gets dimension in which is currently computed
        Eigen::Index dim = directions.cols();
        // only continue if directions and object match dimensionwise
        assert(dim == Eigen::Index(sf.dimension()));
        // generates an empty PointVector for the return value
        std::vector<Point<Number>> res;
        // if the function has an object that is not yet certainly a singleton (i.e. dimension is greater than zero)
        if (dim > 0) {
            // generates an empty PointVector for the return values of the recursive calls
            std::vector<Point<Number>> recursiveSolutions;
            for (Eigen::Index i = 0; i < numberOfDirections; ++i) {
                // determines current evaluation direction
                vector_t<Number> curNormal = directions.row(i);

                // lets the support function evaluate the offset of the halfspace for the current direction
                EvaluationResult<Number> offset = sf.evaluate(curNormal);
                // if result is infinity, try the next direction
                if (offset.errorCode == SOLUTION::INFTY) {
                    continue;
                }
                Number constant = offset.supportValue;

                // creates a Halfspacevector containing only the recently created Halfspace
                std::vector<Halfspace<Number>> curPlaneVector;
                curPlaneVector.emplace_back(curNormal, constant);
                curPlaneVector.emplace_back(-curNormal, -constant);
                assert(curPlaneVector.size() == 2);

                // intersects the current support function with the Halfspace
                SupportFunctionNewT<Number, Converter, inSetting> curPlaneSup = SupportFunctionNewT<Number, Converter, inSetting>(
                        curPlaneVector);
                // std::cout << "current supportplane:" << std::endl;
                // curPlaneSup.print();
                SupportFunctionNewT<Number, Converter, inSetting> curFace = sf.intersect(curPlaneSup);
                // std::cout << "current face:" << std::endl;
                // curFace.print();
                // only continue if face has still the same dimension as the source object (although it is technically now a dim-1 object at most)
                assert(Eigen::Index(curFace.dimension()) == dim);

                // call of the recursive sub-function for the current face
                recursiveSolutions.push_back(
                        computeBoundaryPointsExpensiveRecursive(curFace, directions, std::size_t(dim - 1)));
            }
            // removes duplicate points in order to enable the arithmetic mean to yield best possible results
            recursiveSolutions = Point<Number>::removeDuplicatePoints(recursiveSolutions);
            res = recursiveSolutions;
            // kickoff function gets called with a point for some reason
        } else {  // dim == 0
            // evaluates the object in the first direction (any direction produces the same result)
            EvaluationResult<Number> point = sf.evaluate(directions.row(1));
            // there needs to be a result here, otherwise something went terribly wrong
            assert(point.errorCode != SOLUTION::INFEAS && point.errorCode != SOLUTION::UNKNOWN);
            res.emplace_back(point.optimumValue);
            assert(sf.contains(Point<Number>(point.optimumValue)));
        }
        return res;
    }

/*
 * Recursively computes some boundary points that lie relatively central for each face of the object, this function is constructed to only be called by computeBoundaryPoints
 */
    template<typename Number, typename Converter, typename inSetting>
    Point<Number> computeBoundaryPointsExpensiveRecursive(const SupportFunctionNewT<Number, Converter, inSetting> &sf,
                                                          const matrix_t<Number> &directions, std::size_t curDim) {
        // determines how many directions need to be checked
        Eigen::Index numberOfDirections = directions.rows();
        // only continue if directions and object match dimensionwise
        assert(std::size_t(directions.cols()) == sf.dimension());
        // generates an empty Point for the return value
        Point<Number> res;
        // if the function has an object that is not yet certainly a singleton (i.e. dimension is greater than zero)
        if (curDim > 0) {
            // generates an empty PointVector for the return values of the recursive calls
            std::vector<Point<Number>> recursiveSolutions;
            for (Eigen::Index i = 0; i < numberOfDirections; ++i) {
                // determines current evaluation direction
                vector_t<Number> curNormal = directions.row(i);

                // lets the support function evaluate the offset of the halfspace for the current direction
                EvaluationResult<Number> offset = sf.evaluate(curNormal);
                // if result is infinity, try the next direction
                if (offset.errorCode == SOLUTION::INFTY) {
                    continue;
                }
                Number constant = offset.supportValue;

                // creates a Halfspacevector containing only the recently created Halfspace
                std::vector<Halfspace<Number>> curPlaneVector;
                curPlaneVector.emplace_back(curNormal, constant);
                curPlaneVector.emplace_back(-curNormal, -constant);
                assert(curPlaneVector.size() == 2);

                // intersects the current support function with the Halfspace
                SupportFunctionNewT<Number, Converter, inSetting> curPlaneSup = SupportFunctionNewT<Number, Converter, inSetting>(
                        curPlaneVector);
                // std::cout << "current supportplane:" << std::endl;
                // curPlaneSup.print();
                SupportFunctionNewT<Number, Converter, inSetting> curFace = sf.intersect(curPlaneSup);
                // std::cout << "current face:" << std::endl;
                // curFace.print();
                // only continue if face has still the same dimension as the source object (although it is technically now a dim-1 object at most)
                assert(curFace.dimension() == unsigned(directions.cols()));

                // recursive call of this function for the current face
                recursiveSolutions.push_back(computeBoundaryPointsExpensiveRecursive(curFace, directions, curDim - 1));
                assert(recursiveSolutions.back().rawCoordinates().rows() > 0);
            }
            // removes duplicate points in order to enable the arithmetic mean to yield best possible results
            recursiveSolutions = Point<Number>::removeDuplicatePoints(recursiveSolutions);
            assert(!recursiveSolutions.empty());

            // computes the arithmetic mean as an approximation of the centroid
            res = Point<Number>(computeArithmeticMeanPoint(recursiveSolutions));
            // std::cout << "merged point:" << res << std::endl;
            // call has only a point as source object (deepest recursion layer)
        } else {  // curDim == 0
            // evaluates the object in the first direction (any direction produces the same result)
            EvaluationResult<Number> point = sf.evaluate(directions.row(1));
            // there needs to be a result here, otherwise something went terribly wrong
            assert(point.errorCode != SOLUTION::INFEAS && point.errorCode != SOLUTION::UNKNOWN);
            res = Point<Number>(point.optimumValue);
            assert(sf.contains(point.optimumValue));
            // std::cout << "deepest floor point:" << point.optimumValue << std::endl;
        }
        return res;
    }

// TODO verification of alternative underapproximation (yields only one point for some reason)
//  conversion from Support Function to V-Polytope (OVER, UNDER or ALTERNATIVE)
// ALTERNATIVE mode gives an underapproximation that is probably better but costs a lot more to compute
    template<typename Number>
    template<typename VPolySetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolySetting>
    Converter<Number>::toVPolytope(const SupportFunctionNewT<Number, Converter<Number>, inSetting> &_source,
                                   const CONV_MODE mode, std::size_t numberOfDirections) {
        VPolytopeT<Number, Converter<Number>, VPolySetting> target;
        if (mode == OVER) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();

            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }

            // lets the support function evaluate the offset of the halfspaces for each direction
            std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
            assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
            std::vector<std::size_t> boundedConstraints;
            for (std::size_t offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex) {
                if (offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                    boundedConstraints.push_back(offsetIndex);
            }
            // builds halfspaces with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
            matrix_t<Number> constraints = matrix_t<Number>(boundedConstraints.size(), dim);
            vector_t<Number> constants = vector_t<Number>(boundedConstraints.size());
            std::size_t pos = boundedConstraints.size() - 1;
            while (!boundedConstraints.empty()) {
                constraints.row(pos) = templateDirectionMatrix.row(boundedConstraints.back());
                constants(pos) = offsets[boundedConstraints.back()].supportValue;
                boundedConstraints.pop_back();
                --pos;
            }

            // constructs a V-Polytope out of the computed halfspaces (implicit conversion H->V)
            target = VPolytopeT<Number, Converter, VPolySetting>(constraints, constants);
        }
        if (mode == UNDER) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();

            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }

            // lets the support function evaluate the offset of the halfspaces for each direction
            std::vector<EvaluationResult<Number>> offsets = _source.multiEvaluate(templateDirectionMatrix);
            assert(offsets.size() == std::size_t(templateDirectionMatrix.rows()));
            std::vector<std::size_t> boundedConstraints;
            for (std::size_t offsetIndex = 0; offsetIndex < offsets.size(); ++offsetIndex) {
                if (offsets[offsetIndex].errorCode != SOLUTION::INFTY)
                    boundedConstraints.push_back(offsetIndex);
            }

            // builds a pointVector from boundary points with the evaluation results (uses only results that are not infinity (i.e. where a bound exists))
            std::vector<Point<Number>> points = std::vector<Point<Number>>(boundedConstraints.size());
            std::size_t pos = boundedConstraints.size() - 1;
            while (!boundedConstraints.empty()) {
                points[pos] = offsets[boundedConstraints.back()].optimumValue;
                boundedConstraints.pop_back();
                --pos;
            }

            // constructs a V-Polytope out of the computed points
            target = VPolytopeT<Number, Converter, VPolySetting>(points);
        }

        if (mode == ALTERNATIVE) {
            // gets dimension of source object
            std::size_t dim = _source.dimension();

            // computes a vector of template directions based on the dimension and the requested number of directions which should get evaluated
            std::vector<vector_t<Number>> templateDirections = computeTemplate<Number>(dim, numberOfDirections);
            // only continue if size of the vector is not greater than the upper bound for maximum evaluations (uniformly distributed directions for higher dimensions yield many necessary evaluations)
            assert(templateDirections.size() <= std::size_t(std::pow(numberOfDirections, dim)));
            // creates a matrix with one row for each direction and one column for each dimension
            matrix_t<Number> templateDirectionMatrix = matrix_t<Number>(templateDirections.size(), dim);

            // fills the matrix with the template directions
            for (std::size_t i = 0; i < templateDirections.size(); ++i) {
                templateDirectionMatrix.row(i) = templateDirections[i];
            }
            // computes some central boundary points based on the directions (pretty precise but expensive)
            std::vector<Point<Number>> boundaryPoints = computeBoundaryPointsExpensive(_source,
                                                                                       templateDirectionMatrix);

            target = VPolytopeT<Number, Converter, VPolySetting>(boundaryPoints);
        }
        return target;
    }

    // namespace hypro

    template<typename Number>
    template<typename VPolytopeSetting, typename inSetting>
    VPolytopeT<Number, Converter<Number>, VPolytopeSetting>
    Converter<Number>::toVPolytope(const StarsetT<Number, Converter<Number>, inSetting> &source, const CONV_MODE) {
        return VPolytopeT<Number, Converter<Number>, VPolytopeSetting>();
    }
}
