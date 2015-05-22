/**
 * Implementation of cones.
 */

namespace hypro {
namespace polytope {

	template<typename Number>
	Cone<Number>::Cone() :
	mPlanes()
	{}

	template<typename Number>
	Cone<Number>::Cone(const Cone& _orig) :
	mPlanes(_orig.planes())
	{}

	template<typename Number>
	Cone<Number>::Cone(const planeVector& _planes) :
	mPlanes(_planes)
	{}
	
	template<typename Number>
	Cone<Number>::~Cone()
	{}
	
	template<typename Number>
	const typename Cone<Number>::planeVector& Cone<Number>::planes() const {
		return mPlanes;
	}

	template<typename Number>
	vectorSet<Number> Cone<Number>::vectors() const {
		// create all possible vectors
		vectorSet<Number> intersectionVectors;
		for(const auto& lhsPlane : mPlanes) {
			for(const auto& rhsPlane : mPlanes) {
				if(lhsPlane != rhsPlane) {
					intersectionVectors.insert(lhsPlane.get()->intersectionVector(*rhsPlane.get()));
				}
			}
		}
		// for each vector, determine, if it is inside the original cone
		for(const auto& vector : intersectionVectors) {
			if(!this->contains(vector))
				intersectionVectors.erase(vector);
		}
		return intersectionVectors;
	}

	template<typename Number>
	unsigned Cone<Number>::dimension() const {
		if(!mPlanes.empty())
			return mPlanes[0]->dimension();

		return 0;
	}
	
	template<typename Number>
	unsigned Cone<Number>::size() const {
		return mPlanes.size();
	}
	
	template<typename Number>
	void Cone<Number>::add(std::shared_ptr<Hyperplane<Number>> _plane) {
		// TODO
	}

	template<typename Number>
	void Cone<Number>::add(vector_t<Number> _vector) {
		
		// collect all vectors (v_l, v_r) from both cones (cone_l, cone_r)
		vectorSet<Number> lhsVectors = this->vectors();

		// check if vector is already inside cone_l -> drop
		planeVector insidePlanes;
		planeVector outsidePlanes;
		if(!this->contains(_vector,insidePlanes, outsidePlanes)) { // not inside
			assert(!insidePlanes.empty());

			// get horizon vectors, create new hyperplanes, delete inside planes.
			std::vector<vector_t<Number>> horizonVectors;
			for(const auto& horizonCandidate : lhsVectors) {
				bool found = false;
				for(const auto& insidePlane : insidePlanes) {
					if(insidePlane->contains(horizonCandidate)) {
						// check all other planes, which are not inside, if the candidate is part of one -> horizon vector
						for(const auto& outsidePlane : outsidePlanes) {
							if(outsidePlane->contains(horizonCandidate)) {
								horizonVectors.push_back(horizonCandidate);
								found = true;
								break;
							}
						}
					}
					if(found)
						break;
				}
				found = false;
			}

			// create new hyperplanes
			std::vector<vector_t<Number>> hyperplaneBasis;
			hyperplaneBasis.push_back(_vector);
			for(const auto& horizonVector : horizonVectors) {
				// Todo: check if origin zero is okay.
				vector_t<Number> origin = vector_t<Number>::Zero(_vector.rows());
				
				hyperplaneBasis.push_back(horizonVector);
				outsidePlanes.push_back(std::shared_ptr<Hyperplane<Number>>(new Hyperplane<Number>(origin, hyperplaneBasis)));
				hyperplaneBasis.pop_back();
			}

			// assign new planes
			mPlanes.clear();
			for(const auto& plane : outsidePlanes)
				mPlanes.push_back(plane);
		}
	}

	template<typename Number>
	Cone<Number> Cone<Number>::linearTransformation(const matrix_t<Number> A) const {
		Cone<Number> result;
		for(const auto& plane : mPlanes) {
			result.add(std::shared_ptr<Hyperplane<Number>>(new Hyperplane<Number>(plane->linearTransformation(A))));
		}
		return result;
	}

	template<typename Number>
	Cone<Number> Cone<Number>::minkowskiSum(const Cone& _rhs) const {
		Cone<Number> result = Cone<Number>(*this);
		vectorSet<Number> rhsVectors = _rhs.vectors();
		for(const auto& vector : rhsVectors)
			result.add(vector);

		return result;
	}

	template<typename Number>
	Point<Number> Cone<Number>::getUnitAverageVector() const {
		assert(!mPlanes.empty());
		Point<Number> result;
		unsigned numberPlanes = mPlanes.size();
		for(auto& plane : mPlanes)
		{
			result += (plane->normal()/numberPlanes);
		}
		return result;
	}
	
	template<typename Number>
	bool Cone<Number>::contains(const vector_t<Number>& _vector) const {
		for(const auto& plane : mPlanes) {
			if(_vector.dot(plane->normal()) > 0)
				return false;
		}
		return true;
	}

	template<typename Number>
	bool Cone<Number>::contains(const vector_t<Number>& _vector, planeVector& _insidePlanes, planeVector& _outsidePlanes) const {
		bool contains = true;
		for(const auto& plane : mPlanes) {
			if(_vector.dot(plane->normal()) > 0) {
				_insidePlanes.push_back(plane);
				contains = false;
			} else {
				_outsidePlanes.push_back(plane);
			}
		}
		return contains;
	}

	template<typename Number>
	bool Cone<Number>::contains(const Point<Number>* _vector) const {
		return this->contains(_vector->rawCoordinates());
	}
	
	template<typename Number>
	Cone<Number> Cone<Number>::operator=(const Cone<Number>& _rhs) {
		/*
		if( this != &_rhs )
		{
			Cone<Number> tmp(_rhs);
			std::swap(*this,tmp);
		}*/
		mPlanes.clear();
		mPlanes = _rhs.planes();
		return *this;
	}
	
} // namespace polytope
} // namespace hypro