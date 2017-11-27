#include <stdio.h>

// Procedure to find HCF between m and n
int HCF(int m, int n) {
    if (!m) // m is zero, so n is hcf
        return n;
    if (!n) // n is zero, so m is hcf
        return m;
    // both are non-zero, so re-divide m,
    // and make it new n
    // new m is old n
    return (HCF(n, m % n)); // Recursive call
}

// Procedure to find LCM between m and n
// n : number2
// x : number1
// m : present i*x, i = 1,2,3,...
// initially n < x
int LCM(int m, int n, int x) {
    if (m % n)                       // Remainder is greater than zero, so we're
                                     // gonna go to the next factor of m
                                     // and check if that is divisible by n
        return (LCM((m + x), n, x)); // Recursive call
    else
        return m; // m is completely divisible by n
}

// Driver
int main() {
    int n, i, lc, hc;
    printf("\nEnter number of elements : ");
    scanf("%d", &n);
    if (n < 1) {
        printf("\n[Error] Number of elements must be positive!");
        return 1;
    }
    int A[n];
    printf("Enter 1st number : ");
    scanf("%d", &A[0]);
    lc = hc = A[0];
    for (i = 1; i < n; i++) {
        int j = i + 1, suf = j % 10; // for display purposes
        printf("Enter %d%s number : ", j,
               suf == 1 ? "st" : // *1st
               suf == 2 ? "nd" : // *2nd
               suf == 3 ? "rd" : "th"); // *3rd / *th

        scanf("%d", &A[i]); // input

        if (lc < A[i])
            lc = LCM(A[i], lc, A[i]); // LCM Function calling
        else
            lc = LCM(lc, A[i], lc);
        hc = HCF(hc, A[i]); // HCF function calling
    }
    printf("\nHighest Common Factor : %d", hc);
    printf("\nLowest Common Multiple : %d", lc);
}
