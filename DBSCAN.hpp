#include"point.hpp"
#include <ANN/ANN.h>

class DBSCAN {
public:
    DBSCAN(int n, point* points);
    // DBSCAN(int n, const char* file);
    ~DBSCAN();
    point* PointArray=NULL;
    ANNpointArray pa;
    ANNkd_tree* kdt;
    int n; // number of points
    int n_clusters;
    int* clusters; // -1 = UNCLASSIFIED ; 0 = OUTLIER/NOISE ; >0 = CLUSTER NAME
    void ComputeDBSCAN(double eps, int minpts);
    bool ExpandCluster(int point_idx, int cluster_id, double eps, int minpts);
    double silhouette_p(int pt);
    double silhouette();
};