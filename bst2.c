#include<stdio.h>
#include<stdlib.h>  
typedef struct node{
    int key;
    struct node *left, *right;
}node;  
// A utility function to create a new BST node
node *newNode(int item){
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}  
// A utility function to do inorder traversal of BST
void inorder(struct node *root){
    if (root != NULL){
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}
  
/* A utility function to insert a new node with given key in BST */
node* insert(struct node* node, int key){
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);
 
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);   
 
    /* return the (unchanged) node pointer */
    return node;
}
/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
node * minValueNode(struct node* node){
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
} 
/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
node* deleteNode(struct node* root, int key){
	node *temp;
    // base case
    if (root == NULL) return root; 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key); 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key); 
    // if key is same as root's key, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if (root->left == NULL){
            temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            temp = root->left;
            free(root);
            return temp;
        } 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        temp = minValueNode(root->right); 
        // Copy the inorder successor's content to this node
        root->key = temp->key; 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
/* To find the preorder traversal */
void preorder(node *temp){
    if (temp == NULL){
        printf("No elements in a tree to display\n");
        return;
    }
    printf("%d\n", temp->key);
    if (temp->left != NULL)    
        preorder(temp->left);
    if (temp->right != NULL)    
        preorder(temp->right);
} 
/* To find the postorder traversal */
void postorder(node *temp){
    if (temp == NULL){
        printf("No elements in a tree to display\n");
        return;
    }
    if (temp->left != NULL) 
        postorder(temp->left);
    if (temp->right != NULL) 
        postorder(temp->right);
    printf("%d\n", temp->key);
}  
// Driver Program to test above functions
int main(){
    node *root = NULL;
    int ch,key;
    while(1){    	printf("1.Insert\n2.Delete\n3.Inorder\n4.Preorder\n5.Postorder\n6.Exit\nEnter Your choice: ");
    	scanf("%d",&ch);
    	switch(ch){
    			case 1: printf("Enter the element you want to insert: ");
    				  scanf("%d",&key);
				  root=insert(root,key);
				  break;
			case 2: printf("Enter the element you want to delete: ");
    				  scanf("%d",&key);
				  root=deleteNode(root,key);
				  break;
			case 3: inorder(root);
				  break;
			case 4: preorder(root);
				  break;
			case 5: postorder(root);
				  break;			
			case 6: return 0;
		}
	}    
return 0;
}
