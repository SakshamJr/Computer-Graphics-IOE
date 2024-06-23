#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

#define PI 3.1415

// create a translation matrix T(tx,ty)
void translation(float tx, float ty, float t[3][3])
{
    t[0][0] = 1;
    t[0][1] = 0;
    t[0][2] = tx;
    t[1][0] = 0;
    t[1][1] = 1;
    t[1][2] = ty;
    t[2][0] = 0;
    t[2][1] = 0;
    t[2][2] = 1;
}

// create a scaling matrix S(sx,sy)
void scaling(float sx, float sy, float s[3][3])
{
    s[0][0] = sx;
    s[0][1] = 0;
    s[0][2] = 0;
    s[1][0] = 0;
    s[1][1] = sy;
    s[1][2] = 0;
    s[2][0] = 0;
    s[2][1] = 0;
    s[2][2] = 1;
}

// create a rotation matrix R(theta)
void rotation(float angle, float r[3][3])
{
    float rad = angle * PI / 180.0;
    r[0][0] = cos(rad);
    r[0][1] = -sin(rad);
    r[0][2] = 0;
    r[1][0] = sin(rad);
    r[1][1] = cos(rad);
    r[1][2] = 0;
    r[2][0] = 0;
    r[2][1] = 0;
    r[2][2] = 1;
}

// create a shearing matrix SH(shx, shy)
void shearing(float shx, float shy, float sh[3][3])
{
    sh[0][0] = 1;
    sh[0][1] = shx;
    sh[0][2] = 0;
    sh[1][0] = shy;
    sh[1][1] = 1;
    sh[1][2] = 0;
    sh[2][0] = 0;
    sh[2][1] = 0;
    sh[2][2] = 1;
}

// create a reflection matrix REF(x = a)
void reflectionX(float a, float ref[3][3])
{
    ref[0][0] = -1;
    ref[0][1] = 0;
    ref[0][2] = 2 * a;
    ref[1][0] = 0;
    ref[1][1] = 1;
    ref[1][2] = 0;
    ref[2][0] = 0;
    ref[2][1] = 0;
    ref[2][2] = 1;
}

// create a reflection matrix REF(y = a)
void reflectionY(float a, float ref[3][3])
{
    ref[0][0] = 1;
    ref[0][1] = 0;
    ref[0][2] = 0;
    ref[1][0] = 0;
    ref[1][1] = -1;
    ref[1][2] = 2 * a;
    ref[2][0] = 0;
    ref[2][1] = 0;
    ref[2][2] = 1;
}

// matrix multiply garna
void transform(float p[3], float m[3][3], float result[3])
{
    for (int i = 0; i < 3; i++)
    {
        result[i] = 0;
        for (int j = 0; j < 3; j++)
        {
            result[i] += p[j] * m[i][j];
        }
    }
}

// triangle draw garna lai
void drawTriangle(float p1[3], float p2[3], float p3[3], int color)
{
    setcolor(color);
    line(p1[0], p1[1], p2[0], p2[1]);
    line(p2[0], p2[1], p3[0], p3[1]);
    line(p3[0], p3[1], p1[0], p1[1]);
}

int main()
{
    int repeat = 1;

    int gd = DETECT, gm = DETECT;

    float x1, y1, x2, y2, x3, y3;
    printf("Enter coordinates of the triangle:\n");
    printf("(x1 y1): ");
    scanf("%f %f", &x1, &y1);
    printf("(x2 y2): ");
    scanf("%f %f", &x2, &y2);
    printf("(x3 y3): ");
    scanf("%f %f", &x3, &y3);
    while (repeat == 1)
    {
        initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
        float p1[3] = {x1, y1, 1};
        float p2[3] = {x2, y2, 1};
        float p3[3] = {x3, y3, 1};

        // original triangle (before transformation)
        drawTriangle(p1, p2, p3, WHITE);
        int choice;
        printf("Choose the transformation:\n");
        printf("1. Translation\n2. Scaling\n3. Rotation\n4. Shearing\n5. Reflection about x = a\n6. Reflection about y = a\n");
        scanf("%d", &choice);

        // transformation matrix, like T or R or S or SH or REF
        float t[3][3];
        float t1[3], t2[3], t3[3];

        switch (choice)
        {
        case 1:
        {
            // Translation ko lagi
            float tx, ty;
            printf("Enter translation factors (tx ty): ");
            scanf("%f %f", &tx, &ty);
            translation(tx, ty, t);
            break;
        }
        case 2:
        {
            // Scaling ko lagi
            float sx, sy;
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            scaling(sx, sy, t);
            break;
        }
        case 3:
        {
            // Rotation ko lagi
            float angle;
            printf("Enter rotation angle (in degrees): ");
            scanf("%f", &angle);
            rotation(angle, t);
            break;
        }
        case 4:
        {
            // Shearing ko lagi
            float shx, shy;
            printf("Enter shearing factors (shx shy): ");
            scanf("%f %f", &shx, &shy);
            shearing(shx, shy, t);
            break;
        }
        case 5:
        {
            // Reflection about x = a ko lagi
            float a;
            printf("Enter the x-coordinate of the line x = a for reflection: ");
            scanf("%f", &a);
            reflectionX(a, t);
            break;
        }
        case 6:
        {
            // Reflection about y = a ko lagi
            float a;
            printf("Enter the y-coordinate of the line y = a for reflection: ");
            scanf("%f", &a);
            reflectionY(a, t);
            break;
        }
        default:
            printf("Invalid choice!\n");
            closegraph();
            return 1;
        }

        // apply the transformation matrix to each point of the triangle
        transform(p1, t, t1);
        transform(p2, t, t2);
        transform(p3, t, t3);

        // transformed triangle draw garna lai
        drawTriangle(t1, t2, t3, GREEN);
        printf("\n\n\n");
        printf("Do You Want to redo?: ");
        scanf("%d", &repeat);
        cleardevice();
    }
    closegraph();
    return 0;
}
