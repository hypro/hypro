/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../types.h"
#include "../logging/Logger.h"

#include <glpk.h>

namespace hypro {

    static void cleanupGlpk() {
        glp_free_env();
    }

/**
 * @brief Context for linear optimization using glpk as a backend
 *
 */
    struct glpk_context {
        glp_prob *lp = nullptr;                   ///< glpk problem instance
        glp_smcp parm;                           ///< glpk parameter struct
        int *ia = nullptr;                       ///< row indices
        int *ja = nullptr;                       ///< column indices
        double *ar = nullptr;                   ///< coefficients
        bool arraysCreated = false;               ///< true if array variables have been created.
        mutable bool mInitialized = false;       ///< true if lp instance has been created.
        mutable bool mConstraintsSet = false;  ///< true if lp instance exists, arrays have been set and the lp instance is set up with the current constraints.

        /// default constructor
        glpk_context() {
            std::atexit(cleanupGlpk);
        }

        /// copy constructor
        glpk_context(const glpk_context &orig) {
            if (orig.mInitialized) {
                glp_copy_prob(lp, orig.lp, GLP_ON);
                parm = orig.parm;
                glp_init_smcp(&parm);
                parm.msg_lev = GLP_MSG_OFF;
                glp_set_obj_dir(lp, GLP_MAX);
            }
            mInitialized = orig.mInitialized;
            // We do not attempt to copy the arrays
            arraysCreated = false;
            mConstraintsSet = false;
        }

        /// move constructor (deleted)
        glpk_context(glpk_context &&orig) = delete;

        /// copy-assignment operator
        glpk_context &operator=(const glpk_context &orig) {
            // compare problem instances to avoid self-assignment
            if (*this == orig) {
                return *this;
            }
            deleteLPInstance();
            deleteArrays();
            if (orig.mInitialized) {
                glp_copy_prob(lp, orig.lp, GLP_ON);
                parm = orig.parm;
                glp_init_smcp(&parm);
                parm.msg_lev = GLP_MSG_OFF;
                glp_set_obj_dir(lp, GLP_MAX);
            }
            mInitialized = orig.mInitialized;
            // We do not attempt to copy the arrays
            arraysCreated = false;
            mConstraintsSet = false;
            return *this;
        }

        /// move-assignment operator (deleted)
        glpk_context &operator=(glpk_context &&orig) = delete;

        /// compare-equal operator
        bool operator==(const glpk_context &rhs) {
            return this->lp == rhs.lp;
        }

        /// initializer function for the LP-problem arrays
        void createArrays(unsigned size) {
            if (arraysCreated) {
                deleteArrays();
            }
            ia = new int[size + 1];
            ja = new int[size + 1];
            ar = new double[size + 1];
            arraysCreated = true;
        }

        /// cleanup function for the problem arrays
        void deleteArrays() {
            if (arraysCreated) {
                delete[] ia;
                delete[] ja;
                delete[] ar;
                ia = nullptr;
                ja = nullptr;
                ar = nullptr;
                arraysCreated = false;
            }
        }

        /// initialization of the lp-problem instance
        void createLPInstance() {
            if (!mInitialized) {
                if (lp != nullptr) {
                    glp_delete_prob(lp);
                }
                lp = glp_create_prob();
                glp_init_smcp(&parm);
                parm.msg_lev = GLP_MSG_OFF;
                glp_set_obj_dir(lp, GLP_MAX);
                glp_term_out(GLP_OFF);
                mInitialized = true;
                mConstraintsSet = false;
            }
        }

        /// cleanup of lp-instance
        void deleteLPInstance() {
            if (mInitialized) {
                assert(lp != nullptr);
                glp_delete_prob(lp);
                mInitialized = false;
                mConstraintsSet = false;
                lp = nullptr;
            }
        }

        /**
         * @brief Setter for the lp coefficients	 *
         * @tparam Number
         * @param constraints
         * @param constants
         * @param relations
         * @param maximize
         */
        template<typename Number>
        void updateConstraints(const matrix_t<Number> &constraints, const vector_t<Number> &constants,
                               const std::vector<carl::Relation> &relations, bool maximize) {
            if (!mConstraintsSet) {
                if (mInitialized) {  // clean up old setup.
                    // std::cout << "alreadyInitialized - Cleanup" << std::endl;
                    deleteArrays();

                    deleteLPInstance();
                }
                createLPInstance();

                if (maximize) {
                    glp_set_obj_dir(lp, GLP_MAX);
                } else {
                    glp_set_obj_dir(lp, GLP_MIN);
                }

                int numberOfConstraints = int(constraints.rows());
                if (numberOfConstraints > 0) {
                    // convert constraint constants
                    glp_add_rows(lp, numberOfConstraints);
                    for (int i = 0; i < numberOfConstraints; i++) {
                        // Set relation symbols correctly
                        switch (relations[i]) {
                            case carl::Relation::LEQ:
                                // set upper bounds, lb-values (here 0.0) are ignored.
                                glp_set_row_bnds(lp, i + 1, GLP_UP, 0.0, toDouble(constants(i)));
                                break;
                            case carl::Relation::GEQ:
                                // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                                glp_set_row_bnds(lp, i + 1, GLP_LO, toDouble(constants(i)), 0.0);
                                break;
                            case carl::Relation::EQ:
                                // if it is an equality, the value is read from the lb-value, ub.values (here 0.0) are ignored.
                                glp_set_row_bnds(lp, i + 1, GLP_FX, toDouble(constants(i)), 0.0);
                                break;
                            default:
                                // glpk cannot handle strict inequalities.
                                assert(false);
                                std::cout << "This should not happen." << std::endl;
                        }
                    }
                    // add cols here
                    int cols = int(constraints.cols());
                    glp_add_cols(lp, cols);
                    createArrays(unsigned(numberOfConstraints * cols));

                    // convert constraint matrix
                    ia[0] = 0;
                    ja[0] = 0;
                    ar[0] = 0;
                    assert(constraints.size() == numberOfConstraints * cols);
                    for (int i = 0; i < numberOfConstraints * cols; ++i) {
                        ia[i + 1] = (int(i / cols)) + 1;
                        // std::cout << __func__ << " set ia[" << i+1 << "]= " << ia[i+1];
                        ja[i + 1] = (int(i % cols)) + 1;
                        // std::cout << ", ja[" << i+1 << "]= " << ja[i+1];
                        ar[i + 1] = toDouble(constraints.row(ia[i + 1] - 1)(ja[i + 1] - 1));
                        // TODO:: Assuming ColMajor storage alignment.
                        // assert(*(constraints.data()+(ja[i+1]*numberOfConstraints) - ia[i+1]) ==  constraints.row(ia[i + 1] - 1)( ja[i + 1] - 1 ));
                        // std::cout << ", ar[" << i+1 << "]=" << ar[i+1] << std::endl;
                        // std::cout << "Came from: " << constraints.row(ia[i + 1] - 1)( ja[i + 1] - 1 ) << std::endl;
                    }

                    glp_load_matrix(lp, numberOfConstraints * cols, ia, ja, ar);
                    for (int i = 0; i < cols; ++i) {
                        glp_set_col_bnds(lp, i + 1, GLP_FR, 0.0, 0.0);
                        glp_set_obj_coef(lp, i + 1, 1.0);     // not needed?
                    }
                }

                mConstraintsSet = true;
            }
        }

        // clearing function
        void clear() {
            deleteLPInstance();
            deleteArrays();
        }

        /// destructor
        ~glpk_context() {
            deleteLPInstance();
            //  assume that all fields are set at once so just check one.
            deleteArrays();
        }
    };
}  // namespace hypro
