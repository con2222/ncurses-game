ncurses-game

A simple text-based roguelike quest written in C++ using the ncurses library.
📜 About the Project

This project was created for learning C++ and developing games in a text-based interface.
✨ Key Features

    Text-based Interface: All graphics are created using terminal characters thanks to the ncurses library.

    Enemies: Fight monsters that roam the dungeon.

    Turn-based System: The world moves only when you move.

    Background Music: For complete immersion!

⚙️ Getting Started

To compile and run this project, you will need to install the ncurses development libraries.

Installing Libraries

On Debian-based systems (like Ubuntu), you can install the necessary libraries using the following command in your terminal:
code Bash

    
sudo apt-get install libncurses5-dev libncursesw5-dev

  

This command installs the core ncurses library and the wide character support library, which are needed for compiling the project.[1][2][3][4][5]

Building the Project

Once the libraries are installed, you can build the project using CMake. Follow these steps:

    Create a build directory:
    code Bash

    
mkdir build

  

Navigate into the build directory:
code Bash

    
cd build

  

Run CMake to configure the project:
code Bash

    
cmake ..

  

Compile the project using Make:
code Bash

    
make

  

Run the game:
code Bash

    
./main

  
