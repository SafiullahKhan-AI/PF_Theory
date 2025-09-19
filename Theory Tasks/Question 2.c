#include <stdio.h>
int main(){
    float x;
	float y;
    printf("Enter x co-ordinate:");
    scanf("%f",&x);
    printf("Enter y co-ordinate:");
    scanf("%f",&y);
    if (x==0 && y==0){
        printf("Point is on origin (0,0)");
    }
    else if ((x<0||x>0) && y==0){
        printf("Point (%.2f,0) is at x-intercept",x);
    }
    else if ((y<0||y>0) && x==0){
        printf("Point (0,%.2f) is at y-intercept",y);
    }
     else if ( x>0 && y>0){
        printf("The Point (%.2f,%.2f) lies in Quadrant I", x,y);
    }
     else if ( x<0 && y>0){
        printf("The Point (%.2f,%.2f) lies in Quadrant II", x,y);
    }
      else if (x<0 && y<0){
        printf("The Point (%.2f,%.2f) lies in Quadrant III", x,y);
    }
      else if (x>0 && y<0){
        printf("The Point (%.2f,%.2f) lies in Quadrant IV", x,y);
    }
     return 0;
}
