#include <Window.hpp>
#include <Color.hpp>

void draw_player_bar(WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar, int width) {
    wborder(pl_bar, '|', '|', '=', '=', '#', '#', '#', '#');
    mvwhline(pl_bar, 2, 1, ACS_HLINE, width / 6 - 2);
    mvwaddch(pl_bar, 2, 0, '+');
    mvwaddch(pl_bar, 2, width / 6 - 1, '+');

    wborder(en_bar, '|', '|', '=', '=', '#', '#', '#', '#');
    mvwhline(en_bar, 2, 1, ACS_HLINE, width / 6 - 2);
    mvwaddch(en_bar, 2, 0, '+');
    mvwaddch(en_bar, 2, width / 6 - 1, '+');

    wborder(act_bar, '|', '|', '-', '-', '+', '+', '+', '+');
}

WINDOW* create_player_bar(int height, int width) {
    WINDOW* pl_bar = newwin(height / 5, width / 6, 0, 0);
    return pl_bar;
}

WINDOW* create_enemy_bar(int height, int width) {
    WINDOW* en_bar = newwin(height / 5, width / 6, 0, width - width / 6);
    return en_bar;
}

WINDOW* create_action_bar(int height, int width) {
    WINDOW* act_bar = newwin(height / 5, width / 6, height - height / 5, 0);
    return act_bar;
}

void update_battle_windows(
    WINDOW* pl_bar, WINDOW* en_bar, WINDOW* act_bar,
    std::shared_ptr<Player> player, std::shared_ptr<Enemy> enemy,
    const std::vector<std::string>& options, int selected_option,
    BattleTurn turn, int width)
{
    werase(pl_bar);
    werase(en_bar);
    werase(act_bar);

    draw_player_bar(pl_bar, en_bar, act_bar, width);


    mvwprintw(pl_bar, 5, 5, "Health: %d", player->getHealth());
    if (player->getMode() == MELEE_MODE) {
        mvwprintw(pl_bar, 6, 5, "MODE: MELEE");
    } else {
        mvwprintw(pl_bar, 6, 5, "MODE: RANGE");
    }

    mvwprintw(en_bar, 5, 5, "Health: %d", enemy->getHealth());

    for (int i = 0; i < 2; i++) {
        if (selected_option == i) {
            wattron(act_bar, COLOR_PAIR(static_cast<int>(ColorPair::BATTLE_BUTTON)));
            mvwprintw(act_bar, 5 + i, width / 6 / 4, "%s", options[i].c_str());
            wattroff(act_bar, COLOR_PAIR(static_cast<int>(ColorPair::BATTLE_BUTTON)));
        } else {
            mvwprintw(act_bar, 5 + i, width / 6 / 4, "%s", options[i].c_str());
        }
    }

    wrefresh(act_bar);
    wrefresh(pl_bar);
    wrefresh(en_bar);
}