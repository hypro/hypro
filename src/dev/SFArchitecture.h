#include <iostream>
#include <string>
#include <vector>

//Parent class
class Node {
private:
	//Just some value to test if value of correct class was called
	int m = 0;
public: 
	Node(){}
	virtual ~Node(){}
	virtual int evaluate() {return m;}
};

//Specialized subclass of SumOp for sum operator
class SumOp : public Node {
private:
	int m = 2;
public:
	SumOp(){}
	~SumOp(){}
	int evaluate(){ return m; }
};

//Another still templated subclass of Node
template<typename Rep> 
class Leaf : public Node {
private:
	Rep member;
	int m = 3;
public:
	Leaf() : member(Rep()) {}
	Leaf(Rep r) : member(r) {}
	~Leaf(){}
	int evaluate(){ return m; }
	Rep say(){ return member; }
};

//Support Function Content, N = Node
template<typename N>
class SFC {
private:
	std::vector<N*> children;
public:
	SFC() : children(std::vector<N*>()) {}
	SFC(std::vector<N*> v) : children(v) {}
	void add(N* n){
		children.push_back(n);
	}
	std::vector<N*> getChildren(){
		return children;
	}
};

//Support Function
template<typename N>
class SF {
private:
	SFC<N>* content;
public:
	SF(){}
	SF(SFC<N>* c) : content(c) {}
	void listAllDirectChildren(){
		for(auto ch : content->getChildren()){
			std::cout << ch->evaluate() << "," << std::endl;
		}
	}
};
