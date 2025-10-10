cmake_minimum_required(VERSION 3.10)
project(CLI_game)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR} include)

add_executable(main
    main.cpp
    src/Field.cpp
    src/Game.cpp
    src/Ceil.cpp
    src/Color.cpp
    src/Wall.cpp
    src/Floor.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/GameLogic.cpp
    src/Utils.cpp
    src/LivingEntity.cpp
    src/EnemyBase.cpp
    src/SpikedTrap.cpp
)

target_link_libraries(main ${CURSES_LIBRARIES})
