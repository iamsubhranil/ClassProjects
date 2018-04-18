#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef DEBUG
#include <string.h>
#include <time.h>
#endif

// =============== CLI ================

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_FONT_BOLD     "\x1b[1m"

#ifdef DEBUG
#define dbg(x, ...) dbg2( ANSI_FONT_BOLD "<%s:%d:%s> " ANSI_COLOR_RESET x, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
void dbg2(const char *msg, ...);

#define succs(x, ...) succs2( ANSI_FONT_BOLD "<%s:%d:%s> " ANSI_COLOR_RESET x, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
void succs2(const char *msg, ...);

#define err(x, ...) err2( ANSI_FONT_BOLD "<%s:%d:%s> " ANSI_COLOR_RESET x, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
void err2(const char *msg, ...);

#define info(x, ...) info2( ANSI_FONT_BOLD "<%s:%d:%s> " ANSI_COLOR_RESET x, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
void info2(const char *msg, ...);

#define warn(x, ...) warn2( ANSI_FONT_BOLD "<%s:%d:%s> " ANSI_COLOR_RESET x, __FILE__, __LINE__, __func__, ##__VA_ARGS__)
void warn2(const char *msg, ...);
#else
void dbg(const char *msg, ...);
void err(const char *msg, ...);
void info(const char *msg, ...);
void warn(const char *msg, ...);
#endif

#ifdef DEBUG
void dbg2(const char* msg, ...){
#else
void dbg(const char* msg, ...){
#endif
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_GREEN "\n[Debug] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
}

#ifdef DEBUG
void succs2(const char* msg, ...){
#else
void succs(const char* msg, ...){
#endif
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_GREEN "\n[Success] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
}

#ifdef DEBUG
void info2(const char* msg, ...){
#else
void info(const char* msg, ...){
#endif
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_BLUE "\n[Info] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
}

#ifdef DEBUG
void err2(const char* msg, ...){
#else
void err(const char* msg, ...){
#endif
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_RED "\n[Error] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg,args);
}

#ifdef DEBUG
void warn2(const char* msg, ...){
#else
void warn(const char* msg, ...){
#endif
    printf(ANSI_FONT_BOLD);
    printf(ANSI_COLOR_YELLOW "\n[Warning] ");
    printf(ANSI_COLOR_RESET);
    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
}

// ============== CLI ================

// ============== Core ===============

typedef struct BinarySearchTree{
    int data;
    struct BinarySearchTree *left;
    struct BinarySearchTree *right;
} BinarySearchTree;

static BinarySearchTree* bst_inorder_successor(BinarySearchTree *node){
    if(node->left == NULL)
        return node;
    return node->left;
}

static BinarySearchTree* bst_new_node(){
    BinarySearchTree *node = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    node->data = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void bst_insert(BinarySearchTree **root, int value){
    if(*root == NULL){
        *root = bst_new_node();
        (*root)->data = value;
    }
    else if(value <= (*root)->data){
        bst_insert(&((*root)->left), value);
    }
    else{
        bst_insert(&((*root)->right), value);
    }
}

static int bst_delete2(BinarySearchTree **parentPointer, BinarySearchTree *child, int value){
    if(child == NULL)
        return 0;

    if(child->data == value){
        /* No children */
        if(!child->right && !child->left)
            *parentPointer = NULL, free(child);
        /* Only one child */
        else if(!child->right && child->left)
            *parentPointer = child->left, free(child);
        else if(child->right && !child->left)
            *parentPointer = child->right, free(child);
        /* Both children */
        else{
            /* Find Inorder Predecessor */
            BinarySearchTree *next = child->right, **parent = &child->right;
            while(next->left != NULL){
                parent = &((*parent)->left);
                next = next->left;
            }
            /* Replace the value */
            child->data = next->data;
            /* Delete duplicate */
            bst_delete2(parent, next, next->data);
        }
        return 1;
    }
    else if(value < child->data){
        return bst_delete2(&child->left, child->left, value);
    }
    else
        return bst_delete2(&child->right, child->right, value);
}

static int bst_delete(BinarySearchTree **root, int value){
    if(*root == NULL)
        return 2;
    if(value == (*root)->data){
        return bst_delete2(root, *root, value);
    }
    if(value < (*root)->data){
        return bst_delete2(&((*root)->left), (*root)->left, value);
    }
    else 
        return bst_delete2(&((*root)->right), (*root)->right, value);
}

static BinarySearchTree* bst_create(int *values, int count){
    BinarySearchTree* root = NULL;
    for(int i = 0;i < count;i++){
        bst_insert(&root, values[i]);
    }
    return root;
}

typedef void(*method)(int);

static void bst_inorder(BinarySearchTree *root, method process){
    if(root != NULL){
        bst_inorder(root->left, process);
        process(root->data);
        bst_inorder(root->right, process);
    }
}

static void bst_preorder(BinarySearchTree *root, method process){
    if(root != NULL){
        process(root->data);
        bst_preorder(root->left, process);
        bst_preorder(root->right, process);
    }
}

static void bst_postorder(BinarySearchTree *root, method process){
    if(root != NULL){
        bst_postorder(root->left, process);
        bst_postorder(root->right, process);
        process(root->data);
    }
}

static int bst_check(BinarySearchTree *root){
    if(root == NULL)
        return 1;
    if(root->left != NULL){
        if(root->data < root->left->data)
            return 0;
        if(!bst_check(root->left))
            return 0;
    }
    if(root->right != NULL){
        if(root->data >= root->right->data)
            return 0;
        if(!bst_check(root->right))
            return 0;
    }
    return 1;
}

static void bst_free(BinarySearchTree *root){
    if(root == NULL)
        return;
    if(root->left)
        bst_free(root->left);
    if(root->right)
        bst_free(root->right);
    free(root);
}
// =========== Core ===========

// =========== Driver ============

void process_print_node(int data){
    printf("%d ", data);
}

#ifdef DEBUG

int get_random_int(long range){
    return rand() % range;
}

#define DEFAULT_RANGE 1000
int main(int argc, char *argv[]){
    BinarySearchTree *root = NULL;
    if(argc > 1){
        char *err = NULL;
        long count = strtol(argv[1], &err, 10);
        if(*err != 0){
            warn("Ignoring bad characters : %s", err);
        }
        long range = DEFAULT_RANGE;
        if(argc > 2){
            err = NULL;
            long rtmp = strtol(argv[2], &err, 10);
            if(*err != 0){
                warn("Ignoring bad characters : %s", err);
            }
            range = rtmp;
        }
        dbg("Inserting %ld random numbers to the tree between %ld\n", count, range);
        srand(time(NULL));
        for(long i = 0;i < count;i++){
            bst_insert(&root, get_random_int(range));
        }
        dbg("Tree creation complete!\n");
    }
#else
int main(){
    BinarySearchTree *root = NULL;
#endif
    if(root == NULL){
        info("Creating tree");
reenter:
        info("Enter the number of values you want to enter : ");
        int nums, i = 0, val;
        scanf("%d", &nums);
        if(nums < 1){
            err("Enter atleast one value!");
            goto reenter;
        }
        while(nums--){
            info("Enter value %d : ", (i + 1));
            scanf("%d", &val);
            bst_insert(&root, val);
            i++;
        }
    }
    while(1){
        info("1. Insert");
        info("2. Delete");
        info("3. Preorder traversal");
        info("4. Inorder traversal");
        info("5. Postorder traversal");
        info("6. Exit");
        info("Choice : ");
        char ch;
        scanf(" %c", &ch);
        switch(ch){
            case '1':
                {
                    info("Enter the value to insert : ");
                    int val;
                    scanf("%d", &val);
                    bst_insert(&root, val);
                    succs("Insertion complete!");
                }
                break;
            case '2':
                {
                    if(root == NULL){
                        err("Tree is empty!\n");
                        continue;
                    }
                    info("Enter the value to delete : ");
                    int val;
                    scanf("%d", &val);
                    int ret = bst_delete(&root, val);
                    if(ret == 0)
                        err("Value not found in the tree!");
                    else if(ret == 2)
                        err("Tree is empty!");
                    else
                        succs("Deletion complete!");
                }
                break;
            case '3':
                if(root == NULL)
                    err("Tree is empty!");
                else{
                    info("The preorder traversal of the tree is : ");
                    bst_preorder(root, process_print_node);
                }
                break;
            case '4':
                if(root == NULL)
                    err("Tree is empty!");
                else{
                    info("The inorder traversal of the tree is : ");
                    bst_inorder(root, process_print_node);
                }
                break;
            case '5':
                if(root == NULL)
                    err("Tree is empty!");
                else{
                    info("The postorder traversal of the tree is : ");
                    bst_postorder(root, process_print_node);
                }
                break;
            case '6':
                bst_free(root);
                return 0;
            default:
                err("Wrong choice!");
        }
        printf("\n");
    }
}
