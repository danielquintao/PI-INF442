#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <random>


int main(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    int n=10000; //number of points
    int nc=rand()%20+1; //number of centers
    double x[nc];
    double y[nc];
    double sigma[nc];
    double xx,yy;
    //std::cout<<nc<<std::endl;
    for(int j=0;j<nc;j++){
        x[j]=rand()/(float)RAND_MAX*100000;
        y[j]=rand()/(float)RAND_MAX*100000;
        do{
         sigma[j]=rand()/(float)RAND_MAX*1000;
        }while(sigma[j]==0);
    }
    std::default_random_engine generator;
    int gauss;
    std::ofstream myfile;
    myfile.open ("data/data_10000.txt");
    for (int i=0;i<n;i++) {
        std::cout<<i<<std::endl;
        gauss=rand()%nc;
        std::normal_distribution<double> distribution(x[gauss],sigma[gauss]);
        xx=distribution(generator);
        std::normal_distribution<double> distribution2(y[gauss],sigma[gauss]);
        yy=distribution2(generator);
        myfile <<xx<<" "<<yy<<"\n";
	}
    myfile.close();
	return 0;
}