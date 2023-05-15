/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 */

#pragma once

#include "../../datastructures/Halfspace.h"

#include <memory>
#include <vector>

namespace hypro {

    template<typename Number>
    using vectorSet = std::set<vector_t<Number>>;

    template<typename Number>
    bool operator<(std::shared_ptr<Halfspace<Number>> _lhs, std::shared_ptr<Halfspace<Number>> _rhs) {
        return (*_lhs.get() < *_rhs.get());
    }

    template<typename Number>
    class Cone {
    public:
        using planeVector = std::vector<std::shared_ptr<Halfspace<Number>>>;

    private:
        planeVector mPlanes;

    public:
        Cone();

        Cone(const Cone &_orig);

        Cone(const planeVector &_planes);

        ~Cone();

        /*
         * Getters & setters
         */

        const typename Cone<Number>::planeVector &planes() const;

        vectorSet<Number> vectors() const;

        unsigned dimension() const;

        unsigned size() const;

        void add(std::shared_ptr<Halfspace<Number>> _plane);

        void add(vector_t<Number> _vector);

        Cone<Number> linearTransformation(const matrix_t<Number> A) const;

        Cone<Number> affineTransformation(const matrix_t<Number> A, const vector_t<Number> &b) const;

        Cone<Number> minkowskiSum(const Cone &_rhs) const;

        Point<Number> getUnitAverageVector() const;

        bool contains(const vector_t<Number> &_vector) const;

        bool contains(const vector_t<Number> &_vector, planeVector &_insidePlanes,
                      std::set<std::shared_ptr<Halfspace<Number>>> &_outsidePlanes) const;

        bool contains(const Point<Number> *_vector) const;

        Cone<Number> operator=(const Cone<Number> &_rhs);
    };

    template<typename Number>
    std::ostream &operator<<(std::ostream &_out, Cone<Number> &_cone) {
        _out << "Cone [ " << std::endl;
        for (const auto &plane: _cone.planes()) {
            _out << *plane << ", " << std::endl;
        }
        _out << " ]" << std::endl;
        return _out;
    }

}  // namespace hypro

#include "Cone.tpp"
