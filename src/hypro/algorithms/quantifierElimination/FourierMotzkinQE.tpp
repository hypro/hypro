#include "FourierMotzkinQE.h"

namespace hypro {
    template<typename Number>
    FormulaT<Number> FourierMotzkinQE<Number>::eliminateQuantifiers() {
        // iterate over query
        for(const auto& QuantifierVariablesPair : mQuery) {
            // we are ignoring the quantifier type
            assert(QuantifierVariablesPair.first == QuantifierType::EXISTS);

            // eliminate one variable after the other
            for(const auto& var : QuantifierVariablesPair.second) {
                std::cout << "eliminate " << var << std::endl;

                auto bounds = findBounds(var);
                // combine all lower-upper bound pairs.
                FormulasT<Number> newConstraints;
                if(!bounds[2].empty()) {
                    std::cout << "Found equation(s), substitute." << std::endl;
                    newConstraints = substituteEquations(bounds,var);
                } else {
                    std::cout << "Create lower-upper bound pairs." << std::endl;
                    newConstraints = createNewConstraints(bounds, var);
                }

                // add all constraints which are not containing var to newConstraints
                for(const auto formulaIt : bounds[3]) {
                    assert((formulaIt).getType() == carl::FormulaType::CONSTRAINT);
                    newConstraints.emplace_back(formulaIt);
                }

                // assemble new formula
                mFormula = FormulaT<Number>(carl::FormulaType::AND, newConstraints);
            }
        }

        return mFormula;
    }

    template<typename Number>
    typename FourierMotzkinQE<Number>::FormulaPartition FourierMotzkinQE<Number>::findBounds(const carl::Variable& variable) {
        // result vector initialized with three subsets
        typename FourierMotzkinQE<Number>::FormulaPartition res{4,std::vector<FormulaT<Number>>()};

        // if the formula only contains one constraint, check for occurence of the variable.
        if(mFormula.getType() == carl::FormulaType::CONSTRAINT) {
            if(!mFormula.constraint().hasVariable(variable)) {
                res[3].push_back(mFormula);
            } else {
                if(mFormula.constraint().relation() == carl::Relation::EQ){
                    res[2].push_back(mFormula);
                } else if(isLinearLowerBound(mFormula.constraint(), variable)){
                    res[0].push_back(mFormula);
                } else {
                    res[1].push_back(mFormula);
                }
            }
            return res;
        }

        // More than one constaint: search formula to find bounds
        for(auto formulaIt = mFormula.begin(); formulaIt != mFormula.end(); ++formulaIt) {
            assert((*formulaIt).getType() == carl::FormulaType::CONSTRAINT);
            if((*formulaIt).constraint().hasVariable(variable)) {
                if((*formulaIt).constraint().relation() == carl::Relation::EQ) {
                    res[2].push_back(*formulaIt);
                } else if(isLinearLowerBound((*formulaIt).constraint(), variable)) {
                    res[0].push_back(*formulaIt);
                } else {
                    res[1].push_back(*formulaIt);
                }
            } else {
                res[3].push_back(*formulaIt);
            }
        }

        return res;
    }

    template<typename Number>
    FormulasT<Number> FourierMotzkinQE<Number>::createNewConstraints(const typename FourierMotzkinQE<Number>::FormulaPartition& bounds, carl::Variable v) {

        FormulasT<Number> constraints;

        // combine all pairs of lower and upper bounds.
        for(const auto& lowerBnd : bounds[0]) {
            for(const auto& upperBnd : bounds[1]) {
                std::cout << "Combine " << (lowerBnd) << " and " << (upperBnd) << std::endl;

                PolyT<Number> lhs = getRemainder(lowerBnd.constraint(), v, true);

                std::cout << "Lhs is " << lhs << std::endl;

                PolyT<Number> rhs = getRemainder(upperBnd.constraint(), v, false);

                std::cout << "Rhs is " << rhs << std::endl;

                constraints.emplace_back(FormulaT<Number>(ConstraintT<Number>(lhs-rhs, carl::Relation::LEQ)));

                std::cout << "Created new constraint: " << constraints.back() << std::endl;
            }
        }

        return constraints;
    }

    template<typename Number>
    FormulasT<Number> FourierMotzkinQE<Number>::substituteEquations(const typename FourierMotzkinQE<Number>::FormulaPartition& bounds, carl::Variable v) {
        assert(!bounds[2].empty());
        FormulasT<Number> constraints;

        // check if equations are pairwise equal - if not return false, otherwise use one of the equations.
        // Todo: This test is not correct: having x = 3 + y and x = 3 would fail this test but still is satisfiable when y is existentially quantified or if it is all-quantified it is after x.
        FormulasT<Number> substitutes;
        if(bounds[2].size() == 1) {
            substitutes.push_back(FormulaT<Number>(bounds[2].front()));
        } else {
            for(auto f = bounds[2].begin(); f != bounds[2].end(); ++f) {
                assert(f->getType() == carl::FormulaType::CONSTRAINT);
                assert(f->constraint().relation() == carl::Relation::EQ);

                std::cout << "F: " << *f << std::endl;
                for(auto g = std::next(f); g != bounds[2].end(); ++g) {
                    assert(g->getType() == carl::FormulaType::CONSTRAINT);
                    assert(g->constraint().relation() == carl::Relation::EQ);
                    FormulaT<Number> newEq = FormulaT<Number>(f->constraint().lhs() - g->constraint().lhs(), carl::Relation::EQ);

                    std::cout << "G: " << *g << std::endl;

                    // 1st case: equalities contradict each other - quit substitution.
                    if( newEq.getType() == carl::FormulaType::FALSE) {
                        constraints.clear();
                        constraints.emplace_back(FormulaT<Number>(carl::FormulaType::FALSE));
                        return constraints;
                    } else if( newEq.getType() == carl::FormulaType::TRUE) {
                        // both equations are completely equal, just take one.
                        substitutes.push_back(FormulaT<Number>(*f));
                    } else {
                        // the equations are no equal but involve different variables, e.g. [eliminate x]: x = y AND x = z
                        substitutes.push_back(FormulaT<Number>(*f));
                        substitutes.push_back(FormulaT<Number>(*g));
                        // Todo: We could add the constraint y = z.
                    }
                }
            }
        }

        std::cout << "All equations are equal." << std::endl;

        // substitute
        for(const auto& f : substitutes) {
            std::cout << "Substitute: " << f << std::endl;
            assert(f.getType() == carl::FormulaType::CONSTRAINT);
            PolyT<Number> substitute = -(f.constraint().lhs() - f.constraint().coefficient(v,1)*v);
            // lower bounds
            for(auto fc : bounds[0]) {
                assert(fc.getType() == carl::FormulaType::CONSTRAINT);
                constraints.emplace_back(fc.constraint().lhs().substitute(v, substitute), fc.constraint().relation());
                std::cout << "substitute lower bound to " << constraints.back() << std::endl;
            }
            // upper bounds
            for(auto fc : bounds[1]) {
                assert(fc.getType() == carl::FormulaType::CONSTRAINT);
                constraints.emplace_back(fc.constraint().lhs().substitute(v, substitute), fc.constraint().relation());
                std::cout << "substitute upper bound to " << constraints.back() << std::endl;
            }
        }

        return constraints;
    }

    template<typename Number>
    PolyT<Number> FourierMotzkinQE<Number>::getRemainder(const ConstraintT<Number>& c, carl::Variable v, bool isLowerBnd) {
        if(isLowerBnd) {
            if(c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::LEQ) {
                return c.lhs() - c.coefficient(v,1)*v;
            } else {
                return -(c.lhs() - c.coefficient(v,1)*v);
            }
        } else {
            if(c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::LEQ) {
                return -(c.lhs() - c.coefficient(v,1)*v);
            } else {
                return c.lhs() - c.coefficient(v,1)*v;
            }
        }
    }

    template<typename Number>
    bool FourierMotzkinQE<Number>::isLinearLowerBound(const ConstraintT<Number>& c, carl::Variable v) {
        assert(c.hasVariable(v));
        assert(c.coefficient(v,1).isNumber());

        // is linear lower bound when the coefficient is > 0 and the relation is LEQ or LESS, or if the coefficient is < 0 and the relation is GEQ or GREATER.
        if( ((c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS) && c.coefficient(v,1) < 0) ||
        ((c.relation() == carl::Relation::GEQ || c.relation() == carl::Relation::GREATER) && c.coefficient(v,1) > 0) ) {
            std::cout << c << " is lower bound." << std::endl;
            return true;
        }
        std::cout << c << " is no lower bound." << std::endl;
        return false;
    }

} // hypro