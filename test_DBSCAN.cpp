#include"DBSCAN.hpp"
#include"point.hpp"
#include"vertex.hpp"
#include<iostream>
#include<fstream>

void load(std::ifstream &is, point* points, int& n_points) {
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
    n_points = idx;
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

int main(int argc, char const *argv[]) {

    if ( (argc != 5 && argc != 8) || (argc == 8 && (std::atoi(argv[2]) != -1 && std::atoi(argv[2]) != -2) ) ) {
        std::cout << "Usage: " << std::endl;
         std::cout << argv[0] << " <file> <eps> <Minpts> <dimension> applies DBSCAN once with these arguments" << std::endl;
         std::cout << argv[0] << " <file> -1 <MinPts> <start> <end> <step> <dimension> applies DBSCAN with adapted silhouette method on EPS" << std::endl;
         std::cout << argv[0] << " <file> -2 <eps> <start> <end> <step> <dimension> applies DBSCAN with adapted silhouette method on MINPTS" << std::endl;
        return 1;
    }

    // 2 first coordinates from the most known iris dataset example from TD05
    std::ifstream is(argv[1]);
    if(argc == 5)
        point::d = std::atoi(argv[4]);
    else
        point::d = std::atoi(argv[7]);
    point* points = new point[1000000];
    int n_points;
    load(is, points, n_points);
    
    DBSCAN dbscan(n_points, points);

    if(argc == 5)
    {
        double eps = std::atof(argv[2]);
        int minpts = std::atoi(argv[3]);
        dbscan.ComputeDBSCAN(eps, minpts);
        std::cout << dbscan.n_clusters << " clusters found" << std::endl;
        generate_classified_output(dbscan);
    }

    else if(std::atoi(argv[2]) == -1)
    {
        double start = std::atof(argv[4]);
        double step = std::atof(argv[6]);
        double end = std::atof(argv[5]) + step;
        int minpts = std::atoi(argv[3]);
        std::cout << "silhouette X eps (P.S. eps too small -> no cluster -> s = awkward value)" << std::endl;
        for(double eps = start; eps < end; eps += step){
            dbscan.ResetDBSCAN();
            dbscan.ComputeDBSCAN(eps, minpts);
            std::cout<< "eps: " << eps << ", minpts: " << minpts << ", number of clusters: " << dbscan.n_clusters << ", s: "<<dbscan.silhouette();
            std::cout<< ", s_modified: "<<dbscan.non_convex_silhouette(minpts)<<std::endl;
        }
    }
    
    else if(std::atoi(argv[2]) == -2)
    {
        double start = std::atof(argv[4]);
        double step = std::atof(argv[6]);
        double end = std::atof(argv[5]) + step;
        double eps = std::atof(argv[3]);
        std::cout << "silhouette X minpts (P.S. minpts too big -> no cluster -> s = awkward value)" << std::endl;
        for(int minpts = start; minpts < end; minpts += step){
            dbscan.ResetDBSCAN();
            dbscan.ComputeDBSCAN(eps, minpts);
            std::cout<< "eps: " << eps << ", minpts: " << minpts << ", number of clusters: " << dbscan.n_clusters << ", s: "<<dbscan.silhouette();
            std::cout<< ", s_modified: "<<dbscan.non_convex_silhouette(minpts)<<std::endl;
        }
    }
    

    return 0;
}