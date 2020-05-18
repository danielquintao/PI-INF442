CXX = g++
CXXFLAGS = -Wall -g
ANN_INCLUDE=./ann_1.1.2/include
ANN_LIB=./ann_1.1.2/lib

test_strong_components_in_ER: test_strong_components_in_ER.o strong-components-detector.o ER-generator.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_strong_components_in_ER test_strong_components_in_ER.o strong-components-detector.o ER-generator.o graph.o vertex.o point.o

test_strong_components_in_ER.o: strong-components-detector.hpp ER-generator.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_strong_components_in_ER.cpp

n_componentsXp: n_componentsXp.cpp strong-components-detector.o ER-generator.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o n_componentsXp n_componentsXp.cpp strong-components-detector.o ER-generator.o graph.o vertex.o point.o

test_strong-components-detector: test_strong-components-detector.o strong-components-detector.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_strong-components-detector test_strong-components-detector.o strong-components-detector.o graph.o vertex.o point.o

test_strong-components-detector.o: strong-components-detector.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_strong-components-detector.cpp

test_graph_strong: test_graph_strong.cpp strong-components-detector.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_graph_strong test_graph_strong.cpp strong-components-detector.o graph.o vertex.o point.o

strong-components-detector.o: strong-components-detector.hpp graph.hpp vertex.hpp point.hpp

test_ER-generator: test_ER-generator.o ER-generator.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_ER-generator test_ER-generator.o ER-generator.o graph.o vertex.o point.o

test_ER-generator.o: ER-generator.hpp graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_ER-generator.cpp

ER-generator.o: ER-generator.hpp graph.hpp vertex.hpp point.hpp

test_dataset_strong: test_dataset_strong.cpp strong-components-detector.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_dataset_strong test_dataset_strong.cpp strong-components-detector.o graph.o vertex.o point.o

test_graph_constructor: test_graph_constructor.o graph.o vertex.o point.o
	$(CXX) $(CXXFLAGS) -o test_graph_constructor test_graph_constructor.o graph.o vertex.o point.o

test_graph_constructor.o: graph.hpp vertex.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c test_graph_constructor.cpp

graph.o: graph.hpp vertex.hpp point.hpp vertex.hpp ###

test_DBSCAN: test_DBSCAN.cpp DBSCAN.o point.o vertex.o ###
	$(CXX) $(CXXFLAGS) -I$(ANN_INCLUDE) -o test_DBSCAN test_DBSCAN.cpp DBSCAN.o point.o vertex.o -L$(ANN_LIB) -lANN 

DBSCAN.o: DBSCAN.cpp DBSCAN.hpp point.hpp vertex.hpp ###
	$(CXX) -c -I$(ANN_INCLUDE) $(CXXFLAGS) DBSCAN.cpp 

point.o: point.hpp vertex.hpp ###

vertex.o: vertex.hpp

random_points_generator: random_points_generator.cpp
	$(CXX) $(CXXFLAGS) -o random_points_generator random_points_generator.cpp
