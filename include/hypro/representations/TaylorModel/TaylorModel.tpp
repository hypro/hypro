/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * TaylorModel.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: chen
 */

#include "TaylorModel.h"

namespace hypro {

    template<typename Number>
    TaylorModel<Number>::TaylorModel() {
        carl::Interval <Number> intZero(0);
        remainder = intZero;
    }

    template<typename Number>
    TaylorModel<Number>::~TaylorModel() {
    }

    template<typename Number>
    TaylorModel<Number>::TaylorModel(const MultivariatePolynomial <carl::Interval<Number>> &p,
                                     const carl::Interval <Number> &r) {
        expansion = p;
        remainder = r;
    }

    template<typename Number>
    TaylorModel<Number>::TaylorModel(const MultivariatePolynomial <carl::Interval<Number>> &p) {
        expansion = p;

        carl::Interval <Number> intZero(0);
        remainder = intZero;
    }

    template<typename Number>
    TaylorModel<Number>::TaylorModel(const carl::Interval <Number> &I) {
        MultivariatePolynomial <carl::Interval<Number>> p(I);
        expansion = p;

        carl::Interval <Number> intZero(0);
        remainder = intZero;
    }

    template<typename Number>
    TaylorModel<Number>::TaylorModel(const TaylorModel<Number> &tm) {
        expansion = tm.expansion;
        remainder = tm.remainder;
    }

    template<typename Number>
    TaylorModel<Number>::TaylorModel(const std::initializer_list <Term<carl::Interval < Number>>

    >& terms ) {
    MultivariatePolynomial <carl::Interval<Number>> p(terms);
    expansion = p;

    carl::Interval <Number> intZero(0);
    remainder = intZero;
}

template<typename Number>
TaylorModel<Number>::TaylorModel(const std::initializer_list <Term<carl::Interval < Number>>

>& terms,
const carl::Interval <Number> &r
) {
MultivariatePolynomial <carl::Interval<Number>> p(terms);
expansion = p;

remainder = r;
}

template<typename Number>
TaylorModel<Number>::TaylorModel(const Term <carl::Interval<Number>> &term) {
    MultivariatePolynomial <carl::Interval<Number>> p(term);
    expansion = p;

    carl::Interval <Number> intZero(0);
    remainder = intZero;
}

template<typename Number>
TaylorModel<Number>::TaylorModel(carl::Variable::Arg v) {
    MultivariatePolynomial <carl::Interval<Number>> p(v);
    expansion = p;

    carl::Interval <Number> intZero(0);
    remainder = intZero;
}

/*
template<typename Coeff, typename Number>
TaylorModel<Coeff, Number>::TaylorModel(const Monomial & m)
{
		MultivariatePolynomial<Coeff> p(m);
		expansion = p;

		carl::Interval<Number> intZero(0);
		remainder = intZero;
}

template<typename Coeff, typename Number>
TaylorModel<Coeff, Number>::TaylorModel(std::shared_ptr<const Monomial> m)
{
		MultivariatePolynomial<Coeff> p(m);
		expansion = p;
}

template<typename Number>
TaylorModel<Number>::TaylorModel(std::shared_ptr<const Term<carl::Interval<Number>> >
t)
{
		MultivariatePolynomial<carl::Interval<Number>> p(t);
		expansion = p;

		carl::Interval<Number> intZero(0);
		remainder = intZero;
}

template<typename Coeff, typename Number>
TaylorModel<Coeff, Number>::TaylorModel(const std::initializer_list<carl::Variable> &
terms)
{
		MultivariatePolynomial<Coeff> p(terms);
		expansion = p;

		carl::Interval<Number> intZero(0);
		remainder = intZero;
}
*/

template<typename Number>
bool TaylorModel<Number>::isZero() const {
    carl::Interval <Number> intZero(0);
    return (expansion.isZero() && remainder == intZero);
}

template<typename Number>
bool TaylorModel<Number>::isConstant() const {
    return expansion.isConstant();
}

template<typename Number>
bool TaylorModel<Number>::isLinear() const {
    return expansion.isLinear();
}

template<typename Number>
carl::Interval <Number> TaylorModel<Number>::rmConstantTerm() {
    TermsType &vTerms = expansion.getTerms();

    auto iter = vTerms.begin();

    carl::Interval <Number> constant(0);

    if ((*iter).tdeg() == 0) {
        constant = (*iter).coeff();
        vTerms.erase(iter);
    }

    return constant;
}

template<typename Number>
exponent TaylorModel<Number>::tmOrder() const {
    return expansion.totalDegree();
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::pow(unsigned exp, Domain <Number> &domain, const exponent order) const {
    carl::Interval <Number> intZero(0), intOne(1);

    if (exp == 0) return TaylorModel(intOne);

    if (isZero()) return TaylorModel(intZero);

    TaylorModel <Number> res(intOne);
    TaylorModel <Number> mult(*this);

    while (exp > 0) {
        if (exp & 1) {
            res.multiply_assign(mult, domain, order);
        }

        exp /= 2;

        if (exp > 0) {
            mult.multiply_assign(mult, domain, order);
        }
    }

    return res;
}

template<typename Number>
void TaylorModel<Number>::cutoff(const carl::Interval <Number> &threshold, Domain <Number> &domain) {
    TermsType &vTerms = expansion.getTerms();

    typename TermsType::iterator term = vTerms.begin();

    for (; term != vTerms.end();) {
        MultivariatePolynomial <carl::Interval<Number>> p(*term);

        std::map <carl::Variable, carl::Interval<Number>> &d = domain.get_assignments();
        carl::Interval <Number> intTemp = p.evaluate(d);

        if (threshold.contains(intTemp)) {
            term = vTerms.erase(term);
            remainder += intTemp;
        } else {
            ++term;
        }
    }
}

template<typename Number>
void TaylorModel<Number>::cutoff_nr(const carl::Interval <Number> &threshold, Domain <Number> &domain) {
    TermsType &vTerms = expansion.getTerms();

    typename TermsType::iterator term = vTerms.begin();

    for (; term != vTerms.end();) {
        MultivariatePolynomial <carl::Interval<Number>> p(*term);

        std::map <carl::Variable, carl::Interval<Number>> &d = domain.get_assignments();
        carl::Interval <Number> intTemp = p.evaluate(d);

        if (threshold.contains(intTemp)) {
            term = vTerms.erase(term);
        } else {
            ++term;
        }
    }
}

template<typename Number>
void TaylorModel<Number>::truncation(const exponent order, Domain <Number> &domain) {
    TermsType truncated_terms;

    TermsType &vTerms = expansion.getTerms();

    expansion.makeOrdered();
    for (; vTerms.size() > 0;) {
        auto iter = vTerms.end();
        --iter;

        if ((*iter).tdeg() > order) {
            truncated_terms.insert(truncated_terms.begin(), vTerms.back());
            vTerms.pop_back();
        } else {
            break;
        }
    }

    MultivariatePolynomial <carl::Interval<Number>> p;
    TermsType &vTerms2 = p.getTerms();
    vTerms2 = truncated_terms;

    carl::Interval <Number> I;

    std::map <carl::Variable, carl::Interval<Number>> &d = domain.get_assignments();
    I = p.evaluate(d);

    remainder += I;
}

template<typename Number>
void TaylorModel<Number>::truncation_nr(const exponent order) {
    TermsType &vTerms = expansion.getTerms();

    expansion.makeOrdered();
    for (; vTerms.size() > 0;) {
        auto iter = vTerms.end();
        --iter;

        if ((*iter).tdeg() > order) {
            vTerms.pop_back();
        } else {
            break;
        }
    }
}

template<typename Number>
void TaylorModel<Number>::enclosure(carl::Interval <Number> &I, Domain <Number> &domain) const {
    std::map <carl::Variable, carl::Interval<Number>> &d = domain.get_assignments();

    I = expansion.evaluate(d);
    I += remainder;
}

template<typename Number>
void TaylorModel<Number>::poly_enclosure(carl::Interval <Number> &I, Domain <Number> &domain) const {
    std::map <carl::Variable, carl::Interval<Number>> &d = domain.get_assignments();

    I = expansion.evaluate(d);
}

template<typename Number>
void TaylorModel<Number>::normalize(Domain <Number> &domain) {
    carl::Interval <Number> intZero(0);

    std::map <carl::Variable, TaylorModel<Number>> substitutions;

    std::map <carl::Variable, carl::Interval<Number>> &assignments = domain.get_assignments();

    for (auto iter = assignments.begin(); iter != assignments.end(); ++iter) {
        Number center = iter->second.center();

        carl::Interval <Number> intCenter(center);
        TaylorModel tmCenter(intCenter);

        carl::Interval <Number> intTemp = iter->second - intCenter;
        Number magnitude = intTemp.magnitude();

        carl::Interval <Number> intMagnitude(magnitude);

        TaylorModel <Number> tmReplace(
                {(Term <carl::Interval<Number>>) intCenter, (carl::Interval <Number>) intMagnitude * (iter->first)},
                intZero);

        std::pair<const carl::Variable, TaylorModel < Number>>
        replacement(iter->first, tmReplace);
        substitutions.insert(replacement);
    }

    *this = this->substitute(substitutions, domain, this->tmOrder());
}

template<typename Number>
TaylorModel <Number> &TaylorModel<Number>::operator=(const TaylorModel <Number> &tm) {
    if (this == &tm) return *this;

    expansion = tm.expansion;
    remainder = tm.remainder;

    return *this;
}

template<typename Number>
TaylorModel <Number> &TaylorModel<Number>::operator+=(const TaylorModel <Number> &tm) {
    expansion += tm.expansion;
    remainder += tm.remainder;

    return *this;
}

template<typename Number>
TaylorModel <Number> &TaylorModel<Number>::operator-=(const TaylorModel <Number> &tm) {
    expansion -= tm.expansion;
    remainder -= tm.remainder;

    return *this;
}

template<typename Number>
const TaylorModel <Number> TaylorModel<Number>::operator+(const TaylorModel <Number> &tm) const {
    TaylorModel <Number> result = *this;
    result += tm;

    return result;
}

template<typename Number>
const TaylorModel <Number> TaylorModel<Number>::operator-(const TaylorModel <Number> &tm) const {
    TaylorModel <Number> result = *this;
    result -= tm;

    return result;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::multiply(const carl::Interval <Number> &I) const {
    TaylorModel <Number> result;

    result.expansion = expansion * I;
    result.remainder = remainder * I;

    return result;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::multiply(const TaylorModel <Number> &tm, Domain <Number> &domain,
                                                   const exponent order) const {
    TaylorModel <Number> result;

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    return result;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::multiply(const Term <carl::Interval<Number>> &term, Domain <Number> &domain,
                                                   const exponent order) const {
    TaylorModel <Number> result, tm(term);

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    return result;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::multiply(carl::Variable::Arg v, Domain <Number> &domain,
                                                   const exponent order) const {
    TaylorModel <Number> result, tm(v);

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    return result;
}

template<typename Number>
void TaylorModel<Number>::multiply_assign(const carl::Interval <Number> &I) {
    expansion *= I;
    remainder *= I;
}

template<typename Number>
void TaylorModel<Number>::multiply_assign(const TaylorModel <Number> &tm, Domain <Number> &domain,
                                          const exponent order) {
    TaylorModel <Number> result;

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    *this = result;
}

template<typename Number>
void TaylorModel<Number>::multiply_assign(const Term <carl::Interval<Number>> &term, Domain <Number> &domain,
                                          const exponent order) {
    TaylorModel <Number> result, tm(term);

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    *this = result;
}

template<typename Number>
void TaylorModel<Number>::multiply_assign(carl::Variable::Arg v, Domain <Number> &domain, const exponent order) {
    TaylorModel <Number> result, tm(v);

    result.expansion = expansion * tm.expansion;

    carl::Interval <Number> enclosure_tm1, enclosure_tm2;

    poly_enclosure(enclosure_tm1, domain);
    tm.poly_enclosure(enclosure_tm2, domain);

    enclosure_tm1 *= tm.remainder;
    enclosure_tm2 *= remainder;

    result.remainder = remainder * tm.remainder + enclosure_tm1 + enclosure_tm2;
    result.truncation(order, domain);

    *this = result;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::div(const carl::Interval <Number> &I) const {
    TaylorModel <Number> result;

    carl::Interval <Number> intTemp(1.0);
    intTemp = intTemp / I;

    result.expansion = expansion * intTemp;
    result.remainder = remainder * intTemp;

    return result;
}

template<typename Number>
void TaylorModel<Number>::div_assign(const carl::Interval <Number> &I) {
    carl::Interval <Number> intTemp(1.0);
    intTemp = intTemp / I;

    expansion *= intTemp;
    remainder *= intTemp;
}

template<typename Number>
TaylorModel <Number>
TaylorModel<Number>::substitute(const std::map <carl::Variable, TaylorModel<Number>> &substitutions,
                                Domain <Number> &domain, const exponent order) const {
    TaylorModel <Number> result(*this);

    if (isConstant() || substitutions.empty()) {
        return result;
    }

    MultivariatePolynomial <carl::Interval<Number>> polyZero;

    // Substitute the variables, which have to be replaced by 0, beforehand,
    // as this could significantly simplify this multivariate polynomial.
    for (auto sub = substitutions.begin(); sub != substitutions.end(); ++sub) {
        if (sub->second.isZero()) {
            result.expansion.substituteIn(sub->first, polyZero);
            if (result.isConstant()) {
                return result;
            }
        }
    }

    TermsType &mTerms = result.expansion.getTerms();
    carl::Interval <Number> intOne(1);
    TaylorModel <Number> tmOne(intOne);

    // Find and sort all exponents occurring for all variables to substitute as
    // basis.
    std::map <std::pair<carl::Variable, exponent>, TaylorModel<Number>> expResults;
    for (auto term: mTerms) {
        if (term.monomial()) {
            const Monomial &m = *(term.monomial());

            for (unsigned i = 0; i < m.nrVariables(); ++i) {
                if (m[i].second > 1 && substitutions.find(m[i].first) != substitutions.end()) {
                    expResults[m[i]] = tmOne;
                }
            }
        }
    }

    // Calculate the exponentiation of the multivariate polynomial to substitute
    // the
    // for variables for, reusing the already calculated exponentiations.
    if (!expResults.empty()) {
        auto expResultA = expResults.begin();
        auto expResultB = expResultA;
        auto sub = substitutions.begin();
        while (sub->first != expResultB->first.first) {
            assert(sub != substitutions.end());
            ++sub;
        }

        expResultB->second = sub->second.pow(expResultB->first.second, domain, order);
        ++expResultB;

        while (expResultB != expResults.end()) {
            if (expResultA->first.first != expResultB->first.first) {
                ++sub;
                assert(sub != substitutions.end());
                // Go to the next variable.
                while (sub->second.isZero()) {
                    assert(sub != substitutions.end());
                    ++sub;
                }

                expResultB->second = sub->second.pow(expResultB->first.second, domain, order);
            } else {
                TaylorModel <Number> tmTemp =
                        sub->second.pow(expResultB->first.second - expResultA->first.second, domain, order);
                expResultB->second = expResultA->second.multiply(tmTemp, domain, order);
            }

            ++expResultA;
            ++expResultB;
        }
    }

    carl::Interval <Number> intZero(0);
    TaylorModel <Number> resultB;

    // Substitute the variable for which all occurring exponentiations are
    // calculated.
    for (auto term: mTerms) {
        TaylorModel <Number> termResult(term.coeff());
        if (term.monomial()) {
            const Monomial &m = *(term.monomial());

            for (unsigned i = 0; i < m.nrVariables(); ++i) {
                if (m[i].second == 1) {
                    auto iter = substitutions.find(m[i].first);
                    if (iter != substitutions.end()) {
                        termResult.multiply_assign(iter->second, domain, order);
                    } else {
                        termResult.multiply_assign(m[i].first, domain, order);
                    }
                } else {
                    auto iter = expResults.find(m[i]);
                    if (iter != expResults.end()) {
                        termResult.multiply_assign(iter->second, domain, order);
                    } else {
                        termResult.multiply_assign(Term < carl::Interval < Number >> (intOne, m[i].first, m[i].second),
                                                   domain,
                                                   order);
                    }
                }
            }
        }

        resultB += termResult;
    }

    resultB.remainder += remainder;

    return resultB;
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::substitute(const TaylorModelVec <Number> &substitutions,
                                                     Domain <Number> &domain, const exponent order) const {
    return substitute(substitutions.tms, domain, order);
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::derivative(carl::Variable::Arg v, unsigned nth) const {
    TaylorModel <Number> result;

    result.expansion = this->expansion.derivative(v, nth);

    carl::Interval <Number> intZero(0);
    result.remainder = intZero;

    return result;
}

template<typename Number>
void TaylorModel<Number>::derivative_assign(carl::Variable::Arg v, unsigned nth) {
    expansion = expansion.derivative(v, nth);

    carl::Interval <Number> intZero(0);
    remainder = intZero;
}

template<typename Number>
TaylorModel <Number>
TaylorModel<Number>::integration(carl::Variable::Arg v, const carl::Interval <Number> &range_of_v) {
    TaylorModel <Number> result;

    if (!expansion.has(v)) {
        result.expansion = expansion * v;
        result.remainder = remainder * range_of_v;
        return result;
    } else {
        TermsType &mTerms = expansion.getTerms();

        for (auto term: mTerms) {
            Term <carl::Interval<Number>> newTerm(term);

            MonomialType monomial = newTerm.monomial();

            if (monomial == NULL) {
                newTerm *= v;
            } else {
                exponent d = monomial->exponentOfVariable(v);

                if (d > 0) {
                    carl::Interval <Number> intTemp((double) d + 1), intOne(1);
                    intTemp = intOne / intTemp;
                    newTerm *= intTemp;
                }

                newTerm *= v;
            }

            result.expansion += newTerm;
        }

        result.remainder = remainder * range_of_v;
    }
    return result;    // Todo: Inserted by Stefan, Xin - please check if okay!
}

template<typename Number>
void TaylorModel<Number>::integration_assign(carl::Variable::Arg v, const carl::Interval <Number> &range_of_v) {
    *this = integration(v, range_of_v);
}

template<typename Number>
TaylorModel <Number> TaylorModel<Number>::LieDerivative(const PolynomialODE <Number> &ode) const {
    std::set <carl::Variable> vars;
    expansion.gatherVariables(vars);

    TaylorModel <Number> result;

    std::set<carl::Variable>::iterator iter = vars.begin();
    for (; iter != vars.end(); ++iter) {
        MultivariatePolynomial <carl::Interval<Number>> rhs;

        bool bFound = ode.find_assignment(rhs, *iter);

        if (bFound) {
            MultivariatePolynomial <carl::Interval<Number>> polyTemp = expansion.derivative(*iter);
            polyTemp *= rhs;
            result.expansion += polyTemp;
        } else {
            assert(!bFound);
        }
    }

    vars.clear();

    return result;
}

template<typename Number>
void TaylorModel<Number>::LieDerivative_assign(const PolynomialODE <Number> &ode) {
    *this = LieDerivative(ode);
}

template<typename Number>
void TaylorModel<Number>::checkConsistency() const {
    expansion.checkConsistency();
}

template<typename Number>
bool TaylorModel<Number>::has(carl::Variable::Arg v) const {
    return expansion.has(v);
}

template<typename N>
std::ostream &operator<<(std::ostream &os, const TaylorModel <N> &tm) {
    return os << tm.expansion << '+' << tm.remainder;
}

template<typename Number>
Domain<Number>::Domain() {
}

template<typename Number>
Domain<Number>::~Domain() {
    assignments.clear();
}

template<typename Number>
Domain<Number>::Domain(const Domain <Number> &domain) {
    assignments = domain.assignments;
}

template<typename Number>
void Domain<Number>::assign(const carl::Variable &v, const carl::Interval <Number> &I) {
    auto iter = assignments.find(v);

    assignment_type assignment(v, I);

    if (iter == assignments.end()) {
        assignments.insert(assignment);
    } else {
        assignments.erase(iter);
        assignments.insert(assignment);
    }
}

template<typename Number>
bool Domain<Number>::find_assignment(carl::Interval <Number> &I, const carl::Variable &v) const {
    auto iter = assignments.find(v);

    if (iter == assignments.end()) {
        return false;
    } else {
        I = iter->second;
        return true;
    }
}

template<typename Number>
std::map <carl::Variable, carl::Interval<Number>> &Domain<Number>::get_assignments() {
    return assignments;
}

template<typename Number>
void Domain<Number>::clear() {
    assignments.clear();
}

template<typename Number>
Domain <Number> &Domain<Number>::operator=(const Domain <Number> &domain) {
    if (this == &domain) return *this;

    assignments = domain.assignments;
    return *this;
}

template<typename N>
std::ostream &operator<<(std::ostream &os, const Domain <N> &domain) {
    for (auto iter = domain.assignments.begin(); iter != domain.assignments.end(); ++iter) {
        os << iter->first << " in " << iter->second << std::endl;
    }

    return os;
}

template<typename Number>
PolynomialODE<Number>::PolynomialODE() {
}

template<typename Number>
PolynomialODE<Number>::PolynomialODE(const PolynomialODE <Number> &ode) {
    assignments = ode.assignments;
}

template<typename Number>
PolynomialODE<Number>::~PolynomialODE() {
    assignments.clear();
}

template<typename Number>
void
PolynomialODE<Number>::assign(const carl::Variable &v, const MultivariatePolynomial <carl::Interval<Number>> &rhs) {
    auto iter = assignments.find(v);

    assignment_type assignment(v, rhs);

    if (iter == assignments.end()) {
        assignments.insert(assignment);
    } else {
        iter->second = rhs;
    }
}

template<typename Number>
bool PolynomialODE<Number>::find_assignment(MultivariatePolynomial <carl::Interval<Number>> &rhs,
                                            const carl::Variable &v) const {
    auto iter = assignments.find(v);

    if (iter == assignments.end()) {
        return false;
    } else {
        rhs = iter->second;
        return true;
    }
}

template<typename Number>
std::map <carl::Variable, MultivariatePolynomial<carl::Interval < Number>>>&

PolynomialODE<Number>::get_assignments() {
    return assignments;
}

template<typename Number>
PolynomialODE <Number> &PolynomialODE<Number>::operator=(const PolynomialODE <Number> &ode) {
    if (this == &ode) return *this;

    assignments = ode.assignments;
    return *this;
}

template<typename N>
std::ostream &operator<<(std::ostream &os, const PolynomialODE <N> &ode) {
    for (auto iter = ode.assignments.begin(); iter != ode.assignments.end(); ++iter) {
        os << iter->first << '\'' << " = " << iter->second << std::endl;
    }

    os << std::endl;

    return os;
}

template<typename Number>
Range<Number>::Range() {
}

template<typename Number>
Range<Number>::~Range() {
    assignments.clear();
}

template<typename Number>
Range<Number>::Range(const Range <Number> &range) {
    assignments = range.assignments;
}

template<typename Number>
void Range<Number>::assign(const carl::Variable &v, const carl::Interval <Number> &I) {
    auto iter = assignments.find(v);

    assignment_type assignment(v, I);

    if (iter == assignments.end()) {
        assignments.insert(assignment);
    } else {
        assignments.erase(iter);
        assignments.insert(assignment);
    }
}

template<typename Number>
bool Range<Number>::find_assignment(carl::Interval <Number> &I, const carl::Variable &v) const {
    auto iter = assignments.find(v);

    if (iter == assignments.end()) {
        return false;
    } else {
        I = iter->second;
        return true;
    }
}

template<typename Number>
std::map <carl::Variable, carl::Interval<Number>> &Range<Number>::get_assignments() {
    return assignments;
}

template<typename Number>
void Range<Number>::clear() {
    assignments.clear();
}

template<typename Number>
Range <Number> &Range<Number>::operator=(const Range <Number> &range) {
    if (this == &range) return *this;

    assignments = range.assignments;
    return *this;
}

template<typename N>
std::ostream &operator<<(std::ostream &os, const Range <N> &range) {
    for (auto iter = range.assignments.begin(); iter != range.assignments.end(); ++iter) {
        os << iter->first << " in " << iter->second << std::endl;
    }

    return os;
}

template<typename Number>
TaylorModelVec<Number>::TaylorModelVec() {
}

template<typename Number>
TaylorModelVec<Number>::TaylorModelVec(const std::map <carl::Variable, TaylorModel<Number>> &assignments) {
    tms = assignments;
}

template<typename Number>
TaylorModelVec<Number>::TaylorModelVec(Range <Number> &range) {
    std::map <carl::Variable, carl::Interval<Number>> &assignments = range.get_assignments();

    for (auto iter = assignments.begin(); iter != assignments.end(); ++iter) {
        TaylorModel <Number> tmTemp(iter->second);

        assignment_type assignment(iter->first, tmTemp);

        tms.insert(assignment);
    }
}

template<typename Number>
TaylorModelVec<Number>::TaylorModelVec(const TaylorModelVec &tmv) {
    tms = tmv.tms;
}

template<typename Number>
TaylorModelVec<Number>::~TaylorModelVec() {
}

template<typename Number>
void TaylorModelVec<Number>::assign(const carl::Variable &v, const TaylorModel <Number> &tm) {
    auto iter = tms.find(v);

    assignment_type assignment(v, tm);

    if (iter == tms.end()) {
        tms.insert(assignment);
    } else {
        iter->second = tm;
    }
}

template<typename Number>
bool TaylorModelVec<Number>::find_assignment(TaylorModel <Number> &tm, const carl::Variable &v) const {
    auto iter = tms.find(v);

    if (iter == tms.end()) {
        return false;
    } else {
        tm = iter->second;
        return true;
    }
}

template<typename Number>
bool TaylorModelVec<Number>::isEmpty() const {
    if (tms.size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename Number>
void TaylorModelVec<Number>::clear() {
    tms.clear();
}

template<typename Number>
void TaylorModelVec<Number>::rmConstantTerm(Range <Number> &constant) {
    constant.clear();

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        carl::Interval <Number> intTemp;

        intTemp = iter->second.rmConstantTerm();

        constant.assign(iter->first, intTemp);
    }
}

template<typename Number>
void TaylorModelVec<Number>::cutoff(const carl::Interval <Number> &threshold, Domain <Number> &domain) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.cutoff(threshold, domain);
    }
}

template<typename Number>
void TaylorModelVec<Number>::cutoff_nr(const carl::Interval <Number> &threshold, Domain <Number> &domain) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.cutoff_nr(threshold, domain);
    }
}

template<typename Number>
void TaylorModelVec<Number>::truncation(const exponent order, Domain <Number> &domain) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.truncation(order, domain);
    }
}

template<typename Number>
void TaylorModelVec<Number>::truncation_nr(const exponent order) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.truncation_nr(order);
    }
}

template<typename Number>
void TaylorModelVec<Number>::enclosure(Range <Number> &range, Domain <Number> &domain) const {
    range.clear();

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        carl::Interval <Number> I;
        iter->second.enclosure(I, domain);

        range.assign(iter->first, I);
    }
}

template<typename Number>
TaylorModelVec <Number> &TaylorModelVec<Number>::operator=(const TaylorModelVec <Number> &tmv) {
    if (this == &tmv) return *this;

    tms = tmv.tms;

    return *this;
}

template<typename Number>
TaylorModelVec <Number> &TaylorModelVec<Number>::operator+=(const TaylorModelVec <Number> &tmv) {
    if (tms.size() != tmv.tms.size()) {
        std::cout << "operator +: Dimensions of the operands are not equivalent." << std::endl;
        return *this;
    }

    TaylorModelVec <Number> tmvTemp = *this;

    auto iter1 = tmvTemp.tms.begin();
    auto iter2 = tmv.tms.begin();

    for (; iter1 != tmvTemp.tms.end() && iter2 != tmv.tms.end(); ++iter1, ++iter2) {
        if (iter1->first != iter2->first) {
            std::cout << "operator +: Taylor models in different spaces." << std::endl;
            return *this;
        } else {
            iter1->second += iter2->second;
        }
    }

    *this = tmvTemp;

    return *this;
}

template<typename Number>
TaylorModelVec <Number> &TaylorModelVec<Number>::operator-=(const TaylorModelVec <Number> &tmv) {
    if (tms.size() != tmv.tms.size()) {
        std::cout << "operator +: Dimensions of the operands are not equivalent." << std::endl;
        return *this;
    }

    TaylorModelVec <Number> tmvTemp = *this;

    auto iter1 = tmvTemp.tms.begin();
    auto iter2 = tmv.tms.begin();

    for (; iter1 != tmvTemp.tms.end() && iter2 != tmv.tms.end(); ++iter1, ++iter2) {
        if (iter1->first != iter2->first) {
            std::cout << "operator +: Taylor models in different spaces." << std::endl;
            return *this;
        } else {
            iter1->second -= iter2->second;
        }
    }

    *this = tmvTemp;

    return *this;
}

template<typename Number>
const TaylorModelVec <Number> TaylorModelVec<Number>::operator+(const TaylorModelVec <Number> &tmv) const {
    if (tms.size() != tmv.tms.size()) {
        std::cout << "operator +: Dimensions of the operands are not equivalent." << std::endl;
        return *this;
    }

    TaylorModelVec <Number> result = *this;

    auto iter1 = result.tms.begin();
    auto iter2 = tmv.tms.begin();

    for (; iter1 != result.tms.end() && iter2 != tmv.tms.end(); ++iter1, ++iter2) {
        if (iter1->first != iter2->first) {
            std::cout << "operator +: Taylor models in different spaces." << std::endl;
            return *this;
        } else {
            iter1->second += iter2->second;
        }
    }

    return result;
}

template<typename Number>
const TaylorModelVec <Number> TaylorModelVec<Number>::operator-(const TaylorModelVec <Number> &tmv) const {
    if (tms.size() != tmv.tms.size()) {
        std::cout << "operator +: Dimensions of the operands are not equivalent." << std::endl;
        return *this;
    }

    TaylorModelVec <Number> result = *this;

    auto iter1 = result.tms.begin();
    auto iter2 = tmv.tms.begin();

    for (; iter1 != result.tms.end() && iter2 != tmv.tms.end(); ++iter1, ++iter2) {
        if (iter1->first != iter2->first) {
            std::cout << "operator +: Taylor models in different spaces." << std::endl;
            return *this;
        } else {
            iter1->second -= iter2->second;
        }
    }

    return result;
}

template<typename Number>
TaylorModelVec <Number>
TaylorModelVec<Number>::substitute(const std::map <carl::Variable, TaylorModel<Number>> &substitutions,
                                   Domain <Number> &domain, const exponent order) const {
    TaylorModelVec <Number> result;

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        TaylorModel <Number> tmTemp;

        tmTemp = iter->second.substitute(substitutions, domain, order);

        result.assign(iter->first, tmTemp);
    }

    return result;
}

template<typename Number>
TaylorModelVec <Number> TaylorModelVec<Number>::substitute(const TaylorModelVec <Number> &substitutions,
                                                           Domain <Number> &domain, const exponent order) const {
    TaylorModelVec <Number> result;

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        TaylorModel <Number> tmTemp;

        tmTemp = iter->second.substitute(substitutions, domain, order);

        result.assign(iter->first, tmTemp);
    }

    return result;
}

template<typename Number>
TaylorModelVec <Number> TaylorModelVec<Number>::derivative(carl::Variable::Arg v, unsigned nth) const {
    TaylorModelVec <Number> result;

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        TaylorModel <Number> tmTemp;

        tmTemp = iter->second.derivative(v, nth);

        result.assign(iter->first, tmTemp);
    }

    return result;
}

template<typename Number>
void TaylorModelVec<Number>::derivative_assign(carl::Variable::Arg v, unsigned nth) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.derivative_assign(v, nth);
    }
}

template<typename Number>
TaylorModelVec <Number> TaylorModelVec<Number>::LieDerivative(const PolynomialODE <Number> &ode) const {
    TaylorModelVec <Number> result;

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        TaylorModel <Number> tmTemp;

        tmTemp = iter->second.LieDerivative(ode);

        result.assign(iter->first, tmTemp);
    }

    return result;
}

template<typename Number>
void TaylorModelVec<Number>::LieDerivative_assign(const PolynomialODE <Number> &ode) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.LieDerivative_assign(ode);
    }
}

template<typename Number>
TaylorModelVec <Number>
TaylorModelVec<Number>::integration(carl::Variable::Arg v, const carl::Interval <Number> &range_of_v) {
    TaylorModelVec <Number> result;

    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        TaylorModel <Number> tmTemp;

        tmTemp = iter->second.integration(v, range_of_v);

        result.assign(iter->first, tmTemp);
    }

    return result;
}

template<typename Number>
void TaylorModelVec<Number>::integration_assign(carl::Variable::Arg v, const carl::Interval <Number> &range_of_v) {
    for (auto iter = tms.begin(); iter != tms.end(); ++iter) {
        iter->second.integration_assign(v, range_of_v);
    }
}

template<typename Number>
TaylorModelVec <Number> TaylorModelVec<Number>::Picard(const TaylorModelVec <Number> &x0,
                                                       const PolynomialODE <Number> &ode, Domain <Number> &domain,
                                                       carl::Variable::Arg t, const carl::Interval <Number> &range_of_t,
                                                       const exponent order) const {
    TaylorModelVec <Number> tmvTemp;

    for (auto iter = ode.assignments.begin(); iter != ode.assignments.end(); ++iter) {
        TaylorModel <Number> tmODE(iter->second), tmTemp;

        tmTemp = tmODE.substitute(tms, domain, order);

        tmvTemp.assign(iter->first, tmTemp);
    }

    tmvTemp.integration_assign(t, range_of_t);
    tmvTemp.truncation(order, domain);

    tmvTemp += x0;

    return tmvTemp;
}

template<typename Number>
void TaylorModelVec<Number>::Picard_assign(const TaylorModelVec <Number> &x0, const PolynomialODE <Number> &ode,
                                           Domain <Number> &domain, carl::Variable::Arg t,
                                           const carl::Interval <Number> &range_of_t,
                                           const exponent order) {
    TaylorModelVec <Number> tmvTemp;

    for (auto iter = ode.assignments.begin(); iter != ode.assignments.end(); ++iter) {
        TaylorModel <Number> tmODE(iter->second), tmTemp;

        tmTemp = tmODE.substitute(tms, domain, order);

        tmvTemp.assign(iter->first, tmTemp);
    }

    tmvTemp.integration_assign(t, range_of_t);
    tmvTemp.truncation(order, domain);

    tmvTemp += x0;

    *this = tmvTemp;
}

template<typename N>
std::ostream &operator<<(std::ostream &os, const TaylorModelVec <N> &tmv) {
    for (auto iter = tmv.tms.begin(); iter != tmv.tms.end(); ++iter) {
        os << iter->first << " = " << iter->second << std::endl;
    }

    os << std::endl;

    return os;
}

}  // namespace hypro
