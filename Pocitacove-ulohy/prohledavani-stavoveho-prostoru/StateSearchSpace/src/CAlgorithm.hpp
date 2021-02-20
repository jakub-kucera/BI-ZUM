//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CALGORITHM_HPP
#define STATESEARCHSPACE_CALGORITHM_HPP


#include <memory>
#include <utility>
#include "CMap.hpp"

class CAlgorithm {
protected:
    bool m_FoundDestination = false;

    std::shared_ptr<CMap> m_Map;
public:
    explicit CAlgorithm(std::shared_ptr<CMap> mMap) : m_Map(std::move(mMap)) {}

    virtual void move() = 0;

    bool foundDestination() {
        return m_FoundDestination;
    };
};


#endif //STATESEARCHSPACE_CALGORITHM_HPP
