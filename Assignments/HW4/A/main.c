#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"

void pre_order(struct AVLnode* current, TYPE preValue, TYPE* path,TYPE* path2, int* length,int* length2, TYPE cost, TYPE *cost2);
int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);


/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, start; /* variables for measuring execution time */
	int pathArray[100];  /* static array with values of nodes along the min-cost path of the AVL tree. The means that the depth of the AVL tree cannot be greater than 100 which is  sufficient for our purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){ 
		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);

        printf("\nThe AVL tree has %d nodes.\n",tree->cnt);
	
	printf("\nPrinting the AVL tree breadth-first : \n");
	printBreadthFirstTree(tree);

	gettimeofday(&start, NULL);

	/*Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/*Print out all numbers on the minimum-cost path */
	printf("\n\nThe minimum-cost path has %d nodes printed top-down from the root to the leaf: \n", len);
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - start.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}

void pre_order(struct AVLnode* current, TYPE preValue, TYPE* path,TYPE* path2, int* length,int* length2, TYPE cost, TYPE *cost2){
	int i = 0;
	path2[(*length)] = current->val;
	(*length)++;	

	(cost) += (TYPE)(labs)(preValue - current->val);

	if((current->left == NULL)&&(current->right == NULL)){
		if(cost < *cost2){
			*cost2 = cost;
			*length2 = *length;
			for(i = 0;i < *length;i++){
				path[i] = path2[i];
			}
		}
	}
	
	if(current->left != NULL){
		pre_order(current->left, current->val,path, path2, length,length2, cost, cost2);
		(*length)--;
	}

	if(current->right != NULL){
		pre_order(current->right,current->val, path,path2, length,length2, cost, cost2);
		(*length)--;
	}
}


/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/

int FindMinPath(struct AVLTree *tree, TYPE *path)
{
	/* FIX ME */
	struct AVLnode* current = tree->root;
	TYPE cost = 0;
	TYPE cost2 = 1000000000;
	int length = 0;
	int length2 = 0;
	TYPE path2[100];

	pre_order(current,current->val, path,path2, &length,&length2, cost, &cost2);

	return length2;
}



/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
   /* FIX ME */
   struct AVLnode** queue = (struct AVLnode**)malloc(sizeof(struct AVLnode*)*tree->cnt);
   struct AVLnode* current = tree->root;

   int front = 0;
   int back = 0;
   int i;

   queue[0] = current;
   back++;

   while(front != back){
	   current = queue[front];
	   front++;

	   if(current->left != 0){
		   queue[back] = current->left;
		   back++;
	   }

	   if(current->right != 0){
		   queue[back] = current->right;
		   back++;
	   }
   }

   for(i = 0;i < back;i++){
	   printf("%d\t", queue[i]->val);
   }

   free(queue);
   
}



