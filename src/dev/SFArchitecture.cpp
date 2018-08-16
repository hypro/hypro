#include "SFArchitecture.h"

using namespace std;

int main(){

	//Operations
	SumOp sumOp;
	cout << "sumOp evaluates: " << sumOp.evaluate() << " and should be 2" << endl;

	//Leaf test
	string blub = "blub";
	Leaf<string> leaf(blub);
	cout << "leaf evaluates: " << leaf.evaluate() << " and should be 3" << std::endl;
	cout << "leaf says: " << leaf.say() << std::endl;

	//Make raw pointers to sumOp and l
	SumOp* sptr = &sumOp;
	Leaf<string>* lptr = &leaf;

	//Put everything into SFC
	SFC<Node> sfc;
	sfc.add(sptr);
	sfc.add(lptr);
	cout << "scf evaluate is: ";
	for(Node* n : sfc.getChildren()){
		cout << n->evaluate() << ",";
	}
	cout << endl << " and should be 2,3\n";

	//Make raw pointers to sumOp and l
	SumOp* sptr2 = &sumOp;
	Leaf<string>* lptr2 = &leaf;

	//Put everything into SFC
	SFC<Node> sfc2;
	sfc2.add(sptr2);
	sfc2.add(lptr2);
	SF<Node> sf(&sfc2);
	std::cout << "SupportFunction sf has children sumOp (2) and leaf (3). sf.listAllDirectChildren() gives: \n"; 
	sf.listAllDirectChildren();

}