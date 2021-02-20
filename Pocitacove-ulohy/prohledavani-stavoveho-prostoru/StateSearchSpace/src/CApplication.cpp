//
// Created by kucerj56 on 20.02.21.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "CApplication.hpp"
#include "CCoordinates.hpp"
#include "CDFS.hpp"

CApplication::CApplication() {}

CApplication::~CApplication() {

}

void CApplication::start() {
    //get map file name
    loadMap();

    //chose algorithm
    getAlgorithm();

    paintMap();

    //loop
    while(!m_Algorithm->foundDestination()) {
        //run algorithm step
        m_Algorithm->move();
        //show changes
        m_Interface->paintMap();
        //sleep
        sleep(1);
    }

}

void CApplication::loadMap() {
    //gets name of file with map from user
    std::string mapFileName = getMapFileName();

    getMap(mapFileName);

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
    m_Interface = std::make_shared<CInterface>(m_Map);
}

void CApplication::paintMap() {
    m_Interface->paintMap();
}

void CApplication::getAlgorithm() {
    bool invalidInput = true;
    int choice;

    std::cout << "Choose what algorithm to use (1-5): " << std::endl;
    std::cout << "1 - Random Search" << std::endl;
    std::cout << "2 - DFS" << std::endl;
    std::cout << "3 - BFS" << std::endl;
    std::cout << "4 - Greedy Search" << std::endl;
    std::cout << "5 - A*" << std::endl;


    while (invalidInput) {
        std::cin >> choice;
        if (choice >= 0 && choice <= 5) {
            invalidInput = false;
        } else {
            std::cout << "Invalid input, enter a valid one: " << std::endl;
        }
    }

    switch (choice) {
        case 1:
            break;
        case 2:
            m_Algorithm = std::make_shared<CDFS>(m_Map);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            throw std::runtime_error("Incorrect algorithm id");

    }

}
