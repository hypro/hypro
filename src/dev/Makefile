.PHONY: clean

CXXFLAGS := -std=c++17

test: RootGrowTree.o SFArchitecture.o
	g++ $(CXXFLAGS) -o test RootGrowTree.o SFArchitecture.o

SFArchitecture.o: SFArchitecture.h SFArchitecture.cpp 
	g++ $(CXXFLAGS) -c SFArchitecture.h SFArchitecture.cpp 

RootGrowTree.o: RootGrowNode.h RootGrowTree.h RootGrowTree.cpp
	g++ $(CXXFLAGS) -c RootGrowNode.h RootGrowTree.h RootGrowTree.cpp

clean:
	rm -f *.o
	rm -f *.gch