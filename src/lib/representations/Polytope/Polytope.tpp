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
    
    //@author: Chris K.
    template<typename Number>
        bool Polytope<Number>::altMinkowskiSum(Polytope<Number>& result, const Polytope<Number>& rhs) {
    	//TODO compute adjacency for this & rhs vertices (currently manually defined within the tests)
    	result = Parma_Polyhedra_Library::C_Polyhedron(0,EMPTY);

    	/**
    	 * Preprocessing
    	 */

    	//delta = max vertex degree
    	int delta_1 = this->computeMaxVDegree();
    	int delta_2 = rhs.computeMaxVDegree();

    	//initVertex = initial extreme point & root of spanning tree
    	Point<Number> initVertex = this->computeInitVertex(rhs);
    	result.addPoint(initVertex);

    	//compute the maximizer vector (& its target) for the initial extreme point -> necessary for localSearch()
    	Point<Number> sinkMaximizerTarget;
    	vector sinkMaximizerVector = computeMaximizerVector(sinkMaximizerTarget, initVertex);

    	//compute the normal cone of the initial extreme point
    	polytope::Cone<Number>* cone = computeCone(initVertex, sinkMaximizerVector);
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

    	Point<Number> nextVertex;

    	do {

    		while (counter.first < 2 && counter.second < delta_2) {

    			//increment counter by 1
    			if (counter.second == delta_1) {
    				counter.first = 2;
    				counter.second = 1;
    			} else {
    				counter.second += 1;
    			}

    			//choose next Vertex, only continue if one exists
    			if (polytope::adjOracle(nextVertex, currentVertex, counter)) {
    				Point<Number> localSearchVertex = localSearch(nextVertex, sinkMaximizerTarget);
    				if (localSearchVertex == currentVertex) {
    					//TODO set Neighbors of both accordingly?
    					//reverse traverse
    					currentVertex = nextVertex;
    					counter.first = 1;
    					counter.second =0;

    					//add to result Poly
    					result.addPoint(currentVertex);
    				}
    			}
    		}
    		if (currentVertex != initVertex) {
    			//forward traverse
    			Point<Number> temp = currentVertex;
    			currentVertex = localSearch(currentVertex);

    			//restore counter such that adjOracle(currentVertex,counter) = temp
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

    			} while (result != temp);

    		}

    	} while ( (currentVertex != initVertex) && (counter.first != 2 && counter.second != delta_2) );

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
    	updatePoints();
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
    //TODO add param Point<Number> sink OR new function that computes & stores the m for the sink and just add the vector as a param
    template<typename Number>
    Point<Number> Polytope<Number>::localSearch(Point<Number>& _vertex, Point<Number>& _sinkMaximizerTarget){

    	//compute the maximizer vector of the currently considered vertex
    	Point<Number> maximizerTarget;
    	vector maximizerVector = computeMaximizerVector(maximizerTarget, _vertex);

    	//TODO perform ray shooting between maximizerTarget & _sinkMaximizerTarget

    	//compute the ray direction (a vector)
    	vector ray = computeEdge(maximizerTarget, _sinkMaximizerTarget);

    	//compute the normal cone of _vertex
    	polytope::Cone<Number>* cone = computeCone(_vertex, maximizerVector);

    	//iterate through all planes and check which one intersects with the ray
    	carl::FLOAT_T<Number> factor;
    	Point<Number>& origin = cone->origin();
    	polytope::Hyperplane<Number>* intersectedPlane;

    	for (auto& plane : cone->get()) {
    		if (plane->intersection(factor, ray)) {
    			intersectedPlane = plane;
    			break;
    		}
    	}

    	bool found = false;
    	Point<Number> secondOrigin;

    	//iterate through all cones in the fan
    	for (auto& cone : this->mFan.get()) {
    		for (auto& plane : cone.get()) {
    			//check if our intersectedPlane is also present in the currently examined cone
    			//for that the Scalar has to be the same, and the cross product of both normals has to be 0 (=> normals are parallel)
    			carl::FLOAT_T<Number> crossProduct = intersectedPlane->normal().cross(plane.normal());
    			//TODO crossProduct ~ 0, not exactly (rounding error)
    			if ((intersectedPlane->offset() == plane.offset()) && (crossProduct == 0)) {
    					//found the plane
    					found = true;
    					break;
    			}
    		}
    		if (found) {
    			//retrieve the origin of the cone that has the identical plane
    			secondOrigin = cone.origin();
    			break;
    		}

    	}

    	//add this normal cone to fan of polytope
    	//Important! after localSearch has been applied (so that we dont search in our own cone)
    	this->mFan.add(cone);

    	return secondOrigin;

    	//normal cone N(v;P) is the set of solutions Lambda to
    	//ej(vj,i) *Lambda <= 0 for all valid edges
    	// -> set of vectors?

    	//TODO compute facets of the normal cone of v -> hyperplanes
    	//then insert the line into the hyperplane equation
    	//check if there is a solution
    	//yes -> line intersects hyperplane; no -> no intersection; tautology -> parallel to each other



    }

}
