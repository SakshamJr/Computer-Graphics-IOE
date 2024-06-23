#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;	  // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;	  // 1000

// Clipping Window Boundaries
int xmin, ymin, xmax, ymax;

// Function to find the region code of a point (x, y)
int computeCode(int x, int y)
{
	int code = INSIDE;

	if (x < xmin)
		code |= LEFT;
	else if (x > xmax)
		code |= RIGHT;
	if (y < ymin)
		code |= BOTTOM;
	else if (y > ymax)
		code |= TOP;
	return code;
}

// Cohen-Sutherland clipping algorithm
void cohenSutherClip(int x0, int y0, int x1, int y1)
{
	int code0 = computeCode(x0, y0);
	int code1 = computeCode(x1, y1);
	int accept = 0;

	while (1)
	{
		if ((code0 == 0) && (code1 == 0))
		{
			accept = 1;
			break;
		}
		else if (code0 & code1)
		{
			break;
		}
		else
		{
			int codeOut;
			int x, y;

			if (code0 != 0)
				codeOut = code0;
			else
				codeOut = code1;

			if (codeOut & TOP)
			{
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			}
			else if (codeOut & BOTTOM)
			{
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			}
			else if (codeOut & RIGHT)
			{
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			}
			else if (codeOut & LEFT)
			{
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (codeOut == code0)
			{
				x0 = x;
				y0 = y;
				code0 = computeCode(x0, y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				code1 = computeCode(x1, y1);
			}
		}
	}

	if (accept)
	{
		line(x0, y0, x1, y1);
	}
}

int main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	printf("Enter clipping window coordinates as xmin, ymin, xmax, ymax: ");
	scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);
	int number;
	printf("Enter the number of lines you want: ");
	scanf("%d", &number);
	int(*lines)[4] = (int(*)[4])malloc(number * 4 * sizeof(int));
	for (int i = 0; i < number; i++)
	{
		printf("Enter coordinates of line %d (x0, y0, x1, y1): ", i + 1);
		scanf("%d %d %d %d", &lines[i][0], &lines[i][1], &lines[i][2], &lines[i][3]);
	}

	// Draw the clipping window
	rectangle(xmin, ymin, xmax, ymax);

	// Draw lines before clipping
	for (i = 0; i < number; i++)
	{
		line(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
	}
	printf("Before Line Clipping: ");
	getch();
	cleardevice();
	printf("After Line Clipping:");
	// Draw the clipping window again
	rectangle(xmin, ymin, xmax, ymax);

	// Clip lines using Cohen-Sutherland algorithm and draw clipped lines
	for (i = 0; i < number; i++)
	{
		cohenSutherClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
	}

	getch();
	closegraph();
	return 0;
}
