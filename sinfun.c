#include<stdio.h>
#define PI 3.14159265358979323846
double rad(double x)
{
    return x*(PI/180);
}
double custom_sin(double x)
{
    double term = x;
    double sum = x;
    int i;
    for(i=1;i<=15;i++)
    {
        term = term*(-x*x)/((2*i)*(2*i+1));
        sum = sum + term;
    }
    return sum;
}
int main()
{
    double deg = 90;
    deg = rad(deg);
    double value = custom_sin(deg);
    printf("%lf",value);
    return 0;
}
