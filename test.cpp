#include "mylib.h"
#include <iostream>

int main(int argc, const char** argv) {
    std::string num = "82=9109";
    std::cout << mylib::isNumeric(num) << std::endl;
    return 0;
}
