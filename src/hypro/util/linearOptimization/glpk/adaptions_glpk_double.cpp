/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/util/linearOptimization/glpk/adaptions_glpk.h"

namespace hypro {

    template<>
    EvaluationResult<double>
    glpkOptimizeLinear(glpk_context &context, const vector_t<double> &_direction, const matrix_t<double> &constraints,
                       const vector_t<double> &, bool useExact) {
        // setup glpk
        for (int i = 0; i < constraints.cols(); i++) {
            glp_set_col_bnds(context.lp, i + 1, GLP_FR, 0.0, 0.0);
            glp_set_obj_coef(context.lp, i + 1, toDouble(_direction(i)));
        }

        // scale problem to improve its stability
        glp_scale_prob(context.lp, GLP_SF_AUTO);

        /* solve problem */
        if (useExact) {
            glp_simplex(context.lp, &context.parm);
            glp_exact(context.lp, &context.parm);
        } else {
            glp_simplex(context.lp, &context.parm);
        }

        switch (glp_get_status(context.lp)) {
            case GLP_OPT:
            case GLP_FEAS: {
                vector_t<double> glpkModel(constraints.cols());
                for (int i = 1; i <= constraints.cols(); ++i) {
                    glpkModel(i - 1) = glp_get_col_prim(context.lp, i);
                }

                return {glp_get_obj_val(context.lp), glpkModel, SOLUTION::FEAS};
                break;
            }
            case GLP_UNBND: {
                vector_t<double> glpkModel(constraints.cols());
                for (int i = 1; i <= constraints.cols(); ++i) {
                    glpkModel(i - 1) = glp_get_col_prim(context.lp, i);
                }
                return {1, glpkModel, SOLUTION::INFTY};
                break;
            }
            default:
                return {0, vector_t<double>::Zero(1), SOLUTION::INFEAS};
        }
    }

    template<>
    bool glpkCheckPoint(glpk_context &context, const matrix_t<double> &constraints, const vector_t<double> &,
                        const Point<double> &point) {
        // set point
        assert(constraints.cols() == point.rawCoordinates().rows());
        for (int i = 0; i < constraints.cols(); ++i) {
            glp_set_col_bnds(context.lp, i + 1, GLP_FX, point.rawCoordinates()(i), 0.0);
            glp_set_obj_coef(context.lp, i + 1, 1.0);     // not needed?
        }
        glp_simplex(context.lp, &context.parm);
        return (glp_get_status(context.lp) != GLP_NOFEAS);
    }

    template<>
    std::vector<std::size_t>
    glpkRedundantConstraints(glpk_context &context, matrix_t<double> constraints, vector_t<double> constants,
                             std::vector<carl::Relation> &relations) {
        std::vector<std::size_t> res;

        // TODO: ATTENTION: This relies upon that glpk maintains the order of the constraints!
        for (int i = 0; i < constraints.cols(); ++i) {
            glp_set_col_bnds(context.lp, i + 1, GLP_FR, 0.0, 0.0);
            glp_set_obj_coef(context.lp, i + 1, 1.0);     // not needed?
        }

        // first call to check satisfiability
        glp_simplex(context.lp, &context.parm);

        switch (glp_get_status(context.lp)) {
            case GLP_INFEAS:
            case GLP_NOFEAS:
                return res;
            default:
                break;
        }

        for (Eigen::Index constraintIndex = constraints.rows() - 1;; --constraintIndex) {
            bool redundant = true;
            carl::Relation relation = relations[constraintIndex];
            EvaluationResult<double> actualRes;
            EvaluationResult<double> updatedRes;

            // if ( relation == carl::Relation::GREATER || relation == carl::Relation::LESS ) {
            //	WARN( hypro, "ATTENTION, glpk cannot handle strict inequalities, results will be based on weak inequalities" );
            // }
            if (relation == carl::Relation::LEQ || relation == carl::Relation::LESS || relation == carl::Relation::EQ) {
                // test if upper bound is redundant
                glp_set_obj_dir(context.lp, GLP_MAX);
                actualRes = glpkOptimizeLinear(context, vector_t<double>(constraints.row(constraintIndex)), constraints,
                                               constants, true);
                glp_set_row_bnds(context.lp, int(constraintIndex) + 1, GLP_FR, 0.0, 0.0);
                updatedRes = glpkOptimizeLinear(context, vector_t<double>(constraints.row(constraintIndex)),
                                                constraints, constants, true);
                // actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
                if (actualRes.errorCode != updatedRes.errorCode || actualRes.supportValue != updatedRes.supportValue) {
                    redundant = false;
                }
            }
            if (relation == carl::Relation::GEQ || relation == carl::Relation::GREATER ||
                relation == carl::Relation::EQ) {
                // test if lower bound is redundant
                glp_set_obj_dir(context.lp, GLP_MIN);
                actualRes = glpkOptimizeLinear(context, vector_t<double>(constraints.row(constraintIndex)), constraints,
                                               constants, true);
                glp_set_row_bnds(context.lp, int(constraintIndex) + 1, GLP_FR, 0.0, 0.0);
                updatedRes = glpkOptimizeLinear(context, vector_t<double>(constraints.row(constraintIndex)),
                                                constraints, constants, true);
                // actual solution is always bounded because of the constraint, so updated should still be bounded if redundant
                if (actualRes.errorCode != updatedRes.errorCode && actualRes.supportValue != updatedRes.supportValue) {
                    redundant = false;
                }
            }

            if (redundant) {
                res.push_back(constraintIndex);
            } else {
                // restore bound
                switch (relation) {
                    case carl::Relation::LESS:
                        //( hypro, "ATTENTION, glpk cannot handle strict inequalities, results will be based on weak inequalities" );
                    case carl::Relation::LEQ:
                        // set upper bounds, lb-values (here 0.0) are ignored.
                        glp_set_row_bnds(context.lp, int(constraintIndex) + 1, GLP_UP, 0.0,
                                         toDouble(constants(constraintIndex)));
                        break;
                    case carl::Relation::GREATER:
                        // WARN( hypro, "ATTENTION, glpk cannot handle strict inequalities, results will be based on weak inequalities" );
                    case carl::Relation::GEQ:
                        // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                        glp_set_row_bnds(context.lp, int(constraintIndex) + 1, GLP_LO,
                                         toDouble(constants(constraintIndex)), 0.0);
                        break;
                    case carl::Relation::EQ:
                        // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                        glp_set_row_bnds(context.lp, int(constraintIndex) + 1, GLP_FX,
                                         toDouble(constants(constraintIndex)), 0.0);
                        break;
                    default:
                        // glpk cannot handle strict inequalities.
                        assert(false);
                        std::cout << __func__ << ": Unknown inequality type" << std::endl;
                }
            }

            if (constraintIndex == 0) {
                break;
            }
        }
        // restore original problem
        for (const auto idx: res) {
            switch (relations[idx]) {
                case carl::Relation::LESS:
                    // WARN( hypro, "ATTENTION, glpk cannot handle strict inequalities, results will be based on weak inequalities" );
                case carl::Relation::LEQ:
                    // set upper bounds, lb-values (here 0.0) are ignored.
                    glp_set_row_bnds(context.lp, int(idx + 1), GLP_UP, 0.0, toDouble(constants(idx)));
                    break;
                case carl::Relation::GREATER:
                    // WARN( hypro, "ATTENTION, glpk cannot handle strict inequalities, results will be based on weak inequalities" );
                case carl::Relation::GEQ:
                    // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                    glp_set_row_bnds(context.lp, int(idx + 1), GLP_LO, toDouble(constants(idx)), 0.0);
                    break;
                case carl::Relation::EQ:
                    // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                    glp_set_row_bnds(context.lp, int(idx + 1), GLP_FX, toDouble(constants(idx)), 0.0);
                    break;
                default:
                    // glpk cannot handle strict inequalities.
                    assert(false);
                    std::cout << "This should not happen." << std::endl;
            }
        }

        return res;
    }

}  // namespace hypro
