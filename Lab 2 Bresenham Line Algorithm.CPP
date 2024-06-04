#include <stdio.h>
#include <conio.h>
#include <graphics.h>

void main()
{
	int gd = DETECT, gm = DETECT;
	int x1, y1, x2, y2, i, dx, dy, p;
	int x, y;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	printf("Enter Initial Point (x1, y1): ");
	scanf("%d %d", &x1, &y1);
	printf("Enter Final Point (x2, y2): ");
	scanf("%d %d", &x2, &y2);
	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dy + dx;
	x = x1; // Initial point
	y = y1;
	i = 0; // define gareko

	while (i <= dx)
	{
		putpixel(x, y, WHITE);
		if (p < 0)
		{
			x = x + 1;
			p = p + 2 * dy;
		}
		else
		{
			x = x + 1;
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		i = i + 1;
	};
	getch();
}