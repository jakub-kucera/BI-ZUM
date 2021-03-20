//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CALGORITHM_HPP
#define STATESEARCHSPACE_CALGORITHM_HPP


#include <memory>
#include <utility>
#include <algorithm>
#include "CMap.hpp"

class CAlgorithm {
protected:
    bool m_FoundDestination = false;

    bool m_FoundStart = false;

    CCoordinates m_CurrentCoordsPath;

    std::shared_ptr<CMap> m_Map;

public:
    explicit CAlgorithm(std::shared_ptr<CMap> mMap);

    virtual void move() = 0;

    bool foundDestination() const;

    void initPath();

    void movePath();

    bool foundStart() const;
};


#endif //STATESEARCHSPACE_CALGORITHM_HPP
