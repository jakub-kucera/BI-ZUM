//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CMAP_HPP
#define STATESEARCHSPACE_CMAP_HPP


#include <utility>
#include <vector>
#include <climits>
#include "CCoordinates.hpp"

class CMap {
public:
    std::vector<std::string> m_MapChar;
    std::vector<std::vector<CCoordinates>> m_MapPred;
    CCoordinates m_Start;
    CCoordinates m_end;
    int pathLength = 0;
    int nodesExpanded = 0;

    CMap(std::vector<std::string> mMap, const CCoordinates &mStart, const CCoordinates &mEnd)
            : m_MapChar(std::move(mMap)), m_Start(mStart), m_end(mEnd) {
        m_MapPred.resize(m_MapChar.size());
        int rowLength = m_MapChar[0].size();
        for (auto &row : m_MapPred) {
            row.resize(rowLength);
        }

        CCoordinates empty(-1, -1);

        for (long unsigned int y = 0; y < m_MapChar.size(); y++) {
            for (long unsigned int x = 0; x < m_MapChar[0].size(); x++) {
                switch (m_MapChar[y][x]) {
                    case ' ':
                        m_MapPred[y][x] = empty;
                        break;
                    case 'X':
                        m_MapPred[y][x] = empty;
                        break;
                    case 'S':
                        m_MapPred[y][x] = CCoordinates(x, y);
                        break;
                    case 'E':
                        m_MapPred[y][x] = empty;
                        break;
                    default:
                        throw std::runtime_error("Unknown character on map: " + std::to_string(m_MapChar[y][x]));

                }
            }
        }
    }
};


#endif //STATESEARCHSPACE_CMAP_HPP
