//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CCOORDINATES_HPP
#define STATESEARCHSPACE_CCOORDINATES_HPP

#include <iostream>

/// Used to store coordinates.
struct CCoordinates {
    /// @var X coordinate.
    unsigned int m_X;
    /// @var Y coordinate.
    unsigned int m_Y;

    CCoordinates() : m_X(0), m_Y(0) {}

    CCoordinates(unsigned int x, unsigned int y) : m_X(x), m_Y(y) {}

    friend std::ostream &operator<<(std::ostream &out, const CCoordinates &cords) {
        return out << "X: " << cords.m_X << " Y: " << cords.m_Y << std::endl;
    }

    friend bool operator==(const CCoordinates &leftCords, const CCoordinates &rightCords) {
        return leftCords.m_Y == rightCords.m_Y && leftCords.m_X == rightCords.m_X;
    }
};


#endif //STATESEARCHSPACE_CCOORDINATES_HPP
