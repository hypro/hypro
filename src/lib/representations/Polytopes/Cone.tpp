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
		// adjust vectors to the right direction
		for(const auto& plane : mPlanes) {
			for(auto& vector : intersectionVectors) {
				if(!plane->holds(vector)) {
					vector_t<Number> tmp = vector*-1;
					intersectionVectors.erase(vector);
					intersectionVectors.insert(tmp);

					std::cout << tmp << " is contained in " << *plane << " : " << plane->holds(tmp) << std::endl;
					assert(plane->holds(tmp));
				}
			}
		}

		std::cout << "Collected vectors: " << std::endl;
		for(const auto& vec : intersectionVectors) {
			std::cout << vec << ", " << std::endl;
		}
		std::cout << "######" << std::endl;

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
		mPlanes.push_back(_plane);
	}

	template<typename Number>
	void Cone<Number>::add(vector_t<Number> _vector) {
		// collect all vectors
		vectorSet<Number> lhsVectors = this->vectors();

		for(const auto& vector : lhsVectors){
			std::cout << "lhsVector: " << vector << std::endl;
		}

		// check if vector is already inside cone_l -> drop
		planeVector insidePlanes;
		std::set<std::shared_ptr<Hyperplane<Number>>> outsidePlanes;
		if(!this->contains(_vector,insidePlanes, outsidePlanes)) { // not inside
			std::cout << "vector is not inside." << std::endl;
			assert(!insidePlanes.empty());

			// get horizon vectors, create new hyperplanes, delete inside planes.
			std::vector<vector_t<Number>> horizonVectors;
			for(const auto& horizonCandidate : lhsVectors) {
				bool found = false;
				for(const auto& insidePlane : insidePlanes) {
					std::cout << "Inside plane: " << *insidePlane.get() << std::endl;
					if(insidePlane->contains(horizonCandidate)) {
						std::cout << "is contained (normal*horizonCandidate=" << insidePlane.get()->normal().dot(horizonCandidate) << ")" << std::endl;
						// check all other planes, which are not inside, if the candidate is part of one -> horizon vector
						for(const auto& outsidePlane : outsidePlanes) {
							std::cout << "Consider vector " << horizonCandidate << " to be inside " << *insidePlane.get() << " and " << *outsidePlane.get() << std::endl;
							if(outsidePlane->contains(horizonCandidate)) {
								horizonVectors.push_back(horizonCandidate);
								std::cout << "horizon vector: " << horizonCandidate << std::endl;
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

			std::cout << "Create new hyperplanes." << std::endl;
			// create new hyperplanes
			std::vector<vector_t<Number>> hyperplaneBasis;
			hyperplaneBasis.push_back(_vector);
			for(const auto& horizonVector : horizonVectors) {
				// Todo: check if origin zero is okay.
				vector_t<Number> origin = vector_t<Number>::Zero(_vector.rows());
				
				std::cout << "Create hyperplane from " << _vector << " and " << horizonVector << std::endl;

				hyperplaneBasis.push_back(horizonVector);
				outsidePlanes.insert(std::shared_ptr<Hyperplane<Number>>(new Hyperplane<Number>(origin, hyperplaneBasis)));
				//std::cout << "new plane: " << *outsidePlanes.back().get() << std::endl;
				hyperplaneBasis.pop_back();
			}

			for(const auto& plane : outsidePlanes)
				std::cout << "Outside Plane: " << *plane.get() << std::endl;

			// assign new planes
			mPlanes.clear();
			std::cout << "Set up new object." << std::endl;
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
			if(!plane->holds(_vector))
				return false;
		}
		return true;
	}

	template<typename Number>
	bool Cone<Number>::contains(const vector_t<Number>& _vector, planeVector& _insidePlanes, std::set<std::shared_ptr<Hyperplane<Number>>>& _outsidePlanes) const {
		bool contains = true;
		for(const auto& plane : mPlanes) {
			if(!plane->holds(_vector)) {
				_insidePlanes.push_back(plane);
				contains = false;
			} else {
				_outsidePlanes.insert(plane);
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