#pragma once

#include <vector>
#include <cassert>

#include "Matrix.h"
#include "Node.h"

namespace smtrat::fmplex {

// TODO: equality substitution
template<typename Number>
class FMplexElimination {
    using MatrixT = Matrix<Number>;
    using NodeT   = Node<Number>;
    using RowIndex = typename MatrixT::RowIndex;
    using ColIndex = typename MatrixT::ColIndex;
    using RowEntry = typename MatrixT::RowEntry;
    using Row      = std::vector<RowEntry>;

    struct cmp_row {
        bool operator()(const Row& a, const Row& b) const { // TODO: this does not filter out duplicates with different lin. combs.!
            auto it_a = a.begin(), it_b = b.begin();
            auto end_a = a.end(), end_b = b.end();
            while (it_a != end_a && it_b != end_b) {
                if (it_a->col_index != it_b->col_index) 
                    return it_a->col_index < it_b->col_index;
                if (it_a->value != it_b->value)
                    return it_a->value < it_b->value;
                ++it_a;
                ++it_b;
            }
            return (it_b != end_b); // at this point: a < b only if a is at end and b is not
        }
    };


private:
    std::vector<NodeT> m_nodes;
    ColIndex                m_first_parameter_col;
    ColIndex                m_constant_col;
    ColIndex                m_total_cols;
    std::set<Row, cmp_row>  m_found_rows;

public:
    FMplexElimination(const MatrixT& m, std::size_t n_quantified, std::size_t n_parameters) {
        m_first_parameter_col = n_quantified;
        m_constant_col = n_quantified + n_parameters;

        // filter finished rows from m
        MatrixT filtered(m.n_rows(), m.n_cols());
        for (typename MatrixT::RowIndex i = 0; i < m.n_rows(); ++i) {
            if (m.row_begin(i)->col_index >= m_first_parameter_col) {
                Row r;
                for (const auto& e : m.row_entries(i)) {
                    if (e.col_index > delta_column()) break;
                    r.push_back(e);
                }
                m_found_rows.insert(r);
            } else {
                filtered.append_row(m.row_begin(i), m.row_end(i));
            }
        }

        m_total_cols  = m.n_cols(); //m_constant_col + filtered.n_rows();

        // store initial Node
        std::vector<typename MatrixT::ColIndex> cols_to_elim;
        for (ColIndex j = 0; j < n_quantified; ++j) cols_to_elim.push_back(j);
        m_nodes.emplace_back(filtered, cols_to_elim);
    }


    MatrixT apply() {
        while (!m_nodes.empty()) {
            switch (m_nodes.back().type) {
            case NodeT::Type::CONFLICT:
                return trivial_unsat_matrix();
            case NodeT::Type::UNDETERMINED: {
                auto split = split_into_independent_nodes(m_nodes.back());
                m_nodes.pop_back();
                m_nodes.insert(m_nodes.end(), split.begin(), split.end());
                break;
            }
            case NodeT::Type::NBS:
                m_nodes.back() = unbounded_elimination(m_nodes.back());
                break;
            case NodeT::Type::LBS:[[fallthrough]];
            case NodeT::Type::UBS:
                if (m_nodes.back().is_finished()) m_nodes.pop_back();
                else m_nodes.push_back(bounded_elimination(m_nodes.back()));
                break;
            case NodeT::Type::FM:
                if (!fm_elimination(m_nodes.back())) return trivial_unsat_matrix();
                m_nodes.pop_back();
                break;
            case NodeT::Type::LEAF:
                m_nodes.pop_back();
                break;
            }
        }

        MatrixT result(m_found_rows.size(), m_total_cols);
        for (const auto& r : m_found_rows) {
            result.append_row(r.begin(), r.end());
        }
        
        return result;
    }


private:
    ColIndex constant_column()             const { return m_constant_col; }
    ColIndex delta_column   ()             const { return m_constant_col + 1; }
    ColIndex origin_column  (RowIndex row) const { return delta_column() + 1 + row; }

    bool is_trivial(const Row& row) const {
        assert(!row.empty());
        return row.begin()->col_index >= constant_column();
    }

    bool is_conflict(const Row& row) const {
        assert(!row.empty());
        assert(is_trivial(row));
        const auto& e = row.front();
        return (e.col_index <= delta_column()) && (e.value > 0);
    }

    bool is_positive_combination(const Row& row) const {
        assert(row.front().col_index <= delta_column());
        // don't need to check for it == end because the constraint cannot be trivially true here
        for (auto it = row.rbegin(); it->col_index > delta_column(); ++it) {
            if (it->value < 0) return false;
        }
        return true;
    }

    bool is_global_conflict(const Row& row) const {
        return is_trivial(row) && is_conflict(row) && is_positive_combination(row);
    }

    void collect_constraint(const Row& row) {
        Row truncated = row;
        for (std::size_t i = 0; ; ++i) {
            if (truncated[i].col_index > delta_column()) {
                truncated.resize(i);
                break;
            }
        }
        m_found_rows.insert(truncated);
    }

    std::vector<NodeT> split_into_independent_nodes(const NodeT& n) const;

    NodeT unbounded_elimination(NodeT& parent);
    NodeT bounded_elimination  (NodeT& parent);
    bool fm_elimination       (NodeT& parent);

    MatrixT trivial_unsat_matrix() const {
        MatrixT result = MatrixT(1, m_total_cols);
        std::vector<RowEntry> unsat_row = { RowEntry(constant_column(), Number(1)) };
        result.append_row(unsat_row.begin(), unsat_row.end());
        return result;
    }
};

}

#include "fmplex.tpp"