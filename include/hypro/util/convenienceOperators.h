/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../types.h"

#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace hypro {

/// enum-to-int conversion
    template<typename Enumeration>
    auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type {
        return static_cast<typename std::underlying_type<Enumeration>::type>( value );
    }

/// enum outstream operator
    template<typename Enumeration, carl::EnableIf<std::is_enum<Enumeration>> = carl::dummy>
    std::ostream &operator<<(std::ostream &out, Enumeration in) {
        out << as_integer(in);
        return out;
    }

/// set-outstream operator (element-wise)
    template<typename T>
    std::ostream &operator<<(std::ostream &_out, const std::set<T> &_set) {
        if (!_set.empty()) {
            _out << "{ " << *_set.begin();
            for (auto setIt = ++_set.begin(); setIt != _set.end(); ++setIt) {
                _out << ", " << *setIt;
            }
            _out << " }";
        }

        return _out;
    }

/// vector-outstream operator (element-wise)
    template<typename T>
    std::ostream &operator<<(std::ostream &_out, const std::vector<T> &_vector) {
        if (!_vector.empty()) {
            _out << "( " << *_vector.begin();
            for (auto vectorIt = ++_vector.begin(); vectorIt != _vector.end(); ++vectorIt) {
                _out << ", " << *vectorIt;
            }
            _out << " )";
        }

        return _out;
    }

/// pair-outstream operator (element-wise)
    template<typename T>
    std::ostream &operator<<(std::ostream &_out, const std::pair<T, T> &_pair) {
        _out << _pair.first << ", " << _pair.second;

        return _out;
    }

/// map-outstream operator (element-wise)
    template<typename Key, typename T>
    std::ostream &operator<<(std::ostream &_out, const std::map<Key, T> &_map) {
        if (!_map.empty()) {
            _out << _map.begin()->first << " -> " << _map.begin()->second;
            for (auto mapIt = ++_map.begin(); mapIt != _map.end(); ++mapIt) {
                _out << ", " << mapIt->first << " -> " << mapIt->second;
            }
        }

        return _out;
    }

/// outstream operator for a row of a matrix, passed as a row-vector. Only prints non-zero values.
    template<typename N>
    std::string to_string(const typename matrix_t<N>::ConstRowXpr &row, bool lastIsConst = true) {
        std::stringstream _out;
        bool first = true;
        for (Eigen::Index col = 0; col < row.cols() - 1; ++col) {
            if (row(col) > 0) {
                if (!first) {
                    _out << " + ";
                } else {
                    first = false;
                }
                if (row(col) != N(1)) {
                    _out << row(col) << "·x" << col;
                } else {
                    _out << "x" << col;
                }
            } else if (row(col) < 0) {
                if (first) {
                    first = false;
                }
                _out << " - ";
                if (row(col) != N(-1)) {
                    _out << -row(col) << "·x" << col;
                } else {
                    _out << "x" << col;
                }
            }
        }
        if (lastIsConst) {
            if (row(row.cols() - 1) > 0) {
                if (!first) {
                    _out << " + ";
                }
                _out << row(row.cols() - 1);
            } else if (row(row.cols() - 1) < 0) {
                _out << " - " << -row(row.cols() - 1);
            }
        } else {
            if (row(row.cols() - 1) > 0) {
                if (!first) {
                    _out << " + ";
                }
                _out << row(row.cols() - 1) << "·x" << row.cols() - 1;
            } else if (row(row.cols() - 1) < 0) {
                _out << " - " << -row(row.cols() - 1) << "·x" << row.cols() - 1;;
            }
        }
        return _out.str();
    }

/// outstream operator for matrices which adds variables and only outputs non-zero entries.
    template<typename N>
    std::string to_string(const matrix_t<N> &mat) {
        std::stringstream _out;
        if (mat.rows() > 0) {
            for (Eigen::Index row = 0; row < mat.rows(); ++row) {
                _out << mat.row(row);
            }
        }
        return _out.str();
    }

/// tostring method for tribools
    std::string to_string(const hypro::TRIBOOL in);

/// default case typename to string
    template<typename T>
    struct typeName {
        std::string get() {
            return "unknown";
        }
    };

/// typename to string: double
    template<>
    struct typeName<double> {
        std::string get() {
            return "double";
        }
    };

/// typename to string: mpq_class
    template<>
    struct typeName<mpq_class> {
        std::string get() {
            return "mpq_class";
        }
    };

}  // namespace hypro
