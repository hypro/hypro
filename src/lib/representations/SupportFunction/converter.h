/**
 * Specialization for a converter to a support function.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-05-13
 * @version	2015-05-13
 */

#pragma once

namespace hypro {

	template<typename Number>
	bool convert(const hypro::Box<Number>& _source, SupportFunction<Number>& _target){
		unsigned dim = _source.dimension();

		matrix_t<Number> directions = matrix_t<Number>::Zero(2*dim,dim);
		for(unsigned i=0; i<dim; ++i) {
			directions(2*i, i) = -1;
			directions(2*i+1, i) = 1;
		}

		vector_t<Number> distances = vector_t<Number>(2*dim);

		std::vector<carl::Interval<Number>> intervals = _source.boundaries();
		for(unsigned i=0; i<dim; ++i) {
			distances(2*i) = intervals[i].lowerBound();
			distances(2*i+1) = intervals[i].upperBound();
		}

		_target = SupportFunction<Number>(directions, distances);

		return true;
	}
	
	/*
	template<typename Number>
	hypro::SupportFunction<Number> convert(const hypro::VPolytope<Number>& _source, SupportFunction<Number>& _target) {
		
	}
	*/

	
	template<typename Number>
	bool convert(const hypro::HPolytope<Number>& _source, SupportFunction<Number>& _target) {
		typename HPolytope<Number>::HyperplaneVector& planes = _source.constraints();
		assert(!planes.empty());

		_target = SupportFunction<Number>(SF_TYPE::POLY, planes);

		return true;
	}

	
	template<typename Number>
	bool convert(const hypro::Zonotope<Number>& _source, SupportFunction<Number>& _target) {
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

		return true;
	}

	/*
	template<typename Number>
	hypro::SupportFunction<Number> convert(const hypro::Polytope<Number>& _source) {
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

		return Box<Number>(intervals);
	}
	*/
} //namespace