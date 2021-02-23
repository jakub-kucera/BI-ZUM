TARGET =  kucerj56

CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++17 -g

MKDIR = mkdir -p
BUILD_DIR = build
HEADERS = $(wildcard $(SOURCE_DIR)/*.h)

.PHONY: all
all: compile

.PHONY: compile
compile: $(TARGET)

.PHONY:  run
run: $(TARGET)
	./$(TARGET)

#.PHONY:  doc
#doc: doxygen Doxyfile
#doc: Doxyfile README.md $(BUILD_DIR)/*.hpp
#	doxygen Doxyfile
#doc: Doxyfile zadani.txt $(wildcard $(SOURCE_DIR)/*.h)
#	doxygen Doxyfile


#$(TARGET): $(BUILD_DIR)/CArea.o $(BUILD_DIR)/CAssetLoader.o $(BUILD_DIR)/CBFS.o $(BUILD_DIR)/CDFS.o $(BUILD_DIR)/CEnemy.o $(BUILD_DIR)/CGame.o $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CMap.o $(BUILD_DIR)/CPathFinder.o $(BUILD_DIR)/CTower.o $(BUILD_DIR)/main.o
$(TARGET): $(BUILD_DIR)/CAlgorithm.o $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CAStar.o $(BUILD_DIR)/CBFS.o $(BUILD_DIR)/CDFS.o $(BUILD_DIR)/CGreedySearch.o $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CRandomSearch.o $(BUILD_DIR)/main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@


$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf doc $(TARGET) $(BUILD_DIR)/ 2>/dev/null

#Dependencies
$(BUILD_DIR)/CAlgorithm.o: src/CAlgorithm.cpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CAlgorithm.o: src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CApplication.o: src/CApplication.cpp src/CApplication.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp src/CInterface.hpp src/CDFS.hpp src/CBFS.hpp src/CRandomSearch.hpp src/CGreedySearch.hpp src/CAStar.hpp
$(BUILD_DIR)/CApplication.o: src/CApplication.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp src/CInterface.hpp
$(BUILD_DIR)/CAStar.o: src/CAStar.cpp src/CAStar.hpp src/CGreedySearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CAStar.o: src/CAStar.hpp src/CGreedySearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CBFS.o: src/CBFS.cpp src/CBFS.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CBFS.o: src/CBFS.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
#$(BUILD_DIR)/CCoordinates.o: src/CCoordinates.hpp
$(BUILD_DIR)/CDFS.o: src/CDFS.cpp src/CDFS.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CDFS.o: src/CDFS.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CGreedySearch.o: src/CGreedySearch.cpp src/CGreedySearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CGreedySearch.o: src/CGreedySearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CInterface.o: src/CInterface.cpp src/CInterface.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CInterface.o: src/CInterface.hpp src/CMap.hpp src/CCoordinates.hpp
#$(BUILD_DIR)/CMap.o: src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CRandomSearch.o: src/CRandomSearch.cpp src/CRandomSearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/CRandomSearch.o: src/CRandomSearch.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp
$(BUILD_DIR)/main.o: src/main.cpp src/CApplication.hpp src/CAlgorithm.hpp src/CMap.hpp src/CCoordinates.hpp src/CInterface.hpp

#$(BUILD_DIR)/CAlgorithm.o $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CAStar.o $(BUILD_DIR)/CBFS.o $(BUILD_DIR)/CDFS.o $(BUILD_DIR)/CGreedySearch.o $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CMap.o $(BUILD_DIR)/CRandomSearch.o $(BUILD_DIR)/main.o