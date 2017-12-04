#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
} *h = NULL;

struct node *getnode(int data) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void push(int data) {
    struct node *x;
    x = getnode(data);
    if (h == NULL) {
        h = x;
    } else {
        x->next = h;
        h = x;
    }
}

int pop() {
    int u = 0;
    if (h == NULL)
        printf("UNDERFLOW");
    else {
        u = h->data;
        h = h->next;
    }
    return u;
}

int status(int s[30], int n) {
    int i;
    for (i = 1; i <= n; i++) {
        if (s[i] == 0)
            return 1;
    }
    return 0;
}

void dfs(int l[10][10], int n, int vs) {
    int i, u, s[30], found;
    for (i = 1; i <= n; i++)
        s[i] = 0;
    s[vs] = 1;
    u = vs;
    push(vs);
    do {
        do {
            found = 0;
            for (i = 1; i <= n; i++) {
                if (s[i] == 0 && l[u][i] == 1) {
                    printf("\n%d %d", u, i);
                    push(i);
                    s[i] = 1;
                    found = 1;
                    u = i;
                    break;
                }
            }
            if (found == 0) {
                u = pop();
            }
        } while (h != NULL);
        for (i = 1; i <= n; i++) {
            if (s[i] == 0) {
                s[i] = 1;
                push(i);
                u = i;
                break;
            }
        }
        for (i = 1; i <= n; i++) {
            if (l[u][i] == 1 && s[u] != 2) {
                printf("\n%d to %d", u, i);
                s[u] = 2;
                break;
            }
        }
    } while (status(s, n));
}

void show(int l[10][10], int n) {
    int i, j;
    printf("\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++)
            printf(" %d ", l[i][j]);
        printf("\n");
    }
}

int main() {
    int l[10][10], n, i, j, vs;
    printf(" Enter order of the adjacency matrix : ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            printf("Enter weight between %d & %d : ", i, j);
            scanf("%d", &l[i][j]);
        }
    printf("\nAdjacency matrix is . . .\n");
    show(l, n);
    printf("Enter source vertex :");
    scanf("%d", &vs);
    dfs(l, n, vs);
    return 0;
}
