//
// Created by kucerj56 on 20.02.21.
//

#include <list>
#include "CDFS.hpp"

CDFS::CDFS(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    m_Stack.emplace(m_Map->m_Start);
    m_Map->m_MapPred[m_Map->m_Start.m_Y][m_Map->m_Start.m_X] = m_Map->m_Start;
}

void CDFS::move() {
    CCoordinates coords = m_Stack.top();
    m_Stack.pop();

    if (coords == m_Map->m_end) {
        m_FoundDestination = true;
        return;
    }

    m_Map->nodesExpanded++;

    //neighbors
    std::list<CCoordinates> neighbors;
    neighbors.emplace_back(CCoordinates(coords.m_X + 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X - 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y + 1));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y - 1));

    for(const auto & neighbor : neighbors) {
        char neighborChar = m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X];
        if(neighborChar == ' ') {
            m_Stack.emplace(neighbor);
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X]  = coords;
            m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X] = '#';
        }
        else if(neighborChar == 'E') {
            m_Stack.emplace(neighbor);
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X]  = coords;
        }
    }
}
