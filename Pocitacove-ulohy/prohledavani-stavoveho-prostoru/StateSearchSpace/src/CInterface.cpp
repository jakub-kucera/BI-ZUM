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
    if(colored) {
        paintMapColored();
    }
    else {
        paintMapUnColored();
    }
}

void CInterface::paintMapColored() {

}

void CInterface::paintMapUnColored() {
    clear();

    for(auto & line : m_Map->m_MapChar) {
        std::cout << line << '\n';
    }
    std::cout.flush();
}

void CInterface::clear() {
    std::cout << CLEAR_COMMAND;
}
