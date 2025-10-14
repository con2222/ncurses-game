#include <Utils.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>

void Utils::printMultiline(WINDOW *win, int start_y, int start_x, const std::string& text) {
    std::stringstream ss(text);
    std::string line;
    int current_y = start_y;

    while (std::getline(ss, line, '\n')) {

        mvwprintw(win, current_y, start_x, "%s", line.c_str());
        current_y++; 
    }
}

void Utils::printMultiline(int start_y, int start_x, const std::string& text) {
    std::stringstream ss(text);
    std::string line;
    int current_y = start_y;

    while (std::getline(ss, line, '\n')) {

        mvprintw(current_y, start_x, "%s", line.c_str());
        current_y++; 
    }
}

std::string Utils::readFileToString(const std::string& filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer; 
    buffer << fileStream.rdbuf();
    return buffer.str();
}

void Utils::printNumbers(int y, int x, int number) {
    std::string sNumber = std::to_string(number);
    int i = x;
    for (auto ch : sNumber) {
        printMultiline(y, i, readFileToString("../assets/numbers/" + std::string(1, ch) + ".txt"));
        if (ch == '1') {
            i = i + 3;
        } else {
            i = i + 7;
        }
    }
}