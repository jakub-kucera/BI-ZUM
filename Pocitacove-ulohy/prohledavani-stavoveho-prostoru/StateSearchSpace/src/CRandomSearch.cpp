//
// Created by kucerj56 on 21.02.21.
//

#include <queue>
#include <list>
#include "CRandomSearch.hpp"

CRandomSearch::CRandomSearch(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    srand(time(NULL));
    m_Set.emplace(mMap->m_Start);
    m_Map->m_MapPred[m_Map->m_Start.m_Y][m_Map->m_Start.m_X] = m_Map->m_Start;
}

void CRandomSearch::move() {
    //pick random element
    auto r = rand() % m_Set.size();
    auto it = std::begin(m_Set);
    std::advance(it, r);

    CCoordinates coords = *it;
    m_Set.erase(it);

    if (coords == m_Map->m_end) {
        m_FoundDestination = true;
        return;
    }

    if (coords != m_Map->m_Start) {
        m_Map->m_MapChar[coords.m_Y][coords.m_X] = '@';
    }

    m_Map->nodesExpanded++;

    //neighbors
    std::list<CCoordinates> neighbors;
    neighbors.emplace_back(CCoordinates(coords.m_X + 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X - 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y + 1));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y - 1));

    for (const auto &neighbor : neighbors) {
        char neighborChar = m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X];
        if (neighborChar == ' ') {
            m_Set.emplace(neighbor);
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X] = coords;
            m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X] = '#';
        } else if (neighborChar == 'E') {
            m_Set.emplace(neighbor);
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X] = coords;
        }
    }

}
