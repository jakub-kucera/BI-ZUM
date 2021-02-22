//
// Created by kucerj56 on 21.02.21.
//

#ifndef STATESEARCHSPACE_CGREEDYSEARCH_HPP
#define STATESEARCHSPACE_CGREEDYSEARCH_HPP


#include <map>
#include "CAlgorithm.hpp"
#include "CCoordinatesPair.hpp"

class CGreedySearch : public CAlgorithm {
protected:
    std::multimap<double, CCoordinates> m_PriorityMap;

    std::map<CCoordinates, double> m_DistancesMap; //not used

    double getDistanceToDestination(CCoordinates a);

    double getDistanceToDestinationMem(CCoordinates a);

    static double getDistance(CCoordinates a, CCoordinates b);
public:
    explicit CGreedySearch(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;
};


#endif //STATESEARCHSPACE_CGREEDYSEARCH_HPP
