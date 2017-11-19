#include <stdio.h>
#include <math.h>

#define PI acos(-1.0)

int main(){
    float deg;
    printf("Enter the value of angle (in degree) : ");
    scanf("%f", &deg);
    float rad = (PI/180) * deg;
    float sine = rad;
    int sign = -1, index = 3;
    while(1){
        float numer = pow(rad, index);
        float j = 1, denom = 1;
        while(j <= index)
            denom *= j++;
        if(fabsl(numer/denom) < 0.0001)
            break;
        float term = (sign * numer)/denom;
        sine = sine + term, index = index + 2, sign *= -1;
    }
    float orig = sin(rad);
    float error = fabsl(orig-sine);
    printf("The value of sin(%g) as per series : %g", rad, sine);
    printf("\nThe value of sin(%g) as per library function : %g", rad, orig);
    printf("\nAbsolute error : %g\n", error);
    return 0;
}
