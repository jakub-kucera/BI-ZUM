//
// Created by kucerj56 on 21.02.21.
//

#ifndef STATESEARCHSPACE_CBFS_HPP
#define STATESEARCHSPACE_CBFS_HPP


#include <queue>
#include "CAlgorithm.hpp"

class CBFS : public CAlgorithm {
private:
    std::queue<CCoordinates> m_Queue;
public:
    explicit CBFS(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;
};


#endif //STATESEARCHSPACE_CBFS_HPP
