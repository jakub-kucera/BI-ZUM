cmake_minimum_required(VERSION 3.17)
project(StateSearchSpace)

set(CMAKE_CXX_STANDARD 17)

add_executable(StateSearchSpace src/main.cpp src/CApplication.cpp src/CApplication.hpp src/CAlgorithm.hpp src/CCoordinates.hpp src/CMap.hpp src/CInterface.cpp src/CInterface.hpp src/CDFS.cpp src/CDFS.hpp src/CBFS.cpp src/CBFS.hpp src/CRandomSearch.cpp src/CRandomSearch.hpp src/CCoordinatesPair.hpp src/CGreedySearch.cpp src/CGreedySearch.hpp src/CAStar.cpp src/CAStar.hpp src/CAlgorithm.cpp)