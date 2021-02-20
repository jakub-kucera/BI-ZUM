//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CDFS_HPP
#define STATESEARCHSPACE_CDFS_HPP


#include "CAlgorithm.hpp"

class CDFS : public CAlgorithm {
public:
    explicit CDFS(const std::shared_ptr<CMap> &mMap);

    virtual void move() override;
};


#endif //STATESEARCHSPACE_CDFS_HPP
