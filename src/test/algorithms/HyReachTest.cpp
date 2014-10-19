#include "gtest/gtest.h"
#include "../defines.h"
#include "../../lib/algorithms/reachability/HyReach.h"
#include <string>

//#include "../../lib/algorithms/reachability/SupportFunction.h"
//#include "../../lib/algorithms/reachability/PolytopeSupportfunction.h"
//#include "../../lib/algorithms/reachability/NonLinearOmega0Supportfunction.h"
#include "../../lib/algorithms/reachability/hyreach_utils.h"

using namespace hypro;
using namespace carl;
using namespace std;

class HyReachTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	
    }

    virtual void TearDown()
    {
    }
};

// #define STRUCTURALTEST

#ifdef STRUCTURALTEST

TEST_F(HyReachTest, VectorgeneratorTest)
{
	std::string method = "Vectorgenerator TEST: ";

	cout << method << "Generate matrices to compare\n";
    	std::vector<matrix_t<double>> actual_directions = vectorgeneratorEXT(3,PI_UP/2,10000);
	cout << method << "VectorgeneratorEXT: done\n";

	std::vector<matrix_t<double>> expected = vectorgenerator(3);
	cout << method << "Vectorgenerator: done\n";

	cout << method << "Start comparison\n";
	bool result = true;
	for(auto iterator1 = expected.begin(); iterator1 != expected.end(); ++iterator1)
	{
		result &= contains(actual_directions, *iterator1, 3);
	}

	cout << method << "Comparison completed\n";

    if(result)
	{
		SUCCEED();
	}
	else
	{	
		cout << method << "vectorgeneratorEXT - FAIL\n";
	}
}


TEST_F(HyReachTest, SupportfunctionTest)
{
	std::string method = "PolytopeSupportfunction TEST: ";
	
	// constraints = [1 1; -1 1; 1 -1; -1 -1]
	matrix_t<double> constraints(4,2);
	constraints(0, 0) = 1;
	constraints(0, 1) = 1;

	constraints(1, 0) = -1;
	constraints(1, 1) = 1;

	constraints(2, 0) = 1;
	constraints(2, 1) = -1;

	constraints(3, 0) = -1;
	constraints(3, 1) = -1;

    // constants =[2;1;1;0]
	matrix_t<double> constants(4,1);
	constants(0) = 2;
	constants(1) = 1;
	constants(2) = 1;
	constants(3) = 0;

	cout << "Initialization terminated" <<'\n';
	cout << "constraints: " << constraints << '\n' << "constants: " << constants << '\n';

    // sp = calcPolytopeSP(constraints,constants,'MediumScale','linprog',[0;0],[],[])
	operator_e op = LEQ;
	PolytopeSupportFunction sp(constraints, constants, op, 2);

	cout << "Supportfunction object created" << '\n';
	bool success = true;

    // check evaluation results along constructive directions

    // result = sp(constraints(1,:)')
	evaluationResult result = sp.evaluate(constraints.row(0).transpose());
	cout << "Evaluationresult for l=" << '\n' << constraints.row(0).transpose() << '\n' << " : " << result.supportValue << '\n';
	// result == 2
	success &= result.supportValue == 2;

	cout << '\n';
	cout << '\n';
	
	
	// result = sp(constraints(2,:)')
	result = sp.evaluate(constraints.row(1).transpose());
	cout << "Evaluationresult for l=" << '\n' << constraints.row(1).transpose() << '\n' << " : " << result.supportValue << '\n';
	// result == 1
	success &= result.supportValue == 1;

	cout << '\n';
	cout << '\n';
	
    // result = sp(constraints(3,:)')
	result = sp.evaluate(constraints.row(2).transpose());
	cout << "Evaluationresult for l=" << '\n' << constraints.row(2).transpose() << '\n' << " : " << result.supportValue << '\n';
	// result == 1
	success &= result.supportValue == 1;
	
	
	// result = sp(constraints(4,:)')
	result = sp.evaluate(constraints.row(3).transpose());
	cout << "Evaluationresult for l=" << '\n' << constraints.row(3).transpose() << '\n' << " : " << result.supportValue << '\n';
	// result == 0
	success &= result.supportValue == 0;

	cout << '\n';
	cout << '\n';
	
	
	// check evaluation result along axes
	
	// L = vectorgenerator(2)
	std::vector<matrix_t<double>> L = vectorgenerator(2);
	
	// for i=1:1:size(L,1)
	for(auto iterator = L.begin(); iterator != L.end(); ++iterator)
	{
             // result = sp(L(i,:)')
	         result = sp.evaluate(*iterator);
	         cout << "Evaluationresult for l=" << '\n' << *iterator << '\n' << " : " << result.supportValue << '\n';
    }
    // %return values are correct (checked manually based on output)



    // check multiplication
    cout << "multiplicationtest -------------------------------------------------------" << '\n' << '\n';
    
    //B = [2 0;0 2] % will multiply the results with 2
    matrix_t<double> B(2,2);
    B(0,0) = 2;
    B(0,1) = 0;
    B(1,0) = 0;
    B(1,1) = 2;
    cout << "B =" << '\n' << B << '\n';
      
    
    //hypro::SupportFunction Bsp = B * (&sp);
    //cout << "Bsp constructed" << '\n';
    MultiplicationSupportfunction* Bsp2 = sp.multiply(B);
    cout << "start evaluation of multiplication" << '\n';
    // for i=1:1:size(L,1)
	for(auto iterator = L.begin(); iterator != L.end(); ++iterator)
	{
             // result = sp(B' * L(i,:)')
	         //result = Bsp.evaluate(*iterator);
	         //cout << "Evaluationresult for l=" << '\n' << *iterator << '\n' << " : " << result.supportValue << '\n';
	         
	         result = Bsp2->evaluate(*iterator);
	         cout << "Evaluationresult for l=" << '\n' << *iterator << '\n' << " : " << result.supportValue << '\n';
    }
    //
    
	if (success)
	{
		SUCCEED();
	}
	else
	{
		cout << "TEST FAILED!";
	}
	
	delete Bsp2;
}

TEST_F(HyReachTest, NLOPTtest)
{
    cout << "TEST NLOPT" << '\n';
	//NLOPTTEST test;
	//test.test();
	
	// A = [-1 1; 0.5 -2.5]
	matrix_t<double> A(2,2);
	A(0,0) = -1;
	A(0,1) = 1;
	A(1,0) = 0.5;
	A(1,1) = -2.5;
	cout << "A: " << A << '\n';
	cout << "-------------------" << '\n';
	
	// L = vectorgenerator(2)
	// L = L([4;3;2;1],:)
	std::vector<matrix_t<double>> L = vectorgenerator(2);
	cout << "L" << '\n';
	
	matrix_t<double> LAsMatrix = directionList2Matrix(&L);
	cout << "L matrix" << '\n';
	
	// V = calcPolytopeSP(L,[0;0;0;0],...)
	PolytopeSupportFunction V(LAsMatrix,getZeroVector(4),LEQ,2);
	cout << "V" << '\n';
	
	// range = [4;2;3;3]
	matrix_t<double> range(4,1);
	range(0,0) = 4;
	range(1,0) = 2;
	range(2,0) = 3;
	range(3,0) = 3;
	
	cout << "box value vector" << '\n';
	// X0 = calcPolytopeSP(L,range,'MediumScale','linprog',[0;0],[],[])
	PolytopeSupportFunction X0(LAsMatrix,range,LEQ,2);
     
    cout << "Basic values initialized" << '\n'; 
    
    // omega0 = calcomega0delta() 
    NonLinearOmega0Supportfunction omega0(&A, &V, &X0, 1);
    
    cout << "Omega0 initialized" << '\n';
    
    unsigned int count = 0;
	for (auto iterator = L.begin(); iterator != L.end(); ++iterator)
	{
            cout << "TEST: iteration " << count << '\n';
			matrix_t<double> l = (*iterator);
			
		    evaluationResult res;
            res = omega0.evaluate(l);
		    cout << "TEST: res.optimumValue:"<< '\n' << res.optimumValue << '\n' << " leads to the optimum value: "<< '\n' << res.supportValue << '\n';
		    count++;
	} 
	
	SUCCEED();
}
#endif

#define BB_TEST
#ifdef BB_TEST
// real test (bouncing ball)
#include "TestModels/BouncingBall.cpp"

TEST_F(HyReachTest, BouncingBallTest)
{
    // construct necessary analysis obejcts
    HyReach reachabilityAnalysis;
    HybridAutomaton<double>* model = createBB(); // model (hard coded and provided by included BouncingBall.cpp)
    
    // construct initial values
    std::vector<matrix_t<double>> directionsalongdimensions = vectorgenerator(2);
    matrix_t<double> initialConstraints = directionList2Matrix(&directionsalongdimensions);
    matrix_t<double> initialconstraintValues(4,1);
    initialconstraintValues(0,0) = 2;
    initialconstraintValues(1,0) =-2;
    initialconstraintValues(2,0) = 0;
    initialconstraintValues(3,0) = 0;
    
    SupportFunction* U = 0;
    
    // configuration
    parameters p;
    p.numberOfTransitions = 2;
    p.setsToCompute = 10;
    p.timeHorizon = 1;
    p.timeStep = 0.01;
    
    options opt;
    opt.angle = PI_UP/2;
    opt.precision = 10000;
    
    // start analysis (preprocessing & flowpipe construction)
    reachabilityAnalysis.start(model, p, opt, initialConstraints, operator_e::LEQ, initialconstraintValues, U);

    // clean heap
    delete U;
    delete model;    // TODO: delete all parts of the model
}


#endif

}
