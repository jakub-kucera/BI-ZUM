TARGET =  kucerj56

CXX = g++
CXX_FLAGS = -std=c++17 -Wall -pedantic -Wextra -g

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


$(TARGET): $(BUILD_DIR)/bruteforce.o $(BUILD_DIR)/genetic.o $(BUILD_DIR)/main.o $(BUILD_DIR)/path.o $(BUILD_DIR)/tmatrix.o
	$(CXX) $(CXX_FLAGS) $^ -o $@


$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf doc $(TARGET) $(BUILD_DIR)/ 2>/dev/null

#Dependencies
$(BUILD_DIR)/bruteforce.o: src/bruteforce.cpp src/bruteforce.h src/tmatrix.h src/path.h
#$(BUILD_DIR)/bruteforce.o: bruteforce.h tmatrix.h
$(BUILD_DIR)/genetic.o: src/genetic.cpp src/genetic.h src/tmatrix.h src/path.h
#$(BUILD_DIR)/genetic.o: genetic.h tmatrix.h
$(BUILD_DIR)/main.o: src/main.cpp src/tmatrix.h src/path.h src/bruteforce.h src/genetic.h
$(BUILD_DIR)/path.o: src/path.cpp src/path.h src/tmatrix.h
#$(BUILD_DIR)/path.o: path.h tmatrix.h
$(BUILD_DIR)/tmatrix.o: src/tmatrix.cpp src/tmatrix.h
#$(BUILD_DIR)/tmatrix.o: tmatrix.h