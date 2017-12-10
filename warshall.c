#include <stdio.h>

void display(int n, int a[20][20]); // prototype declaration

int main() {
    int a[20][20], i, j, k, n; // variable declaration
    printf("\nEnter the total number of vertices : ");
    scanf("%d", &n);
    printf("\nThe existence of path between every pair of  vertices : ");
    printf("\n1 : There is a path between vertices\n0 : There is no path between "
           "vertices");
    // loop for taking inputs of the matrix from the user
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("\nEnter the existence of path between vertices %d & %d : ",
                   i+1, j+1);
            scanf("%d", &a[i][j]);
        }
    }
    printf("\n\nThe adjacency matrix is : \n");
    display(n, a); // calling method display
    // loop for finding the minimum distance
    for (k = 0; k <= n; k++) {
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= n; j++) {
                a[i][j] = a[i][j] || (a[i][k] && a[k][j]);
            }
        }
    }
    printf("\n\nThe minimum distance between every pair of vertices : \n");
    display(n, a);
    return 0;
}

void display(int n, int a[20][20]) { // method to display the matrix
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf(" %d ", a[i][j]);
        }
        printf("\n");
    }
}
