#include<stdio.h>
#include<math.h>
#include<unistd.h>
int main()
{
    float a = 0;
    while(1)
    {
        int p1 = 20 +sin(a)*10;
        int p2 = 20 +sin(a+3.14)*10;
        for(int i=0;i<35;i++)
        {
            if(i==p1) printf("\033[1;32m001");
            else if(i==p2) printf("\033[1;33m101");
            else if (i<p1 && i>p2) printf("\033[1;31m=");
            else if (i<p2 && i>p1) printf("\033[1;31m=");
            else printf(" ");
        }
        printf("\n");
        usleep(100000);
        a+=0.2;
    }
}