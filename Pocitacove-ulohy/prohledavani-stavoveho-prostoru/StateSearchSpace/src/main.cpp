#include <iostream>
#include "CApplication.hpp"

int main() {
    CApplication application;
    try {
        application.start();
    }
    catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
