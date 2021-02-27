//
// Created by kucerj56 on 22.02.21.
//

#include "CAlgorithm.hpp"

CAlgorithm::CAlgorithm(std::shared_ptr<CMap> mMap) : m_Map(std::move(mMap)), m_CurrentCoordsPath(mMap->m_end) {}

bool CAlgorithm::foundDestination() const {
    return m_FoundDestination;
}

void CAlgorithm::initPath() {
    m_CurrentCoordsPath = m_Map->m_MapPred[m_Map->m_end.m_Y][m_Map->m_end.m_X];
}

void CAlgorithm::movePath() {
    if (m_CurrentCoordsPath == m_Map->m_Start) {
        m_FoundStart = true;
        if (m_Map->m_Start != m_Map->m_end){
            m_Map->pathLength++;
        }
        return;
    }
    m_Map->pathLength++;
    m_Map->m_MapChar[m_CurrentCoordsPath.m_Y][m_CurrentCoordsPath.m_X] = 'o';

    m_CurrentCoordsPath = m_Map->m_MapPred[m_CurrentCoordsPath.m_Y][m_CurrentCoordsPath.m_X];

}

bool CAlgorithm::foundStart() const {
    return m_FoundStart;
}