//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CAPPLICATION_HPP
#define STATESEARCHSPACE_CAPPLICATION_HPP


#include <memory>
#include "CAlgorithm.hpp"
#include "CMap.hpp"
#include "CInterface.hpp"

class CApplication {
private:

    const char *const MAP_FILE = "../examples/";

    const int TICK_SPEED = 10 * 1000;

    const bool SKIP_SEARCH_DRAW = false;

    const int SKIP_FRAMES_SEARCH_DESTINATION = 0;

    const bool SKIP_CREATE_PATH_DRAW = false;

    const int SKIP_FRAMES_CREATE_PATH = 0;

    //slower rendering if enabled
    const bool PAINT_MAP_COLORED = false;

    std::shared_ptr<CAlgorithm> m_Algorithm;

    std::shared_ptr<CMap> m_Map;

    std::shared_ptr<CInterface> m_Interface;

    void loadMap();

    std::string getMapFileName();

    void getMap(const std::string &mapFileName);

    void getAlgorithm();

public:
    CApplication();

    virtual ~CApplication();

    void start();

};


#endif //STATESEARCHSPACE_CAPPLICATION_HPP
