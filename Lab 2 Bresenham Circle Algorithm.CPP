#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>

void main()
{
int gd = DETECT, gm = DETECT;
int x, y, p, q, d, r;
initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
printf("Enter Center of Circle(h,k): ");
scanf("%d %d", &p, &q);
printf("Enter radius of Circle(r): ");
scanf("%d", &r);
d = 3 - 2*r;
x = 0;            // Initial point
y = r;	    // define gareko
while(x <= y){
	putpixel(x+p, y+q, RED);
	putpixel(x+p,-y+q, RED);
	putpixel(-x+p,-y+q, RED);
	putpixel(-x+p, y+q, RED);
	putpixel(y+p, x+q, RED);
	putpixel(y+p,-x+q, RED);
	putpixel(-y+p, -x+q, RED);
	putpixel(-y+p, x+q, RED);
	if(d<=0){
	x = x + 1;
	d = d + 4*x + 6;
	}
	else{
	x = x + 1;
	y = y - 1;
	d = d + 4*(x-y) + 10;
	}
}
getch();
}