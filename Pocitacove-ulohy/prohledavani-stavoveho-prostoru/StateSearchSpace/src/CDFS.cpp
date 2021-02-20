//
// Created by kucerj56 on 20.02.21.
//

#include "CDFS.hpp"

CDFS::CDFS(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X + 1, m_Map->m_Start.m_Y), 1);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X - 1, m_Map->m_Start.m_Y), 1);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y + 1), 1);
    m_Stack.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y - 1), 1);
}

void CDFS::move() {
    CCoordinates coords = m_Stack.top().first;
    int pathLength = m_Stack.top().second;
    m_Stack.pop();

    if (coords == m_Map->m_end) {
        m_FoundDestination = true;
        return;
    }

    if(m_Map->m_MapChar[coords.m_Y][coords.m_X] != ' ') {
        return;
    }

    m_Map->m_MapChar[coords.m_Y][coords.m_X] = '#';
    m_Map->m_MapNum[coords.m_Y][coords.m_X]  = pathLength;


    //neighbors
    m_Stack.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), pathLength + 1);
    m_Stack.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), pathLength + 1);
    m_Stack.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), pathLength + 1);
    m_Stack.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), pathLength + 1);

    return;
}
