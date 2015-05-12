/**
 * Specialization for a converter to a box.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-05-12
 * @version	2015-05-12
 */

#pragma once

namespace hypro {

	template<typename Number>
	class Converter <hypro::Box<Number>, hypro::SupportFunction<Number> > {
		private:
			VariablePool& mPool;

		public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		hypro::Box<Number> convert(const hypro::SupportFunction<Number>& _source) const {
			unsigned dim = _source.dimension();

			matrix_t<Number> directions = matrix_t<Number>::Zero(2*dim,dim);
			for(unsigned i=0; i<dim; ++i) {
				directions(2*i, i) = -1;
				directions(2*i+1, i) = 1;
			}

			vector_t<Number> distances = _source.multiEvaluate(directions);

			typename Box<Number>::intervalMap intervals;
			for(unsigned i=0; i<dim; ++i) {
				intervals.insert(std::make_pair(mPool.carlVarByIndex(i), carl::Interval<Number>(distances(2*i), distances(2*i+1))));
			}

			return Box<Number>(intervals);
		}
	};

	template<typename Number>
	class Converter <hypro::Box<Number>, hypro::VPolytope<Number> > {
		private:
			VariablePool& mPool;

		public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		hypro::Box<Number> convert(const hypro::VPolytope<Number>& _source) const {
			typename VPolytope<Number>::vertexSet vertices = _source.vertices();
			assert(!vertices.empty());
			vector_t<Number> minima = *vertices.begin();
			vector_t<Number> maxima = *vertices.begin();

			for(const auto& vertex : vertices) {
				for(unsigned d=0; d<_source.dimension(); ++d) {
					minima(d) = vertex(d) < minima(d) ? vertex(d) : minima(d);
					maxima(d) = vertex(d) > maxima(d) ? vertex(d) : maxima(d);
					assert(minima(d) <= maxima(d));
				}
			}

			typename Box<Number>::intervalMap intervals;
			for(unsigned i=0; i<_source.dimension(); ++i) {
				intervals.insert(std::make_pair(mPool.carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
			}

			return Box<Number>(intervals);
		}
	};

	template<typename Number>
	class Converter <hypro::Box<Number>, hypro::HPolytope<Number> > {
		private:
			VariablePool& mPool;

		public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		hypro::Box<Number> convert(const hypro::HPolytope<Number>& _source) const {
			typename VPolytope<Number>::vertexSet vertices = _source.vertices();
			assert(!vertices.empty());
			vector_t<Number> minima = *vertices.begin();
			vector_t<Number> maxima = *vertices.begin();

			for(const auto& vertex : vertices) {
				for(unsigned d=0; d<_source.dimension(); ++d) {
					minima(d) = vertex(d) < minima(d) ? vertex(d) : minima(d);
					maxima(d) = vertex(d) > maxima(d) ? vertex(d) : maxima(d);
					assert(minima(d) <= maxima(d));
				}
			}

			typename Box<Number>::intervalMap intervals;
			for(unsigned i=0; i<_source.dimension(); ++i) {
				intervals.insert(std::make_pair(mPool.carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
			}

			return Box<Number>(intervals);
		}
	};

	template<typename Number>
	class Converter <hypro::Box<Number>, hypro::Zonotope<Number> > {
		private:
			VariablePool& mPool;

		public:
		Converter() : mPool(hypro::VariablePool::getInstance()){
		}
		~Converter(){}

		hypro::Box<Number> convert(const hypro::Zonotope<Number>& _source) const {
			std::vector<vector_t<Number>> vertices = _source.computeZonotopeBoundary();
			assert(!vertices.empty());
			vector_t<Number> minima = vertices[0];
			vector_t<Number> maxima = vertices[0];

			for(unsigned i=0; i<vertices.size(); ++i) {
				for(unsigned d=0; d<_source.dimension(); ++d) {
					minima(d) = vertices[i](d) < minima(d) ? vertices[i](d) : minima(d);
					maxima(d) = vertices[i](d) > maxima(d) ? vertices[i](d) : maxima(d);
					assert(minima(d) <= maxima(d));
				}
			}

			typename Box<Number>::intervalMap intervals;
			for(unsigned i=0; i<_source.dimension(); ++i) {
				intervals.insert(std::make_pair(mPool.carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
			}

			return Box<Number>(intervals);
		}
	};


} //namespace