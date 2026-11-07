#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include "Cube.h"
#include "Algorithm_Reader.h"

int main(int argc, char* argv[]) {
    std::string FILEPATH = "";
    for(int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "--file") {
            if(i == argc-1) {
                std::cerr<<"ERROR: No File Path Specified"<<std::endl;
                return -1;
            }
            FILEPATH = argv[i+1];
        }
    }
    if(!FILEPATH.empty()) {
        std::ifstream file(FILEPATH);
        if(!file.is_open()) {
            std::cerr<<"ERROR: Could Not Open File"<<std::endl;
            return -1;
        }
        std::string current_line;
        int current = 0;

        int cubesize;
        std::string algorithm;

        while(std::getline(file, current_line)) {
            if(current_line.empty()) continue;

            if(current == 0) {
                std::stringstream current_stream(current_line);
                current_stream >> cubesize;
            }
            else if(current == 1) {
                algorithm = current_line;
                break;
            }
            current++;
        }        
        Cube cube = Cube(cubesize);
        Algorithm_Reader alg = Algorithm_Reader();
        alg.parse(algorithm, cube);
        cube.print();
        return 0;
    }
    int size;
    std::cout<<"Enter Cube Size: ";
    std::cin>>size;
    std::cout<<std::endl;

    using piece_map = std::unordered_map<Eigen::Vector3f, std::unique_ptr<pieces::Piece>, matrix_hash<Eigen::Vector3f>>;
    std::unordered_map<int, piece_map> States; //NOT CURRENTLY USED

    Cube cube = Cube(size);
    Algorithm_Reader alg = Algorithm_Reader();
    std::string input;
    cube.print();

    while(true) {
        std::cout<<"Enter Algorithm: ";
        std::getline(std::cin>>std::ws, input);
        std::cout<<std::endl;
        if(input == "quit") break;
        alg.parse(input, cube);
        cube.print();
        std::cout<<States.size()<<std::endl;
    }

    std::cin.get();
    
    return 0;
}