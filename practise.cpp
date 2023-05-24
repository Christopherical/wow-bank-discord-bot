#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){

    // std::ifstream myInfo("C:\\Program Files (x86)\\World of Warcraft\\_classic_\\WTF\\Account\\ANGELITEWEAPON\\Pyrewood Village\\Naelo\\SavedVariables\\ChronkzBankAddon.lua");

    std::fstream newFile;
    newFile.open("..\\practiseFile.txt", std::ios::in); 

    std::string sa;
    std::vector<std::string> fileVector;

    if(newFile.is_open()){
        while (std::getline(newFile, sa)) {  
            fileVector.push_back(sa); 
        }
    }
    
    for (auto g : fileVector){
        std::cout << g << std::endl;
    }

    return 0;
}