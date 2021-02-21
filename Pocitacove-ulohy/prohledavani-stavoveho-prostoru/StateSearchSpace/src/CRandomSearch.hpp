//
// Created by kucerj56 on 21.02.21.
//

#ifndef STATESEARCHSPACE_CRANDOMSEARCH_HPP
#define STATESEARCHSPACE_CRANDOMSEARCH_HPP

#include <set>
#include "CAlgorithm.hpp"
#include "CCoordinatesPair.hpp"


class CRandomSearch : public CAlgorithm {
private:
    //current coordinates, predecessors coordinates

    std::set<CCoordinatesPair> m_Set;


public:
    explicit CRandomSearch(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;

};


#endif //STATESEARCHSPACE_CRANDOMSEARCH_HPP
