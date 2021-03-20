//
// Created by kucerj56 on 22.02.21.
//

#ifndef STATESEARCHSPACE_CASTAR_HPP
#define STATESEARCHSPACE_CASTAR_HPP


#include "CGreedySearch.hpp"

class CAStar : public CGreedySearch {
private:
    std::vector<std::vector<int>> m_DistanceFromStart;

    std::map<CCoordinates, bool> m_ClosedMap;

    void removeFromPriorityMap(CCoordinates);

    bool isOpenedClosed(CCoordinates coords);

public:
    CAStar(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;
};


#endif //STATESEARCHSPACE_CASTAR_HPP
