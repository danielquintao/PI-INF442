#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "point.hpp"
#include<iterator>
graph::graph(){
    
}

graph::~graph() { }

graph::graph(char const* file) {
    std::ifstream is(file);
    if (is.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
    int max_id = 0;
    while(is.peek() != EOF)
	{

		int v1, v2;
        is >> v1 >> v2;

        if(v1 > max_id) max_id = v1;
        if(v2 > max_id) max_id = v2;

        if(!HasVertex(v1)){
            vertex p;
            p.id=v1;
            AddVertex(p);
        }

        if(!HasVertex(v2)){
            vertex p;
            p.id=v2;
            AddVertex(p);
        }

        AddEdge(VertexList[v1], VertexList[v2]);

		// consume \n :
		is.get();
        // std::cout << idx-1 << ": " << points[idx-1].coords[0] << " " << points[idx-1].coords[1] << std::endl;
	}

    for(int i = 0; i <= max_id; i++)
    {
        if(!HasVertex(i)) {
            vertex p;
            p.id = i;
            AddVertex(p);
        }
    }
}

graph::graph(char const* file, bool start_in_zero){
    std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
	int max_index;
    int start = 0;
    std::string line, word, temp; 
    int count_line;
    if(!start_in_zero) start  =1;
    count_line = start;
    max_index = count_line;
    while (getline(fin, line)) {
        if(!HasVertex(count_line)){
            vertex p;
            p.id=count_line;
            AddVertex(p);
        }
        std::stringstream s(line);
        while (s>>word) { 
            int val = std::atoi(word.c_str());
            if(!HasVertex(val)){
                vertex q;
                q.id=val;
                AddVertex(q);
                AddEdge(VertexList[count_line],VertexList[val]);
            }
            else{
                AddEdge(VertexList[count_line],VertexList[val]);
            }
            if(val > max_index) max_index = val;
        }       
		count_line ++;
	}

    max_index = std::max(count_line-1, max_index);
    for(int i = start; i <= max_index; i++)
    {
        if(!HasVertex(i)) {
            vertex p;
            p.id = i;
            AddVertex(p);
        }
    }
	
	fin.close();
}

graph::graph(char const* file, double eps, int dim){
    std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
    std::string line,word; 
    if (dim==0){
        while (getline(fin, line)) {
            std::stringstream s(line);
            int position=0;
            int pid,qid;
            double dist;
            while (s>>word){
                if(position==0){
                    pid = std::atoi(word.c_str()); 
                }
                else if(position==1){
                    qid = std::atoi(word.c_str()); 
                }
                else{
                    dist=std::atof(word.c_str());
                }
                position++;
            }
            if(!HasVertex(pid)){
                vertex p;
                p.id=pid;
                AddVertex(p);
            }
            if(!HasVertex(qid)){
                vertex q;
                q.id=qid;
                AddVertex(q);
            }
            if(dist<eps){
                AddEdge(VertexList[pid],VertexList[qid]);
            }

        }
    }   
    else{
        //std::unordered_map<int,point> PointList;
        int n=1000000;//need to change if there are really too many points
        point* pts=new point[n];
        int count_line=0;
        while (getline(fin, line)) {
            std::stringstream s(line);
            int position=0;
            pts[count_line].id=count_line;
            //point pt;
            //pt.id=count_line;
            //PointList[pt.id]=pt;
            while (s>>word){
                //PointList[pt.id].coords[position]=std::atof(word.c_str());
                pts[count_line].coords[position]=std::atof(word.c_str());
                position++;
            }
            AddVertex(pts[count_line]);
            count_line++;
        }

        for(int i=0;i<count_line;i++){
            for(int j=0;j<count_line;j++){
                if(i!=j && pts[i].dist(pts[j])<eps){
                    AddEdge(VertexList[i],VertexList[j]);
                }
            }
        }
	}
	fin.close();
}

void graph::AddVertex(vertex& p){
    VertexList[p.id]=p;
}

bool graph::HasVertex(int id){
    return (VertexList.find(id)!=VertexList.end());
}

void graph::AddEdge(vertex& p,vertex& q){
    EdgeList[&p].insert(&q);
}

void graph::RemoveEdge(vertex& p,vertex& q){
    EdgeList[&p].erase(&q);
}

bool graph::HasEdge(vertex& p, vertex& q){
    if(EdgeList[&p].find(&q)==EdgeList[&p].end()){
        return false;
    }
    else
    {
        return true;
    }
    
}