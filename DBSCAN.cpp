#include"DBSCAN.hpp"
#include"point.hpp"
#include <ANN/ANN.h>
#include<queue>

DBSCAN::DBSCAN(int n, point* points) {
    pa = annAllocPts(n, point::get_dim());
    for(int i = 0; i < n; i++)
    {
        pa[i] = points[i].coords;
    }
    kdt = new ANNkd_tree(pa, n, point::get_dim());
    
    this->n = n;
    clusters = new int[n];
    for(int i = 0; i < n; i++)
    {
        clusters[i] = -1;
    }
}

DBSCAN::~DBSCAN() {
    annDeallocPts(pa);
    delete[] clusters;
    delete kdt;
}

bool DBSCAN::ExpandCluster(int point_idx, int cluster_id, double eps, int minpts)
{
    // to use ANN to make a fixed-radius search, its manual recommends to run
    // annkFRSearch with k = 0. Its output is the number of points within the
    // chosen boundary. Next, we run a knn algorithm with that parameter:
    ANNidxArray nn_idx = new ANNidx[1];
    int k = kdt->annkFRSearch(pa[point_idx], eps * eps, 0, nn_idx, nullptr, 0.0);
    // k = number of points in eps-neighbourhood of point of index point_idx

    if(k < minpts)
    {
        clusters[point_idx] = 0; // NOISE
        return false;
    }

    delete[] nn_idx;
    nn_idx = new ANNidx[k]; // indexes ANN array = nearest neighb. pos.
    ANNdistArray trash_dd = new ANNdist[k];
    kdt->annkSearch(pa[point_idx], k, nn_idx, trash_dd, 0.0);

    // point of index point_idx is a core point and we add neighbours to the cluster :
    for(int i = 0; i < k; i++)
    {
        clusters[nn_idx[i]] = cluster_id;
        // obs : nn_idx[0] = point_idx (closest point to itself)
    }

    // creating auxiliary structure "queue" to look for reachable points
    std::queue<int> seed;
    for(int i = 0; i < k; i++) seed.push(nn_idx[i]);
    seed.pop(); // remove point_idx (we could do it above but we look for clarity)

    while(!seed.empty())
    {
        int current = seed.front();
        int k2 = kdt->annkFRSearch(pa[current], eps * eps, 0, nn_idx, nullptr, 0.0);
        delete[] nn_idx;
        delete[] trash_dd;
        nn_idx = new ANNidx[k2];
        trash_dd = new ANNdist[k2];
        kdt->annkSearch(pa[current], k2, nn_idx, trash_dd, 0.0);

        if(k2 >= minpts)
        {
            for(int i = 1; i < k2; i++) // starting in 1 == not to include 'current'
            {
                int result_p = nn_idx[i];
                if(clusters[result_p] == -1 || clusters[result_p] == 0)
                {
                    if(clusters[result_p] == -1) // if point was not yet visited (a.k.a. UNCLASSIFIED)
                    {
                        seed.push(result_p);
                    }
                    clusters[result_p] = cluster_id;
                }
            }
        }

        seed.pop(); // remove 'current'
    }

    return true;
}

void DBSCAN::ComputeDBSCAN(double eps, int minpts) {
    int cluster_id = 1;
    for(int i = 0; i < n; i++)
    {
        if(clusters[i] == -1) // UNCLASSIFIED
        {
            if(ExpandCluster(i, cluster_id, eps, minpts))
                cluster_id++;
        }
    }
}