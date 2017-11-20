#include <stdio.h>
#include <string.h>

void permut(char *s, int i,
            int m) /* Function to show the permutations of the given string*/
{
    int j;
    char c;
    if (i == m) {
        for (j = 0; j < m; j++) // Printing each permutation with every call
            printf(" %c", s[j]);
        printf("\n");
    } else {
        for (j = i; j < m; j++) {
            // Swapping a[i] and a[j]
            c = s[i];
            s[i] = s[j];
            s[j] = c;
            permut(s, i + 1, m); // Recursive call

            c = s[i]; // Swapping back
            s[i] = s[j];
            s[j] = c;
        }
    }
}
int main() {
    char str[100];
    printf("\nEnter the string : ");
    scanf("%s", str);
    printf("\nThe required permutations are : \n");
    permut(str, 0, strlen(str));
}
