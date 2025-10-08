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