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
#include "CBFS.hpp"
#include "CRandomSearch.hpp"
#include "CGreedySearch.hpp"
#include "CAStar.hpp"

CApplication::CApplication() {}

CApplication::~CApplication() {

}

void CApplication::start() {
    //get map file name
    loadMap();

    //chose algorithm
    getAlgorithm();

    m_Interface->paintMap(PAINT_MAP_COLORED);


    int skippedFrames = 0;
    //searching for destination
    while(!m_Algorithm->foundDestination()) {
        //run algorithm step
        m_Algorithm->move();

        if(++skippedFrames > SKIP_FRAMES_SEARCH_DESTINATION && !SKIP_SEARCH_DRAW){
            //show changes
            m_Interface->paintMap(PAINT_MAP_COLORED);
            //sleep
            usleep(TICK_SPEED);

            skippedFrames = 0;
        }
    }

    skippedFrames = 0;
    m_Algorithm->initPath();
    //creating path
    while(!m_Algorithm->foundStart()) {
        //move path
        m_Algorithm->movePath();

        if(++skippedFrames > SKIP_FRAMES_CREATE_PATH && !SKIP_CREATE_PATH_DRAW){
            //show changes
            m_Interface->paintMap(PAINT_MAP_COLORED);
            //sleep
            usleep(TICK_SPEED);

            skippedFrames = 0;
        }
    }

//    m_Interface->paintMap(pathLength, PAINT_MAP_COLORED);
    m_Interface->paintMap(PAINT_MAP_COLORED);
    m_Interface->paintExplanations();

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
            m_Algorithm = std::make_shared<CRandomSearch>(m_Map);
            break;
        case 2:
            m_Algorithm = std::make_shared<CDFS>(m_Map);
            break;
        case 3:
            m_Algorithm = std::make_shared<CBFS>(m_Map);
            break;
        case 4:
            m_Algorithm = std::make_shared<CGreedySearch>(m_Map);
            break;
        case 5:
            m_Algorithm = std::make_shared<CAStar>(m_Map);
            break;
        default:
            throw std::runtime_error("Incorrect algorithm id");

    }

}
