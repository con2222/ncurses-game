cmake_minimum_required(VERSION 3.10)
project(CLI_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Явно ищем ncursesw ===
# Попробуем найти библиотеку ncursesw
find_library(CURSES_NCURSESW_LIBRARY NAMES ncursesw libncursesw)
if(NOT CURSES_NCURSESW_LIBRARY)
    message(FATAL_ERROR "ncursesw library not found! Please install libncursesw-dev (or equivalent).")
endif()

# Найдём заголовочный файл (обычно curses.h, но для wide — тот же файл)
find_path(CURSES_NCURSESW_INCLUDE_DIR
    NAMES ncurses.h curses.h
    PATH_SUFFIXES ncursesw
)

if(NOT CURSES_NCURSESW_INCLUDE_DIR)
    message(FATAL_ERROR "ncursesw header not found!")
endif()

# === Создаём исполняемый файл ===
add_executable(main
    main.cpp
    src/Field.cpp
    src/Game.cpp
    src/Ceil.cpp
    src/Wall.cpp
    src/Floor.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Enemy.cpp
    src/Utils.cpp
    src/LivingEntity.cpp
    src/EnemyBase.cpp
    src/SpikedTrap.cpp
    src/Menu.cpp
    src/BattleController.cpp
    src/BattleUI.cpp
    src/Animator.cpp
)

# Подключаем include-директории
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CURSES_NCURSESW_INCLUDE_DIR}
)

# Линкуем с ncursesw
target_link_libraries(main PRIVATE ${CURSES_NCURSESW_LIBRARY})

# === Важно: определяем макросы для wide-char поддержки ===
target_compile_definitions(main PRIVATE
    _GNU_SOURCE
    _XOPEN_SOURCE_EXTENDED
)
