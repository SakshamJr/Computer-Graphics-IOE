#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> // For malloc and freer

// Clipping window
int xmin, ymin, xmax, ymax;

void liangBarskyClip(int x0, int y0, int x1, int y1)
{
    float t0 = 0.0, t1 = 1.0;
    int dx = x1 - x0;
    int dy = y1 - y0;

    float p[4], q[4];
    p[0] = -dx;
    q[0] = x0 - xmin;
    p[1] = dx;
    q[1] = xmax - x0;
    p[2] = -dy;
    q[2] = y0 - ymin;
    p[3] = dy;
    q[3] = ymax - y0;

    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0)
        {
            if (q[i] < 0)
                return; // Parallel line is outside the clipping window
        }
        else
        {
            float t = q[i] / p[i];
            if (p[i] < 0)
            {
                if (t > t1)
                    return;
                if (t > t0)
                    t0 = t;
            }
            else
            {
                if (t < t0)
                    return;
                if (t < t1)
                    t1 = t;
            }
        }
    }

    if (t0 > t1)
        return;

    int clipped_x0 = x0 + t0 * dx;
    int clipped_y0 = y0 + t0 * dy;
    int clipped_x1 = x0 + t1 * dx;
    int clipped_y1 = y0 + t1 * dy;

    line(clipped_x0, clipped_y0, clipped_x1, clipped_y1);
}

int main()
{
    int gd = DETECT, gm = DETECT;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    printf("Enter clipping window boundaries xmin, ymin, xmax, ymax: ");
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);

    int number;
    printf("Enter number of lines you want: ");
    scanf("%d", &number);
    // Create  n arrays for the lines
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
    printf("After Line Clipping: ");

    // Draw the clipping window again
    rectangle(xmin, ymin, xmax, ymax);

    // Clip lines using Liang-Barsky algorithm and draw clipped lines
    for (i = 0; i < number; i++)
    {
        liangBarskyClip(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
    }

    // Free dynamically allocated memory
    free(lines);

    getch();
    closegraph();
    return 0;
}
