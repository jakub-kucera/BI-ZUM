//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CALGORITHM_HPP
#define STATESEARCHSPACE_CALGORITHM_HPP


#include <memory>
#include <utility>
#include <algorithm>
#include "CMap.hpp"

class CAlgorithm {// todo create .cpp
protected:
    bool m_FoundDestination = false;

    bool m_FoundStart = false;

    CCoordinates m_CurrentCoordsPath;

    std::shared_ptr<CMap> m_Map;

    CCoordinates getNextPathCoords(CCoordinates coords) {
        std::vector<CCoordinates> neighbors;
        std::cout << "Main coords distance: " <<  m_Map->m_MapNum[coords.m_Y][coords.m_X] << std::endl;
        neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y - 1));
        neighbors.emplace_back(CCoordinates(coords.m_X, coords.m_Y + 1));
        neighbors.emplace_back(CCoordinates(coords.m_X - 1, coords.m_Y));
        neighbors.emplace_back(CCoordinates(coords.m_X + 1, coords.m_Y));
        std::cout << "Neighbor coords distance: " <<  m_Map->m_MapNum[neighbors[0].m_Y][neighbors[0].m_X] << std::endl;
        std::cout << "Neighbor coords distance: " <<  m_Map->m_MapNum[neighbors[1].m_Y][neighbors[1].m_X] << std::endl;
        std::cout << "Neighbor coords distance: " <<  m_Map->m_MapNum[neighbors[2].m_Y][neighbors[2].m_X] << std::endl;
        std::cout << "Neighbor coords distance: " <<  m_Map->m_MapNum[neighbors[3].m_Y][neighbors[3].m_X] << std::endl;
        auto it = find_if(neighbors.begin(), neighbors.end(), [&] (const CCoordinates & a) -> bool {
            return m_Map->m_MapNum[a.m_Y][a.m_X] == m_Map->m_MapNum[coords.m_Y][coords.m_X] - 1;
        });
        std::cout << m_Map->m_MapNum[it->m_Y][it->m_X] << " == " << m_Map->m_MapNum[coords.m_Y][coords.m_X] << " - 1" << std::endl;
        if(it == neighbors.end()) {
            throw std::runtime_error("Predecessor not found, coords: X:" + std::to_string(coords.m_X) + " Y: " + std::to_string(coords.m_Y));
        }
        return *it;
//        std::sort(neighbors.begin(), neighbors.end(), [&](const CCoordinates & a, const CCoordinates & b) -> bool
//        {
//            return m_Map->m_MapNum[b.m_Y][b.m_X] > m_Map->m_MapNum[a.m_Y][a.m_X];
//        });

//        return neighbors[0];
    }
public:
    explicit CAlgorithm(std::shared_ptr<CMap> mMap) : m_Map(std::move(mMap)), m_CurrentCoordsPath(mMap->m_end) {}

    virtual void move() = 0;

    bool foundDestination() const {
        return m_FoundDestination;
    };

    void initPath() {
        m_CurrentCoordsPath = getNextPathCoords(m_Map->m_end);
    }

    void movePath() {
        if(m_CurrentCoordsPath == m_Map->m_Start) {
            m_FoundStart = true;
            return;
        }
        m_Map->m_MapChar[m_CurrentCoordsPath.m_Y][m_CurrentCoordsPath.m_X] = 'o';
//        m_Map->m_MapNum[m_CurrentCoordsPath.m_Y][m_CurrentCoordsPath.m_X] = INT_MAX;

        m_CurrentCoordsPath = getNextPathCoords(m_CurrentCoordsPath);
    }

    bool foundStart() const {
        return m_FoundStart;
    };
};


#endif //STATESEARCHSPACE_CALGORITHM_HPP
