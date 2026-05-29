#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define HEIGHT 20
#define WIDTH 40

float velocity = 0;
float gravity = 9.8;
float y = 1;
float dt = 0.1;

void draw()
{
    int i,j;

    for(i=0;i<HEIGHT;i++)
    {
        for(j = 0;j<WIDTH; j++)
        {
            if((int)y==i && j==WIDTH/2)
            {
                printf("0");
            }

            else if(i==HEIGHT-1)
            {
                printf("_");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
void ball(float dt)
{
    velocity = velocity+gravity*dt;
    y = y+velocity*dt;
    if(y>=HEIGHT-1)
    {
        y = HEIGHT-1;
        velocity = -velocity*0.8;
    }
}
int main()
{
    while(1)
    {
        system("cls");
        draw();
        ball(dt);
        usleep(10000);
    }

}
