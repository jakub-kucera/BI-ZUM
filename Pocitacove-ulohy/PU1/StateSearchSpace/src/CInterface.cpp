//
// Created by kucerj56 on 20.02.21.
//

#include "CInterface.hpp"

#include <utility>

CInterface::CInterface(std::shared_ptr<CMap> mMap) : m_Map(std::move(mMap)) {}

void CInterface::paintMap(int pathLength, bool colored) {
    paintMap(colored);
    std::cout << "Path length: " << pathLength << std::endl;
}

void CInterface::paintMap(bool colored) {
    if (colored) {
        paintMapColored();
    } else {
        paintMapUnColored();
    }
}

void CInterface::paintMapColored() {
    clear();

    for (const auto &line : m_Map->m_MapChar) {
        for (char c : line) {
            std::cout << "\033[1;";
            switch (c) {
                case 'X':
                    std::cout << std::to_string(m_ColorTable.find("black")->second);
                    break;
                case ' ':
                    std::cout << std::to_string(m_ColorTable.find("black")->second);
                    break;
                case '#':
                    std::cout << std::to_string(m_ColorTable.find("yellow")->second);
                    break;
                case '@':
                    std::cout << std::to_string(m_ColorTable.find("green")->second);
                    break;
                case 'o':
                    std::cout << std::to_string(m_ColorTable.find("blue")->second);
                    break;
                case 'S':
                    std::cout << std::to_string(m_ColorTable.find("red")->second);
                    break;
                case 'E':
                    std::cout << std::to_string(m_ColorTable.find("red")->second);
                    break;
                default:
                    std::cout << std::to_string(m_ColorTable.find("cyan")->second);
                    break;

            }

            std::cout << "m";
            std::cout << c;
            std::cout << "\033[0m";
        }
        std::cout << '\n';
    }
    std::cout.flush();
}

void CInterface::paintMapUnColored() {
    clear();

    for (auto &line : m_Map->m_MapChar) {
        std::cout << line << '\n';
    }
    std::cout.flush();
}

void CInterface::clear() {
    std::cout << CLEAR_COMMAND;
}

void CInterface::paintExplanations() {
    std::cout << "-------------------------" << std::endl;
    std::cout << "S Start" << std::endl;
    std::cout << "E End" << std::endl;
    std::cout << "# Opened node" << std::endl;
    std::cout << "@ Closed node" << std::endl;
    std::cout << "o Path" << std::endl;
    std::cout << "X Wall" << std::endl;
    std::cout << "space Fresh node" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Nodes expanded: " << m_Map->nodesExpanded << std::endl;
    std::cout << "Path length: " << m_Map->pathLength << std::endl;
}
