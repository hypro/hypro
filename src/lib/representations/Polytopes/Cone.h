/**
 * 
 */
 
#pragma once

namespace hypro {
namespace polytope {
	
	template<typename Number>
	class Cone 
	{
		public:
			typedef std::vector<std::shared_ptr<Hyperplane<Number>> > planeVector;
		private:
			planeVector     mPlanes;

		public:
			Cone();
			Cone(const Cone& _orig);
			Cone(const planeVector& _planes);			
			~Cone();

			/*
			 * Getters & setters
			 */
			
			const typename Cone<Number>::planeVector& planes() const;
			vectorSet<Number> vectors() const;
			unsigned dimension() const;			
			unsigned size() const;
			
			void add(std::shared_ptr<Hyperplane<Number>> _plane);
			void add(vector_t<Number> _vector);

			Cone<Number> linearTransformation(const matrix_t<Number> A) const;
			Cone<Number> minkowskiSum(const Cone& _rhs) const;			
			Point<Number> getUnitAverageVector() const;
			
			bool contains(const vector_t<Number>& _vector) const;
			bool contains(const vector_t<Number>& _vector, planeVector& _insidePlanes, planeVector& _outsidePlanes) const;
			bool contains(const Point<Number>* _vector) const;
			
			Cone<Number> operator=(const Cone<Number>& _rhs);
	};
} // namespace polytope
} // namespace hypro

#include "Cone.tpp"