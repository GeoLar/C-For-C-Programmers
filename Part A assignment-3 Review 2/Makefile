

out: Edge.o EdgeWeightedGraph.o MinimumSpanningTree.o test.o
	g++ -o out -Wall -Werror -Wunused -pedantic -std=c++17 Edge.o EdgeWeightedGraph.o MinimumSpanningTree.o test.o


test.o: test.cpp
	g++ -Wall -Werror -Wunused -pedantic -std=c++17 -c test.cpp

MinimumSpanningTree.o: MinimumSpanningTree.hpp MinimumSpanningTree.cpp
	g++ -Wall -Werror -Wunused -pedantic -std=c++17 -c MinimumSpanningTree.cpp

EdgeWeightedGraph.o: EdgeWeightedGraph.hpp EdgeWeightedGraph.cpp
	g++ -Wall -Werror -Wunused -pedantic -std=c++17 -c EdgeWeightedGraph.cpp

Edge.o: Edge.hpp Edge.cpp
	g++ -Wall -Werror -Wunused -pedantic -std=c++17 -c Edge.cpp

clear:
	rm *.o
