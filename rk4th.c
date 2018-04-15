#include <stdio.h>

double f(double x, double y){
    return 1 + y/x;
}

int main(){
    double x0, y0, xn;
    int steps;
    printf("\nEnter x0 : ");
    scanf("%lf", &x0);
    printf("\nEnter value of y(%g) : ", x0);
    scanf("%lf", &y0);
    printf("\nEnter xn : ");
    scanf("%lf", &xn);
    printf("\nEnter number of steps : ");
    scanf("%d", &steps);

    double h = (xn - x0)/steps, x = x0, y = y0;
    while(steps--){
        double k1 = h*f(x, y);
        double k2 = h*f(x + h/2, y + k1 / 2);
        double k3 = h*f(x + h/2, y + k2 / 2);
        double k4 = h*f(x + h, y + k3);
        y += (k1 + 2*k2 + 2*k3 + k4)/6;
        x += h;
    }

    printf("\ny(%g) : %g", x, y);

    return 0;
}
