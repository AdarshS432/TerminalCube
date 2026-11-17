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
    bool color_enabled = true;
    for(int i = 0; i < argc; i++) {
        std::string arg = argv[i];
        if(arg == "--file") {
            if(i == argc-1) {
                std::cerr<<"ERROR: No File Path Specified"<<std::endl;
                return -1;
            }
            FILEPATH = argv[i+1];
        }
        if(arg == "--nocolor") {
            color_enabled = false;
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
        cube.print(color_enabled);
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
    cube.print(color_enabled);

    while(true) {
        std::cout<<"Enter Algorithm: ";
        std::getline(std::cin>>std::ws, input);
        std::cout<<std::endl;
        if(input == "quit") break;
        alg.parse(input, cube);
        cube.print(color_enabled);
    }

    std::cin.get();
    
    return 0;
}
/*
int main() {
    int max_moves = 3674160;

    const char* FILEPATH = "/home/adarsh/Projects/Cpp/Cube2x2Cases/py/output_characters.txt";
    Cube cube = Cube(2); 
    Algorithm_Reader algreader = Algorithm_Reader();

    using piece_map = std::unordered_map<Eigen::Vector3f, std::unique_ptr<pieces::Piece>, matrix_hash<Eigen::Vector3f>>;
    std::unordered_map<int, piece_map> STATES;

    cube.update_state_on_turns();
    
    std::vector<std::string> alg;
    ifstream file(FILEPATH);
    if(file.is_open()) {
        std::string line;
        while(std::getline(file, line)) {
            std::istringstream iss(line);
            std::string move;
            int count = 0;
            while(iss >> move && count <= max_moves) {
                count++;
                alg.push_back(move);
            }
        }
    } else {
        std::cerr<<"ERROR: File Could Not Be Opened"<<std::endl;
        return -1;
    }
    int k = 0;
    for(std::string move : alg) {
        algreader.parse(move, cube);
        STATES.emplace(k, cube.get_last_state());
        std::cout<<k<<std::endl;
        k++;
    }
    return 0;
}*/