#pragma once

#include "../../../representations/TaylorModel/TaylorModel.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"
#include "../Handles/ClassHandle.h"
#include "../Handles/ObjectHandle.h"
#include <vector>
#include <carl/interval/Interval.h>
#include <carl/interval/set_theory.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/VariablePool.h>

class MHyProTaylorModel{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void emptyTM(int, mxArray**, int, const mxArray**);
        static void polyn_interTM(int, mxArray**, int, const mxArray**);
        static void polynTM(int, mxArray**, int, const mxArray**);
        static void interTM(int, mxArray**, int, const mxArray**);
        static void initlistTM(int, mxArray**, int, const mxArray**);
        static void initlist_interTM(int, mxArray**, int, const mxArray**);
        static void termTM(int, mxArray**, int, const mxArray**);
        static void varTM(int, mxArray**, int, const mxArray**);
        static void deleteTM(int, mxArray**, int, const mxArray**);
        static void isZero(int, mxArray**, int, const mxArray**);
        static void isConstant(int, mxArray**, int, const mxArray**);
        static void isLinear(int, mxArray**, int, const mxArray**);
        static void rmConstantTerm(int, mxArray**, int, const mxArray**);
        static void tmOrder(int, mxArray**, int, const mxArray**);
        static void pow(int, mxArray**, int, const mxArray**);
        static void checkConsistency(int, mxArray**, int, const mxArray**);
        static void has(int, mxArray**, int, const mxArray**);
        static void cutoff(int, mxArray**, int, const mxArray**);
        static void cutoff_nr(int, mxArray**, int, const mxArray**);
        static void truncation(int, mxArray**, int, const mxArray**);
        static void truncation_nr(int, mxArray**, int, const mxArray**);
        static void enclosure(int, mxArray**, int, const mxArray**);
        static void enclosure_nr(int, mxArray**, int, const mxArray**);
        static void poly_enclosure(int, mxArray**, int, const mxArray**);
        static void normalize(int, mxArray**, int, const mxArray**);
        static void add(int, mxArray**, int, const mxArray**);
        static void subtract(int, mxArray**, int, const mxArray**);
        static void mult_inter(int, mxArray**, int, const mxArray**);
        static void mult_tm(int, mxArray**, int, const mxArray**);
        static void mult_term(int, mxArray**, int, const mxArray**);
        static void mult_var(int, mxArray**, int, const mxArray**);


};

#include "MHyProTaylorModel.tpp"