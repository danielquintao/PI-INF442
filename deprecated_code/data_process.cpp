#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <stdio.h>


void process(char const* file){
    std::ifstream fin(file);
	
	if (fin.fail()) {
		std::cout<<"Cannot read from file "<<file<<" !"<<std::endl;
		exit(1);
	}
	
    std::string line, word, temp; 
    std::ofstream myfile;
    myfile.open ("data/US_road_NY.txt");
    while (getline(fin, line)) {
        std::stringstream s(line);
        s>>word;
        while (s>>word) { 
            myfile <<word<<" ";
        }       
         myfile <<"\n";
	}
    myfile.close();
	
	fin.close();
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }

	process(argv[1]);

    


    return 0;
}
