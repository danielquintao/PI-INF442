#include"strong-components-detector.hpp"
#include"graph.hpp"
#include"vertex.hpp"
#include"point.hpp"

#include<iostream>
#include<fstream>
#include<chrono>
#include<algorithm>

int main(int argc, char const *argv[]) {

    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <data_file> <dimension> <eps>" << std::endl;
        std::cout << "choose dimension = 0 if each row is of the form 'v1' 'v2' 'distance'" << std::endl;
        return 1;
    }

    // constructing graph :
    int dim=std::atoi(argv[2]);
    point::d = dim;
    double eps=std::atof(argv[3]);
    auto time1 = std::chrono::high_resolution_clock::now();
    graph g(argv[1],eps,dim);
    auto time2 = std::chrono::high_resolution_clock::now();

    // saving points coordinates to prepare a fancy output file with the clusters
    int idx = 0;
    point* points = new point[g.VertexList.size()];
    std::ifstream is(argv[1]);
	while(is.peek() != EOF)
	{
		// read new points
		for(int m = 0; m < point::get_dim(); m++)
		{
			is >> points[idx].coords[m];
		}
		idx++;
		// consume \n :
		is.get();
        // std::cout << idx-1 << ": " << points[idx-1].coords[0] << " " << points[idx-1].coords[1] << std::endl;
	}
    is.close();

    std::cout << "number of vertices with at least one neighbour:" << g.EdgeList.size() << std::endl;
    std::cout << "total number of vertices :" << g.VertexList.size() << std::endl;

    auto time3 = std::chrono::high_resolution_clock::now();
    StrongComponentDetector detector(g.VertexList.size()-1, &g);
    auto time4 = std::chrono::high_resolution_clock::now();
    detector.ComputeStrongConnectedComponents();
    auto time5 = std::chrono::high_resolution_clock::now();

    std::ofstream os;
    std::string s (argv[1]);
    s+= "strong_output.txt";
    os.open("./output/test_strong_output.txt");
    for(int i = 0; i < (int) g.VertexList.size(); i++)
    {
        for(int m = 0; m < point::get_dim(); m++)
        { 
            os << points[i].coords[m] << " ";
        }
        os << detector.component[i] <<"\n";
    }
    os.close();
    std::cout << "output file generated \nformat : coord_1 coord_2 ... coord_d component\n";
    std::cout << "total of " << (*std::max_element(detector.component, detector.component + sizeof(detector.component)/sizeof(int))) << " components" << std::endl;
    // developer note : due to a deep mistery, using the above expression for retrieving the number of clusters will not work with the file "test_graph_strong" (in that case we used the explicit number of vertices)
    
    std::cout << "time to build graph from dataset: " << std::chrono::duration_cast<std::chrono::milliseconds>(time2-time1).count() << " ms" << std::endl;
    std::cout << "time to tarjan algo (without kd-tree construction): " << std::chrono::duration_cast<std::chrono::milliseconds>(time5-time4).count() << " ms" << std::endl;

    return 0;
}