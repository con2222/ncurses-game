#pragma once

constexpr size_t FIELD_WIDTH = 20;
constexpr size_t FIELD_HEIGHT = 10;

constexpr int DOWN = 258;
constexpr int UP = 259;
constexpr int LEFT = 260;
constexpr int RIGHT = 261;
constexpr int ENTER = '\n';
constexpr int SPACE = ' ';
constexpr int TAB = 9;

#
constexpr char FLOOR = ' ';
constexpr char WALL = '#';
constexpr char PLAYER = 'K';
constexpr char ENEMY = 'X';
constexpr char ENEMY_BASE = 'B';
constexpr char SPIKED_TRAP = '^';

constexpr int PL_HEALTH = 100;
constexpr int MELEE_MODE = 0;
constexpr int MELEE_DAMAGE = 100;
constexpr int RANGE_MODE = 1;
constexpr int RANGE_DAMAGE = 3;

constexpr int EN_BASE_HP = 10;
constexpr int EN_HEALTH = 20;
constexpr int EN_DAMAGE = 5;

constexpr int WALLS_COUNT = 10;

constexpr int SPAWN_COOLDOWN = 5;

constexpr const char* KNIGHT_MELEE_BATTLE   = "../assets/knight/inBattle.txt";
constexpr const char* KNIGHT_RANGED_BATTLE  = "../assets/knight/withBow.txt";
constexpr const char* GOBLIN_BATTLE         = "../assets/enemy/goblin.txt";

constexpr const char* KNIGHT_ATTACK1        = "../assets/knight/attack1.txt";
constexpr const char* KNIGHT_ATTACK2        = "../assets/knight/attack2.txt";
constexpr const char* KNIGHT_ATTACK3        = "../assets/knight/attack3.txt";
constexpr const char* KNIGHT_SHOOT1         = "../assets/knight/shoot1.txt";
constexpr const char* KNIGHT_SHOOT2         = "../assets/knight/shoot2.txt";
constexpr const char* KNIGHT_BLOCK          = "../assets/knight/block3.txt";

constexpr const char* GOBLIN_ATTACK1        = "../assets/enemy/goblinAttack1.txt";
constexpr const char* GOBLIN_ATTACK2        = "../assets/enemy/goblinAttack2.txt";

constexpr const char* PLAYER_TURN_TXT       = "../assets/battle/playerTurn.txt";
constexpr const char* ENEMY_TURN_TXT        = "../assets/battle/enemyTurn.txt";

constexpr int PLAYER_X_OFFSET = -50;
constexpr int ENEMY_X_OFFSET  = +13;
constexpr int BATTLE_Y_OFFSET = -15;

constexpr int PLAYER_TURN_X_OFFSET = +26;
constexpr int ENEMY_TURN_X_OFFSET  = +24;




















/*const char* ascii_art = R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⢰⠀⠀⠀⠀⠀⠀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢡⠠⠀⠀⡇⣯⡄⢀⢀⢰⠢⡀⢣⠘⡄⠀⢀⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⢂⠑⡀⡇⢿⠐⡈⠪⠄⣧⣐⣄⠿⡱⢄⠀⢺⠤⢀⢰⣀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤⣀⠀⠑⢦⡤⢤⣥⡬⢧⠼⢧⠬⠯⡙⣷⣖⠧⡙⣒⣧⠵⣀⠩⣢⢿⣌⢓⢄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢄⠳⡌⠙⠡⣍⡓⠦⣌⠭⢬⣤⣡⠐⢎⢼⠷⢞⣼⣬⣱⣽⣲⢫⢻⢕⣍⠣⡱⡽⡲⡠
⠀⠀⠀⠀⠀⠀⠀⠀⡀⢕⡢⢈⠣⡾⢌⡃⠠⢘⣧⣋⠙⠦⡭⢭⡝⠶⣳⠷⢮⣽⣶⣷⣭⣹⢷⡷⣿⣯⣷⡨⢶⣿⣵⢌⡦⡀⠀
⠀⠀⠀⠀⠀⢀⢈⠢⣹⣢⣨⠖⢍⡒⠶⠨⣡⣒⣷⣶⣭⡗⣚⠚⡭⠝⠴⠦⣤⠍⣛⣓⢯⣬⣿⣽⣽⡿⣿⣿⣮⣾⡽⢷⣲⢱⡀⢀
⠀⠀⠀⠀⠀⠈⢋⢼⢽⢯⢦⡙⣓⠞⡛⣳⣙⣾⣭⣧⣄⣀⠤⠐⠒⠉⠊⠙⢛⣿⣟⣯⣾⣭⣻⣮⣻⣿⣿⣿⣿⣿⣦⠘⣞⡌⡿⣼
⠀⠀⠀⠀⠀⠀⠀⣱⢻⡔⢤⣉⣐⣤⣋⣥⡤⣽⡷⠒⠌⡀⢀⣠⡤⠚⢈⣉⡴⠯⠛⠻⢃⢛⣻⣿⣷⣿⣿⡿⣿⣿⣿⣧⣿⣶⣲⢻
⠀⠀⠀⠀⠀⠀⠀⠀⠑⠺⢅⣝⣛⣥⣍⡁⢀⣉⣠⣴⠞⣋⣽⠡⢴⠾⣋⡡⢄⣲⣈⠭⠙⠛⣻⣿⣿⣷⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠒⡤⢤⢶⠚⣋⡩⢤⣖⣍⣉⣾⢋⣬⣛⣷⡿⠋⣨⣕⣦⠓⠁⠀⣀⠴⢎⣉⠵⢛⣻⣩⣽⣿⣿⣿⣿⣿⣿⣋⣟
⠀⠀⠀⠀⠀⠀⠀⠀⣴⣙⡽⣯⡝⣋⣡⣴⣤⢿⢡⣿⣿⡿⢊⣤⠾⠋⡩⠂⢀⣴⡫⠕⣊⠕⢁⠔⢁⡼⠋⠁⡁⣸⣿⣿⣿⣿⣛⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⡇⠀⠀⠀⢠⡀⢸⡻⡴⣷⣩⡟⠩⡠⢊⡠⣰⠟⢁⠄⠊⢀⡴⠋⠔⠉⠀⡘⢰⢀⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢡⢠⡄⠀⠀⡘⢩⠗⢪⢋⡟⣐⠥⠶⣹⠼⠑⢈⣀⣴⠜⢁⠀⠀⢠⡕⣽⠀⣟⣾⣿⢻⢻⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⠚⡁⠋⠀⠠⡦⠢⠴⢥⣎⣜⣡⣶⣾⣶⣾⣿⣭⣽⣠⠴⢃⣔⣪⡞⣱⣷⠸⣼⣟⣧⣟⣼⣟⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡟⣷⡀⠀⠀⠀⣧⢠⡔⢋⣡⣾⣿⣿⢻⡏⠛⢻⣿⡟⢁⣴⣫⢻⣿⣲⣿⣾⡀⣷⣛⡟⣬⣿⢹⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⣛⠻⢿⣦⠀⠀⠈⠈⢡⡜⣿⡿⠟⡿⠃⠀⣄⢳⣿⡿⣿⢿⡿⣿⣽⣿⣿⡿⣧⣿⣿⣷⣿⠛⢸⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣡⠻⡷⣦⡿⠆⠀⠀⢠⣦⠀⢸⡅⠰⠃⠘⣦⡾⣧⡏⡄⢣⡄⣀⣿⣛⣬⡅⣶⣿⣿⣿⣿⢹⡄⣻⣿⣯⣿
⠀⠀⠀⠀⠀⠀⠀⠀⡠⠃⠀⢧⠀⣳⡀⠀⢠⣾⡿⠆⢈⣣⠀⠀⠀⡞⠃⠻⢀⠀⢾⣧⣉⣛⣉⣤⣶⣿⡟⠸⡌⢾⠀⣣⣿⡏⢫⡿
⠀⠀⠀⠀⠀⠀⠀⣾⣀⠀⠀⠙⠃⠘⠃⠠⣼⡇⠀⠀⢨⡖⠀⠀⠀⠁⠀⠀⠈⠁⠈⠻⢿⣿⣿⣿⠟⡹⠶⠁⡓⡘⣆⠿⠡⢠⡏⡿
⠀⠀⠀⠀⠀⠀⠀⠈⠺⢗⣦⣄⣀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠤⠀⠀⠀⠀⣫⣿⣿⣿⠀⢧⢸⠀⡿⢰⢣⢸⡇⡜⣸⣼
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢮⣿⡟⡿⣿⡿⣿⡿⣿⠿⢻⡿⠟⢉⠀⠔⠁⠀⠀⠀⢿⣹⡟⣿⡄⣽⣿⢃⢣⢸⣮⢿⢼⢡⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣧⣵⣾⣾⣿⠿⢻⠇⢀⠔⠁⠀⡜⠐⠀⠄⢐⣿⣎⣿⡹⢷⡄⣿⣿⣼⢿⡟⢹⢀⣡⡽⣽
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⣠⡾⢁⣴⣏⡠⠊⠀⡠⠊⠀⠀⣄⣀⣼⣇⠫⢢⡧⢘⣧⡽⣬⢷⡞⡷⡠⢳⢾⠣⡼
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠖⠁⠀⢀⠟⡹⠋⠁⣴⠁⠀⠀⠀⣸⡟⠀⢦⣁⣬⢡⠷⣫⢵⡘⠸⠇⡷⠯⡍⠸⡔⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⡄⠀⠀⣼⣚⣁⣀⣞⣉⣀⣀⣴⣯⣾⣧⣴⣾⣿⣿⠊⠀⠈⠃⠹⠃⠀⠣⠀⠀⠀⢷⠤
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡦
⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀
⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀
⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀
)";*/