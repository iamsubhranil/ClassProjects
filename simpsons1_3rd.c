#include <stdio.h>
#include <math.h>
#define f(x) (x*log(x))

int main(){
    double start, end, numStep;
inputlimit:
    printf("\nEnter lower limit : ");
    scanf("%lf", &start);
    printf("\nEnter upper limit : ");
    scanf("%lf", &end);
    if(end < start)
        goto inputlimit;
inputstep:
    printf("\nEnter number of steps : ");
    scanf("%lf", &numStep);
    if(numStep < 1)
        goto inputstep;

    double delta = (end - start)/numStep, temp = start + delta, sum = f(start)+f(end);
    int count = 1;
    while(temp < end){
        double y = f(temp);
        if(count % 2 == 1)
            y *= 4;
        else
            y *= 2;
        sum += y;
        temp += delta;
        count++;
    }
    sum *= (delta/3);

    printf("\nIntegral value : %g", sum);
    return 0;
}
