# INF422 - Project 5

## Xuwen LIU, Daniel QUINTAO DE MORAES

## Classes:

* vertex: graph vertex (has an id)
* point: descendent of vertex; has a static dimension d and a property coords for its coordinates
* graph: graph class; has a list of vertices VertexList and an adjency list structure EdgeList. Several constructors available.
* ERGenerator: descendent of graph for Erdös-Rényi graph (number of vertices and probability threshold given to constructor)
* StrongComponentsDetector: has a method to compute the strongly connected components of a graph with an algorithm by Tarjan
* DBSCAN: applies DBSCAN algorithm on a n-dimensional dataset; also applies some adapted heuristics (as silhouette method)
    * ANN C++ library was used to build kd-tree and make kNN search.

## Other files:

* test_graph_constructor.cpp: test graph constructor with an input file (dataset); run ./test_graph_constructor to see usage
* test_strong-components-detector.cpp: test StrongComponentsDetector with the example from Tarjan's paper
* test_ER-generator.cpp: builds fixed size random ER digraph and prints its adjacency list
* test_graph_strong.cpp : gets graph as file and applies Tarjan algorithm on it; run w/o arg to see usage
* test_strong_components_in_ER.cpp: builds ER digraph of fixed size, then applies Tarjan algorithm on it
* n_componentsXp.cpp: applies Tarjan algorithm on sets of ER-digraphs obtained for differente values of p
* random_points_generator.cpp : generate random 2D datasets with as mush as 20 clusters (each one in normal distribution)
* test_DBSCAN.cpp: gets dataset as file and applies DBSCAN algorithm on it (can generate output file); run w/o arg to see usage
* test_dataset_strong.cpp: gets dataset as file, applies Tarjan algorithm and generates output file
* Makefile: One may need to change it dependind on the ANN library location

## Sample data

We present already some data, namely :

* coordinates_USA_road_NY.txt (dataset) - http://users.diag.uniroma1.it/challenge9/download.shtml
* US_road_NY.txt (weighted graph) - http://users.diag.uniroma1.it/challenge9/download.shtml
* data_1000.txt (and data_5000.txt, data_10000.txt) - sample 2D datasets that can be constructed with random_points_generator.cpp
* double_spiral.txt : dataset from TD05
* irisFirst2Coordinates.txt - sample extracted from the great iris dataset
* Email-EuAll.txt : EU email communication network (access in http://snap.stanford.edu/data/email-EuAll.html)
    * Directed graph (each unordered pair of nodes is saved once): Email-EuAll.txt 
    * Email network of a large European Research Institution (directed edge means at least one email was sent between October 2003 and March 2005)
    * Nodes: 265214 Edges: 420045
    * P.S.: This is an interesting graph to test with test_graph_strong. We found the correct value of 34203 nodes in the largest strongly connected component (check SNAP description)
* WikiTalk.txt : Wikipedia Talk network (access in http://snap.stanford.edu/data/wiki-Talk.html)
    * Directed graph (each unordered pair of nodes is saved once): WikiTalk.txt 
    * Communication network of Wikipedia (till January 2008). Directed edge A->B means user A edited talk page of B.
    * Nodes: 2394385 Edges: 5021410
    * P.S.: This is an interesting graph to test with test_graph_strong. We found the correct value of 111881 nodes in the largest strongly connected component (check SNAP description)