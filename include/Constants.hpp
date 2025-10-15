#pragma once

constexpr const size_t FIELD_WIDTH = 20;
constexpr const size_t FIELD_HEIGHT = 10;

constexpr const int DOWN = 258;
constexpr const int UP = 259;
constexpr const int LEFT = 260;
constexpr const int RIGHT = 261;
constexpr const int ENTER = '\n';
constexpr const int SPACE = ' ';
constexpr const int TAB = 9;

constexpr const char FLOOR = ' ';
constexpr const char WALL = '#';
constexpr const char PLAYER = 'K';
constexpr const char ENEMY = 'X';
constexpr const char ENEMY_BASE = 'B';
constexpr const char SPIKED_TRAP = '^';

constexpr const int PL_HEALTH = 10;
constexpr const int MELEE_MODE = 0;
constexpr const int MELEE_DAMAGE = 7;
constexpr const int RANGE_MODE = 1;
constexpr const int RANGE_DAMAGE = 15;

constexpr const int EN_BASE_HP = 10;
constexpr const int EN_HEALTH = 20;
constexpr const int EN_DAMAGE = 5;

constexpr const int WALLS_COUNT = 10;

constexpr const int SPAWN_COOLDOWN = 5;

constexpr const int PLAYER_X_OFFSET = -50;
constexpr const int ENEMY_X_OFFSET  = 13;
constexpr const int BATTLE_Y_OFFSET = -15;

constexpr const int PLAYER_TURN_X_OFFSET = 26;
constexpr const int ENEMY_TURN_X_OFFSET  = 24;

constexpr const int TIME_BETWEEN_ANIMATIONS = 1000; 

//BattleLogic.cpp
constexpr const char* KNIGHT_MELEE_BATTLE = "../assets/knight/inBattle.txt";
constexpr const char* KNIGHT_RANGED_BATTLE = "../assets/knight/withBow.txt";
constexpr const char* GOBLIN_BATTLE = "../assets/enemy/goblin.txt";
constexpr const char* GRAVE = "../assets/battle/grave.txt";

constexpr const char* KNIGHT_ATTACK1 = "../assets/knight/attack1.txt";
constexpr const char* KNIGHT_ATTACK2 = "../assets/knight/attack2.txt";
constexpr const char* KNIGHT_ATTACK3 = "../assets/knight/attack3.txt";
constexpr const char* KNIGHT_SHOOT1 = "../assets/knight/shoot1.txt";
constexpr const char* KNIGHT_SHOOT2 = "../assets/knight/shoot2.txt";
constexpr const char* KNIGHT_BLOCK = "../assets/knight/block3.txt";

constexpr const char* GOBLIN_ATTACK1 = "../assets/enemy/goblinAttack1.txt";
constexpr const char* GOBLIN_ATTACK2 = "../assets/enemy/goblinAttack2.txt";

constexpr const char* PLAYER_TURN_TXT = "../assets/battle/playerTurn.txt";
constexpr const char* ENEMY_TURN_TXT = "../assets/battle/enemyTurn.txt";

constexpr const int BLOCK_WINDOW_MS = 300;

//Menu.cpp
constexpr const char* START_BUTTON = "../assets/menu/start.txt";
constexpr const char* EXIT_BUTTON = "../assets/menu/exit.txt";
constexpr const char* GAMEOVER = "../assets/menu/gameOver.txt";
constexpr const char* DEFEATED_KNIGHT = "../assets/knight/defeated.txt";
constexpr const char* LEFT_UP_CORNER = "../assets/menu/1.txt";
constexpr const char* RIGHT_UP_CORNER = "../assets/menu/2.txt";
constexpr const char* LEFT_DOWN_CORNER = "../assets/menu/3.txt";
constexpr const char* RIGHT_DOWN_CORNER = "../assets/menu/4.txt";
constexpr const char* KNIGHT_ICON = "../assets/knight/main.txt";

//Player.cpp
constexpr const char* KNIGHT = "../assets/knight/icon.txt";
constexpr const char* HP = "../assets/bar/hp.txt";
constexpr const char* DMG = "../assets/bar/dmg.txt";
constexpr const char* SWORD = "../assets/knight/sword.txt";
constexpr const char* BOW = "../assets/knight/bow.txt";

//Field.cpp
constexpr const char* TURN_BAR = "../assets/bar/turn.txt";