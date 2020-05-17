#include"vertex.hpp"
#include"graph.hpp"
#include"ER-generator.hpp"
#include"strong-components-detector.hpp"

#include<iostream>
#include<algorithm>

int main(int argc, char const *argv[]) {

    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <n_points> <p_step> <n_repetitions>" << std::endl;
        std::cout << "choose dimension = 0 if each row is of the form 'v1' 'v2' 'distance'" << std::endl;
        return 1;
    }

    int n_points = std::stoi(argv[1]);
    double step = std::atof(argv[2]);
    int n_repetitions = std::atoi(argv[3]);

    for(double p = step; p <= 1; p += step)
    {
        double avg_n_components = 0;
        for(int i = 0; i < n_repetitions; i++)
        {
            ERGenerator* g = new ERGenerator(n_points, p);
            StrongComponentDetector* detector = new StrongComponentDetector(n_points-1, g);
            detector->ComputeStrongConnectedComponents();
            avg_n_components += (*std::max_element(detector->component, detector->component + sizeof(detector->component)/sizeof(int)));
            delete g;
            delete detector;
        }
        avg_n_components /= n_repetitions;
        std::cout << p << " " << avg_n_components << std::endl;
    }




    return 0;
}