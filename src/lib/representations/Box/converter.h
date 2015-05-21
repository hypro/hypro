/**
 * Specialization for a converter to a box.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-05-12
 * @version	2015-05-13
 */

#pragma once

namespace hypro {

	template<typename Number>
	bool convert(const hypro::Box<Number>& _source, hypro::Box<Number>& _target){
		_target = _source;
		return true;
	}
	
	template<typename Number>
	bool convert(std::shared_ptr<hypro::SupportFunction<Number>> _source, hypro::Box<Number>& _target){
		unsigned dim = _source->dimension();

		matrix_t<Number> directions = matrix_t<Number>::Zero(2*dim,dim);
		for(unsigned i=0; i<dim; ++i) {
			directions(2*i, i) = -1;
			directions(2*i+1, i) = 1;
		}

		vector_t<Number> distances = _source->multiEvaluate(directions);

		typename Box<Number>::intervalMap intervals;
		for(unsigned i=0; i<dim; ++i) {
			intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), carl::Interval<Number>(distances(2*i), distances(2*i+1))));
		}

		_target = Box<Number>(intervals);

		return false; // Todo: if precise, return true
	}

	template<typename Number>
	bool convert(const hypro::VPolytope<Number>& _source, hypro::Box<Number>& _target) {
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
			intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
		}

		_target = Box<Number>(intervals);
		return false;
	}

	template<typename Number>
	bool convert(const hypro::HPolytope<Number>& _source, hypro::Box<Number>& _target) {
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
			intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
		}

		_target = Box<Number>(intervals);

		return false; // Todo: if precise, return true
	}

	template<typename Number>
	bool convert(const hypro::Zonotope<Number>& _source, hypro::Box<Number>& _target) {
		Zonotope<Number> tmp = _source.intervalHull();
		std::vector<vector_t<Number>> vertices = tmp.computeZonotopeBoundary();
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
			intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
		}

		_target = Box<Number>(intervals);

		return false; // Todo: if precise, return true
	}

	template<typename Number>
	bool convert(const hypro::Polytope<Number>& _source, hypro::Box<Number>& _target) {
		hypro::Polytope<Number> tmp = _source;
		std::vector<Point<Number>> points = tmp.points();
		assert(!points.empty());

		vector_t<Number> minima = points[0].rawCoordinates();
		vector_t<Number> maxima = points[0].rawCoordinates();

		for(unsigned i=0; i<points.size(); ++i) {
			for(unsigned d=0; d<_source.dimension(); ++d) {
				minima(d) = points[i].rawCoordinates()(d) < minima(d) ? points[i].rawCoordinates()(d) : minima(d);
				maxima(d) = points[i].rawCoordinates()(d) > maxima(d) ? points[i].rawCoordinates()(d) : maxima(d);
				assert(minima(d) <= maxima(d));
			}
		}

		typename Box<Number>::intervalMap intervals;
		for(unsigned i=0; i<_source.dimension(); ++i) {
			intervals.insert(std::make_pair(hypro::VariablePool::getInstance().carlVarByIndex(i), carl::Interval<Number>(minima(i), maxima(i))));
		}

		_target = Box<Number>(intervals);

		return false; // Todo: if precise, return true
	}
	
} //namespace