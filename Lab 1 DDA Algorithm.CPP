#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <graphics.h>

void main()
{
	int gd = DETECT, gm = DETECT;
	int i, x1, y1, x2, y2, step, dx, dy;
	float x, y, xinc, yinc;
	initgraph(&gd, &gm, "C:\TURBOC3\\BGI");
	printf("enter x1,y1:");
	scanf("%d %d", &x1, &y1);
	printf("enter x2, y2:");
	scanf("%d %d", &x2, &y2);
	dx = x2 - x1;
	dy = y2 - y1;
	x = x1;
	y = y1;
	step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	xinc = dx / (float)step;
	yinc = dy / (float)step;
	putpixel(x, y, RED);
	for (i = 0; i <= step; i++)
	{
		x = x + xinc;
		y = y + yinc;
		putpixel((int)(x + 0.5), (int)(y + 0.5), RED);
	}
	getch();
}