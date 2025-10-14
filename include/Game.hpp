#pragma once
#include <Field.hpp>
#include <ScreenSize.hpp>

class Game {
    ScreenSize screen;
    Field field;
    
public:
    Game();
    bool help();
    void start();
    void initScreen();
    void cleanup();
};