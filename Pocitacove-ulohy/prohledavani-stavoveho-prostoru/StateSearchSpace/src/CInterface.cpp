//
// Created by kucerj56 on 20.02.21.
//

#include "CInterface.hpp"

#include <utility>

CInterface::CInterface(std::shared_ptr<CMap> mMap) : m_Map(std::move(mMap)) {}

void CInterface::paintMap() {
    for(auto & line : m_Map->m_Map) {
        std::cout << line << std::endl;
    }
}

void CInterface::clear() {
    std::cout << CLEAR_COMMAND;
}
