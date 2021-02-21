//
// Created by kucerj56 on 21.02.21.
//

#include <queue>
#include "CRandomSearch.hpp"

CRandomSearch::CRandomSearch(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    srand (time(NULL));
    m_Set.emplace(CCoordinates(m_Map->m_Start.m_X + 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Set.emplace(CCoordinates(m_Map->m_Start.m_X - 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Set.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y + 1), mMap->m_Start);
    m_Set.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y - 1), mMap->m_Start);
}

void CRandomSearch::move() {
    //pick random element
    auto r = rand() % m_Set.size();
    auto it = std::begin(m_Set);
    std::advance(it,r);

    CCoordinates coords = it->m_Coords;
    CCoordinates predecessorCoords = it->m_Predecessor;
    m_Set.erase(it);

    if (coords == m_Map->m_end) {
        m_FoundDestination = true;
        m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCoords;
        return;
    }

    if(m_Map->m_MapChar[coords.m_Y][coords.m_X] != ' ') {
        return;
    }

    m_Map->m_MapChar[coords.m_Y][coords.m_X] = '#';
    m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCoords;

    m_Set.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), coords);
    m_Set.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), coords);
    m_Set.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), coords);
    m_Set.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), coords);

//    //neighbors
//    std::queue<CCoordinatesPair> neighbors;
//    neighbors.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), coords);
//    neighbors.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), coords);
//    neighbors.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), coords);
//    neighbors.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), coords);

//    while(!neighbors.empty()) {
//        CCoordinates
//
//
//        if (coords == m_Map->m_end) {
//            m_FoundDestination = true;
//            m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCoords;
//            return;
//        }
//    }

}
