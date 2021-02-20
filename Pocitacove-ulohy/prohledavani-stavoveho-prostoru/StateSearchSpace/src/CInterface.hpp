//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CINTERFACE_HPP
#define STATESEARCHSPACE_CINTERFACE_HPP


#include <memory>
#include "CMap.hpp"

class CInterface {
public:
    explicit CInterface(std::shared_ptr<CMap> mMap);

    void paintMap();

private:
    // Sequence of characters that clears the users terminal.
    const char * const CLEAR_COMMAND = "\x1B[2J\x1B[H";

    std::shared_ptr<CMap> m_Map;

    void clear();
};


#endif //STATESEARCHSPACE_CINTERFACE_HPP
