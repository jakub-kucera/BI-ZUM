//
// Created by kucerj56 on 20.02.21.
//

#include "CDFS.hpp"

CDFS::CDFS(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X + 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X - 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y + 1), mMap->m_Start);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y - 1), mMap->m_Start);
}

void CDFS::move() {
    CCoordinates coords = m_Stack.top().first;
    CCoordinates predecessorCoords = m_Stack.top().second;
    m_Stack.pop();

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


    //neighbors
    m_Stack.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), coords);
    m_Stack.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), coords);
    m_Stack.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), coords);
    m_Stack.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), coords);

    return;
}
