/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file Transformation.tpp
 * @author Jan Philipp Hafer
 */
#include "Transformation.h"

namespace hypro {

    template<typename Number>
    Transformation<Number>::Transformation(const HybridAutomaton<Number> &_hybrid) {
        const size_t CONDITION_LIMIT = 100;
        Matrix<Number> matrix_in_parser;
        size_t m_size, i;
        Matrix<Number> V_EVD;
        DiagonalMatrix<Number> D_EVD;
        Matrix<Number> Vinv_EVD;
        Matrix<Number> V;
        Matrix<Number> Vinv;
        Matrix<Number> A_in;
        Vector<Number> b_tr;  // later transformed (b + taking linear terms into account)
        Matrix<Number> A_nonlinear;
        Vector<Number> b_nonlinear;
        typename HybridAutomaton<Number>::Locations locations;
        Location<Number> *PtrtoNewLoc;
        mTransformedHA = HybridAutomaton<Number>();
        // LOCATIONS
        for (Location<Number> *LocPtr: _hybrid.getLocations()) {
            matrix_in_parser = LocPtr->getFlow();  // copy for calculation; TODO many flows? -> lots of duplicate code/management
            m_size = matrix_in_parser.cols();       // rows
            assert(m_size >= 1);                   // exit if location size < 1  ==>> underflow error
            m_size -= 1;                           // Due to parsing: for representation zero row is added for constant coefficients we do not need
            STallValues<Number> mSTallvalues;
            mSTallvalues.mSTindependentFunct.expFunctionType.resize(m_size);
            for (i = 0; i < m_size; ++i) {
                mSTallvalues.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::INITIALIZED;
                assert(mSTallvalues.mSTindependentFunct.expFunctionType[i] == EXP_FUNCT_TYPE::INITIALIZED);
            }
            assert(mSTallvalues.mSTindependentFunct.expFunctionType.capacity() ==
                   mSTallvalues.mSTindependentFunct.expFunctionType.size());
            declare_structures(mSTallvalues, m_size);
            b_tr = Vector<Number>(m_size);
            A_in = Matrix<Number>(m_size, m_size);  // no change due to being lookup
            V = Matrix<Number>(m_size, m_size);      // mSTallvalues gets V as well
            Vinv = Matrix<Number>(m_size, m_size);
            b_tr = matrix_in_parser.topRightCorner(m_size, 1);
            A_in = matrix_in_parser.topLeftCorner(m_size, m_size);
            mSTallvalues.mSTflowpipeSegment.trafoInput.setIdentity(m_size,
                                                                   m_size);  // x'=Ax with A=identity and crossed out influence of linear terms
            std::cout << "inital A:\n"
                      << A_in;
            size_t numberLinear = countLinearAndRemember(A_in, m_size, mSTallvalues);
            std::cout << "Number of Linear Terms: " << numberLinear << "\n";
            // LINEARONLY
            if (numberLinear == m_size) {
                std::cout << "linear FLOW only\n";
                Vinv.setIdentity(m_size, m_size);
                V.setIdentity(m_size, m_size);
                mSTallvalues.mSTindependentFunct.D.diagonal().setZero(m_size);
                mSTallvalues.mSTflowpipeSegment.Vinv = Vinv;
                mSTallvalues.mSTflowpipeSegment.V = V;
                for (i = 0; i < m_size; ++i) {
                    mSTallvalues.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::CONSTANT;
                }
            } else {
                // LINEAR TERMS INSIDE matrix A -> size adaption for transformation
                if (numberLinear > 0) {
                    std::cout << "flow has linear terms\n";
                    size_t nonLinearsize = m_size - numberLinear;
                    A_nonlinear = Matrix<Number>(nonLinearsize, nonLinearsize);
                    b_nonlinear = Vector<Number>(nonLinearsize);
                    V_EVD = Matrix<Number>(nonLinearsize, nonLinearsize);
                    D_EVD = DiagonalMatrix<Number>(nonLinearsize);
                    Vinv_EVD = Matrix<Number>(nonLinearsize, nonLinearsize);
                    std::cout << "nonLinearsize: " << nonLinearsize << "\n";
                    // ADAPTION of size and remember linear terms(in mSTallvalues)
                    insertNonLinearAndClassify(A_in, b_tr, m_size, A_nonlinear, b_nonlinear, mSTallvalues);
                    std::cout << "A_nonlinear\n"
                              << A_nonlinear;
                    EigenvalueDecomposition(A_nonlinear, nonLinearsize, CONDITION_LIMIT, V_EVD, D_EVD, Vinv_EVD);
                    // convert the linear terms to change convergence point
                    adjustLinearAndEVDcomponents(V_EVD, D_EVD, Vinv_EVD, A_in, b_nonlinear, m_size, V, Vinv, b_tr,
                                                 mSTallvalues);
                } else {
                    // NO LINEAR TERMS
                    std::cout << "no linear terms\n";
                    EigenvalueDecomposition(A_in, m_size, CONDITION_LIMIT, V, mSTallvalues.mSTindependentFunct.D, Vinv);
                    mSTallvalues.mSTflowpipeSegment.Vinv = Vinv;
                    mSTallvalues.mSTflowpipeSegment.V = V;
                }
                // TRAFO of b_tr to Eigenspace
                b_tr = Vinv * b_tr;
                analyzeExponentialTerms(m_size, mSTallvalues);
            }
            std::unique_ptr<Location<Number>> PtrtoNewLoc = std::make_unique<Location<Number>>(matrix_in_parser);
            mLocationPtrsMap.insert(std::make_pair(LocPtr, PtrtoNewLoc.get()));
            // SAVING STRUCT
            TRACE("hypro.eigendecomposition", "D exact:\n"
                    << mSTallvalues.mSTindependentFunct.D.diagonal());
            TRACE("hypro.eigendecomposition", "b_tr :\n"
                    << b_tr);
            for (i = 0; i < m_size; ++i) {
                // SCALING dependents on linear terms
                if ((mSTallvalues.mSTindependentFunct.expFunctionType[i] == EXP_FUNCT_TYPE::CONVERGENT) ||
                    (mSTallvalues.mSTindependentFunct.expFunctionType[i] == EXP_FUNCT_TYPE::DIVERGENT)) {
                    mSTallvalues.mSTindependentFunct.xinhom(i) =
                            b_tr(i) / mSTallvalues.mSTindependentFunct.D.diagonal()(i);
                    continue;
                }
                if (mSTallvalues.mSTindependentFunct.expFunctionType[i] == EXP_FUNCT_TYPE::LINEAR) {
                    mSTallvalues.mSTindependentFunct.xinhom(i) = b_tr(i);
                    continue;
                }
                if (mSTallvalues.mSTindependentFunct.expFunctionType[i] == EXP_FUNCT_TYPE::CONSTANT) {
                    mSTallvalues.mSTindependentFunct.xinhom(i) = 0;
                    continue;
                }
                FATAL("hypro.eigendecomposition", "INVALID FUNCTION TYPE RECOGNIZED");
                std::exit(EXIT_FAILURE);
            }
            TRACE("hypro.eigendecomposition", "xinhom :\n"
                    << mSTallvalues.mSTindependentFunct.xinhom);
            mLocPtrtoComputationvaluesMap.insert(std::make_pair(PtrtoNewLoc.get(), mSTallvalues));
            // std::cout << "old loc: "<<LocPtr<<"\n";
            // std::cout << "new loc: "<<PtrtoNewLoc<<"\n";
            // INVARIANTS(TYPE CONDITION)
            const Condition<Number> &invar1 = LocPtr->getInvariant();
            Condition<Number> invar1NEW;
            // Condition(Ax<=b): A*Vsource*xeigen <= b;
            for (i = 0; i < invar1.size(); ++i) {
                invar1NEW.setMatrix(invar1.getMatrix(i) * V, i);
                invar1NEW.setVector(invar1.getVector(i), i);
            }
            PtrtoNewLoc->setInvariant(invar1NEW);
            locations.emplace(std::move(PtrtoNewLoc));
        }
        mTransformedHA.setLocations(std::move(locations));
        // TRANSITIONS
        typename HybridAutomaton<Number>::transitionVector transitions;
        for (auto *TransPtr: _hybrid.getTransitions()) {
            auto NewTransPtr = std::make_unique<Transition<typename HybridAutomaton<Number>::LocationType>>(*TransPtr);
            // TODO transitionManager? transitions not freed, shared_ptr too costly in multithreaded context
            // POINTER
            Location<Number> *NewSourceLocPtr = mLocationPtrsMap[TransPtr->getSource()];
            Location<Number> *NewTargetLocPtr = mLocationPtrsMap[TransPtr->getTarget()];
            const Matrix<Number> &VSource =
                    mLocPtrtoComputationvaluesMap[NewSourceLocPtr].mSTflowpipeSegment.V;
            const Matrix<Number> &VinvTarget =
                    mLocPtrtoComputationvaluesMap[NewTargetLocPtr].mSTflowpipeSegment.Vinv;
            const Matrix<Number> &trafoInputTarget =
                    mLocPtrtoComputationvaluesMap[NewTargetLocPtr].mSTflowpipeSegment.trafoInput;

            NewTransPtr->setSource(NewSourceLocPtr);
            NewTransPtr->setTarget(NewTargetLocPtr);
            // GUARD ( when transition can be made )
            const Condition<Number> &guard1 = TransPtr->getGuard();
            Condition<Number> guard1NEW;  // = NewTransPtr->getGuard();
            // Condition(Ax<=b): A*Vsource*xeigen <= b;
            for (i = 0; i < guard1.size(); ++i) {
                guard1NEW.setMatrix(guard1.getMatrix(i) * VSource, i);
                guard1NEW.setVector(guard1.getVector(i), i);
            }
            NewTransPtr->setGuard(guard1NEW);
            // RESET ( reset into new location ) note: s:=source, t:=target, inv:=^(-1)
            const Reset<Number> &reset1 = TransPtr->getReset();
            Reset<Number> reset1NEW;  // = NewTransPtr->getReset();
            // reset(into Eigenspace of new location): Vtarget^(-1)x'=
            // Vtinv*removelinearTerms*A*Vsource*xeigen[Vsource^(-1)x] + Vtarget^(-1)b
            for (i = 0; i < reset1.size(); ++i) {
                reset1NEW.setMatrix(VinvTarget * trafoInputTarget * reset1.getMatrix(i) * VSource, i);
                reset1NEW.setVector(VinvTarget * reset1.getVector(i), i);
            }
            NewTransPtr->setReset(reset1NEW);
            NewTargetLocPtr->addTransition(NewTransPtr.get());
            transitions.emplace(std::move(NewTransPtr));
        }
        mTransformedHA.setTransitions(std::move(transitions));
        // INITIAL STATES (transformed into Eigenspace later on reachability analysis)
        locationStateMap initialStates;
        for (typename locationStateMap::const_iterator it = _hybrid.getInitialStates().begin();
             it != _hybrid.getInitialStates().end(); ++it) {
            Location<Number> *NewLocPtr = mLocationPtrsMap[it->first];
            auto state1NEW = State_t<Number>(it->second);
            state1NEW.setTimestamp(carl::Interval<Number>(0));
            state1NEW.setLocation(NewLocPtr);
            mTransformedHA.addInitialState(state1NEW);
        }
        // LOCAL BAD STATES (condition [matrix,vector] matrix=matrix*V
        for (typename HybridAutomaton<Number>::locationConditionMap::const_iterator it = _hybrid.getLocalBadStates().begin();
             it != _hybrid.getLocalBadStates().end(); ++it) {
            Location<Number> *NewLocPtr = mLocationPtrsMap[it->first];
            TRACE("hypro.eigendecomposition", "OldLocPtr" << it->first);
            TRACE("hypro.eigendecomposition", "NewLocPtr" << NewLocPtr);
            const Condition<Number> &badState = it->second;
            TRACE("hypro.eigendecomposition", "BadState" << badState);
            Condition<Number> badStateNEW;
            const Matrix<Number> &V =
                    mLocPtrtoComputationvaluesMap[NewLocPtr].mSTflowpipeSegment.V;
            for (i = 0; i < badState.size(); ++i) {
                // Condition(Ax<=b): A*Vsource*xeigen <= b;
                badStateNEW.setMatrix(badState.getMatrix(i) * V, i);
                badStateNEW.setVector(badState.getVector(i), i);
            }
            TRACE("hypro.eigendecomposition", "transformed localBadState: " << badStateNEW);
            mTransformedHA.addLocalBadStates(NewLocPtr, badStateNEW);
        }
        // for (const auto & locBadState : mTransformedHA.getLocalBadStates() ) {
        //     TRACE("hypro.eigendecomposition","in location: " << locBadState.first)
        //     TRACE("hypro.eigendecomposition","after trafo State:" << locBadState.second);
        // }
        // eigen decompositions from eigen with complex eigenvalues seem to result in wrong results (V even not invertible)
        // LOOP through all locations checking V,D,Vinv for NaN, Inf, -Inf (implicitly also sNan, qNaN)
        // bool outOfRange = false;
        // for (typename locationVector::const_iterator locIt=mTransformedHA.getLocations().begin();
        //   locIt!=mTransformedHA.getLocations().end(); ++locIt) {
        //     STflowpipeSegment<Number>& segmentinfo   = mLocPtrtoComputationvaluesMap[*locIt].mSTflowpipeSegment;
        //     STindependentFunct<Number>& indepentinfo = mLocPtrtoComputationvaluesMap[*locIt].mSTindependentFunct;
        //     if( (segmentinfo.Vinv.array().isNaN() == 1).any() || (segmentinfo.Vinv.array().isNaN() == 1).any() )
        //         outOfRange = true;
        //     if( (segmentinfo.V.array().isNaN() == 1).any()  || (segmentinfo.V.array().isNaN() == 1).any() )
        //         outOfRange = true;
        //     if( (indepentinfo.D.diagonal().array().isNaN() == 1).any() || (indepentinfo.D.diagonal().array().isNaN() == 1).any() )
        //         outOfRange = true;
        // }
        // if (outOfRange) {
        //     FATAL("hypro.eigendecomposition","OUT OF BOUNDS on EVD computation, please check the results in DEBUG mode");
        //     std::exit(EXIT_FAILURE);
        // }
    }

    template<typename Number>
    void Transformation<Number>::addGlobalBadStates(const HybridAutomaton<Number> &_hybrid, const bool transform) {
        // CHECK MATCH OF LOCATION PTRS
        assert(_hybrid.getLocations().size() == mLocationPtrsMap.size());
        typename locationPtrMap::const_iterator locIt = mLocationPtrsMap.begin();
        typename locationPtrMap::const_iterator endLocIt = mLocationPtrsMap.end();
        for (typename locationVector::iterator origIt = _hybrid.getLocations().begin();
             origIt != _hybrid.getLocations().end(); ++origIt) {
            // locations is set -> value is ptrs to origLoc, in map key is ptrs to origLoc
            assert(*origIt == locIt->first);
            if (locIt != endLocIt)
                ++locIt;
        }
        assert(locIt == endLocIt);
        // TRANSFORMATION -> for each globalBadState : set localBadState A*Vx <= b for according V of location
        // 1. loop through global states
        // 2. loop through ptr to location map and create new localBadState
        if (transform) {
            assert(!globalBadStatesTransformed);
            // TODO MEMORY ASSERTION?
            size_t i;
            for (typename conditionVector::const_iterator it = _hybrid.getGlobalBadStates().begin();
                 it != _hybrid.getGlobalBadStates().end(); ++it) {
                for (typename locationPtrMap::iterator locMapIt = mLocationPtrsMap.begin();
                     locMapIt != mLocationPtrsMap.end(); ++locMapIt) {
                    Condition<Number> badStateNEW;
                    const Matrix<Number> &V = mLocPtrtoComputationvaluesMap[locMapIt->second].mSTflowpipeSegment.V;
                    for (i = 0; i < it->size(); ++i) {
                        badStateNEW.setMatrix(it->getMatrix(i) * V, i);
                        badStateNEW.setVector(it->getVector(i), i);
                    }
                    mTransformedHA.addLocalBadStates(locMapIt->second, badStateNEW);
                }
            }
            globalBadStatesTransformed = true;
        } else {
            // NO TRANSFORMATION -> add to globalBadStates
            size_t i;
            for (typename conditionVector::const_iterator it = _hybrid.getGlobalBadStates().begin();
                 it != _hybrid.getGlobalBadStates().end(); ++it) {
                // loop through global states + copy to other HybridAutomaton
                for (typename locationPtrMap::iterator locMapIt = mLocationPtrsMap.begin();
                     locMapIt != mLocationPtrsMap.end(); ++locMapIt) {
                    Condition<Number> globalbadStateNEW;
                    for (i = 0; i < it->size(); ++i) {
                        globalbadStateNEW.setMatrix(it->getMatrix(i), i);
                        globalbadStateNEW.setVector(it->getVector(i), i);
                    }
                    mTransformedHA.addGlobalBadStates(globalbadStateNEW);
                }
            }
        }
    }

    template<typename Number>
    void Transformation<Number>::declare_structures(STallValues<Number> &mSTallValues, const int n) {
        mSTallValues.mSTindependentFunct.D = DiagonalMatrix<Number>(n);
        mSTallValues.mSTindependentFunct.xinhom = Vector<Number>(n);
        mSTallValues.mSTflowpipeSegment.V = Matrix<Number>(n, n);
        mSTallValues.mSTflowpipeSegment.Vinv = Matrix<Number>(n, n);
        mSTallValues.mSTflowpipeSegment.trafoInput = Matrix<Number>(n, n);
    }

// count linear and remember in according std::vector
    template<typename Number>
    size_t Transformation<Number>::countLinearAndRemember(const Matrix<Number> &A_in,
                                                          const size_t dimension, STallValues<Number> &mSTallvalues) {
        // std::cout << "starting linear counting\n";
        // dimension = dimension of A_in
        size_t count_linearVariables = 0;
        size_t nrow, ncol;
        bool linear;
        for (nrow = 0; nrow < dimension; ++nrow) {
            linear = true;
            for (ncol = 0; ncol < dimension; ++ncol) {
                if (A_in(nrow, ncol) != 0) {
                    linear = false;
                    break;
                }
            }
            if (linear == true) {
                ++count_linearVariables;
                mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = EXP_FUNCT_TYPE::LINEAR;
            } else {
                assert(A_in(nrow, nrow) != 0);    // diagonal of nonlinear-term has to be defined
            }
        }
        return count_linearVariables;
    }

// having linear terms, we grep nonlinear terms to apply EVD on
    template<typename Number>
    void Transformation<Number>::insertNonLinearAndClassify(const Matrix<Number> &A_in, const Vector<Number> &b_in,
                                                            const size_t dimension, Matrix<Number> &A_nonlinear,
                                                            Vector<Number> &b_nonlinear,
                                                            STallValues<Number> &mSTallvalues) {
        size_t ncol, nrow;
        size_t count_linVar_row = 0;
        size_t count_linVar_col = 0;
        // CHECK if according vector contains linear behavior -> skip columns
        // for rows: count the according occurences of linear terms to access correct element
        for (ncol = 0; ncol < dimension; ++ncol) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
                ++count_linVar_col;
                continue;
            }
            count_linVar_row = 0;
            for (nrow = 0; nrow < dimension; ++nrow) {
                if (mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                    ++count_linVar_row;
                } else {
                    // std::cout << "A_nonlinear: \n" << A_nonlinear << "\n";
                    A_nonlinear(nrow - count_linVar_row, ncol - count_linVar_col) = A_in(nrow, ncol);
                    // std::cout << "A_nonlinear: \n" << A_nonlinear << "\n";
                }
            }
        }
        count_linVar_col = 0;
        for (ncol = 0; ncol < dimension; ++ncol) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
                ++count_linVar_col;
                if (b_in(ncol) == 0) {
                    mSTallvalues.mSTindependentFunct.expFunctionType[ncol] = EXP_FUNCT_TYPE::CONSTANT;
                }
            } else {
                b_nonlinear(ncol - count_linVar_col) = b_in(ncol);
            }
        }
        std::cout << "A_nonlinear after reduction\n"
                  << A_nonlinear;
    }

    template<typename Number>
    void Transformation<Number>::EigenvalueDecomposition(const Matrix<Number> &A_nonlinear,
                                                         const size_t dimensionNonLinear, const size_t CONDITION_LIMIT,
                                                         Matrix<Number> &V_EVD,
                                                         DiagonalMatrix<Number> &D_EVD, Matrix<Number> &Vinv_EVD) {
        // ONE DIMENSION -> set values(to save time)
        if (dimensionNonLinear == 1) {
            std::cout << "dimension == 1\n";
            V_EVD(0, 0) = 1;
            Vinv_EVD(0, 0) = 1;
            D_EVD.diagonal()(0) = A_nonlinear(0, 0);
            std::cout << "D_EVD:\n"
                      << A_nonlinear << "\n";
            return;
        }
        DiagonalMatrixdouble Ddouble = DiagonalMatrixdouble(dimensionNonLinear);    // formulation in .h
        Matrix<double> Vdouble = Matrix<double>(dimensionNonLinear, dimensionNonLinear);
        Matrix<double> Vinvdouble = Matrix<double>(dimensionNonLinear, dimensionNonLinear);
        Matrix<double> matrixCalcDouble = Matrix<double>(dimensionNonLinear, dimensionNonLinear);
        matrixCalcDouble = convert<Number, double>(A_nonlinear);
        Eigen::EigenSolver<Matrix<double>> es(matrixCalcDouble);
        Vdouble << es.eigenvectors().real();
        Ddouble.diagonal() << es.eigenvalues().real();
        Vinvdouble = Vdouble.inverse();
        // ASSERTION CONDITION TODO making this faster for big/sparse matrices
        Eigen::JacobiSVD<Matrix<double>> svd(Vinvdouble);
        double cond = svd.singularValues()(0) / svd.singularValues()(svd.singularValues().size() - 1);
        if (std::abs(cond) > CONDITION_LIMIT) {
            FATAL("hypro.eigendecomposition", "condition is higher than CONDITION_LIMIT");
        }
        std::cout << "A_nonlinear\n"
                  << A_nonlinear;
        // CHECKUP for invalid results
        bool outOfRange = false;
        if ((Vinvdouble.array().isNaN() == 1).any() || (Vinvdouble.array().isInf() == 1).any())
            outOfRange = true;
        if ((Vdouble.array().isNaN() == 1).any() || (Vdouble.array().isInf() == 1).any())
            outOfRange = true;
        if ((Ddouble.diagonal().array().isNaN() == 1).any() || (Ddouble.diagonal().array().isInf() == 1).any())
            outOfRange = true;
        // CONVERSION TO RATIONAL
        V_EVD = convert<double, Number>(Vdouble);
        D_EVD = convert<double, Number>(Ddouble);
        Vinv_EVD = convert<double, Number>(Vinvdouble);
        std::cout << "Vinv_EVD(condition): (" << cond << ")\n"
                  << Vinv_EVD;
        std::cout << "V_EVD:\n"
                  << V_EVD;
        std::cout << "D_EVD:\n"
                  << D_EVD.diagonal();
        TRACE("hypro.eigendecomposition", "V\n" << V_EVD);
        TRACE("hypro.eigendecompositoin", "Vinv\n"
                << Vinv_EVD);
        // exit after output of EVD for quick feedback
        if (outOfRange) {
            FATAL("hypro.eigendecomposition",
                  "OUT OF BOUNDS on EVD computation, please check the results in DEBUG mode");
            std::exit(EXIT_FAILURE);
        }
    }

    template<typename Number>
    void Transformation<Number>::adjustLinearAndEVDcomponents(
            const Matrix<Number> &V_EVD, const DiagonalMatrix<Number> &D_EVD, const Matrix<Number> &Vinv_EVD,
            const Matrix<Number> &A_in, const Vector<Number> &b_nonlinear, const size_t dimension,
            Matrix<Number> &V, Matrix<Number> &Vinv,
            Vector<Number> &b_tr, STallValues<Number> &mSTallvalues) {
        // 1.setting V,Vinv,D, b_tr
        V.setIdentity(dimension, dimension);
        Vinv.setIdentity(dimension, dimension);
        mSTallvalues.mSTindependentFunct.D.diagonal().setZero(dimension);
        size_t nrow, ncol;
        size_t count_linVar_row = 0;
        size_t count_linVar_col = 0;
        for (ncol = 0; ncol < dimension; ++ncol) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
                ++count_linVar_col;
                continue;
            }
            count_linVar_row = 0;
            for (nrow = 0; nrow < dimension; ++nrow) {
                if (mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                    ++count_linVar_row;
                    continue;
                } else {
                    V(nrow, ncol) = V_EVD(nrow - count_linVar_row, ncol - count_linVar_col);
                    Vinv(nrow, ncol) = Vinv_EVD(nrow - count_linVar_row, ncol - count_linVar_col);
                    mSTallvalues.mSTindependentFunct.D.diagonal()(ncol) = D_EVD.diagonal()(ncol - count_linVar_col);
                }
            }
            // ASSIGN b_tr
            b_tr(ncol) = b_nonlinear(ncol - count_linVar_col);
        }
        mSTallvalues.mSTflowpipeSegment.V = V;
        mSTallvalues.mSTflowpipeSegment.Vinv = Vinv;
        // 2.ADJUSTING b_tr (b_nonlinear was assigned)
        std::cout << "A_in\n"
                  << A_in;
        std::cout << b_tr;
        for (nrow = 0; nrow < dimension; ++nrow) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                for (ncol = 0; ncol < dimension; ++ncol) {
                    b_tr(ncol) += A_in(nrow, ncol) * b_tr(nrow);
                }
            }
        }
        // 3.ADJUSTING trafoMatrix for x
        for (ncol = 0; ncol < dimension; ++ncol) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                for (nrow = 0; nrow < dimension; ++nrow) {
                    if (nrow != ncol) {
                        mSTallvalues.mSTflowpipeSegment.trafoInput(nrow, ncol) = A_in(nrow, ncol);
                    }
                }
            }
        }
        // std::cout << "D[" << nrow <<"]: " << mSTallvalues.mSTindependentFunct.D.diagonal()(nrow) << "\n";
        DEBUG("hypro.eigendecomposition", "A_in\n"
                << A_in);
        DEBUG("hypro.eigendecomposition", "b_tr\n"
                << b_tr);
        DEBUG("hypro.eigendecomposition", "Vinv\n"
                << Vinv);
        DEBUG("hypro.eigendecomposition", "V\n" << V);
        DEBUG("hypro.eigendecomposition", "D\n" << mSTallvalues.mSTindependentFunct.D.diagonal());
        DEBUG("hypro.eigendecomposition", "trafoInput\n"
                << mSTallvalues.mSTflowpipeSegment.trafoInput);
    }

    template<typename Number>
    void Transformation<Number>::analyzeExponentialTerms(const size_t dimension, STallValues<Number> &mSTallvalues) {
        size_t nrow;
        // TODO COMPARISON ALMOST EQUAL 0 [else div by 0] (D.diagonal()(i) == 0 theoretically possible)
        for (nrow = 0; nrow < dimension; ++nrow) {
            if (mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::INITIALIZED) {
                assert(mSTallvalues.mSTindependentFunct.D.diagonal()(nrow) != 0);
                if (mSTallvalues.mSTindependentFunct.D.diagonal()(nrow) > 0) {
                    mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = CONVERGENT;
                } else {
                    mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = DIVERGENT;
                }
            }
            assert(mSTallvalues.mSTindependentFunct.expFunctionType[nrow] != EXP_FUNCT_TYPE::INITIALIZED);
        }
    }

    template<typename Number>
    void Transformation<Number>::output_HybridAutomaton() {
        std::cout << "\n-------------- STARTOF transformed AUTOMATA ------------------" << std::endl;
        std::cout << mTransformedHA << "\n-------------- ENDOF transformed AUTOMATA ------------------" << std::endl;
    }

}  // namespace hypro
