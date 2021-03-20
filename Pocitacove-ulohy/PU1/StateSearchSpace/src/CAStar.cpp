//
// Created by kucerj56 on 22.02.21.
//

#include <list>
#include "CAStar.hpp"

CAStar::CAStar(const std::shared_ptr<CMap> &mMap) : CGreedySearch(mMap) {
    m_DistanceFromStart.resize(m_Map->m_MapChar.size());
    int rowLength = m_Map->m_MapChar[0].size();
    for (auto &row : m_DistanceFromStart) {
        row.resize(rowLength);
    }

    for (auto &r : m_DistanceFromStart) {
        for (auto &c : r) {
            c = INT_MAX;
        }
    }

    m_DistanceFromStart[m_Map->m_Start.m_Y][m_Map->m_Start.m_X] = 0;
}

void CAStar::move() {
    const auto &mapBeginIt = m_PriorityMap.begin();
    CCoordinates coords = mapBeginIt->second;
    m_PriorityMap.erase(mapBeginIt);

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
        if (m_ClosedMap[neighbor] || neighborChar == 'X') {
            continue;
        }

        double newDistance = m_DistanceFromStart[coords.m_Y][coords.m_X] + 1;


        if (!isOpenedClosed(neighbor) || m_DistanceFromStart[neighbor.m_Y][neighbor.m_X] > newDistance) {
            m_DistanceFromStart[neighbor.m_Y][neighbor.m_X] = newDistance;
            m_Map->m_MapPred[neighbor.m_Y][neighbor.m_X] = coords;

            if (isOpenedClosed(neighbor)) {
                removeFromPriorityMap(neighbor);
            } else {
                m_Map->m_MapChar[neighbor.m_Y][neighbor.m_X] = '#';
            }
            m_PriorityMap.emplace(newDistance + 1 * getDistanceToDestination(neighbor), neighbor);

        }
    }
    m_ClosedMap[coords] = true;
}

void CAStar::removeFromPriorityMap(CCoordinates coords) {
    auto it = m_PriorityMap.begin();
    while (it != m_PriorityMap.end()) {
        if (it->second == coords) {
            m_PriorityMap.erase(it);
            break;
        }
        it++;
    }
}

bool CAStar::isOpenedClosed(CCoordinates coords) {
    return !(m_Map->m_MapPred[coords.m_Y][coords.m_X] == CCoordinates(-1, -1))
           && (m_Map->m_MapChar[coords.m_Y][coords.m_X] == '#'
//               || m_Map->m_MapChar[coords.m_Y][coords.m_X] == '@'
               || m_Map->m_MapChar[coords.m_Y][coords.m_X] == 'E');
}
