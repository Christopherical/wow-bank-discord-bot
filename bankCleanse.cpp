#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "json.hpp"
#include <set>

using json = nlohmann::json;

int main() {
    std::string line;
    std::vector<std::string> myLines;
    std::ifstream myfile("bankDump.txt");
    while (std::getline(myfile, line)){
        myLines.push_back(line);
    }
    myLines.pop_back();

    std::vector<std::string> ree = {};
    for(int i = 4; i < myLines.size(); i++){
        if(myLines[i][1] != '{' && myLines[i][1] != '}'){
            ree.push_back(myLines[i]);
        }
    }

    std::vector<std::string> ree2 = {};
    for(int i = 0; i < ree.size(); i++){
        if(ree[i][1] != '{' && ree[i][1] != '}'){
            ree2.push_back(ree[i]);
        }
    }
    std::vector<std::string> ree3 = {};
    for(int i = 0; i < ree2.size(); i++){
        if(ree2[i].find("No Item") != std::string::npos){
            continue;
        }
        ree3.push_back(ree2[i]);

    }

    // Removes the tabs of all of it (move up TODO)
    for(int i = 0; i < ree3.size(); i++){
        ree3[i].erase(std::remove(ree3[i].begin(), ree3[i].end(), '\t'), ree3[i].end()); // Removes the tabs
    }

    std::vector<std::string> ree4 = {};
    for(int i = 0; i < ree3.size(); i++){
        if(i % 2 == 0){
            std::string str2 = ree3[i].substr(ree3[i].find("[")+1);
            std::size_t posSecond = str2.find("]");
            std::string mystr = str2.substr(0, str2.find("]", 0));
            ree4.push_back(mystr);
        }
        else{
            std::string mystr = ree3[i].substr(0, ree3[i].find(",", 0));
            ree4.push_back(mystr);
        }
    }



    std::map<std::string, int> my_map = {};
    for(int i = 0; i < ree4.size(); i+=2){
        if(!my_map[ree4[i]]){
            my_map[ree4[i]] = stoi(ree4[i+1]); 

        }
        else{
            my_map[ree4[i]] = my_map[ree4[i]] + stoi(ree4[i+1]);
        }
    }

    std::set<std::string> keepSet= {
        "Abyss Crystal",
        "Dream Shard",
        "Greater Cosmic Essence",
        "Infinite Dust",
        "Fish Feast",
        "Nettlefish",
        "Musselback Sculpin",
        "Glacial Salmon",
        "Northern Spices",
        "Red Power Crystal",
        "Blue Power Crystal"
    };

    // Twice?? TODO
    for (auto  lol : my_map){
        if (keepSet.find(lol.first) == keepSet.end()) {
            my_map.erase(lol.first);
        }
    }
    for (auto  lol : my_map){
        if (keepSet.find(lol.first) == keepSet.end()) {
            my_map.erase(lol.first);
        }
    }


    for (auto const& x : my_map){
        std::cout << x.first  // string (key)
                << ':' 
                << x.second // string's value 
                << std::endl;
    }

    return 0;
}