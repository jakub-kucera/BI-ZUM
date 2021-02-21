//
// Created by kucerj56 on 21.02.21.
//

#ifndef STATESEARCHSPACE_CBFS_HPP
#define STATESEARCHSPACE_CBFS_HPP


#include <queue>
#include "CAlgorithm.hpp"
#include "CCoordinatesPair.hpp"

class CBFS : public CAlgorithm {
private:
    //current coordinates, predecessors coordinates
    std::queue<CCoordinatesPair> m_Queue;
public:
    explicit CBFS(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;
};


#endif //STATESEARCHSPACE_CBFS_HPP
