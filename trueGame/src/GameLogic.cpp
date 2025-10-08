#include <GameLogic.hpp>
#include <Utils.hpp>
#include <Constants.hpp>
#include <Color.hpp>
#include <Floor.hpp>
#include <ncurses.h>
#include <iostream>
#include <locale.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>   // для fork, exec, getpid
#include <sys/wait.h> // для waitpid
#include <signal.h>   // для kill
#include <fcntl.h>
//int startBattle(ScreenSize* screen, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy)

const char* ascii_art = R"(
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
)";

/*int startBattle() {
    clear();


    int height, width;
    getmaxyx(stdscr, height, width);

    int middle_col = width / 2;
    int left_width = middle_col;
    int right_width = width - middle_col;


    WINDOW* left_win = newwin(height, left_width, 0, 0);
    WINDOW* right_win = newwin(height, right_width, 0, left_width);

    box(left_win, 0, 0);
    box(right_win, 0, 0);

    print_multiline(left_win, 5, 10, ascii_art);
    print_multiline(right_win, 4, 2, ascii_art);

    refresh();
    wrefresh(left_win);
    wrefresh(right_win);


    while(getch() != 'q');

    delwin(left_win);
    delwin(right_win);

    return 0;
}*/

static pid_t music_pid = -1;

void stopMusic();

void playMusicInBackground(const std::string& filename) {
    // Если уже играет — сначала остановим
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс: подавляем весь вывод
        int fd = open("/dev/null", O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        close(fd);

        // Запускаем mpg123 в тихом режиме
        execlp("mpg123", "mpg123", "-q", filename.c_str(), (char*)nullptr);
        _exit(1); // если не удалось запустить
    } else if (pid > 0) {
        // Родитель: запоминаем PID
        music_pid = pid;
        //std::cout << "Музыка запущена в фоне (PID: " << music_pid << ")\n";
    } else {
        std::cerr << "Ошибка: не удалось создать процесс\n";
    }
}

void stopMusic() {
    if (music_pid == -1) {
        std::cout << "Музыка не воспроизводится.\n";
        return;
    }

    //Отправляем сигнал завершения
    if (kill(music_pid, SIGTERM) == 0) {
        // Ждём завершения (но не блокируем надолго — можно добавить таймаут)
        int status;
        waitpid(music_pid, &status, 0);
        std::cout << "Музыка остановлена.\n";
    } else {
        std::cerr << "Не удалось остановить процесс " << music_pid << "\n";
    }
    kill(music_pid, SIGTERM);

    music_pid = -1;
}

int startBattle(const ScreenSize* const screen, std::vector<std::vector<Ceil>>& ceils, std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy) {
    clear();

    int width, height;
    height = screen->yMax;
    width = screen->xMax;
    WINDOW* pl_bar = newwin(height/5, width/6, 0, 0);
    wborder(pl_bar, '|', '|', '=', '=', '#', '#', '#', '#');
    mvwhline(pl_bar, 2, 1, ACS_HLINE, width/6 - 2);
    mvwaddch(pl_bar, 2, 0, '+');
    mvwaddch(pl_bar, 2, width/6 - 1, '+');
    
    WINDOW* en_bar = newwin(height/5, width/6, 0, width - width/6);
    wborder(en_bar, '|', '|', '=', '=', '#', '#', '#', '#');
    mvwhline(en_bar, 2, 1, ACS_HLINE, width/6 - 2);
    mvwaddch(en_bar, 2, 0, '+');
    mvwaddch(en_bar, 2, width/6 - 1, '+');

    WINDOW* act_bar = newwin(height/5, width/6, height - height / 5, 0);
    wborder(act_bar, '|', '|', '-', '-', '+', '+', '+', '+');
    
    print_multiline(height/2 - height/4, width/2 - width/4, ascii_art);

    refresh();
    wrefresh(pl_bar);
    wrefresh(en_bar);
    wrefresh(act_bar);

    std::vector<std::string> options {"Attack", "Change weapon"};
    int option = 0;
    int ch;
    playMusicInBackground("music1.mp3");
    while (ch != 'q') {
        
        mvwprintw(pl_bar, 5, 5, "Health: %d", player->getHealth());
        mvwprintw(en_bar, 5, 5, "Health: %d", enemy->getHealth());
        if (player->getMode() == MELEE_MODE) {
            mvwprintw(pl_bar, 6, 5, "MODE: MELEE");
        } else {
            mvwprintw(pl_bar, 6, 5, "MODE: RANGE");
        }
        for (int i = 0; i < 2; i++) {
            if (option == i) {
                wattron(act_bar, COLOR_PAIR(static_cast<int>(ColorPair::BATTLE_BUTTON)));
                mvwprintw(act_bar, 5 + i, width/6/4, "%s", options[i].c_str());
                wattroff(act_bar, COLOR_PAIR(static_cast<int>(ColorPair::BATTLE_BUTTON)));
            } else {
                mvwprintw(act_bar, 5 + i, width/6/4, "%s", options[i].c_str());
            }
        }
        refresh();
        wrefresh(act_bar);
        wrefresh(pl_bar);
        wrefresh(en_bar);
        ch = getch();

        switch (ch) {
            case KEY_UP:
                if (option > 0) {
                    option--;
                }
                break;
            case KEY_DOWN:
                if  (option < 1) {
                    option++;
                }
                break;
            default:
                break;
        }

        if (ch == ENTER) {
            if (options[option] == "Attack") {
                enemy->takeDamage(player->attack());
                if (enemy->getHealth() <= 0) {
                    ceils[enemy->getY() - screen->yMax/2 + FIELD_HEIGHT/2][enemy->getX() - screen->xMax/2 + FIELD_WIDTH/2].setEntity(std::make_shared<Floor>(enemy->getX(), enemy->getY()));
                    break;
                }
            }
        }

    }
    stopMusic();

    delwin(pl_bar);
    delwin(en_bar);
    delwin(act_bar);
    endwin();

    return 0;
}