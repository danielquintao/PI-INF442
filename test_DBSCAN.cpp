#include"DBSCAN.hpp"
#include"point.hpp"
#include<iostream>
#include<fstream>

void load(std::ifstream &is, point* points, int n_points) {
    int idx = 0;
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
}

void generate_classified_output(DBSCAN& dbscan) {

    std::ofstream os;
    os.open("./output/test_DBSCAN_output.txt");
    for(int i = 0; i < dbscan.n; i++)
    {
        for(int m = 0; m < point::get_dim(); m++)
        { 
            os << dbscan.pa[i][m] << " ";
        }
        os << dbscan.clusters[i] <<"\n";
    }
    os.close();
    std::cout << "output file generated \nformat : coord_1 coord_2 ... coord_d cluster\n";
}

int main() {

    // 2 first coordinates from the most known iris dataset example from TD05
    std::ifstream is("data/irisFirst2Coordinates.txt");
    point* points = new point[150];
    load(is, points, 150);
    
    DBSCAN dbscan(150, points);
    dbscan.ComputeDBSCAN(0.2, 5);

    std::cout << "number of clusters: " << dbscan.n_clusters << std::endl;
    //for(int i = 0; i < 150; i++)
    //    std::cout << points[i].coords[0] << " " << points[i].coords[1] << ": cluster " << dbscan.clusters[i] << std::endl;

    generate_classified_output(dbscan);

    return 0;
}