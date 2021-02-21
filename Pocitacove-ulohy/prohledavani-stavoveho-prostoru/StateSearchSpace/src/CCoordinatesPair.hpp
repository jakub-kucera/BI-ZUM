//
// Created by kucerj56 on 21.02.21.
//

#ifndef STATESEARCHSPACE_CCOORDINATESPAIR_HPP
#define STATESEARCHSPACE_CCOORDINATESPAIR_HPP

#include "CCoordinates.hpp"

struct CCoordinatesPair {
    CCoordinates m_Coords;
    CCoordinates m_Predecessor;

    CCoordinatesPair(const CCoordinates &mCoords, const CCoordinates &mPredecessor) : m_Coords(mCoords),
                                                                                      m_Predecessor(mPredecessor) {}

    bool operator<(const CCoordinatesPair &rhs) const {
        return m_Coords < rhs.m_Coords;
    }

    bool operator>(const CCoordinatesPair &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const CCoordinatesPair &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const CCoordinatesPair &rhs) const {
        return !(*this < rhs);
    }
};


#endif //STATESEARCHSPACE_CCOORDINATESPAIR_HPP
