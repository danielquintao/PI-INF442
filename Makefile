CXX = g++
CXXFLAGS = -Wall -g

test_strong-components-detector: test_strong-components-detector.o strong-components-detector.o graph.o vertex.o
	$(CXX) $(CXXFLAGS) -o test_strong-components-detector test_strong-components-detector.o strong-components-detector.o graph.o vertex.o

test_strong-components-detector.o: strong-components-detector.cpp graph.hpp vertex.hpp
	$(CXX) $(CXXFLAGS) -c test_strong-components-detector.cpp

strong-components-detector.o: strong-components-detector.hpp graph.hpp vertex.hpp

test_ER: test_ER.o graph.o vertex.o $(CXX) $(CXXFLAGS) -o test_ER test_ER.o graph.o vertex.o
test_ER.o: test_ER.cpp $(CXX) $(CXXFLAGS) -c  graph.hpp vertex.hpp

graph.o: graph.hpp vertex.hpp

vertex.o: vertex.hpp

