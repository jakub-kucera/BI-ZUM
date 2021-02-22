//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CINTERFACE_HPP
#define STATESEARCHSPACE_CINTERFACE_HPP


#include <memory>
#include <unordered_map>
#include "CMap.hpp"

class CInterface {
public:
    explicit CInterface(std::shared_ptr<CMap> mMap);

    void paintMap(int pathLength, bool colored);

    void paintMap(bool colored);

    void paintMapColored();

    void paintMapUnColored();

    void paintExplanations();

private:
    // Sequence of characters that clears the users terminal.
    const char *const CLEAR_COMMAND = "\x1B[2J\x1B[H";

    const std::unordered_map<std::string, uint8_t> m_ColorTable = {{"black",   40},
                                                                   {"red",     41},
                                                                   {"green",   42},
                                                                   {"yellow",  43},
                                                                   {"blue",    44},
                                                                   {"magenta", 45},
                                                                   {"cyan",    46},
                                                                   {"white",   47}};

    std::shared_ptr<CMap> m_Map;

    void clear();
};


#endif //STATESEARCHSPACE_CINTERFACE_HPP
