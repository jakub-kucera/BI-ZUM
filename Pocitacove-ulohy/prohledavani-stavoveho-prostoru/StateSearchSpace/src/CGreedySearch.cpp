//
// Created by kucerj56 on 21.02.21.
//

#include <cmath>
#include <queue>
#include <list>
#include "CGreedySearch.hpp"

CGreedySearch::CGreedySearch(const std::shared_ptr<CMap> &mMap) : CAlgorithm(mMap) {
    m_PriorityMap.emplace(getDistanceToDestination(m_Map->m_Start), m_Map->m_Start);
}

void CGreedySearch::move() {
    const auto & it = m_PriorityMap.begin();
    CCoordinates coords = it->second;
    m_PriorityMap.erase(it);

    //neighbors
    std::list<CCoordinates> neighbors;
    neighbors.emplace_back(CCoordinates(coords.m_X + 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X - 1, coords.m_Y));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y + 1));
    neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y - 1));

    std::cout << "main distance: " << getDistanceToDestination(coords) << std::endl;
    for(const auto & neighbor : neighbors) {
        if (neighbor == m_Map->m_end) {
            m_FoundDestination = true;
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X]  = coords;
            return;
        }

        if(m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X] == ' ') {
            m_PriorityMap.emplace(getDistanceToDestination(neighbor), neighbor);
            std::cout << "neighbor distance: " << getDistanceToDestination(neighbor) << std::endl;
            m_Map->m_MapChar[coords.m_Y][coords.m_X] = '#';
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X]  = coords;
        }
    }


//    if(m_Map->m_MapChar[coords.m_Y][coords.m_X] != ' ') {
//        return;
//    }
//
//    m_Map->m_MapChar[coords.m_Y][coords.m_X] = '#';
//    m_Map->m_MapPred[coords.m_Y][coords.m_X]  = predecessorCords;

}

double CGreedySearch::getDistanceToDestination(CCoordinates a) {
    return getDistance(a, m_Map->m_end);
}

double CGreedySearch::getDistanceToDestinationMem(CCoordinates a) {
    auto it = m_DistancesMap.find(a);
    if(it == m_DistancesMap.end()) {
        double distance = getDistance(a, m_Map->m_end);
        m_DistancesMap[a] = distance;
        return distance;
    }
    return it->second;
}

double CGreedySearch::getDistance(CCoordinates a, CCoordinates b) {
    return sqrt((b.m_X - a.m_X)*(b.m_X - a.m_X) + (b.m_Y - a.m_Y)*(b.m_Y - a.m_Y));
}
