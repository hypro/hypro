/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "Cone.h"

#include <cassert>

namespace hypro {

/**
 * @brief      Class for a polytopal fan.
 *
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    class Fan {
    public:
        using cones = std::vector<const Cone<Number> *>;

    private:
        cones mCones;
        unsigned mDimension;

    public:
        Fan()
                : mCones(), mDimension() {}

        ~Fan() { mCones.clear(); }

        Fan(const Fan &_orig)
                : mCones(_orig.get()), mDimension(_orig.dimension()) {}

        /*
         * Getters & setters
         */

        const cones &get() const { return mCones; }

        const Cone<Number> *get(unsigned _index) const {
            assert(_index < mCones.size());
            return mCones.at(_index);
        }

        unsigned dimension() const { return mDimension; }

        unsigned size() const { return mCones.size(); }

        void add(const Cone<Number> *_cone) {
            mCones.push_back(_cone);
            mDimension = mDimension < _cone->dimension() ? _cone->dimension() : mDimension;
        }

        const Cone<Number> *containingCone(const Point<Number> &_vector) const {
            Optimizer<Number> opt{};

            // set up glpk
            glp_prob *cones;
            cones = glp_create_prob();
            glp_set_obj_dir(cones, GLP_MAX);

            typename Cone<Number>::vectors vectors;
            for (auto &cone: mCones) {
                vectors.insert(vectors.end(), cone.begin(), cone.end());
            }
            unsigned numPlanes = vectors.size();
            // unsigned elements = this->mDimension * numPlanes;

            matrix_t<Number> constraints = matrix_t<Number>::Zero(this->mDimension, numPlanes);

            for (unsigned i = 1; i <= this->mDimension; ++i) {
                for (unsigned j = 1; j <= numPlanes; ++j) {
                    constraints(i, j) = vectors.at(j).at(i);
                }
            }

            opt.checkConsistency();
            // TODO: output and stuff.
        }

        Fan<Number> operator=(const Fan<Number> &_rhs) {
            /* if( this != &rhs )
             {
                 Fan<Number> tmp(rhs);
                 std::swap(*this,tmp);
             }
             return *this;
             */
            this->mCones = _rhs.get();
            this->mDimension = _rhs.dimension();
            return *this;
        }
    };

}  // namespace hypro
