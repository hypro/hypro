/* 
 * Contains utilities to wrap the ppl polyhedra to our datastructure.
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since       2014-04-01
 * @version     2014-04-03
 */

#pragma once

#include <ppl.hh>
#include <carl/core/Variable.h>
#include "../../util/eigenTypetraits.h"
#include "../../util/VariablePool.h"

#include "../Polytopes/util.h"

namespace hypro
{
namespace polytope
{
    using carl::operator<<;
    
    
    static inline std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        Parma_Polyhedra_Library::Generator_System gs = poly.generators();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
        for(auto& generator : gs)
        {
            Parma_Polyhedra_Library::Generator::expr_type l = generator.expression();

            for(auto& variableIt : VariablePool::getInstance().pplVariables())
            {
                if((int)Parma_Polyhedra_Library::raw_value(l.coefficient(variableIt)).get_si() != 0)
                {
                    variables.insert(variableIt);
                }
            }
        }
        return variables;
    }
    
    static inline const unsigned gsSize(const Parma_Polyhedra_Library::Generator_System& gs)
    {
        using namespace Parma_Polyhedra_Library;
        unsigned i = 0;
        for(const auto& g : gs)
        {
            ++i;
            (void)g; // just to suppress "unused variable" warning.
        }           
        return i;
    }
    
    static inline const unsigned csSize(const Parma_Polyhedra_Library::Constraint_System& cs)
    {
        using namespace Parma_Polyhedra_Library;
        unsigned i = 0;
        for(const auto& c : cs)
        {
            ++i;
            (void)c; // just to suppress "unused variable" warning.
        }
                    
        return i;
    }
    
    template<typename Number>
    static inline Parma_Polyhedra_Library::Generator pointToGenerator(const Point<Number>& point)
    {
        //std::cout << "PTG." << std::endl;
        using namespace Parma_Polyhedra_Library;
        double tmpValue;
        Linear_Expression ls;
        for(auto pointIt = point.begin(); pointIt != point.end(); ++pointIt)
        {
            //std::cout << "Var: " << (*pointIt).first << " found as: " << VariablePool::getInstance().variable((*pointIt).first) << std::endl;
            tmpValue = (*pointIt).second.toDouble() * fReach_DENOMINATOR;
            //std::cout << "tmpValue: " << tmpValue << std::endl;
            Linear_Expression tmp = tmpValue * VariablePool::getInstance().variable((*pointIt).first);
            ls += tmp;
        }
        Generator result = Generator::point(ls, fReach_DENOMINATOR);
        return result;
    }
    
    /**
     * Creates a generator from a point, which is a colum-vector (mx1)
     */
    template<typename Number>
    static inline Parma_Polyhedra_Library::Generator pointToGenerator(Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, 1> point)
    {
        using namespace Parma_Polyhedra_Library;
        double tmpValue;
        Linear_Expression ls;
        for(unsigned i = 0; i < point.rows(); ++i)
        {
            tmpValue = point(i,0).toDouble() * fReach_DENOMINATOR;
            Linear_Expression tmp = tmpValue * VariablePool::getInstance().pplVarByIndex(i);
            ls += tmp;
        }
        Generator result = Generator::point(ls, fReach_DENOMINATOR);
        return result;
    }
    
    template<typename Number>
    static inline Point<Number> generatorToPoint(const Parma_Polyhedra_Library::Generator& gen, const std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare>& variables)
    {
        Point<Number> result;
        carl::FLOAT_T<Number> coefficient;
        carl::FLOAT_T<Number> divisor;
        carl::FLOAT_T<Number> value;
        for(auto varIt = variables.begin(); varIt != variables.end(); ++varIt)
        {
            if( gen.space_dimension() >= (*varIt).space_dimension() )
            {
                coefficient = (int)Parma_Polyhedra_Library::raw_value(gen.coefficient(*varIt)).get_si();
                divisor = (int)Parma_Polyhedra_Library::raw_value(gen.divisor()).get_si();
                value = coefficient/divisor;
                //std::cout << "Coordinates: " << value << std::endl;
                //std::cout << __func__ << " Coefficient: " << coefficient << ", Divisor: " << divisor << ", Value: " << value << std::endl;
                result.setCoordinate(hypro::VariablePool::getInstance().variable(*varIt), value );
            }
            else
            {
                // TODO: What about variables that have a greater space dimension? I guess this does not matter, as they do not seem to be part of the generator
                result.setCoordinate(hypro::VariablePool::getInstance().variable(*varIt), carl::FLOAT_T<Number>(0));
            }
        }
        return result;
    }
    
    static inline unsigned pplDimension(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        Parma_Polyhedra_Library::Generator_System gs = poly.generators();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables;
        for(auto& generator : gs)
        {
            Parma_Polyhedra_Library::Generator::expr_type l = generator.expression();
            for(auto& variableIt : VariablePool::getInstance().pplVariables())
            {
                if(l.coefficient(variableIt) != 0)
                {
                    //std::cout << "Add: " << (variableIt) << " (" << l.coefficient(variableIt) << ")" << std::endl;
                    variables.insert(variableIt);
                }
            }
        }
        return variables.size();
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const Point<Number>& point)
    {
        unsigned result = 0;
        for(auto& coordinate : point)
        {
            result = result > VariablePool::getInstance().variable(coordinate.first).id() ? result : VariablePool::getInstance().variable(coordinate.first).id();
        }
        return result;
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const typename std::set<Point<Number> >& points)
    {
        unsigned result = 0;
        for(auto& point : points)
        {
            unsigned tmp = pplDimension(point);
            result = result > tmp ? result : tmp;
        }
        return result;
    }
    
    template<typename Number>
    static inline unsigned pplDimension(const typename std::vector<Eigen::Matrix<Number, Eigen::Dynamic, 1>>& points)
    {
        unsigned result = 0;
        for(auto& point : points)
        {
            result = result < point.rows() ? point.rows() : result;
        }
        return result;
    }
    
    template<typename Number>
    static inline Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> polytopeToMatrix(const Parma_Polyhedra_Library::C_Polyhedron& poly)
    {
        // TODO: What about the constant factor?
        unsigned rowCount = 0;
        unsigned columCount = 0;
        //poly.print();
        Parma_Polyhedra_Library::Constraint_System cs = poly.constraints();
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> vars = variables(poly);
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> result = Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>(hypro::polytope::csSize(cs), pplDimension(poly));
        //std::cout << "CSSize: " << hypro::polytope::csSize(cs) << ", Dimension: " << pplDimension(poly) << std::endl;
        for(auto constraintIt = cs.begin(); constraintIt != cs.end(); ++constraintIt)
        {
            columCount = 0;
            Parma_Polyhedra_Library::Constraint::expr_type t = (*constraintIt).expression();
            for(auto variableIt = vars.begin(); variableIt != vars.end(); ++variableIt)
            {
                carl::FLOAT_T<Number> val = (int)Parma_Polyhedra_Library::raw_value(t.get(*variableIt)).get_si();
                std::cout << "Insert " << val << " at (" << rowCount << ", " << columCount << ")" << std::endl; 
                result(rowCount, columCount) = val;
                ++columCount;
            }
            ++rowCount;
        }
        return result;
    }

    /**
     * @author Chris K.
     * Utility Functions for the Minkowski Sum Computation according to Fukuda
     */

    /**
     * computes the edge between two input points
     */
    template<typename Number>
    vector_t<Number> computeEdge(Point<Number>& _point1, Point<Number>& _point2) {
    	vector_t<Number> edge = vector_t<Number>(_point1.dimension(),1);
    	std::vector<carl::Variable> variables = _point1.variables();
    	int i = 0;

    	for (auto it=variables.begin(); it != variables.end(); ++it) {
    		edge(i) = _point2.at(*it) - _point1.at(*it);
    		i++;
    	}
    	return edge;
    }

    /**
     * computes the target point given a starting point and an edge
     */
    template<typename Number>
    Point<Number> computePoint(Point<Number>& _point, vector_t<Number>& _edge, bool ofPolyFlag) {
    	Point<Number> result = Point<Number>(_point);
    	std::vector<carl::Variable> variables = _point.variables();

    	assert(_point.dimension() == _edge.rows());
    	int i = 0;

    	for (auto it=variables.begin(); it != variables.end(); ++it) {
    		result.setCoordinate(*it,result.at(*it) + _edge(i));
    		i++;
    	}

    	//if the flag was set, then we are looking for a point which is part of a polytope
    	//has neighbors! we cannot just compute a new point
    	if (ofPolyFlag) {
    		for (unsigned i=0; i<_point.neighbors().size(); ++i) {
    			// == operator for points only compares coordinates, not neighbors
    			if (result == _point.neighbors().at(i)) {
    				result = _point.neighbors().at(i);
    				break;
    			}
    		}
    	}

    	return result;
    }

    /**
     * the Adjacency Oracle as per Fukuda's paper
     * computes one adjacent vertex in the sum polytope, given a specific direction (indirectly by the counter)
     */
    template<typename Number>
    bool adjOracle(Point<Number>& result, Point<Number>& _vertex, std::pair<int,int>& _counter) {
    	//retrieve the edge that is defined by the counter (j,i)
    	//first get both source & target vertex (dependent on the counter param.)
#ifdef fukuda_DEBUG
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "AdjOracle for vertex: " << _vertex  << std::endl;
    	std::cout << "-------------------------" << std::endl;
#endif

    	std::vector<Point<Number>> vertexComposition = _vertex.composedOf();
    	Point<Number> sourceVertex;
    	Point<Number> targetVertex;

    	if (_counter.first == 1 || _counter.first == 2) {
    		sourceVertex = vertexComposition[_counter.first-1];
    	}
    	std::vector<Point<Number>> neighbors = sourceVertex.neighbors();
    	if (neighbors.size() < _counter.second) {
    		//this neighbor does not exist for this vertex
#ifdef fukuda_DEBUG
        	std::cout << "-------------------------" << std::endl;
        	std::cout << "AdjOracle result: no neighbor in this direction"  << std::endl;
        	std::cout << "-------------------------" << std::endl;
#endif
    		return false;
    	} else {
    		targetVertex = neighbors[_counter.second-1];
    	}

    	//the edge is represented by a vector
    	vector_t<Number> edge = computeEdge(sourceVertex,targetVertex);

    	//check if there is a parallel edge in the other polytope that points in the same direction (not the origin of the sourceVertex)
    	//add all non-parallel edges to a set (needed for constraints in LP)
    	vector_t<Number> parallelEdge;
    	//indicates whether a parallel edge has been identified
    	bool parallelFlag = false;
    	std::vector<vector_t<Number>> nonParallelEdges;
    	Point<Number> otherSource;

    	if (_counter.first == 1) {
    		otherSource = vertexComposition[1];
    	} else {
    		otherSource = vertexComposition[0];
    	}

    	std::vector<Point<Number>> otherNeighbors = otherSource.neighbors();

    	vector_t<Number> tempEdge;
		carl::FLOAT_T<Number> dotProduct;
		carl::FLOAT_T<Number> normFactor;
		for (typename std::vector<Point<Number>>::iterator it=otherNeighbors.begin(); it != otherNeighbors.end(); ++it) {
			tempEdge = computeEdge(otherSource, *it);

			//check if edges are parallel (considering direction too)
			//for this the following has to hold: (x dot_product y) / (|x|*|y|) = 1

			dotProduct = tempEdge.dot(edge);
			normFactor = tempEdge.norm() * edge.norm();

			//has to be done... to avoid rounding problems
			dotProduct = std::round(dotProduct.toDouble()*1000000);
			normFactor = std::round(normFactor.toDouble()*1000000);

#ifdef fukuda_DEBUG
			std::cout << "Dot Product: " << dotProduct << std::endl;
			std::cout << "Norm Factor: " << normFactor << std::endl;
			std::cout << "Parallelism Factor: " << dotProduct/normFactor << std::endl;
			std::cout << "Value of the if condition: " << (dotProduct/normFactor == 1) << std::endl;
#endif

			if ( (dotProduct/normFactor == 1+EPSILON) || (dotProduct/normFactor == 1-EPSILON) ||
					(dotProduct/normFactor == -1+EPSILON) || (dotProduct/normFactor == -1-EPSILON) ||
					(dotProduct/normFactor == -1) || (dotProduct/normFactor == 1)) {
#ifdef fukuda_DEBUG
				std::cout << "Parallel Edge detected" << std::endl;
#endif
				parallelEdge = tempEdge;
				parallelFlag = true;
			} else {
				nonParallelEdges.push_back(tempEdge);
			}
		}

		//add all edges incident of the original source vertex to the Set of non-parallel edges as well
		for (typename std::vector<Point<Number>>::iterator it=neighbors.begin(); it!= neighbors.end(); ++it) {
			//dont add the original edge to the set
			if (*it != neighbors[_counter.second-1]) {
				vector_t<Number> tempEdge2 = computeEdge(sourceVertex, *it);
				nonParallelEdges.push_back(tempEdge2);
			}
		}

    	/*
    	 * Setup Linear Feasibility Problem (in form of a min. LP) with GLPK
    	 */
		glp_prob *feasibility;
		feasibility = glp_create_prob();
		glp_set_obj_dir(feasibility, GLP_MIN);

		//each row corresponds to one non-parallel edge (except for the first row, which refers to the edge we examine)
		glp_add_rows(feasibility, nonParallelEdges.size()+1);

		//set bound of first row
		//since < 0 is not possible, we have <= -EPSILON
		glp_set_row_bnds(feasibility, 1, GLP_UP, 0.0, -(EPSILON));

		//constraints of auxiliary variables
		for (int i=1; i <= nonParallelEdges.size(); ++i) {
			//start from second row
			glp_set_row_bnds(feasibility, i+1, GLP_LO, 0.0, 0.0);
		}

		//each column corresponds to one dimension of the vector
		glp_add_cols(feasibility, edge.rows());

		//coefficients of objective function
		for (int i=1; i<= edge.rows(); ++i) {
			glp_set_obj_coef(feasibility, i, 1.0);
		}

		//constrains for structural variables: x>=0, y>=0 for Lambda
		//not specified in paper, but else there is no feasible primal solution
		for (unsigned i=1; i<=edge.rows(); ++i) {
			glp_set_col_bnds(feasibility, i, GLP_DB, -1.0, 1.0);
		}

		//setup the matrix coefficients
		unsigned elements = (nonParallelEdges.size()+1) * (edge.rows());
#ifdef fukuda_DEBUG
		std::cout << "source Vertex: " << sourceVertex << std::endl;
		std::cout << "target Vertex: " << targetVertex << std::endl;
		std::cout << "other source Vertex: " << otherSource << std::endl;
		std::cout << "considered Edge: " << edge << std::endl;
#endif
        int ia[1+elements];
        int ja[1+elements];
        double ar[1+elements];
        unsigned pos = 1;

        //to prevent bugs
        ia[0] = 0;
        ja[0] = 0;
        ar[0] = 0;

        //setup the first row coefficients individually
		for(unsigned j = 1; j <= edge.rows(); ++j)
		{
		  ia[pos] = 1;
		  ja[pos] = j;
		  ar[pos] = edge(j-1).toDouble();
#ifdef fukuda_DEBUG
		  std::cout << "Coeff. at (1," << j << "): " << ar[pos] << std::endl;
#endif
		  ++pos;
		}

        //then the rest (for the set of non-parallel edges)
        for(unsigned i = 2; i <= nonParallelEdges.size()+1; ++i)
          {
              for(unsigned j = 1; j <= edge.rows(); ++j)
              {
                  ia[pos] = i;
                  ja[pos] = j;
                  vector_t<Number> tmpVec = nonParallelEdges.at(i-2);
                  ar[pos] = tmpVec(j-1).toDouble();
#ifdef fukuda_DEBUG
                  std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
#endif
                  ++pos;
              }
          }
        assert(pos-1 <= elements);

        glp_load_matrix(feasibility, elements, ia, ja, ar);
        glp_simplex(feasibility, NULL);

#ifdef fukuda_DEBUG
        std::cout << "Parallel Flag: " << parallelFlag << std::endl;
#endif

        //check if a feasible solution exists
        if (glp_get_status(feasibility) == GLP_NOFEAS) {
#ifdef fukuda_DEBUG
        	std::cout << "-------------------------" << std::endl;
        	std::cout << "AdjOracle result: no feasible solution" << std::endl;
        	std::cout << "-------------------------" << std::endl;
#endif
        	return false;
        } else {
        		//since there is a feasible solution, our edge determines an edge direction of P=P1+P2
        		//compute the new adjacent vertex in P using this information
        		if (!parallelFlag) {
        			//if there was no parallel edge: v_new = a1(v1,i1) + v2
        			//a1(v1,i1) := i1-th vertex adjacent to v1 (ref. Fukuda)
        			result = targetVertex.extAdd(otherSource);

        			//set the composition of the new Vertex accordingly
        			result.addToComposition(targetVertex);
        			result.addToComposition(otherSource);
        		} else {
        			//if there was a parallel edge: v_new = a1(v1,i1) + a2(v2,i2)
        			Point<Number> otherTargetVertex = computePoint(otherSource, parallelEdge, true);
#ifdef fukuda_DEBUG
        			std::cout << "parallel Edge: " << parallelEdge << std::endl;
        			std::cout << "Other Target Vertex: " << otherTargetVertex << std::endl;
#endif
        			result = targetVertex.extAdd(otherTargetVertex);

        			result.addToComposition(targetVertex);
        			result.addToComposition(otherTargetVertex);
        		}
        }

        glp_delete_prob(feasibility);

#ifdef fukuda_DEBUG
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "AdjOracle result: " << result << std::endl;
    	std::cout << "-------------------------" << std::endl;
#endif

        return true;
    }

    /**
     * computes the unique maximizer vector for a given vertex (and also the target point of this vector)
     */
    template<typename Number>
    vector_t<Number> computeMaximizerVector(Point<Number>& _targetVertex, Point<Number>& _vertex) {

    	//to prepare the LP, compute all incident edges of v1 & v2 for v=v1+v2
    	std::vector<Point<Number>> vertexComposition = _vertex.composedOf();
    	Point<Number> sourceVertex1 = vertexComposition[0];
    	Point<Number> sourceVertex2 = vertexComposition[1];

#ifdef fukuda_DEBUG
    	std::cout << "Decomposition: " << sourceVertex1 << ", " << sourceVertex2 << std::endl;
#endif

    	std::vector<Point<Number>> neighbors1 = sourceVertex1.neighbors();
    	std::vector<Point<Number>> neighbors2 = sourceVertex2.neighbors();

    	std::vector<vector_t<Number>> edges;
    	vector_t<Number> tmpEdge;

    	//traverse neighbors of v1
    	for (auto neighbor : neighbors1) {
    		tmpEdge = computeEdge(sourceVertex1,neighbor);
    		edges.push_back(tmpEdge);
    	}

    	//traverse neighbors of v2
    	for (auto neighbor : neighbors2) {
    		tmpEdge = computeEdge(sourceVertex2,neighbor);
    		edges.push_back(tmpEdge);
    	}

    	//check for degeneracy of the summand polytopes
    	std::vector<bool> degeneracyCheck(tmpEdge.rows(), true);
    	for (auto& edge : edges) {
    		for (unsigned i = 0; i < edge.rows(); ++i) {
    			if (edge(i) != 0) {
    				degeneracyCheck.at(i) = false;
    			}
    		}
    	}

#ifdef fukuda_DEBUG
		std::cout << "Bool Vector: " << degeneracyCheck << std::endl;
#endif

    	/*
		 * Setup LP with GLPK
		 */
		glp_prob *maximizer;
		maximizer = glp_create_prob();
		glp_set_obj_dir(maximizer, GLP_MAX);

		//we have one row for each edge in our set
		glp_add_rows(maximizer, edges.size());

		//constraints of auxiliary variables (bounds for rows)
		for (int i=1; i <= edges.size(); ++i) {
			glp_set_row_bnds(maximizer, i, GLP_UP, 0.0, 0.0);
		}

		//each column corresponds to one dimension of the vector + one column for Lambda0
		glp_add_cols(maximizer, tmpEdge.rows()+1);

		//coefficients of objective function: only Lambda0 has a non-zero coefficient (last column)
		for (int i=1; i<= tmpEdge.rows(); ++i) {
			glp_set_obj_coef(maximizer, i, 0.0);
		}
		glp_set_obj_coef(maximizer, tmpEdge.rows()+1, 1.0);

		//constraints for structural variables
		for (int i=1; i<= tmpEdge.rows(); ++i) {
			glp_set_col_bnds(maximizer, i, GLP_DB, -1.0, 1.0);
		}
		glp_set_col_bnds(maximizer, tmpEdge.rows()+1, GLP_UP, 0.0, POS_CONSTANT);

		//setup matrix coefficients
		unsigned elements = (edges.size()) * (tmpEdge.rows()+1);
        int ia[1+elements];
        int ja[1+elements];
        double ar[1+elements];
        unsigned pos = 1;

        //to prevent bugs
        ia[0] = 0;
        ja[0] = 0;
        ar[0] = 0;

        for (unsigned i=1; i <= edges.size(); ++i) {

        	//the rest depends on the current edge
        	for (unsigned j=1; j <= tmpEdge.rows(); ++j) {
				ia[pos] = i;
				ja[pos] = j;
				vector_t<Number> tmpVec = edges.at(i-1);
				ar[pos] = tmpVec(j-1).toDouble();
#ifdef fukuda_DEBUG
				std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
#endif
				++pos;
        	}

        	//for each row the last column is handled individually (Lambda0)
        	ia[pos] = i;
        	ja[pos] = tmpEdge.rows()+1;
        	ar[pos] = 1;
#ifdef fukuda_DEBUG
        	std::cout << "Coeff. at (" << i << "," << tmpEdge.rows()+1 << "): " << ar[pos] << std::endl;
#endif
        	++pos;
        }

        assert(pos-1 <= elements);

        glp_load_matrix(maximizer, elements, ia, ja, ar);
        glp_simplex(maximizer, NULL);

        vector_t<Number> result = vector_t<Number>(tmpEdge.rows(),1);

        //fill the result vector based on the optimal solution returned by the LP
        for (unsigned i=1; i <= tmpEdge.rows(); ++i) {
        	result(i-1) = glp_get_col_prim(maximizer, i);
        }

        //compute the target of this new edge
        _targetVertex = computePoint(_vertex, result, false);

        glp_delete_prob(maximizer);

#ifdef fukuda_DEBUG
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "Computed MaximizerVector: " << result << std::endl;
    	std::cout << "-------------------------" << std::endl;
#endif

        return result;

    }

    /**
     * computes one of dimension-1 vectors that contribute to the normal cone of a vertex
     */
    template<typename Number>
    vector_t<Number> computeNormalConeVector(std::vector<vector_t<Number>>& _edgeSet, vector_t<Number>& _maximizerVector) {

    	/*
		 * Setup LP with GLPK
		 */
		glp_prob *coneVector;
		coneVector = glp_create_prob();
		glp_set_obj_dir(coneVector, GLP_MAX);

		//we have one row for each edge in our set
		glp_add_rows(coneVector, _edgeSet.size());

		//constraints of auxiliary variables (bounds for rows)
		for (unsigned i=1; i <= _edgeSet.size(); ++i) {
			glp_set_row_bnds(coneVector, i, GLP_FX, 0.0, 0.0);
		}

		//each column corresponds to one dimension of a vector in our edgeSet
		glp_add_cols(coneVector, _edgeSet.at(0).rows());

		//coefficients of objective function:
		//maximize the scalar product between the computed Maximizer Vector of the vertex in P and the vector of the cone that we look for
		//=> this secures that our returned vector is oriented "the right way"
		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
			glp_set_obj_coef(coneVector, i, _maximizerVector(i-1).toDouble());
		}

		//constraints for structural variables
		for (unsigned i=1; i<= _edgeSet.at(0).rows(); ++i) {
			glp_set_col_bnds(coneVector, i, GLP_DB, -1.0, 1.0);
		}

		//setup matrix coefficients
		unsigned elements = (_edgeSet.size()) * (_edgeSet.at(0).rows());
		int ia[1+elements];
		int ja[1+elements];
		double ar[1+elements];
		unsigned pos = 1;

        //to prevent bugs
        ia[0] = 0;
        ja[0] = 0;
        ar[0] = 0;

		for (unsigned i=1; i <= _edgeSet.size(); ++i) {

			for (unsigned j=1; j <= _edgeSet.at(0).rows(); ++j) {
				ia[pos] = i;
				ja[pos] = j;
				vector_t<Number> tmpVec = _edgeSet.at(i-1);
				ar[pos] = tmpVec(j-1).toDouble();
#ifdef fukuda_DEBUG
				std::cout << "Coeff. at (" << i << "," << j << "): " << ar[pos] << std::endl;
#endif
				++pos;
			}
		}
		assert(pos-1 <= elements);

		glp_load_matrix(coneVector, elements, ia, ja, ar);
		glp_simplex(coneVector, NULL);

		vector_t<Number> result = vector_t<Number>(_edgeSet.at(0).rows(),1);

		//fill the result vector based on the optimal solution returned by the LP
		for (unsigned i=1; i <= _edgeSet.at(0).rows(); ++i) {
			result(i-1) = glp_get_col_prim(coneVector, i);
		}

		glp_delete_prob(coneVector);

		return result;
    }

    /**
     * for a given vertex in the sum polytope, computes all possible edge candidates
     * i.e. consider all incident edges at the vertex decomposition
     */
    template<typename Number>
    std::vector<vector_t<Number>> computeEdgeSet(Point<Number>& _vertex) {
    	std::vector<Point<Number>> vertexComposition = _vertex.composedOf();
		Point<Number> sourceVertex1 = vertexComposition[0];
		Point<Number> sourceVertex2 = vertexComposition[1];

		std::vector<Point<Number>> neighbors1 = sourceVertex1.neighbors();
		std::vector<Point<Number>> neighbors2 = sourceVertex2.neighbors();

		std::vector<vector_t<Number>> edges;
		vector_t<Number> tmpEdge;

		//traverse neighbors of v1
		for (auto neighbor : neighbors1) {
			tmpEdge = computeEdge(sourceVertex1,neighbor);
			edges.push_back(tmpEdge);
		}

		//traverse neighbors of v2
		for (auto neighbor : neighbors2) {
			tmpEdge = computeEdge(sourceVertex2,neighbor);
			edges.push_back(tmpEdge);
		}

		return edges;
    }

    /**
     * computes the normal cone for a given vertex
     */
    template<typename Number>
    polytope::Cone<Number>* computeCone(Point<Number>& _vertex, vector_t<Number>& _maximizerVector) {
    	std::vector<vector_t<Number>> edges = computeEdgeSet(_vertex);

    	std::vector<vector_t<Number>> tmpEdges;
    	unsigned dimension = edges.at(0).rows();
    	vector_t<Number> tmpVector;
    	std::vector<vector_t<Number>> resultVectorSet;

#ifdef fukuda_DEBUG
        std::cout<< "Edges: " << edges << std::endl;
#endif

    	//dimension-1 edges define one (edge) vector of our cone
    	for (unsigned i = 0; i <= edges.size()-dimension+1; ++i) {
    		tmpEdges.clear();
    		for (unsigned j = 0; j < dimension-1; ++j) {
    			//consider dimension-1 edges
    			tmpEdges.push_back(edges.at(i+j));
    		}
    		tmpVector = polytope::computeNormalConeVector<Number>(tmpEdges, _maximizerVector);
#ifdef fukuda_DEBUG
            std::cout<< "Normal Cone Vector: " << tmpVector << std::endl;
#endif
    		resultVectorSet.push_back(tmpVector);
    	}

    	//dimension-1 (edge) vectors define one hyperplane of our cone
    	// -> iterate over resultVectorSet & consider every edge with its direct neighbor
    	polytope::Cone<Number>* cone = new polytope::Cone<Number>();
    	//set the origin of the cone
    	cone->setOrigin(_vertex);
    	std::vector<vector_t<Number>> vectorTuple;

    	//fill cone
    	for (unsigned i = 0; i <= resultVectorSet.size()-dimension+1; ++i) {
    		for (unsigned j=0; j <dimension-1; ++j) {
    			vectorTuple.push_back(resultVectorSet.at(i+j));
    		}

    		//convert Point<Number> to Vector by explicit cast
    		polytope::Hyperplane<Number>* plane = new polytope::Hyperplane<Number>(vector_t<Number>(_vertex), vectorTuple);
    		cone->add(plane);
#ifdef fukuda_DEBUG
    		std::cout << "Plane added to the cone" << std::endl;
#endif
    		vectorTuple.clear();
    	}

    	return cone;
    }

}
}
