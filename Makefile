CXX = g++
CXXFLAGS = -Wall -g
ANN_INCLUDE=./ann_1.1.2/include
ANN_LIB=./ann_1.1.2/lib

test_strong_components_in_ER: test_strong_components_in_ER.o strong-components-detector.o ER-generator.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_strong_components_in_ER test_strong_components_in_ER.o strong-components-detector.o ER-generator.o graph.o vertex.o point.o

test_strong_components_in_ER.o: strong-components-detector.hpp ER-generator.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_strong_components_in_ER.cpp

test_strong-components-detector: test_strong-components-detector.o strong-components-detector.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_strong-components-detector test_strong-components-detector.o strong-components-detector.o graph.o vertex.o point.o

test_strong-components-detector.o: strong-components-detector.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_strong-components-detector.cpp

strong-components-detector.o: strong-components-detector.hpp graph.hpp vertex.hpp point.hpp

test_ER-generator: test_ER-generator.o ER-generator.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_ER-generator test_ER-generator.o ER-generator.o graph.o vertex.o point.o

test_ER-generator.o: ER-generator.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_ER-generator.cpp

ER-generator.o: ER-generator.hpp graph.hpp vertex.hpp point.hpp

#test_ER: test_ER.o graph.o vertex.o 
#	$(CXX) $(CXXFLAGS) -o test_ER test_ER.o graph.o vertex.o

#test_ER.o: test_ER.cpp graph.hpp vertex.hpp
#	$(CXX) $(CXXFLAGS) -c test_ER.cpp

test_graph_constructor: test_graph_constructor.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_graph_constructor test_graph_constructor.o graph.o vertex.o point.o

test_graph_constructor.o: graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_graph_constructor.cpp

graph.o: graph.hpp vertex.hpp point.hpp

vertex.o: vertex.hpp

test_DBSCAN: test_DBSCAN.cpp DBSCAN.o point.o
	$(CXX) $(CXXFLAGS) -I$(ANN_INCLUDE) -o test_DBSCAN test_DBSCAN.cpp DBSCAN.o point.o -L$(ANN_LIB) -lANN 

DBSCAN.o: DBSCAN.cpp DBSCAN.hpp point.hpp
	$(CXX) -c -I$(ANN_INCLUDE) $(CXXFLAGS) DBSCAN.cpp 

point.o: point.hpp

clean:
	rm *.o