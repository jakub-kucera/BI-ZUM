//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CMAP_HPP
#define STATESEARCHSPACE_CMAP_HPP


#include <utility>
#include <vector>
#include "CCoordinates.hpp"

class CMap {
public:
    std::vector<std::string> m_Map;
    CCoordinates m_Start;
    CCoordinates m_end;

    CMap(std::vector<std::string> mMap, const CCoordinates &mStart, const CCoordinates &mEnd) : m_Map(std::move(mMap)),
                                                                                           m_Start(mStart),
                                                                                           m_end(mEnd) {}
};


#endif //STATESEARCHSPACE_CMAP_HPP
