/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file   representations/SupportFunction/util.h
 */

//#define HYPRO_USE_VECTOR_CACHING

#pragma once

#include "../../config.h"
#include "../../types.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"

#ifdef HYPRO_USE_VECTOR_CACHING
#include "../../datastructures/LRUCache.h"
#endif

namespace hypro {
/**
 * This enum represents the support function type and is used to identify support function instances without instanceof operations.
 */
    enum SF_TYPE {
        SUM,
        INTERSECT,
        LINTRAFO,
        SCALE,
        UNITE,
        POLY,
        INFTY_BALL,
        TWO_BALL,
        ELLIPSOID,
        BOX,
        ZONOTOPE,
        PROJECTION,
        NONE
    };

    template<typename Content>
    struct Cacheable {
        mutable std::size_t mHash = 0;
        std::pair<unsigned, Content> item;

        std::size_t hash() const {
            if (mHash == 0) {
                mHash = std::hash<std::pair<unsigned, Content>>()(item);
            }
            return mHash;
        }

        explicit Cacheable(const std::pair<unsigned, Content> &i)
                : item(i) {}

        Cacheable(unsigned exp, const Content &cont)
                : item(std::make_pair(exp, cont)) {}

        friend bool operator==(const Cacheable<Content> &lhs, const Cacheable<Content> &rhs) {
            if (lhs.hash() != rhs.hash()) {
                return false;
            }
            return (lhs.item.first == rhs.item.first) && (lhs.item.second == rhs.item.second);
        }
    };

}  // namespace hypro

namespace std {
    template<typename Content>
    struct hash<hypro::Cacheable<Content>> {
        std::size_t operator()(hypro::Cacheable<Content> const &item) const {
            return item.hash();
        }
    };
}  // namespace std

namespace hypro {

/**
 * @brief      Struct holding linear and affine transformation parameters.
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    struct lintrafoParameters {
        mutable std::map<unsigned, std::pair<matrix_t<Number>, vector_t<Number>>> parameters;
#ifdef HYPRO_USE_VECTOR_CACHING
        mutable LRUCache<Cacheable<vector_t<Number>>, vector_t<Number>> mVectorCache;
        mutable LRUCache<Cacheable<matrix_t<Number>>, matrix_t<Number>> mMatrixCache;
#endif
        unsigned power = 2;     // 2^power operations are collected
        mutable std::size_t mHash = 0;

        lintrafoParameters() = delete;

        lintrafoParameters(const matrix_t<Number> &_A, const vector_t<Number> &_b, unsigned _power = 2)
                :
#ifdef HYPRO_USE_VECTOR_CACHING
                mVectorCache( SF_CACHE_SIZE )
                , mMatrixCache( SF_CACHE_SIZE )
                ,
#endif
                power(_power) {
            // TRACE("hypro.representations.supportFunction", "Created new lintrafo object." << " (@" << this << ")");
            assert(_A.rows() == _b.rows());
            parameters[1] = std::make_pair(_A, _b);
        }

        ~lintrafoParameters() {
            // TRACE("hypro.representations.supportFunction", "Delete lintrafo object." << " (@" << this << ")");
        }

        const matrix_t<Number> &matrix() const {
            assert(parameters.begin()->first == 1);
            return parameters.begin()->second.first;
        }

        const vector_t<Number> &vector() const {
            assert(parameters.begin()->first == 1);
            return parameters.begin()->second.second;
        }

        std::size_t hash() const {
            if (mHash == 0) {
                // std::hash<hypro::vector_t<Number>> vectorHasher;
                // std::hash<hypro::matrix_t<Number>> matrixHasher;
                mHash = std::hash<hypro::vector_t<Number>>()(this->parameters.begin()->second.second);
                carl::hash_add(mHash, std::hash<hypro::matrix_t<Number>>()(this->parameters.begin()->second.first));
            }
            return mHash;
        }

        const std::pair<matrix_t<Number>, vector_t<Number>> &getParameterSet(unsigned exponent) const {
            // std::cout << this << " Request parameter set for exponent " << exponent << std::endl;
            if (parameters.find(exponent) != parameters.end()) {
                return parameters.at(exponent);
            }
            // create new parameters
            while ((--parameters.end())->first < exponent) {
                createNextReduct();
            }
            assert(parameters.find(exponent) != parameters.end());
            return parameters.at(exponent);
        };

        vector_t<Number> getTransformedDirection(const vector_t<Number> &inDirection, unsigned exponent) const {
#ifdef HYPRO_USE_VECTOR_CACHING
            // TRACE("hypro.representations.supportFunction","Attempt to access cache." << " (@" << this << ")");
            auto cachePos = mVectorCache.get( Cacheable<vector_t<Number>>( exponent, inDirection ) );
            if ( cachePos == mVectorCache.end() ) {
                // TRACE("hypro.representations.supportFunction","Insert item into cache." << " (@" << this << ")");
                vector_t<Number> tmp = getParameterSet( exponent ).first.transpose() * inDirection;
                auto pos = mVectorCache.insert( Cacheable<vector_t<Number>>( exponent, inDirection ), tmp );
                assert( ( *pos ).second.rows() == inDirection.rows() );
                return ( *pos ).second;
            }
            assert( ( *cachePos ).second.rows() == inDirection.rows() );
            return ( *cachePos ).second;
#else
            matrix_t<Number> tmp = getParameterSet(exponent).first.transpose();
            return tmp * inDirection;
#endif
        }

        matrix_t<Number> getTransformedDirections(const matrix_t<Number> &inDirections, unsigned exponent) const {
#ifdef HYPRO_USE_VECTOR_CACHING
            // std::cout << __func__ << " attempt to access cache ";
            auto cachePos = mMatrixCache.get( Cacheable<matrix_t<Number>>( exponent, inDirections ) );
            // std::cout << "done." << std::endl;
            if ( cachePos == mMatrixCache.end() ) {
                // std::cout << __func__ << " insert item into cache." << std::endl;
                auto pos = mMatrixCache.insert( Cacheable<matrix_t<Number>>( exponent, inDirections ), inDirections * getParameterSet( exponent ).first );
                return ( *pos ).second;
            }
            return ( *cachePos ).second;
#else
            return inDirections * getParameterSet(exponent).first;
#endif
        }

        void createNextReduct() const {
            // the last created reduction pair is at the back, as a std::map is per default sorted ascending
            assert(parameters.size() > 0);
            unsigned powerOfTwo = carl::pow(2, power);
            // first compute the new b
            vector_t<Number> bTrans = (--parameters.end())->second.second;
            matrix_t<Number> aTrans = (--parameters.end())->second.first;
            // std::cout << "Starting from exponent " << (--matrices.end())->first << std::endl;
            unsigned exponent = ((--parameters.end())->first) * powerOfTwo;
            // std::cout << "New exponent: " << exponent << std::endl;
            //  accumulate b
            for (std::size_t i = 1; i < powerOfTwo; i++) {
                // Note: aTrans hasn't changed yet -> we can use it for transformation.
                bTrans = aTrans * bTrans + (--parameters.end())->second.second;
            }
            // accumulate A
            for (std::size_t i = 0; i < power; i++) {
                aTrans = aTrans * aTrans;
            }
            parameters[exponent] = std::make_pair(aTrans, bTrans);
        }

        bool operator==(const lintrafoParameters<Number> &rhs) const {
            // return (this->parameters.begin()->second == rhs.parameters.begin()->second);
            if (this->hash() != rhs.hash()) {
                return false;
            }
            return (this->parameters.begin()->second == rhs.parameters.begin()->second);
        }
    };

}  // namespace hypro
