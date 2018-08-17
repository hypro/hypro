test: RootGrowTree.o SFArchitecture.o
	g++ -o test RootGrowTree.o SFArchitecture.o

SFArchitecture.o: SFArchitecture.h SFArchitecture.cpp 
	g++ -c SFArchitecture.h SFArchitecture.cpp 

RootGrowTree.o: RootGrowNode.h RootGrowTree.h RootGrowTree.cpp
	g++ -c RootGrowNode.h RootGrowTree.h RootGrowTree.cpp