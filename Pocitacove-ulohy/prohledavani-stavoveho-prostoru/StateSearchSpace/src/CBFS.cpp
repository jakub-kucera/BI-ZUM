//
// Created by kucerj56 on 21.02.21.
//

#include "CBFS.hpp"

CBFS::CBFS(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X + 1, m_Map->m_Start.m_Y), 1);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X - 1, m_Map->m_Start.m_Y), 1);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y + 1), 1);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y - 1), 1);
}

void CBFS::move() {
    CCoordinates coords = m_Queue.front().first;
    int pathLength = m_Queue.front().second;
    m_Queue.pop();

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
    m_Queue.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), pathLength + 1);
    m_Queue.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), pathLength + 1);
    m_Queue.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), pathLength + 1);
    m_Queue.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), pathLength + 1);
}