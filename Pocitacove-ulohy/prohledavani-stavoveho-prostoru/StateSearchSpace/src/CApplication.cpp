//
// Created by kucerj56 on 20.02.21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "CApplication.hpp"
#include "CCoordinates.hpp"

CApplication::CApplication() {}

CApplication::~CApplication() {

}

void CApplication::start() {
    //get map file name
    loadMap();

    //chose algorithm

    //loop
    //run algorithm step
    //show changes


}

void CApplication::loadMap() {
    //gets name of file with map from user
    std::string mapFileName = getMapFileName();

    //map =

}

std::string CApplication::getMapFileName() {
    bool invalidInput = true;
    std::string mapFileName;

    std::cout << "Enter name of file with map: " << std::endl;
    while (invalidInput) {
        std::cin >> mapFileName;
        std::ifstream inputStream;
        inputStream.open(MAP_FILE + mapFileName);
        if (inputStream.is_open() && inputStream.good()) {
            invalidInput = false;
        } else {
            std::cout << "Invalid file path, enter a valid one: " << std::endl;
        }
        inputStream.close();
    }


    return mapFileName;
}

void CApplication::getMap(const std::string& mapFileName) {
    std::string line;
    std::vector<std::string> map;
    CCoordinates start;
    CCoordinates end;
    int x, y;

    std::ifstream inputStream;
    inputStream.open(MAP_FILE + mapFileName);

    while (getline(inputStream, line)) {
        switch (line[0]) {
            case 'X':
                map.emplace_back(line);
                break;
            case 's':
                sscanf(line.c_str(), "start %d, %d", &x, &y);
                start.m_X = x;
                start.m_Y = y;
                map[y][x] = 'S';
                break;
            case 'e':
                sscanf(line.c_str(), "end %d, %d", &x, &y);
                end.m_X = x;
                end.m_Y = y;
                map[y][x] = 'E';
                break;
            default:
                throw std::runtime_error("Incorrect map format");
        }
    }
    inputStream.close();

    m_Map = std::make_shared<CMap>(map, start, end);
}
