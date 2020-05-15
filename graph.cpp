#include "graph.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include<iterator>
graph::graph(){
    
}

graph::~graph() { }

graph::graph(char const* file){
    std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
	
    std::string line, word, temp; 
    int count_line=0;
    while (getline(fin, line)) {
        // if(count_line<=5){
        //     std::cout<< line<<std::endl;
        // }
        // if(count_line<=5){
        //     std::cout<< count_line<<",";
        // }
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
                // if(count_line<=5){
                //     std::cout<< HasEdge(VertexList[count_line],q)<<" ";
                // }
            }
            else{
                AddEdge(VertexList[count_line],VertexList[val]);
            }
            // if(count_line<=5){
            //     std::cout<< val<<" ";
            // }
        }       
        // if(count_line<=5){
        //         std::cout<<std::endl;
        //     }
		count_line ++;
	}
	
	fin.close();
}

graph::graph(char const* file, double eps){
    std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
	
    std::string line,word; 
    while (getline(fin, line)) {
        // if(count_line<=5){
        //     std::cout<< line<<std::endl;
        // }
        // if(count_line<=5){
        //     std::cout<< count_line<<",";
        // }
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
        if(dist>eps){
            AddEdge(VertexList[pid],VertexList[qid]);
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