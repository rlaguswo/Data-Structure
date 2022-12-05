/* ENTER YOUR FIRST AND LAST NAME: Hyunjae Kim */
/* TO COMPILE:  gcc -Wall -ansi -o program RetakeExam3.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program 2.3 input1.txt  */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE1 int
#define TYPE2 double
#define LT(a,b) (a<b)
#define ADIFF(a,b) (abs(a - b))

struct Node {
  TYPE1   val;
  struct Node *left;
  struct Node *right;
};

struct BST{
  struct Node *root;
  int size;
};

/****************************************/
/* Interface of BST */
void addBST(struct BST *tree, TYPE1 val);
struct Node * _addNode(struct Node * node, TYPE1 val);
void printBreadthFirstTree(struct BST *tree);
struct Node* _removeNode(struct Node *node);
TYPE1 _leftMost(struct Node *node);
struct Node *_removeLeftmost(struct Node *node);
void compressNode(struct Node* current, TYPE2 threshold, struct BST* tree);
void compressBST(struct BST * tree, TYPE2 threshold);


/****************************************/
int main (int argc, const char * argv[]) {
   const char *filename;
   FILE *fileptr;
   struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
   assert(tree);
   tree->root = 0;
   tree->size = 0;
   TYPE1 value;
   TYPE2 threshold;
   char *ptr;

    if(argc == 3){
        threshold = strtod(argv[1], &ptr);
        filename = argv[2];
    }
    else{
        threshold = 1.5; /* default threshold value */
        filename = "input1.txt"; /* default file name */
    }
    fileptr = fopen(filename,"r");

    /* printf("Adding nodes to BST with values from the file: %s\n", filename); */
    while (!feof(fileptr)) {
      fscanf(fileptr, "%d", &value);
      addBST(tree, value);
    }
    printf("\nThere are %d nodes in input BST.\n", tree->size);
    printf("Their values printed breadth-first are:\n");
    printBreadthFirstTree(tree);
    printf("\n");

    if(tree->root) compressBST(tree, threshold);

    printf("\nThere are %d nodes in the compressed BST for threshold = %g.\n", tree->size, threshold);
    printf("Their values printed breadth-first are:\n");
    printBreadthFirstTree(tree);
    printf("\n");

    return 0;
}

/****************************************/
/* Printing nodes of BST in the breadth-first fashion
   param: pointer to a tree
   pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct BST *tree){
   assert(tree);
   struct Node **queue;  /* print using a queue, where queue is implemented as a static array */
   struct Node *current = tree->root;
   int start = 0; /* start index of queue indicating the first element to be processed */
   int end = 0;  /* end index of queue indicating the latest element added to the queue */

   /* allocate memory to queue */
   queue = (struct Node **) malloc(tree->size*sizeof(struct Node));
   
   queue[end] =  current; /* put the root at the end of the queue */
   end++;
   
   while(start < end){
      current = queue[start];  /* get the front element of queue */
      start ++;  /* "remove" the front element from queue */
      printf("%d ",current->val);
      if(current->left != 0){
         queue[end] =  current->left; /* put the left child at the end of the queue */
         end++;
      }
      if(current->right != 0){
         queue[end] =  current->right; /* put the right child at the end of the queue */
         end++;
      }
   }
}

/****************************************/
/* Add a new node to BST */
/* Input: tree -- pointer to BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
void addBST(struct BST *tree, TYPE1 val) {
   assert(tree);
   tree->root = _addNode(tree->root, val);
   tree->size++;
}

/****************************************/
/* Auxiliary recursive function to add a new node to BST */
/* Input: current -- pointer to a node in BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
struct Node * _addNode(struct Node * current, TYPE1 val){
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
/* Removes a given node from BST
   Input: node -- pointer to a node to be removed
   Output: the function returns the node's pointer
   Pre-condition: node is not a NULL pointer
*/
struct Node* _removeNode(struct Node *node){
   struct Node* temp;
   if (node->right == NULL){
      /* no right child */
      temp = node->left;
      free(node);
      return temp; 
   }
   /* right child exists */
   /* copy the value of the leftmost descendant*/
   node->val = _leftMost(node->right);
   /* remove leftmost desc. of right child */
   node->right = _removeLeftmost(node->right);
   return node;
}

/****************************************/
/*Finds and returns a value of the leftmost descendant of a node
  Input: node -- pointer to a node
  Output: return the value of the node's leftmost descendant
  Pre-condition: node is not a NULL pointer
*/
TYPE1 _leftMost(struct Node *node) { 
   while(node->left != 0) 
      node = node->left; 
   return node->val; 
} 

/****************************************/
/* Finds and removes the leftmost descendant of a node
  Input: node -- pointer to a node
  Output: the function returns the node's pointer
*/
struct Node *_removeLeftmost(struct Node *node) { 
   struct Node *temp; 
   if(node->left != 0){ 
      node->left = _removeLeftmost(node->left); 
      return node; 
   } 
   temp = node->right; 
   free(node);
   return temp; 
}


void compressNode(struct Node* current, TYPE2 threshold,struct BST* tree){


      if(abs(current->val - current->left->val) < threshold){
         current->left = _removeNode(current->left);
         tree->size--;
      }
      else if(abs(current->val - current->right->val) < threshold){
         current->right = _removeNode(current->right);
         tree->size--;
      }
      
      if(current->left != 0){
       compressNode(current->left,threshold, tree);
      }
      
      if(current->right != 0){
       compressNode(current->right, threshold,tree);
      }

   
   

   
}

/****************************************/
/* Compress BST
   Input: tree -- pointer to BST
          threshold -- for thresholding the absolute parent-child difference
   Constraint: complexity O(n), no new memory allocation
   Requirement: maintain the correct tree size
*/
void compressBST(struct BST * tree, TYPE2 threshold){ 
   assert(tree); 
   /* FIX ME */

   compressNode(tree->root, threshold,tree);


}




