#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 60
#define HEIGHT 25

#define MAX_BULLETS 40
#define MAX_ENEMIES 6

typedef struct {
    int x, y, active;
} Bullet;

typedef struct {
    int x, y, active;
} Enemy;

Bullet bullets[MAX_BULLETS];
Enemy enemies[MAX_ENEMIES];

int playerX = WIDTH / 2;
int playerY = HEIGHT - 2;

int score = 0;
int hp = 3;

HANDLE hConsole;

void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void gotoXY(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(hConsole, c);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}

void spawnEnemy(int i) {
    enemies[i].x = rand() % WIDTH;
    enemies[i].y = 0;
    enemies[i].active = 1;
}

void shoot() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].x = playerX;
            bullets[i].y = playerY - 1;
            bullets[i].active = 1;
            return;
        }
    }
}

int main() {

    srand(time(NULL));
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    hideCursor();

    for (int i = 0; i < MAX_ENEMIES; i++)
        spawnEnemy(i);

    while (hp > 0) {

        // INPUT
        if (_kbhit()) {
            char c = _getch();

            if (c == 'a' && playerX > 0) playerX--;
            if (c == 'd' && playerX < WIDTH - 1) playerX++;
            if (c == ' ') shoot();
            if (c == 'q') break;
        }

        // update bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].y--;
                if (bullets[i].y < 0)
                    bullets[i].active = 0;
            }
        }

        // update enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) continue;

            enemies[i].y++;

            if (enemies[i].y >= HEIGHT)
                spawnEnemy(i);

            if (enemies[i].x == playerX &&
                enemies[i].y == playerY) {

                hp--;
                spawnEnemy(i);
            }
        }

        // collision
        for (int b = 0; b < MAX_BULLETS; b++) {
            if (!bullets[b].active) continue;

            for (int e = 0; e < MAX_ENEMIES; e++) {
                if (!enemies[e].active) continue;

                if (bullets[b].x == enemies[e].x &&
                    bullets[b].y == enemies[e].y) {

                    bullets[b].active = 0;
                    spawnEnemy(e);
                    score++;
                }
            }
        }

        // DRAW
        gotoXY(0, 0);

        for (int y = 0; y < HEIGHT; y++) {

            for (int x = 0; x < WIDTH; x++) {

                // SKY BACKGROUND
                setColor(9); // blue sky

                char ch = '.';

                // PLAYER (GREEN)
                if (x == playerX && y == playerY) {
                    setColor(10);
                    ch = '^';
                }

                // BULLET (WHITE)
                for (int i = 0; i < MAX_BULLETS; i++) {
                    if (bullets[i].active &&
                        bullets[i].x == x &&
                        bullets[i].y == y) {
                        setColor(15);
                        ch = '|';
                    }
                }

                // ENEMY (RED)
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    if (enemies[i].active &&
                        enemies[i].x == x &&
                        enemies[i].y == y) {
                        setColor(12);
                        ch = 'V';
                    }
                }

                putchar(ch);
            }

            putchar('\n');
        }

        setColor(15);
        printf("Score: %d   HP: %d   (A/D move, SPACE shoot, Q quit)\n", score, hp);

        Sleep(33);
    }

    gotoXY(0, HEIGHT + 2);
    setColor(15);
    printf("\nGAME OVER! Score: %d\n", score);

    return 0;
}
