#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define inf INT_MAX
#define MAXSIZE 1000

void print_2d(int matrix[MAXSIZE][MAXSIZE], int n){
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(matrix[i][j] == INT_MAX)
                printf("-- ");
            else
                printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void prims(int gptr[MAXSIZE][MAXSIZE], int n, int v0){
    bool selected[n];
    int tree[MAXSIZE][MAXSIZE], i = 0, j = 0, ne = 0, min, x, y;
    // Initializations
    while(i < n)
        selected[i++] = false;
    for(i = 0;i < n;i++)
        for(j = 0;j < n;j++)
            tree[i][j] = 0;
    selected[v0] = true, ne = 1;

    // Finding the nearest neighbour of the selected vertex
    while(ne < n){
        min = inf;
        for(i = 0;i < n;i++){
            if(selected[i] == true){
                for(j = 0;j < n;j++){
                    if(selected[j] == false){
                        if(min > gptr[i][j]){
                            min = gptr[i][j];
                            x = i, y = j;
                        }
                    }
                }
            }
        }
        tree[x][y] = 1;
        selected[y] = true;
        ne++;
    }
    printf("\nThe adjacency matrix of the minimal spanning tree of the given graph is : \n");
    print_2d(tree, n);
}

int main(){
    int n, v0;
    int gptr[MAXSIZE][MAXSIZE];
    printf("\nEnter number of vertices : ");
    scanf("%d", &n);
    printf("\n(If any two vertices is not connected by an edge, enter 0)");
    printf("\n\n");
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            printf("\b\rEnter the weight between vertices %d and %d : ", (i + 1), (j + 1));
            scanf("%d", &(gptr[i][j]));
            if(gptr[i][j] == 0)
                gptr[i][j] = inf;
        }
    }
    printf("\nEnter the starting vertex : ");
    scanf("%d", &v0);
    if(v0 < 1 || v0 > n){
        printf("\nInvalid staring vertex %d!", v0);
        goto freeall;
    }
    printf("\nThe weighted adjacency matrix of the given graph is : \n");
    print_2d(gptr, n);
    prims(gptr, n, v0);
freeall:
    printf("\n");
    return 0;
}
