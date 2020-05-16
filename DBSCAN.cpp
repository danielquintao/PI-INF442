#include"DBSCAN.hpp"
#include"point.hpp"
#include <ANN/ANN.h>
#include<queue>
#include<iostream>

DBSCAN::DBSCAN(int n, point* points) {
    pa = annAllocPts(n, point::get_dim());
    PointArray=points;
    for(int i = 0; i < n; i++)
    {
        for(int m = 0; m < point::get_dim(); m++)
        {
            pa[i][m] = points[i].coords[m];
        }
    }
    kdt = new ANNkd_tree(pa, n, point::get_dim());

    this->n = n;
    clusters = new int[n];
    for(int i = 0; i < n; i++)
    {
        clusters[i] = -1;
    }
    n_clusters = 0;
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
    n_clusters = cluster_id-1;
}

double DBSCAN::silhouette_p(int pt){//index of point in PointArray
    if(clusters[pt]>0){
        double ap=0;
        double bp=0;
        int na=0;
        int nb[n_clusters+1];
        double b_dist[n_clusters+1];
        nb[clusters[pt]]=0;
        b_dist[clusters[pt]]=0;
        for(int i=0;i<n;i++){
            if(i==pt) continue;
            if(clusters[i]==clusters[pt]){
                na++;
                ap+=PointArray[pt].dist(PointArray[i]);
            }
            else{
                b_dist[clusters[i]]+=PointArray[pt].dist(PointArray[i]);
                nb[clusters[i]]++;
            }
        }
        ap=ap/(float)na;
        b_dist[0]=b_dist[0]/(float)nb[0];
        bp=b_dist[0];
        for(int j=1;j<n_clusters+1;j++){
            if(j==clusters[pt]) continue;
            else
            {
                b_dist[j]=b_dist[j]/(float)nb[j];
                if(bp>b_dist[j]){
                    bp=b_dist[j];
                }
            }
            
        }
        if(ap>bp){
            return(bp-ap)/ap;
        }
        else{
            return (bp-ap)/bp;
        }
    }
    else{
        return 0;
    }
    
}

double DBSCAN::silhouette(){
    int n_no_noise=0;
    int s=0;
    for(int i=0;i<n;i++){
        if(clusters[i]>0){
            s+=silhouette_p(i);
            n_no_noise++;
        }
    }
    return s/(float)n_no_noise;
}