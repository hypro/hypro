/**
 * The class which represents a hyperplane.
 *
 * @file Hyperplane.h
 * @author jongan
 *
 * @since   2014-08-29 3:53 PM
 * @version
 */

#pragma once
#include <Eigen/Dense>
#include <glpk.h>
#include "../../config.h"
#include "../../datastructures/Point.h"

namespace hypro {

template<typename Number>
class Hyperplane
{
    private:
        vector_t<Number>        mNormal;
        Number   mScalar;
        unsigned                mDimension;
        
        public:
			Hyperplane() :
			mNormal(),
			mScalar(),
			mDimension()
			{}
			~Hyperplane()
			{}
			Hyperplane(const Hyperplane<Number>& _orig) :
			mNormal(_orig.mNormal),
			mScalar(_orig.mScalar),
			mDimension(_orig.mDimension)
			{}
			Hyperplane(const Point<Number>& _vector, const Number& _off);
			Hyperplane(std::initializer_list<Number> _coordinates, const Number& _off);
			Hyperplane(const vector_t<Number>& _vector, const Number& _off) :
			mNormal(_vector),
			mScalar(_off),
			mDimension(_vector.rows())
			{}
			Hyperplane(const vector_t<Number>& _vec, const std::vector<vector_t<Number>>& _vectorSet);

			unsigned dimension() const;
			vector_t<Number> normal() const;
			void setNormal(const vector_t<Number>& _normal);
			Number offset() const;
			void setOffset(Number _offset);
			Number signedDistance(const vector_t<Number>& _point) const;
			bool intersection(Number& _result, const vector_t<Number>& _vector) const;
			bool intersection(Number& _result, const Point<Number>& _vector) const;
        private:
            const Number& internalOffset() const;

           /**
            * @author: Chris K
            * Method to compute the normal of a plane based on two direction vectors
            * simply computing the cross product does not work since the dimension is not necessarily 3
            */
            vector_t<Number> computePlaneNormal(const std::vector<vector_t<Number>>& _edgeSet);
        
			/*
			 * Changes the dimension of this hyperplane to a new one
			 * @param newDimension The new dimension the hyperplane's gonna get
			 */
			bool changeDimension(unsigned int newDimension);
};
}

#include "Hyperplane.tpp"


