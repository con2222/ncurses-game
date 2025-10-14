# ncurses-game

A simple text-based roguelike quest written in C++ using the `ncurses` library.

## 📜 About the Project

This project was created for learning C++ and developing games in a text-based interface.

### ✨ Key Features

*   **Text-based Interface:** All graphics are created using terminal characters thanks to the `ncurses` library.
*   **Enemies:** Fight monsters that roam the dungeon.
*   **Turn-based System:** The world moves only when you move.
*   **Background Music:** For complete immersion!

## 🛠️ Installation and Build

### Installing Dependencies

First, install the required ncurses library:

```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

# Create build directory
```bash
mkdir build
cd build
```
# Configure with CMake
```bash
cmake ..
```
# Build the project
```bash
make
```
# Run the game
```bash
./main
```
