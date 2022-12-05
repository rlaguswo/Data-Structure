/* ENTER YOUR FIRST AND LAST NAME: Hyunjae Kim      */
/* TO COMPILE:  gcc -Wall -ansi -o program Group3.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program input1.txt  */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a==b)
#define LT(a,b) (a<b)

# define TYPE int
struct Node {
  TYPE   val;
  struct Node *left;
  struct Node *right;
};

struct BST{
  struct Node *root;
  int size;
};

/****************************************/
/* Interface of BST */
void addBST(struct BST *tree, TYPE val);
struct Node * _addNode(struct Node * node, TYPE val);
void print_inorder(struct Node *node);
int _containsNode(struct Node * node, TYPE val);
void removeAllMinBST(struct BST * tree);
TYPE getMinBST(struct BST* tree);
struct Node* _removeMinBST(struct Node* node);

/****************************************/
int main (int argc, const char * argv[]) {
   const char *filename;
   FILE *fileptr;
   struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
   assert(tree);
   tree->root = 0;
   tree->size = 0;
   int value;

    if(argc == 2)
        filename = argv[1];
    else
        filename = "input.txt"; /* default file name */
    fileptr = fopen(filename,"r");

    printf("Adding nodes to BST with values from the file: %s\n", filename);
    while (!feof(fileptr)) {
      fscanf(fileptr, "%d", &value);
      addBST(tree, value);
    }
    printf("\nThere are %d nodes in input BST.\n", tree->size);
    printf("Their values printed in-order are:\n");
    print_inorder(tree->root);
    printf("\n");

    if(tree->root) removeAllMinBST(tree);

    printf("\nThere are %d nodes in BST after removing minimum nodes.\n", tree->size);
    printf("Their values printed in-order are:\n");
    print_inorder(tree->root);
    printf("\n");

    return 0;
}

/****************************************/
/* Add a new node to BST */
/*
    input: tree -- pointer to BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
void addBST(struct BST *tree, TYPE val) {
   assert(tree);
   tree->root = _addNode(tree->root, val);
   tree->size++;
}

/****************************************/
/* Auxiliary recursive function to add a new node to BST */
/*
    input: current -- pointer to a node in BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
struct Node * _addNode(struct Node * current, TYPE val){
   if (current == 0)
   {   /* we hit the leaf level */
       /*make a new node, and return new*/
       struct Node * new = (struct Node *) malloc(sizeof(struct Node));
       assert(new != 0);

      new->val = val;
      new->left = new->right = 0;
      return new;
   }
   else{ /* recursive calls left or right */
      if (val < current->val)
         current->left = _addNode(current->left, val);
      else
         current->right = _addNode(current->right, val);
   }
   return current;
}

/****************************************/
/* Finds recursively a given value in
   a subtree rooted at a specified node.
   Input: node -- pointer to the root node of the subtree
   Output: returns 1 for found; or 0 for not found
   Pre-conditions: current is not NULL
*/
int _containsNode(struct Node * node, TYPE val){
   if(!node) return 0; /* stopping criterion */
   if ( EQ(val, node->val) )
       return 1; /* found it */
   else if ( LT(val, node->val) && node->left )
       /* continue the search in the left subtree */
       return _containsNode(node->left, val);  
   else if ( node->right )
       /* continue the search in the right subtree */
       return _containsNode(node->right, val);
   return 0;
}

/****************************************/
void print_inorder(struct Node *node) {
   if (node != 0){
      print_inorder(node->left);
      printf("%d ",node->val);
      print_inorder(node->right);
   }
}

/****************************************/
/* Remove all minimum nodes of BST
   Input: tree -- pointer to BST
   Constraint: complexity O(log n), no new memory allocation
   Requirement: maintain the correct tree size
   Pre-condition: BST is not empty
*/
void removeAllMinBST(struct BST * tree){
   assert(tree);
   /* FIX ME */
   TYPE v = getMinBST(tree); 
   int check = 1;
   while(check != 0){
      tree->root = _removeMinBST(tree->root);
      tree->size--;
      check = _containsNode(tree->root, v);
   }
   
}

TYPE getMinBST(struct BST* tree){
   assert(tree);
   struct Node* current = tree->root;
   while(current->left != 0){
      current = current->left;
   }

   return current->val;
}

struct Node* _removeMinBST(struct Node* node){
   struct Node* temp;
   if(node->left != 0){
      node->left = _removeMinBST(node->left);
      return node;
   }
   temp = node->right;
   free(node);
   return temp;
}


