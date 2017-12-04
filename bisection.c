#include <stdio.h>
#include <math.h>

#define f(x) (x*x*x - 3*x*x + 3*x - 1)
#define EPSILON 0.0001
#define STEPS 20

int main(){
    double a, b;
    printf("\nEquation : x^3 - 3*x^2 + 3*x - 1");
restart:
    printf("\nEnter initial approximation of the root : ");
    scanf("%lf%lf", &a, &b);
    if(f(a)*f(b) > 0){
        printf("The root does not lie between %g and %g!", a, b);
        goto restart;
    }
    int it = 0;
    double prevroot = a, preva = a, prevb = b;
    printf("\nIteration\t    a    \t   f(a)  \t    b    \t   f(b)  \t    c    \t   f(c)  ");
    printf("\n=========\t=========\t=========\t=========\t=========\t=========\t=========");
    while(it < STEPS){
        double c = (a+b)/2;
        printf("\n%9d\t", (it+1));
        if(preva != a)
            printf("*%8lf", a);
        else
            printf("%9lf", a);
        printf("\t%9lf\t", f(a));
        if(prevb != b)
            printf("*%8lf", b);
        else
            printf("%9lf", b);
        printf("\t%9lf\t%9lf\t%9lf", f(b), c, f(c));
        preva = a; prevb = b;
        if(fabs(c-prevroot) < EPSILON){
            printf("\nRoot found : %10lf", prevroot);
            return 0;
        }
        if(f(b) * f(c) < 0){
            a = c;
        }
        else{
            b = c;
        }
        prevroot = c;
        it++;
    }
    printf("\nRoot does not converge in %2d steps!", it);
}
