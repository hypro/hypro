#include "SFArchitecture.h"

using namespace std;

int main(){

	std::cout << "TESTING BUILDING OF TREE\n";

	//Operations
	TrafoOp traOp;
	cout << "Unary operator traOp evaluates to type: " << traOp.getType() << " and should be 1" << endl;
	cout << "traOp unary? " << traOp.isItUnary() << endl;

	SumOp sumOp;
	cout << "Binary operator sumOp evaluates to type: " << sumOp.getType() << " and should be 2" << endl;

	//Leaf test
	string blub = "blub";
	Leaf<string> leaf1(blub);
	cout << "leaf1 evaluates to type: " << leaf1.getType() << " and should be 3" << endl;
	cout << "leaf1 says: " << leaf1.say() << std::endl;

	//Leat 2
	string bam = "bam";
	Leaf<string> leaf2(blub);

	//Make raw pointers to sumOp and l
	TrafoOp* tptr = &traOp;
	SumOp* sptr = &sumOp;
	Leaf<string>* l1ptr = &leaf1;
	Leaf<string>* l2ptr = &leaf2;

	//Put everything into SFC. Tree looks like
	//		
	//		binOp
	//    /		 \
	// traOp    leaf2
	//   |
	// leaf1
	//

	SFC sfc(l1ptr);
	sfc.addUnaryOp(tptr);
	
	//For testing: only make support function with content leaf2. 
	SFC sfc2(l2ptr);
	SF sf2(&sfc2);
	cout << "Made sf2 with only leaf2 of type " << sfc2.getRoot()->getType() << ". underlying tree of sf2 is: ";
	sf2.listUnderlyingTree();

	//Finish building the tree
	sfc.RootGrowTree::addBinaryOp(sptr, &sfc2);
	
	cout << "Made sfc with bigger tree structure. sfc is:\n" << sfc << endl;
	
	//Make raw pointers to sumOp and traOp
	SumOp* sptr2 = &sumOp;
	TrafoOp* tptr2 = &traOp;

	//Put everything into SFC
	SF sf(&sfc);
	cout << "All direct children of sf are of type: \n";
	sf.listAllDirectChildren();
	cout << "underlying tree of sf is: \n";
	sf.listUnderlyingTree();

	//Traversal Test
	cout << "TESTING TRAVERSAL AND TEMPLATES\n";
	std::function<void(int)> f1 = RootGrowTree::prepareStack;
	//sfc.traverse<void,int>(f1, 2000);
	std::function<int(float)> f2 = RootGrowTree::accumulate;
	//sfc.traverse<int,int>(f2, 1000);
	std::function<void()> f3 = RootGrowTree::test;

	auto f1Param = std::make_tuple(1000);
	auto f2Param = std::make_tuple(2000.0f);
	auto f3Param = std::make_tuple();
	traOp.execute<void,int>(f1, f1Param);
	auto m = traOp.execute<int,float>(f2, f2Param);
	std::cout << "Indeed! f2 returned: " << m << std::endl;
	traOp.execute<void>(f3, f3Param);


	cout << "TESTING TRAVERSAL \n";
	traOp.traverse(f1, f1Param, f2, f2Param, f3, f3Param);

	cout << "TESTING EVALUATION \n";
	Matrix mat(3);
	sfc.evaluate(mat);


}