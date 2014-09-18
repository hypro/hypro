/* 
 * File:   Polytope.tpp
 * Author: Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * 
 * @since       2014-03-20
 * @version     2014-04-04
 */

#include "Polytope.h"
#include "util.h"

namespace hypro
{
    template<typename Number>
    Polytope<Number>::Polytope() :
    mPointsUpToDate(true)
    {
    }

    template<typename Number>
    Polytope<Number>::Polytope(const Polytope& orig) :
    mPolyhedron(orig.mPolyhedron),
    mPoints(orig.mPoints),
    mPointsUpToDate(orig.mPointsUpToDate)
    {}

    template<typename Number>
    Polytope<Number>::~Polytope() {
    }

    template<typename Number>
    Polytope<Number>::Polytope(unsigned dimension) :
    mPolyhedron(dimension, Parma_Polyhedra_Library::EMPTY),
    mPoints(),
    mPointsUpToDate(true)
    {}

    template<typename Number>
    Polytope<Number>::Polytope(const Point<Number>& _point) :
        mPolyhedron(C_Polyhedron(polytope::pplDimension(_point)+1, Parma_Polyhedra_Library::EMPTY))
    {
        //std::cout << "Try Ppint: " << _point << std::endl;
        mPolyhedron.add_generator(polytope::pointToGenerator(_point));
        mPoints.push_back(_point);
        mPointsUpToDate = true;
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const typename std::vector<Point<Number>>& points)
    {
        //mPolyhedron.initialize();
        //std::cout << "Try Ppints" << std::endl;
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension(points)+1, Parma_Polyhedra_Library::EMPTY);
        for(auto& pointSetIt : points)
        {
            mPolyhedron.add_generator(polytope::pointToGenerator(pointSetIt));
            mPoints.push_back(pointSetIt);
        }
        mPointsUpToDate = true;
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const typename std::vector<Eigen::Matrix<carl::FLOAT_T<Number>,Eigen::Dynamic,1>>& points)
    {
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension(points), Parma_Polyhedra_Library::EMPTY);
        for(auto pointIt = points.begin(); pointIt != points.end(); ++pointIt)
        {
            Generator tmp = polytope::pointToGenerator(*pointIt);
            mPolyhedron.add_generator(tmp);
            Point<Number> tmpPoint = Point<Number>(*pointIt);
            mPoints.push_back(tmpPoint);
        }
        mPointsUpToDate = true;
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const matrix& A, const vector& b)
    {
        assert(A.rows() == b.rows());
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(A.cols(), Parma_Polyhedra_Library::UNIVERSE);
        for(unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex)
        {
            Parma_Polyhedra_Library::Linear_Expression polynom;
            polynom.set_space_dimension(A.cols());
            for(unsigned columIndex = 0; columIndex < A.cols(); ++columIndex)
            {
            	//std::cout << "Matrix Coefficient: " << (A(rowIndex,columIndex)*fReach_DENOMINATOR).toDouble() << std::endl;
            	polynom.set_coefficient(hypro::VariablePool::getInstance().pplVarByIndex(columIndex), (A(rowIndex,columIndex)*fReach_DENOMINATOR).toDouble());
                //polynom.set_coefficient(hypro::VariablePool::getInstance().pplVarByIndex(columIndex), A(rowIndex,columIndex).toDouble());
                //std::cout << hypro::VariablePool::getInstance().pplVarByIndex(columIndex) << " = " << A(rowIndex,columIndex).toDouble() << std::endl;
            }
            //std::cout << "Vector Coefficient: " << -(b(rowIndex,0)*fReach_DENOMINATOR).toDouble() << std::endl;
            polynom.set_inhomogeneous_term(-(b(rowIndex,0)*fReach_DENOMINATOR).toDouble());
            //polynom.set_inhomogeneous_term(-b(rowIndex,0).toDouble());
            Parma_Polyhedra_Library::Constraint constraint;
            constraint = polynom <= 0;
            
            mPolyhedron.add_constraint(constraint);
            //mPolyhedron.add_generator(gen);
        }
        mPointsUpToDate = false;
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const matrix& A)
    {
        mPolyhedron = Parma_Polyhedra_Library::C_Polyhedron(A.rows(), Parma_Polyhedra_Library::UNIVERSE);
        for(unsigned rowIndex = 0; rowIndex < A.rows(); ++rowIndex)
        {
            Parma_Polyhedra_Library::Linear_Expression polynom;
            polynom.set_space_dimension(A.cols());
            for(unsigned columIndex = 0; columIndex < A.cols(); ++columIndex)
            {
                //std::cout << hypro::VariablePool::getInstance().pplVarByIndex(columIndex) << " = " << A(rowIndex,columIndex).toDouble() << std::endl;
                polynom.set_coefficient(hypro::VariablePool::getInstance().pplVarByIndex(columIndex), A(rowIndex,columIndex).toDouble());
            }
            Parma_Polyhedra_Library::Constraint constraint;
            constraint = polynom <= 0;
            
            mPolyhedron.add_constraint(constraint);
            //mPolyhedron.add_generator(gen);
        }
        mPointsUpToDate = false;
    }
    
    template<typename Number>
    Polytope<Number>::Polytope(const C_Polyhedron& _rawPoly) :
    mPolyhedron(_rawPoly),
    mPoints(),
    mPointsUpToDate(false)
    {}
    
    template<typename Number>
    bool Polytope<Number>::isEmpty() const
    {
        return mPolyhedron.is_empty();
    }
    
    template<typename Number>
    void Polytope<Number>::addPoint(const Point<Number>& point)
    {
        Generator tmp = polytope::pointToGenerator(point);
        if(mPolyhedron.space_dimension() != tmp.space_dimension()) {
            mPolyhedron.add_space_dimensions_and_embed(tmp.space_dimension());
        }
        mPolyhedron.add_generator(tmp);
        mPoints.push_back(point);
    }
    
    template<typename Number>
    void Polytope<Number>::updatePoints()
    {
    	if (!mPointsUpToDate) {
			std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables = hypro::polytope::variables(mPolyhedron);
			for(auto& generator : mPolyhedron.generators())
			{
				// TODO: Call generatorToPoint only with the variables occuring in the actual generator (some might be degenerated)
				Point<Number> tmp = polytope::generatorToPoint<Number>(generator, variables);
				bool found = false;
				for (auto& point : mPoints) {
					if (point == tmp) {
						found = true;
						break;
					}
				}
				if (!found) {
					mPoints.push_back(tmp);
				}
			}
			mPointsUpToDate = true;
    	}

    }

    template<typename Number>
    const std::vector<Point<Number>>& Polytope<Number>::points()
    {
    	/*
        typename Point<Number>::pointSet result;
        std::set<Parma_Polyhedra_Library::Variable, Parma_Polyhedra_Library::Variable::Compare> variables = hypro::polytope::variables(mPolyhedron);
        for(auto& generator : mPolyhedron.generators())
        {
            // TODO: Call generatorToPoint only with the variables occuring in the actual generator (some might be degenerated)
            Point<Number> tmp = polytope::generatorToPoint<Number>(generator, variables);
            result.insert(tmp);
        }
        return result;
        */
    	if (!mPointsUpToDate) {
    		updatePoints();
    	}
    	return mPoints;
    }

    template<typename Number>
    std::vector<Point<Number>>& Polytope<Number>::rPoints()
    {
    	/*
    	if (!mPointsUpToDate) {
    		updatePoints();
    	}*/
    	return mPoints;
    }
    

    //returns the fan of the Polytope
    template<typename Number>
    const polytope::Fan<Number>& Polytope<Number>::fan() {
    	return mFan;
    }

    template<typename Number>
    polytope::Fan<Number>& Polytope<Number>::rFan() {
    	return mFan;
    }

    //sets the fan of the Polytope
    template<typename Number>
    void Polytope<Number>::setFan(const polytope::Fan<Number>& _fan){
    	mFan = _fan;
    }

    template<typename Number>
    void Polytope<Number>::print() const
    {
        std::cout << "[";
        for(auto& generator : mPolyhedron.generators())
        {
            generator.print();
        }
        std::cout << "]" << std::endl;
    }
    
    template<typename Number>
    void Polytope<Number>::writeToFile(std::string _filename) const
    {
    	/*
        std::ofstream outputFile;
        outputFile.open(_filename);
        outputFile << *this;
        outputFile.close();
        */
    }
    
    template<typename Number>
    const C_Polyhedron& Polytope<Number>::rawPolyhedron() const
    {
        return mPolyhedron;
    }

    template<typename Number>
    C_Polyhedron& Polytope<Number>::rRawPolyhedron()
    {
        return mPolyhedron;
    }

    template<typename Number>
    unsigned int Polytope<Number>::dimension() const
    {
        return hypro::polytope::pplDimension(mPolyhedron);
    }
    
    template<typename Number>
    bool Polytope<Number>::linearTransformation(Polytope<Number>& result, const matrix& A, const vector& b)
    {
        using namespace Parma_Polyhedra_Library;
        
        result = *this;
        
        std::vector<Parma_Polyhedra_Library::Variable> variables;
        for(unsigned i = 0; i < A.rows(); ++i)
            variables.push_back(VariablePool::getInstance().pplVarByIndex(i));
        
        const Generator_System generators = this->mPolyhedron.generators();
        
        // Create Eigen::Matrix from Polytope
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> polytopeMatrix(variables.size(), polytope::gsSize(generators));
        unsigned gCount = 0;
        
        carl::FLOAT_T<Number> coefficient;
        carl::FLOAT_T<Number> divisor;
        carl::FLOAT_T<Number> value;
        
        for(Generator_System::const_iterator generatorIt = generators.begin(); generatorIt != generators.end(); ++generatorIt)
        {
            unsigned vCount = 0;
            // Assuming the divisor stays the same in one generator
            divisor = (int)raw_value(generatorIt->divisor()).get_si();
            for(auto& var : variables)
            {
                coefficient = (int)raw_value(generatorIt->coefficient(var)).get_si();
                value = coefficient/divisor;
                
                polytopeMatrix(vCount, gCount) = value;
                ++vCount;
            }
            ++gCount;
        }
        
        // apply lineartransformation
        Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> res(variables.size(), polytope::gsSize(generators));
        //std::cout << "ARows: " << A.rows() << ", ACols: " << A.cols() << ", polyRows: " << polytopeMatrix.rows() << ", polyCols: " << polytopeMatrix.cols() << ", bRows: " << b.rows() << ", bCols: " << b.cols() << std::endl;
        if(b.rows() != 0)
        {
            res = (A*polytopeMatrix);
            Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic> tmp(res.rows(), res.cols());
            for(unsigned m = 0; m < tmp.rows(); ++m)
                for(unsigned n = 0; n < tmp.cols(); ++n)
                {
                    tmp(m,n) = b(m);
                }
            res += tmp;
        }
        else
        {
            res = (A*polytopeMatrix);
        }
            
        std::cout << "[EIGEN] linear transformation result: " << std::endl;
        std::cout << res << std::endl;
        
        
        // clear actual generators and add new ones
        std::vector<vector> ps;
        for(unsigned i = 0; i < res.cols(); ++i)
        {
            //std::cout << res.col(i) << std::endl;
            vector t = vector(res.rows());
            for(unsigned j = 0; j < res.rows(); ++j)
                t(j) = res.col(i)(j);
            ps.push_back(t);
        }
        C_Polyhedron tmp = Parma_Polyhedra_Library::C_Polyhedron(polytope::pplDimension<Number>(ps), Parma_Polyhedra_Library::EMPTY);
        for(auto& pointSetIt : ps)
        {
            tmp.add_generator(polytope::pointToGenerator(pointSetIt));
        }
        result.mPolyhedron = tmp;

        mPointsUpToDate = false;

        return true;
    }
    
    template<typename Number>
    bool Polytope<Number>::minkowskiSum(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        /*
        typedef Point<Number> point;
        // initialize algorithm
        point::pointSet resultSet;
        
        // initialize sink node
        point sink = *this->points().begin() + *rhs.points().begin();
        point current = sink;
        
        // determine deltaK
        int deltaK = 0; // TODO
        
        std::pair<int, int> neighborCounter = std::make_pair(1,0);
        std::pair<int, int> maxCounter = std::make_pair(2, deltaK);
        
        do
        {
            while( neighborCounter < maxCounter ) 
        } while ( current != sink || neighborCounter != (2, deltaK));
        */
        
        
        // unelegant version creating the powerset of all points and reducing it afterwards
        //std::cout << "Result before: " << std::endl;
        result = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
        //result.print();
        
        for( auto& genA : mPolyhedron.generators() )
        {
            Point<Number> tmpA = polytope::generatorToPoint<Number>(genA, polytope::variables(mPolyhedron));
            for( auto& genB : rhs.rawPolyhedron().generators() )
            {
                //std::cout << __func__ << " Generator: " << genB << std::endl;
                Point<Number> tmpB = polytope::generatorToPoint<Number>(genB, polytope::variables(rhs.rawPolyhedron()));
                
                //std::cout << __func__ << " Point: " << tmpB << std::endl;
                
                //std::cout << "Points in Hausdorff Poly: " << tmpB << std::endl;
                //std::cout << "tmpA: " << tmpA << std::endl;

                Point<Number> res = tmpA.extAdd(tmpB);
                
                //std::cout << "Add point: " << res << std::endl;
                result.addPoint(res);
                //std::cout << "Intermediate result:" << std::endl;
                //result.print();
            }
        }
        //std::cout << "Result:" result.print() << std::endl;
        result.hull(result);

        mPointsUpToDate = false;

        return true;
    }
    
    /**
     * @author: Chris K.
     * Minkowski Sum computation based on Fukuda
     */
    template<typename Number>
        bool Polytope<Number>::altMinkowskiSum(Polytope<Number>& result, Polytope<Number>& rhs) {
    	//TODO compute adjacency for this & rhs vertices (currently manually defined within the tests)
    	result = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);
    	std::vector<Point<Number>> alreadyExploredVertices;

    	/**
    	 * Preprocessing
    	 */

    	//delta = max vertex degree
    	int delta_1 = this->computeMaxVDegree();
    	int delta_2 = rhs.computeMaxVDegree();

    	//initVertex = initial extreme point & root of spanning tree
    	Point<Number> initVertex = this->computeInitVertex(rhs);
    	result.addPoint(initVertex);
    	alreadyExploredVertices.push_back(initVertex);
    	std::cout << "---------------" << std::endl;
    	std::cout << "following Vertex is part of result: " << initVertex << std::endl;
    	std::cout << "---------------" << std::endl;

    	//compute the maximizer vector (& its target) for the initial extreme point -> necessary for localSearch()
    	Point<Number> sinkMaximizerTarget;
    	vector sinkMaximizerVector = polytope::computeMaximizerVector(sinkMaximizerTarget, initVertex);

    	//compute the normal cone of the initial extreme point
    	polytope::Cone<Number>* cone = polytope::computeCone(initVertex, sinkMaximizerVector);
    	//add this normal cone to the fan of the polytope
    	result.rFan().add(cone);

    	//set currentVertex to initVertex
    	Point<Number> currentVertex = initVertex;

    	//counter initially (1,0)
    	std::pair<int,int> counter;
    	counter.first = 1;
    	counter.second = 0;

    	/**
    	 * Reverse Search Algorithm
    	 */
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "The Preprocessing Ends here - Start of Algorithm" << std::endl;
    	std::cout << "-------------------------" << std::endl;
    	std::cout << "-------------------------" << std::endl;

    	Point<Number> nextVertex;
    	std::vector<std::pair<int,int>> counterMemory;
    	bool alreadyExplored;
    	std::map<Point<Number>, Point<Number>> parentMap;

    	do {

    		while (counter.first < 2 || (counter.first==2 && counter.second < delta_2) ) {

    	    	std::cout << "Max. Vertex Degree in Poly 1: " << delta_1 << std::endl;
    	    	std::cout << "Max. Vertex Degree in Poly 2: " << delta_2 << std::endl;

    	    	alreadyExplored = false;

    			//increment counter by 1
    			if (counter.second == delta_1) {
    				counter.first = 2;
    				counter.second = 1;
    			} else {
    				counter.second += 1;
    			}

    			std::cout << "Counter tuple: (" << counter.first << "," << counter.second << ")" << std::endl;

    			//choose next Vertex, only continue if one exists
    			if (polytope::adjOracle(nextVertex, currentVertex, counter)) {
					for (unsigned i=0; i < alreadyExploredVertices.size(); ++i) {
	    				if (nextVertex == alreadyExploredVertices.at(i)) {
	    					alreadyExplored = true;
	        				std::cout << "Vertex has already been explored: "<< nextVertex << std::endl;
	    				}
					}
    				if (alreadyExplored) {
    					std::cout << "continue with next loop iteration" << std::endl;
    					std::cout << "-------------------------" << std::endl;
    					//dont traverse back and forth between two vertices
    					continue;
    				}
    				Point<Number> localSearchVertex = result.localSearch(nextVertex, sinkMaximizerTarget);
    				parentMap.insert( std::make_pair(nextVertex, localSearchVertex) );
    				if (localSearchVertex == currentVertex) {
    					//TODO problem: addNeighbor requires a pointer
    					//set Neighbors of the new vertices accordingly
    					//currentVertex.addNeighbor(&nextVertex);
    					//nextVertex.addNeighbor(&currentVertex);

    					//reverse traverse
    					currentVertex = nextVertex;

    					//add to result Poly
    					result.addPoint(currentVertex);
    			    	std::cout << "---------------" << std::endl;
    			    	std::cout << "following Vertex is part of result: " << currentVertex << std::endl;
    			    	std::cout << "---------------" << std::endl;

    					alreadyExploredVertices.push_back(currentVertex);
    					//store the current counter value - needed if DFS comes back this vertex
    					counterMemory.push_back(counter);
    					std::cout << "---------------" << std::endl;
    					std::cout << "Counter Memory Stack - add Counter: (" << counter.first << "," << counter.second << ")"  << std::endl;
    					std::cout << "Already explored Vertices: " << alreadyExploredVertices << std::endl;
    					std::cout << "---------------" << std::endl;

    					counter.first = 1;
    					counter.second = 0;
    				}
    			}
    		}
	    	std::cout << "---------------" << std::endl;
	    	std::cout << "While Loop left" << std::endl;
	    	std::cout << "---------------" << std::endl;
    		if (currentVertex != initVertex) {
    			//forward traverse
    			//currentVertex = result.localSearch(currentVertex, sinkMaximizerTarget);
    			//instead of computing the local Search result again, retrieve the parent from the parentMap
    			currentVertex = parentMap.at(currentVertex);

    			std::cout << "Local Search finished" << std::endl;
    			std::cout << "counterMemory size: " << counterMemory.size() << std::endl;

    			//restore counter such that adjOracle(currentVertex,counter) = temp
    			//use the "stack" counterMemory for that
    			counter = counterMemory.at(counterMemory.size()-1);
    			counterMemory.pop_back();
    			std::cout << "---------------" << std::endl;
    			std::cout << "Counter restored to: (" << counter.first << "," << counter.second << ")"  << std::endl;
    			std::cout << "While Loop Condition: " << ( (currentVertex != initVertex) || (counter.first != 2 && counter.second != delta_2) ) << std::endl;
    			std::cout << "CurrrentVertex != initVertex: " << (currentVertex != initVertex) << std::endl;
    			std::cout << "Counter != (2,2): " << (counter.first != 2 || counter.second != delta_2) << std::endl;
    			std::cout << "---------------" << std::endl;
    			/*
    			//approach: start at (1,1), increment till desired counter is found
    			counter.first = 1;
    			counter.second = 0;

    			Point<Number> result;
    			do {
    	    			//increment counter by 1
    	    			if (counter.second == delta_1) {
    	    				counter.first = 2;
    	    				counter.second = 1;
    	    			} else {
    	    				counter.second += 1;
    	    			}
    	    			bool not_used = polytope::adjOracle(result, currentVertex, counter);

    			} while (result != temp);*/

    		}

    	} while ( (currentVertex != initVertex) || (counter.first != 2 || counter.second != delta_2) );

    	mPointsUpToDate = false;

    	return true;

    }

    template<typename Number>
    bool Polytope<Number>::intersect(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        C_Polyhedron res = mPolyhedron;
        res.intersection_assign(rhs.rawPolyhedron());
        result = Polytope<Number>(res);

        mPointsUpToDate = false;

        return true;
    }
    
    template<typename Number>
    bool Polytope<Number>::hull(Polytope<Number>& result)
    {
        Generator_System gs = mPolyhedron.minimized_generators();
        result = Polytope<Number>(C_Polyhedron(gs));

        mPointsUpToDate = false;

        return true;
    }
    
    template<typename Number>
    bool Polytope<Number>::contains(const Point<Number>& point)
    {
        return mPolyhedron.contains(Polytope<Number>(point).rawPolyhedron());
    }
    
    template<typename Number>
    bool Polytope<Number>::contains(const Polytope<Number>& poly)
    {
        return mPolyhedron.contains(poly.rawPolyhedron());
    }
    
    template<typename Number>
    bool Polytope<Number>::unite(Polytope<Number>& result, const Polytope<Number>& rhs)
    {
        C_Polyhedron res = mPolyhedron;
        res.poly_hull_assign(rhs.rawPolyhedron());
        result = Polytope<Number>(res);

        mPointsUpToDate = false;

        return true;
    }
    
    template<typename Number>
    Number Polytope<Number>::hausdorffError(const Number& delta, const Eigen::Matrix<carl::FLOAT_T<Number>, Eigen::Dynamic, Eigen::Dynamic>& matrix)
    {
        using namespace Eigen;
        // TODO: Can we omit conversion to carl::FLOAT_T<Number> and use Number instead?
        carl::FLOAT_T<Number> result;
        carl::FLOAT_T<Number> d = carl::FLOAT_T<Number>(delta);
        //TODO: What about the constant factor?
        //Eigen::Matrix<carl::FLOAT_T<Number>, Dynamic, Dynamic> matrix = Eigen::Matrix<carl::FLOAT_T<Number>, Dynamic, Dynamic>(polytope::csSize(mPolyhedron.constraints()), polytope::pplDimension(mPolyhedron));
        //matrix = hypro::polytope::polytopeToMatrix<Number>(this->mPolyhedron);
    	//std::cout << "in hausdorffError() - matrix: " << std::endl;
    	//std::cout << matrix << std::endl;
        
        // TODO: Matrix lpNorm function of Eigen does not work ...
        //carl::FLOAT_T<Number> t = matrix.lpNorm<Infinity>();
        
        // calculate matrix infinity norm by hand
        carl::FLOAT_T<Number> norm = 0;
        for(unsigned rowCnt = 0; rowCnt < matrix.rows(); ++rowCnt)
        {
            for(unsigned colCnt = 0; colCnt < matrix.cols(); ++colCnt)
            {
                carl::FLOAT_T<Number> value = matrix(rowCnt, colCnt);
                value.abs_assign();
                norm = norm < value ? value : norm;
            }
        }
        
        //carl::FLOAT_T<Number> tmp = d * t;
        carl::FLOAT_T<Number> tmp = d * norm;
        tmp.exp(result);
        result = result - 1 - tmp;
        
        // compute RX_0
        Number max = 0;
        for(auto& point : points())
        {
            Number inftyNorm = hypro::Point<Number>::inftyNorm(point);
            max = max > inftyNorm ? max : inftyNorm;
        }
        result *= carl::FLOAT_T<Number>(max);
        
        return result.value();
    }
    
    /*
    template<typename Number>
    Polytope<Number>& Polytope<Number>::operator= (const Polytope<Number>& rhs) 
    { 
      if (this != &rhs)
      { 
        Polytope<Number> tmp(rhs);
        std::swap(*this, tmp);
      } 
      return *this;
    }
    */
    
    template<typename Number>
    bool operator== (const Polytope<Number>& rhs, const Polytope<Number>& lhs) 
    { 
        return (rhs.rawPolyhedron() == lhs.rawPolyhedron());
    }
    template<typename Number>
    bool operator!= (const Polytope<Number>& rhs, const Polytope<Number>& lhs) 
    { 
        return (rhs.rawPolyhedron() != lhs.rawPolyhedron());
    }

    /**
     * @author: Chris K.
     * in the following: Utility functions for altMinkowskiSum()
     */
    //returns max. Vertex degree in a Polytope
    //TODO has to be assured that no inner vertices exist -> assume convex Hull?
    template<typename Number>
    int Polytope<Number>::computeMaxVDegree() {
    	std::vector<Point<Number>> points = this->points();
    	int max = 0;
        //std::cout << "Points in compute..: " << this->points() << std::endl;
    	for (typename std::vector<Point<Number>>::iterator it=points.begin(); it!=points.end(); ++it) {
    		if (max < it->neighbors().size()) {max=it->neighbors().size();}
    	}

    	return max;
    }

    //returns the point of of a Polytope with maximum x-value
    //-> unique maximizer extreme point v of cx over P with c = (1,0,0..)
    template<typename Number>
    Point<Number> Polytope<Number>::computeMaxPoint() {
    	Point<Number> result;
    	//updatePoints();
    	if(!mPoints.empty())
    	{
    		result = *(mPoints.begin());
			for (typename std::vector<Point<Number>>::iterator it=mPoints.begin(); it!=mPoints.end(); ++it) {
				assert(it->dimension() == result.dimension());
				assert(it->hasDimension(result.coordinates().begin()->first));
				carl::FLOAT_T<Number> coeff = it->coordinate(result.coordinates().begin()->first);
				if (result.coordinates().begin()->second < coeff)
				{
					result = *it;
				}
			}

    	}
    	return result;
    }

    //returns one extreme point of P = P1+P2
    template<typename Number>
    Point<Number> Polytope<Number>::computeInitVertex(Polytope<Number> _secondPoly) {
    	Point<Number> p1 = this->computeMaxPoint();
    	Point<Number> p2 = _secondPoly.computeMaxPoint();

    	Point<Number> res = p1.extAdd(p2);

    	//remember how the resulting point is composed (v= v1+v2)
    	res.addToComposition(p1);
    	res.addToComposition(p2);
    	return res;
    }

    //local Search function
    template<typename Number>
    Point<Number> Polytope<Number>::localSearch(Point<Number>& _vertex, Point<Number>& _sinkMaximizerTarget){

    	std::cout << "-------------------------" << std::endl;
    	std::cout << "in the following: Local Search for Vertex " << _vertex << std::endl;
    	std::cout << "-------------------------" << std::endl;

    	//TODO REMOVE
    	//std::cout.setstate(std::ios::failbit);
    	//glp_term_out(GLP_ON);

    	//compute the maximizer vector of the currently considered vertex
    	Point<Number> maximizerTarget;
    	vector maximizerVector = polytope::computeMaximizerVector(maximizerTarget, _vertex);

    	//std::cout << "maximizerVector in localSearch: " << maximizerVector << std::endl;

    	//compute the ray direction (a vector)
    	vector ray = polytope::computeEdge(maximizerTarget, _sinkMaximizerTarget);

    	std::cout << "Starting Point of Ray: " << maximizerTarget << std::endl;
    	std::cout << "End Point of Ray: " << _sinkMaximizerTarget << std::endl;
    	//std::cout << "Ray Vector: " << ray << std::endl;

    	//compute the normal cone of _vertex
    	polytope::Cone<Number>* cone = polytope::computeCone(_vertex, maximizerVector);

    	//iterate through all planes and check which one intersects with the ray
    	carl::FLOAT_T<Number> factor;
    	Point<Number> origin = cone->origin();
    	polytope::Hyperplane<Number> intersectedPlane;

    	std::vector<polytope::Hyperplane<Number>*> planes = cone->get();

    	std::cout << "-----------------" << std::endl;
    	std::cout << "Ray: " << ray << std::endl;

    	for (typename std::vector<polytope::Hyperplane<Number>*>::iterator it=planes.begin(); it!=planes.end(); ++it) {
    		if ((*it)->intersection(factor,ray)) {
    			std::cout << "Intersection found " << std::endl;
    			intersectedPlane = *(*it);
    			break;
    		}
    	}

    	//bool found = false;
    	Point<Number> secondOrigin;

    	std::cout << "-----------------" << std::endl;
		std::cout << "Normal of Intersection Plane: " << intersectedPlane.normal() << std::endl;
		std::cout << "Offset of Intersection Plane: " << intersectedPlane.offset() << std::endl;
		std::cout << "-----------------" << std::endl;

		std::vector<vector> decompositionEdges = polytope::computeEdgeSet(_vertex);
		//std::cout << "Decomposition Edges: " << decompositionEdges << std::endl;

		for (unsigned i=0; i < decompositionEdges.size(); i++) {
			carl::FLOAT_T<Number> dotProduct = intersectedPlane.normal().dot(decompositionEdges.at(i));
			carl::FLOAT_T<Number> normFactor = intersectedPlane.normal().norm() * decompositionEdges.at(i).norm();

			//has to be done...
			dotProduct = std::round(dotProduct.toDouble()*1000000);
			normFactor = std::round(normFactor.toDouble()*1000000);

			std::cout << "Dot Product: " << dotProduct << std::endl;
			std::cout << "Norm Factor: " << normFactor << std::endl;
			std::cout << "Parallelism Factor: " << dotProduct/normFactor << std::endl;
			std::cout << "Value of the if condition: " << (dotProduct/normFactor == 1) << std::endl;

			if ( (dotProduct/normFactor == 1+EPSILON) || (dotProduct/normFactor == 1-EPSILON) ||
					(dotProduct/normFactor == -1+EPSILON) || (dotProduct/normFactor == -1-EPSILON) ||
					(dotProduct/normFactor == -1) || (dotProduct/normFactor == 1)) {
				std::cout << "Parallel Edge found" << std::endl;
				std::cout << "-----------------" << std::endl;

				//we have to find out from which decomposition our edge came from
				//and accordingly initialize a counter that describes the direction
				unsigned half = decompositionEdges.size()/2;

		    	std::pair<int,int> counter;
		    	if (i+1 <= half) {
		    		counter.first = 1;
		    		counter.second = i+1;
		    	} else {
		    		counter.first = 2;
		    		counter.second = i+1-half;
		    	}

		    	//now we have to retrieve the new vertex in this edge direction, using the adjacency oracle
		    	//the result is stored in secondOrigin
		    	bool res = polytope::adjOracle(secondOrigin, _vertex ,counter);
		    	if (res) {
		    		break;
		    	}
			}
		}

		//TODO REMOVE
		/*
    	//iterate through all cones in the fan
    	for (auto& cone : this->mFan.get()) {
    		for (auto& plane : cone->get()) {
    			//check if our intersectedPlane is also present in the currently examined cone
    			//for that the Scalar has to be the same, and the cross product of both normals has to be 0 (=> normals are parallel)
    			std::cout << "Normal of comparison Plane: " << plane->normal() << std::endl;
    			std::cout << "Offset of comparison Plane: " << plane->offset() << std::endl;

    			carl::FLOAT_T<Number> dotProduct = intersectedPlane.normal().dot(plane->normal());
    			carl::FLOAT_T<Number> normFactor = intersectedPlane.normal().norm() * plane->normal().norm();
    			bool parallel = false;

    			std::cout << "dotProduct: " << dotProduct << std::endl;
    			std::cout << "normalizationFactor: " << normFactor << std::endl;

    			//TODO ~ 1, not exactly (rounding error)
    			if (dotProduct/normFactor == 1) {
    				std::cout << "Parallel Plane found" << std::endl;
        			std::cout << "-----------------" << std::endl;
    				parallel = true;
    				//store the origin of the cone this plane belongs to
    				secondOrigin = cone->origin();
    			}

    			if (parallel) {
    				//check if the edge between the input vertex and the possible parent is parallel to the normal of the intersectedPlane
    				std::vector<vector> edges = polytope::computeEdgeSet(_vertex);
    				vector candidateEdge = polytope::computeEdge(_vertex, secondOrigin);
    				std::cout << "Candidate Edge: " << candidateEdge << std::endl;

        			carl::FLOAT_T<Number> dot = intersectedPlane.normal().dot(candidateEdge);
        			carl::FLOAT_T<Number> norm = intersectedPlane.normal().norm() * candidateEdge.norm();

        			if (dot/norm == 1) {
        				std::cout << "Candidate Edge is parallel to normal of IntersectedPlane" << std::endl;

        				//a further check has to be made:
        				//the candidate edge also has to be parallel to at least one edge in P1 or P2, else this edge direction would not exist
        				for (auto& edge : decompositionEdges) {
                			carl::FLOAT_T<Number> dotLast = edge.dot(candidateEdge);
                			carl::FLOAT_T<Number> normLast = edge.norm() * candidateEdge.norm();
        					if (dotLast/normLast == 1) {
        						std::cout << "Solution found: there is also an edge in the decomposition that is parallel to the candidate" << std::endl;
        						found = true;
        						break;
        					}
        				}
        				if (found) {
        					break;
        				}
        			}
    			}

    		}
    		if (found) {
    			//retrieve the origin of the cone that has the identical plane
    			//secondOrigin = cone->origin();
    			break;
    		}

    	}
    	*/

    	//add this normal cone to fan of polytope
    	//Important! after localSearch has been applied (so that we dont search in our own cone)
    	this->mFan.add(cone);

    	//TODO REMOVE
    	//std::cout.clear();
    	//glp_term_out(GLP_OFF);

    	std::cout << "-------------------------" << std::endl;
    	std::cout << "Local Search result: " << secondOrigin << std::endl;
    	std::cout << "-------------------------" << std::endl;

    	return secondOrigin;

    }

}
