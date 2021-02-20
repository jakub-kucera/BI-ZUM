//
// Created by kucerj56 on 20.02.21.
//

#ifndef STATESEARCHSPACE_CAPPLICATION_HPP
#define STATESEARCHSPACE_CAPPLICATION_HPP


#include <memory>
#include "CAlgorithm.hpp"
#include "CMap.hpp"

class CApplication {
private:

    const char *const MAP_FILE = "../examples/";

    std::shared_ptr<CAlgorithm> m_Algorithm;

    std::shared_ptr<CMap> m_Map;

    std::shared_ptr<CInterface> m_Interface;

    void loadMap();

    std::string getMapFileName();

    void getMap(const std::string& mapFileName);

public:
    CApplication();

    virtual ~CApplication();

    void start();

};


#endif //STATESEARCHSPACE_CAPPLICATION_HPP
