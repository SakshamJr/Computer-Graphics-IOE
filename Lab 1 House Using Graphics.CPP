#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <conio.h>
void main()
{
    int gd = DETECT, gm = DETECT;
    initgraph(&gd, &gm, "C:\TURBOC3\\BGI");
    outtext("Graphics Lab!");
    line(10, 300, 10, 200);
    line(10, 200, 150, 200);
    line(10, 300, 150, 300);
    line(150, 300, 150, 200);
    circle(30, 240, 10);
    circle(130, 240, 10);
    rectangle(70, 250, 90, 300);
    line(10, 200, 80, 150); // roof
    line(80, 150, 150, 200);
    getch();
}