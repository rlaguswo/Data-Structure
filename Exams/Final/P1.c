#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <time.h>


#define TYPE double
struct Node {
    TYPE val; /*node’s value*/
    struct Node *left; /*pointer to the left child*/
    struct Node *right; /*pointer to the right child*/
};
    struct Tree {
    struct Node *root;
    int size;
};
/* Breadth-last traversal of a binary tree
- Input: tree = pointer to a binary tree.
- Pre-conditions: tree was initialized well and exists in memory, but may be empty.
- Constraints: time complexity <= O(n); no new data structures allowed,
no new memory locations can be allocated, except for a couple of integers
*/
void printBreadthLastBinaryTree(struct Tree *tree){
    assert(tree);
    /* FIX ME */
    struct Node* current = tree->root;
    struct Node** stack = (struct Node**)malloc(sizeof(struct Node*) * (tree->size));
   
    int front = 0;
    int back = 0;
    int i = 0;

    stack[0] = current;
    back++;
    while(front != back){
        current = stack[front];
        front++;
        if(current->right != 0){
            stack[back] = current->right;
            back++;
        }
        if(current->left != 0){
            stack[back] = current->left;
            back++;
        }
    }
    
    for(i = back-1;i >=0; i--){
        printf("%f\t", stack[i]->val);
    }

    free(stack);

}

void initAVLTree(struct Tree *tree)
{
	tree->size = 0;
	tree->root = 0;

}
struct Tree * newAVLTree()
{
	struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));
	assert(tree != 0);
	
	initAVLTree(tree);
	return tree;
}

/* Initialize AVL tree structure. */

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


void addBST(struct Tree *tree, TYPE val) {
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



int main(int argc, const char* argv[]){
    struct Tree tree;
    initAVLTree(&tree);
    addBST(&tree,2);
    addBST(&tree,3);
    addBST(&tree,4);
    addBST(&tree,16);
    addBST(&tree, 7);
    addBST(&tree, 7);
    addBST(&tree, 21);
    addBST(&tree, 10);
    addBST(&tree, 12);
    printBreadthLastBinaryTree(&tree);
    return 0;
}