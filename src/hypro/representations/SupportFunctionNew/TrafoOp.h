/*
 * TrafoOp.h
 *
 * A RootGrowNode that represents a linear transformation operation in the tree of operations representing a SupportFunction.
 * Every TrafoOp knows its parameters for the linear transformation, which is a separate object for an optimization.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"

namespace hypro {

//Forward Declaration
template<typename Number, typename Converter, typename Setting>
class SupportFunctionNewT;

//A data struct for TrafoOp, containing all needed info to construct a TrafoOp from it. No connectivity info is saved.
//TODO: Do currentExponent and successiveTransformations need to be stored?
template<typename Number, typename Setting>
struct TrafoData : public RGNData {
	unsigned currentExponent;
	std::size_t successiveTransformations;
	std::shared_ptr<const LinTrafoParameters<Number,Setting>> parameters;

	TrafoData(unsigned exp, std::size_t suc, const std::shared_ptr<const LinTrafoParameters<Number,Setting>>& param)
		: currentExponent(exp), successiveTransformations(suc), parameters(param)
	{}

	template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > = carl::dummy>
	TrafoData(const TrafoData<Number,SettingRhs>& rhs)
		: currentExponent(1)
		, successiveTransformations(0)
	{
		const std::pair<matrix_t<Number>,vector_t<Number>>& parameterPair = rhs.parameters->getParameterSet(rhs.currentExponent);
		parameters = std::make_shared<const LinTrafoParameters<Number,Setting>>(parameterPair.first, parameterPair.second, Setting::LIN_TRANS_REDUCTION_GROUP_SIZE);
	}
};

//Specialized subclass for transformations as example of a unary operator
template<typename Number, typename Converter, typename Setting>
class TrafoOp : public RootGrowNode<Number,Converter,Setting> {

	using PointerVec = typename RootGrowNode<Number,Converter,Setting>::PointerVec;

  private:

	////// General Interface

	SFNEW_TYPE type = SFNEW_TYPE::TRAFO;
	unsigned originCount;
	PointerVec mChildren;
	std::size_t mDimension;

	////// Members for this class

	unsigned currentExponent;												//Has value 2^power if 2^power successive transformations has been reached, else 1
	std::size_t successiveTransformations;									//Counts how many transformations with the same parameters are used consecutively
	std::shared_ptr<const LinTrafoParameters<Number,Setting>> parameters;	//A ptr to the object where its parameters are stored

  public:

	////// Constructors & Destructors

	//Thou shalt not make an unconnected transformation without any parameters
	TrafoOp() = delete;

	//Set new trafoOp object as parent of origin.
	//During construction, find out how many TrafoOps with the same parameters are chained successively in the tree
	//and summarize groups of 2^power linear transformations for optimization
	TrafoOp(const SupportFunctionNewT<Number,Converter,Setting>& origin, const matrix_t<Number>& A, const vector_t<Number>& b)
		: originCount(1)
		, mChildren(PointerVec(1,nullptr))
		, mDimension(origin.dimension())
		, currentExponent(1)
	{
		parameters = std::make_shared<const LinTrafoParameters<Number,Setting>>(A,b);

		origin.addOperation(this);
		assert(this->getChildren().size() == 1);

		// Determine, if we need to create new parameters or if this matrix and vector pair has already been used (recursive).
		// in case this transformation has already been performed, parameters will be updated.

		origin.hasTrafo(parameters, A, b);

		// best points for reduction are powers of 2 thus we only use these points for possible reduction points
		if(Setting::LIN_TRANS_REDUCTION == true){
			bool reduced;
			do {
				reduced = false;
				if (this->getChildren().at(0)->getType() == SFNEW_TYPE::TRAFO){
					auto child = dynamic_cast<TrafoOp<Number,Converter,Setting>*>(this->getChildren().at(0).get());
					if(child->getParameters() == parameters && child->getCurrentExponent() == currentExponent){
					//if(child->getParameters()->matrix().isApprox(parameters->matrix()) && child->getCurrentExponent() == currentExponent){
						successiveTransformations = child->getSuccessiveTransformations()+1;
					} else {
						successiveTransformations = 0;
					}
				} else {
					successiveTransformations = 0;
				}

				if (successiveTransformations == unsigned(carl::pow(2,parameters->power)-1)) {
					reduced = true;
					currentExponent = currentExponent*(carl::pow(2,parameters->power));
					std::shared_ptr<RootGrowNode<Number,Converter,Setting>> grandChild = this->getChildren().at(0);
					for(std::size_t i = 0; i < unsigned(carl::pow(2,parameters->power)-1); i++ ){
						grandChild = grandChild->getChildren().at(0);
					}
					this->clearChildren();
					this->addToChildren(grandChild);
					assert(this->getChildren().size() == 1);
				}

			} while (reduced == true);
		}
	}

	//TrafoData constructor
	TrafoOp(const TrafoData<Number,Setting>& d)
		: originCount(1)
		, mChildren(PointerVec({1,nullptr}))
		//, mDimension(d.origin->getDimension())
		, currentExponent(d.currentExponent)
		, successiveTransformations(d.successiveTransformations)
		, parameters(d.parameters)
	{}

	~TrafoOp(){ }

	////// Getters & Setters

	SFNEW_TYPE getType() const override { return type; }
	unsigned getOriginCount() const override { return originCount; }
	std::size_t getDimension() const override { return mDimension; }
	unsigned getCurrentExponent() const { return currentExponent; }
	std::size_t getSuccessiveTransformations() const { return successiveTransformations; }
	const std::shared_ptr<const LinTrafoParameters<Number,Setting>>& getParameters() const { return parameters; }
	RGNData* getData() const override { return new TrafoData<Number,Setting>(currentExponent, successiveTransformations, parameters); }
	void setDimension(const std::size_t d) override { mDimension = d; }

	////// RootGrowNode Interface

	//transforms given evaluation directions with the transformation matrix and vector
	matrix_t<Number> transform(const matrix_t<Number>& param) const override {
		return parameters->getTransformedDirections(param, currentExponent);
	}

	//should not be reachable
	std::vector<EvaluationResult<Number>> compute(const matrix_t<Number>& , bool ) const override {
		std::cout << "USED COMPUTE FROM TRAFOOP SUBCLASS.\n";
		assert(false);
		return std::vector<EvaluationResult<Number>>();
	}

	//Given the results, return vector of evaluation results (here only first place needed, since unary op), transform the evaluation results
	std::vector<EvaluationResult<Number>> aggregate(std::vector<std::vector<EvaluationResult<Number>>>& resultStackBack, const matrix_t<Number>& currentParam) const override {
		assert(resultStackBack.size() == 1);
		assert(Eigen::Index(resultStackBack.front().size()) == currentParam.rows());
		const std::pair<matrix_t<Number>, vector_t<Number>>& parameterPair = parameters->getParameterSet(currentExponent);
		if(resultStackBack.front().begin()->errorCode != SOLUTION::INFEAS){
			unsigned directionCnt = 0;
			for(auto& entry : resultStackBack.front()){
				vector_t<Number> currentDir(currentParam.row(directionCnt));
				if(entry.errorCode == SOLUTION::INFTY) {
					entry.supportValue = 1;
				} else {
					assert(entry.errorCode != SOLUTION::INFEAS);
					if(Setting::LE_GUERNIC_HSPACE_INTERSECTION){
						//Generate a point that will be on the same plane as the optimal value,
						//Since le guernic hspace intersection does not return an optimal value
						vector_t<Number> pointOnPlane = vector_t<Number>::Zero(currentDir.rows());
						unsigned i = 0;
						while(i<currentDir.rows() && currentDir(i) == 0) {
							++i;
						}
						pointOnPlane(i) = entry.supportValue;
						pointOnPlane += parameterPair.second;
						entry.supportValue = pointOnPlane.dot(currentDir);
					} else {
						assert(entry.optimumValue != vector_t<Number>::Zero(getDimension()));
						assert(parameterPair.first.cols() == entry.optimumValue.rows());
						entry.optimumValue = parameterPair.first * entry.optimumValue + parameterPair.second;
						// As we know, that the optimal vertex lies on the supporting Halfspace, we can obtain the distance by dot product.
						entry.supportValue = entry.optimumValue.dot(currentDir);
					}
				}
				//TRACE("hypro.representations.supportFunction", "Direction: " << t << ", Entry value: " << entry.supportValue);
				++directionCnt;
				assert(directionCnt <= currentParam.rows());
			}
		}
		return resultStackBack.front();
	}

	//Checks emptiness
	bool empty(const std::vector<bool>& childrenEmpty) const override {
		assert(childrenEmpty.size() == 1);
		if(childrenEmpty.front()) return true;
		return false;
	}

	//Transform the supremum
	Point<Number> supremumPoint(std::vector<Point<Number>>& points) const override {
		assert(points.size() == 1);
		if(points.front().dimension() == 0) return points.front();
		std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = parameters->getParameterSet(currentExponent);
		return Point<Number>(parameterPair.first * points.front().rawCoordinates() + parameterPair.second);
	}

	//Invert transformation
	vector_t<Number> reverseOp(const vector_t<Number>& point) const override {
		std::pair<matrix_t<Number>, vector_t<Number>> parameterPair = parameters->getParameterSet(currentExponent);
		vector_t<Number> tmp = (parameterPair.first.inverse() * point) - parameterPair.second;
		return tmp;
	}

	//If child contains p, then scaled version will contain it too
	bool contains(const std::vector<bool>& v, const vector_t<Number>& /*point*/) const override {
		assert(v.size() == 1);
		if(v.front()) return true;
		return false;
	}

	bool hasTrafo(std::shared_ptr<const LinTrafoParameters<Number,Setting>>& ltParam, const matrix_t<Number>& A, const vector_t<Number>& b){
		//Use eigen3's isApprox() to make fuzzy matrix comparison instead of exact comparison.
		//Saves computation time if matrices are big.
		if(parameters->matrix().isApprox(A) && parameters->vector().isApprox(b)){
			ltParam = parameters;
		}
		return true;
	}
};

} //namespace hypro