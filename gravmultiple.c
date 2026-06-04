#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define WIDTH 50
#define HEIGHT 20

#define G 0.5
#define DT 0.1
#define NUM_PLANETS 5


#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

typedef struct {
    double x, y;
    double vx, vy;
    double mass;
} Body;

void hideCursor() {
    printf("\033[?25l");
}

void showCursor() {
    printf("\033[?25h");
}

void handle_exit(int sig) {
    showCursor();
    printf("\n");
    exit(0);
}

void draw(Body sun, Body planets[], int num_planets) {
    char grid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = ' ';

    int sx = (int)sun.x;
    int sy = (int)sun.y;

    if (sx >= 0 && sx < WIDTH && sy >= 0 && sy < HEIGHT)
        grid[sy][sx] = '*';

    for (int i = 0; i < num_planets; i++) {
        int px = (int)planets[i].x;
        int py = (int)planets[i].y;
        if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
            grid[py][px] = '1' + i;
        }
    }

    printf("\033[H");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            char c = grid[i][j];

            if (c == '*')
                printf(YELLOW "%c" RESET, c);
            else if (c == '1')
                printf(CYAN "@" RESET);
            else if (c == '2')
                printf(GREEN "O" RESET);
            else if (c == '3')
                printf(MAGENTA "0" RESET);
            else if (c == '4')
                printf(RED "o" RESET);
            else if (c == '5')
                printf(BLUE "@" RESET);
            else
                printf("%c", c);
        }
        putchar('\n');
    }
}

void update(Body *sun, Body *planet) {
    double dx = sun->x - planet->x;
    double dy = sun->y - planet->y;

    double dist = sqrt(dx*dx + dy*dy + 0.0001);

    double force = (G * sun->mass * planet->mass) / (dist * dist);

    double ax = force * dx / dist / planet->mass;
    double ay = force * dy / dist / planet->mass;

    planet->vx += ax * DT;
    planet->vy += ay * DT;

    planet->x += planet->vx * DT;
    planet->y += planet->vy * DT;
}

int main() {
    signal(SIGINT, handle_exit);

    setbuf(stdout, NULL);
    hideCursor();

    Body sun = {20, 10, 0, 0, 500};

    Body planets[NUM_PLANETS];


    double r1 = 4.5;
    double v1 = sqrt(G * sun.mass / r1);
    planets[0] = (Body){20 + r1, 10, 0, v1, 10};


    double r2 = 6.5;
    double v2 = sqrt(G * sun.mass / r2);
    planets[1] = (Body){20 + r2, 10, 0, v2, 10};


    double r3 = 8.5;
    double v3 = sqrt(G * sun.mass / r3);
    planets[2] = (Body){20 + r3, 10, 0, v3, 10};


    double r4 = 3.5;
    double v4 = sqrt(G * sun.mass / r4);
    planets[3] = (Body){20 + r4, 10, 0, v4, 10};


    double r5 = 9.5;
    double v5 = sqrt(G * sun.mass / r5);
    planets[4] = (Body){20 + r5, 10, 0, v5, 10};

    while (1) {
        draw(sun, planets, NUM_PLANETS);

        for (int i = 0; i < NUM_PLANETS; i++) {
            update(&sun, &planets[i]);
        }

        usleep(15000);
    }

    return 0;
}
