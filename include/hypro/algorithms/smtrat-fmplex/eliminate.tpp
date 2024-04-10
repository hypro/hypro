#pragma once

#include <iostream>
#include <fstream>

#include "eliminate.h"

namespace smtrat::fmplex {

template<typename Var>
struct VariableIndex {
    std::vector<Var> m_vars;

    VariableIndex() {}

    explicit VariableIndex(const std::vector<Var>& vs) : m_vars(vs) {}

    std::size_t add_variable(const Var v) {
        if (std::find(m_vars.begin(), m_vars.end(), v) == m_vars.end()) {
            m_vars.push_back(v);
        }
        return m_vars.size() - 1;
    }

    std::size_t index(Var v) const {
        auto it = std::find(m_vars.begin(), m_vars.end(), v);
        assert(it != m_vars.end());
        return std::distance(m_vars.begin(), it);
    }

    Var var(std::size_t i) const {
        assert(i < m_vars.size());
        return m_vars[i];
    }

    std::size_t size() const { return m_vars.size(); }
};

template<typename Number>
using Poly = carl::MultivariatePolynomial<Number>;

template<typename Number>
Formula<Number> eliminate_variables(const Formula<Number>& f, const std::vector<carl::Variable>& vars) {
    if (f.type() == carl::FormulaType::CONSTRAINT) {
        auto f_vars = f.variables();
        if (std::any_of(
            vars.begin(), vars.end(), [&f_vars](const auto& v){ return f_vars.count(v) > 0; }
        )) {
            return Formula<Number>(carl::FormulaType::TRUE);
        }
        return f;
    }
    assert(f.type() == carl::FormulaType::AND);

    // transform formula to matrix
    std::vector<Formula<Number>> constraints = f.subformulas();
    // TODO: equality substitution, filtering
    VariableIndex<carl::Variable> var_idx(vars);
    carl::carlVariables vs;
    for (const auto& f : constraints) carl::variables(f, vs);
    for (const auto  v : vs) var_idx.add_variable(v);

    // reserve enough space for the matrix
    std::size_t constant_col = var_idx.size();
    std::size_t delta_col = constant_col + 1;
    Matrix<Number> m(constraints.size(), var_idx.size() + constraints.size() + 2); // +2 : delta & rhs.
    std::size_t non_zeros = 2*constraints.size(); // one origin & at most one delta for each row
    for (const auto& f : constraints) non_zeros += f.constraint().lhs().nr_terms();
    m.reserve(non_zeros);

    // transform each constraint into a row
    for (std::size_t r = 0; r < constraints.size(); ++r) {
        carl::Relation rel = constraints[r].constraint().relation();

        // smtrat automatically converts constraints to < or <=
        assert(rel != carl::Relation::GREATER && rel != carl::Relation::GEQ);
        assert(rel != carl::Relation::NEQ); // we don't support NEQ yet

        Poly<Number> lhs = constraints[r].constraint().lhs();
        Number constant_part = lhs.constant_part();
        lhs -= constant_part;

        std::vector<typename Matrix<Number>::RowEntry> entries; // TODO: make it so that the contents of the row are actually already in the matrix data
        for (const auto& term : lhs) {
            entries.emplace_back(var_idx.index(term.single_variable()), term.coeff());
        }
        // the order in the polynomial may be different from the order in the var index
        std::sort(entries.begin(), entries.end(),
            [](const auto& lhs, const auto& rhs){ return lhs.col_index < rhs.col_index; }
        );

        // constant part, delta, and origin
        if (!carl::is_zero(constant_part)) entries.emplace_back(constant_col, constant_part);
        if (rel == carl::Relation::LESS)   entries.emplace_back(delta_col, Number(1));
        entries.emplace_back(delta_col + r + 1, Number(1));

        m.append_row(entries.begin(), entries.end());
    }

    Matrix res = FMplexElimination<Number>(m, vars.size(), var_idx.size() - vars.size()).apply();

    // transform Matrix back to formula
    if (res.n_rows() == 0) return Formula<Number>(carl::FormulaType::TRUE);
    std::vector<Formula<Number>> conjuncts;
    for (std::size_t i = 0; i < res.n_rows(); ++i) {
        Poly<Number> lhs;
        auto it = res.row_begin(i);
        auto row_end = res.row_end(i);
        for (; it !=row_end && it->col_index < constant_col; ++it) {
            lhs += it->value*Poly(var_idx.var(it->col_index));
        }
        if (it != row_end && it->col_index == constant_col) {
            lhs += it->value;
            ++it;
        }
        // This method is only applied to pos.lin. combinations, so the delta coeff will be >=0
        if (it != row_end && it->col_index == delta_col) conjuncts.emplace_back(lhs, carl::Relation::LESS);
        else conjuncts.emplace_back(lhs, carl::Relation::LEQ);
    }

    if (conjuncts.size() == 1) return conjuncts.front();
    else return Formula(carl::FormulaType::AND, conjuncts);
}


template<typename Number>
std::pair<EigenMat<Number>, EigenVec<Number>> eliminate_cols(const EigenMat<Number>& constraints,
                                             const EigenVec<Number>& constants,
                                             const std::vector<std::size_t>& cols) {
    // convert to internal matrix type
    Matrix<Number> m(constraints.rows(), constraints.cols() + 2 + constraints.rows());
    std::size_t quantified_cols = cols.size();
    VariableIndex<std::size_t> var_idx(cols);
    for (std::size_t i = 0, q = 0; i < constraints.rows(); ++i) {
        if (q < cols.size() && i == cols[q]) ++q;
        else var_idx.add_variable(i);
    }

    for (std::size_t i = 0; i < constraints.rows(); ++i) {
        std::vector<typename Matrix<Number>::RowEntry> row;
        for (std::size_t j = 0; j < constraints.cols(); ++j) {
            if (!carl::is_zero(constraints(i,var_idx.var(j)))) {
                row.emplace_back(j, constraints(i,var_idx.var(j)));
            }
        }
        if (!carl::is_zero(constants(i))) row.emplace_back(constraints.cols(), -constants(i));
        row.emplace_back(constraints.cols() + 1 + i, Number(1)); // TODO: maybe this transformation should be done by fmplex internally?
        m.append_row(row.begin(), row.end());
    }

    Matrix<Number> res = FMplexElimination<Number>(m, quantified_cols, constraints.cols() - quantified_cols).apply();

    EigenMat<Number> res_mat = EigenMat<Number>::Zero(res.n_rows(), constraints.cols());
    EigenVec<Number> res_const = EigenVec<Number>::Zero(res.n_rows());
    // convert back to original format
    for (std::size_t i = 0; i < res.n_rows(); ++i) {
        for (const auto& e : res.row_entries(i)) {
            if (e.col_index == constraints.cols()) {
                res_const(i) = -e.value;
                break;
            }
            if (e.col_index > constraints.cols()) break;
            res_mat(i, var_idx.var(e.col_index)) = e.value;
        }
    }

    return {res_mat, res_const};
}

template<typename Number>
void write_matrix_to_ine(const EigenMat<Number>& constraints,
                         const EigenVec<Number>& constants,
                         const std::vector<std::size_t>& cols,
                         const std::string& filename) {
    std::ofstream file;
    file.open(filename);
    file << "H-representation\n";
    file << "begin\n";
    file << constraints.rows() << "  " << constraints.cols() + 1 << "  Number\n";
    for (std::size_t i = 0; i < constraints.rows(); ++i) {
        /*Number lcm = (carl::is_zero(constants(i)) ? Number(1) : constants(i).get_den());
        for (std::size_t j = 0; j < constraints.cols(); ++j) {
            lcm = carl::lcm(lcm.get_num(), constraints(i,j).get_den());
        }
        */
        Number lcm = 1;
        file << "  " << constants(i)*lcm; // first column contains the constants
        for (std::size_t j = 0; j < constraints.cols(); ++j) {
            file << "  " << constraints(i,j)*(-lcm);
        }
        file << "\n";
    }
    file << "end\n";
    file << "project " << cols.size();
    for (const auto i : cols) file << " " << i+1;
    file << "\n";
    file.close();
}

}