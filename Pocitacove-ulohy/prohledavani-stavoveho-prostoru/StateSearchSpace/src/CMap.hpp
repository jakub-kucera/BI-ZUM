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
    std::vector<std::vector<int>> m_MapNum;
    CCoordinates m_Start;
    CCoordinates m_end;

    CMap(std::vector<std::string> mMap, const CCoordinates &mStart, const CCoordinates &mEnd)
        : m_MapChar(std::move(mMap)), m_Start(mStart), m_end(mEnd) {
        m_MapNum.resize(m_MapChar.size());
        int rowLength = m_MapChar[0].size();
        for (auto & row : m_MapNum) {
            row.resize(rowLength);
        }

        //r, c

        for(int r = 0; r < m_MapChar.size(); r++) {
            for (int c = 0; c < m_MapChar[0].size(); c++) {
                switch (m_MapChar[r][c]) {
                    case ' ':
                        m_MapNum[r][c] = INT_MAX;
                        break;
                    case 'X':
                        m_MapNum[r][c] = INT_MAX;
                        break;
                    case 'S':
                        m_MapNum[r][c] = 0;
                        break;
                    case 'E':
                        m_MapNum[r][c] = INT_MAX;
                        break;
                    default:
                        throw std::runtime_error("Unknown character on map: " + std::to_string(m_MapNum[r][c]));

                }
            }
        }
    }
};


#endif //STATESEARCHSPACE_CMAP_HPP
