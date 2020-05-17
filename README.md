# INF422 - Project 5

## Xuwen LIU, Daniel QUINTAO DE MORAES

## Classes:

* vertex: graph vertex (has an id)
* point: descendent of vertex; has a static dimension d and a property coords for its coordinates
* graph: graph class; has a list of vertices VertexList and an adjency list structure EdgeList. Several constructors available.
* ERGenerator: descendent of graph for Erdös-Rényi graph (number of vertices and probability threshold given to constructor)
* StrongComponentsDetector: has a method to compute the strongly connected components of a graph with an algorithm by Tarjan
* DBSCAN: applies DBSCAN algorithm on a n-dimensional dataset; also applies some adapted heuristics (as silhouette method)

## Files:

* test_graph_constructor.cpp: test graph constructor with an input file (dataset); run ./test_graph_constructor to see usage
* test_strong-components-detector.cpp: test StrongComponentsDetector with the example from Tarjan's paper
* test_ER-generator.cpp: builds fixed size random ER digraph and prints its adjacency list
* test_strong_components_in_ER.cpp: builds ER digraph of fixed size, then applies Tarjan algorithm on it
* n_componentsXp.cpp: applies Tarjan algorithm on sets of ER-digraphs obtained for differente values of p
* test_DBSCAN.cpp: gets dataset as file and applies DBSCAN algorithm on it (can generate output file); run w/o arg to see usage
* test_dataset_strong.cpp: gets dataset as file, applies Tarjan algorithm and generates output file
