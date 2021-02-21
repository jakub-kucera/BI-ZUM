//
// Created by kucerj56 on 21.02.21.
//

#include "CBFS.hpp"

CBFS::CBFS(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
//    m_Queue.emplace(mMap->m_Start, mMap->m_Start); //todo change
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X + 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X - 1, m_Map->m_Start.m_Y), mMap->m_Start);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y + 1), mMap->m_Start);
    m_Queue.emplace(CCoordinates(m_Map->m_Start.m_X, m_Map->m_Start.m_Y - 1), mMap->m_Start);
}

void CBFS::move() {
    CCoordinates coords = m_Queue.front().m_Coords;
    CCoordinates predecessorCords = m_Queue.front().m_Predecessor;
    m_Queue.pop();

    if (coords == m_Map->m_end) {
        m_FoundDestination = true;
        m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCords;
        return;
    }

    if(m_Map->m_MapChar[coords.m_Y][coords.m_X] != ' ') {
        return;
    }

    m_Map->m_MapChar[coords.m_Y][coords.m_X] = '#'; //todo change # to opened instead of closed
    m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCords;


    //neighbors
    m_Queue.emplace(CCoordinates(coords.m_X + 1, coords.m_Y), coords);
    m_Queue.emplace(CCoordinates(coords.m_X - 1, coords.m_Y), coords);
    m_Queue.emplace(CCoordinates(coords.m_X, coords.m_Y + 1), coords);
    m_Queue.emplace(CCoordinates(coords.m_X, coords.m_Y - 1), coords);
}