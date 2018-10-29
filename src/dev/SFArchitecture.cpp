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
	//		binOp (sum)
	//    /		 		\
	// traOp (5x-10)    leaf2 (2)
	//   |
	// leaf1 (2)
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

	// Evaluation procedure should be:
	// - Input: 3
	// - Give to trafoOp: 5*3-10 = 5
	// - When reaching leaf1: [5,5]
	// - Forward result to trafoOp: [5*5-10,5*5-10] = [15,15]
	// - SumOp gets [15,15] from trafoOp and [3,3] from leaf2, so summed up: [18,18]
	// Endresult: [18,18]

	cout << "TESTING TRAVERSAL \n";
	Matrix mat(3);
	auto tmp = sfc.evaluate(mat);
	std::cout << "[";
	for(EvalResult e : tmp){
		std::cout << e << ",";
	}
	std::cout << "]\n";

	sfc.functionTest();

	return 0;
}