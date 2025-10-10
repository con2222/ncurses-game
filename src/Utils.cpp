#include <Utils.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>

void printMultiline(WINDOW *win, int start_y, int start_x, const std::string& text) {
    std::stringstream ss(text);
    std::string line;
    int current_y = start_y;

    while (std::getline(ss, line, '\n')) {

        mvwprintw(win, current_y, start_x, "%s", line.c_str());
        current_y++; 
    }
}

void print_multiline(int start_y, int start_x, const std::string& text) {
    std::stringstream ss(text);
    std::string line;
    int current_y = start_y;

    while (std::getline(ss, line, '\n')) {

        mvprintw(current_y, start_x, "%s", line.c_str());
        current_y++; 
    }
}

std::string readFileToString(const std::string& filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer; 
    buffer << fileStream.rdbuf();
    return buffer.str();
}