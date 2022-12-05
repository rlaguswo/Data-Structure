/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE:  gcc -Wall -ansi -o program Group3.c */

/* TO RUN, ENTER SIZE OF STACK 1 AND SIZE OF STACK 2 */
/* FOR EXAMPLE:  ./program 5 7 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a==b)

struct DLink {
   TYPE value;
   struct DLink * next;
   struct DLink * prev;
};

struct DList {
   int size;
   struct DLink * frontSentinel;
   struct DLink * backSentinel;
};

/*----------------------------------------------*/
/*Interface of a doubly linked list*/
void initDList (struct DList *dl);
void freeDList (struct DList *dl);
void _printDList(struct DList *dl);
void  _removeDLink (struct DList *dl, struct DLink *lnk) ;
void _addDLink(struct DList* dl, struct DLink* lnk, TYPE val);

/*----------------------------------------------*/
/*Interface of Stack implemented as doubly linked list*/
void pushStack (struct DList *stack, TYPE val);
void merge2stacks(struct DList *s1, struct DList *s2);


/*----------------------------------------------*/
int main(int argc, char **argv)
{
   /* Two stacks implemented as a doubly linked list */
   struct DList *s1 = (struct DList *) malloc(sizeof(struct DList));
   struct DList *s2 = (struct DList *) malloc(sizeof(struct DList));
   assert(s1); assert(s2);

   int i;
   TYPE val;
   int  size1 = atoi(argv[1]); /*input argument is the size of stack 1*/
   int  size2 = atoi(argv[2]); /*input argument is the size of stack 2*/

   assert(size1 >= 0 && size2 >= 0);

   srand(time(NULL)); /*initialize random generator*/

   /*initialize two stacks*/
   initDList(s1);
   initDList(s2);

   for(i=1; i<=size1; i++){
      val = (TYPE) rand() % 10;
      pushStack(s1, val); /*add val to stack 1*/
   }
   for(i=1; i<=size2; i++){
      val = (TYPE) (rand() % 10)*10;
      pushStack(s2, val); /*add val to stack 2*/
   }

   printf("\nStack1 from Top to Bottom:\n");
   _printDList(s1); /*print stack*/
  printf("\nStack2 from Top to Bottom:\n");
   _printDList(s2); /*print stack*/

   merge2stacks(s1, s2); /*merge s1 and s2 into s1*/

   printf("\nMerger Stack from Top to Bottom:\n");
   _printDList(s1); /*print stack*/

   freeDList(s1);
   free(s1);

   freeDList(s2);
   free(s2);


   return 0;
}

/*========== IMPLEMENTATION OF STACK ==========*/
/*----------------------------------------------*/
/*Add val to Stack implemented as a doubly linked list*/
/*input:
    s -- pointer to Stack
    val -- value to be added to Stack
*/
void pushStack (struct DList *stack, TYPE val){
   assert(stack);
   /* FIX ME */
   _addDLink(stack, stack->backSentinel,val);
}
/*----------------------------------------------*/
/*Merge Two Stacks*/
/*input:
    s1 -- pointer to Stack 1
    s2 -- pointer to Stack 2
  output:
    s1 is the merger of s1 and s2
  remove s2 from memory
*/
void merge2stacks(struct DList *s1, struct DList *s2)
{
   assert(s1 && s2);

   /*FIX ME*/

   /*Step 1: iterate through s1 and s2 starting from the top */
   struct DLink* c1 = s1->frontSentinel->next;
   struct DLink* c2 = s2->frontSentinel->next;
   while(c1 != s1->backSentinel && c2 != s2->backSentinel){
   /*Step 2: in every iteration add an element from s2 to s1 after every element of s1 */
      _addDLink(s1,c1->next,c2->value);
      s2->size--;
      c1 = c1->next->next;
      c2 = c2->next;
   }
      
   /*Step 3: check if s2 has more elements than s1, and if yes
             add the remaining elements of s2 to s1 */
      if(s2->size > 0){
         while(c2 != s2->backSentinel){
            pushStack(s1,c2->value);
            c2 = c2->next;
         }
      }

      
   
   
   /*Step 4: remove s2 from memory */
   freeDList(s2);

}

/*====== IMPLEMENTATION OF DOUBLY LINKED LIST ======*/
/*----------------------------------------------*/
/*Initialize doubly linked list*/
void initDList (struct DList *dl) {
   dl->frontSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->frontSentinel != 0);
   dl->backSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->backSentinel);
   dl->frontSentinel->next = dl->backSentinel;
   dl->backSentinel->prev = dl->frontSentinel;
   dl->size = 0;
}
/*----------------------------------------------*/
/*Free all memory occupied by doubly linked list*/
void freeDList (struct DList *dl) {
   while (dl->size > 0) _removeDLink (dl, dl->frontSentinel->next);
   free (dl->frontSentinel);
   free (dl->backSentinel);
   dl->frontSentinel = dl->backSentinel = NULL;
}
/*----------------------------------------------*/
/*Remove a link of doubly linked list*/
void  _removeDLink (struct DList *dl, struct DLink *lnk) {
   assert(dl && lnk);
   lnk->prev->next = lnk->next;
   lnk->next->prev = lnk->prev;
   free(lnk);
   dl->size--;
}
/*----------------------------------------------*/
/*Print elements of doubly linked list from front to back */
void _printDList(struct DList *dl){
   assert(dl);
   printf("\nTOP: ");
   struct DLink *current = dl->frontSentinel->next;
   while (current != dl->backSentinel){
      printf("%d ", current->value);
      current = current->next;
   }
   printf(" :BOTTOM\n");
}

void _addDLink(struct DList* dl, struct DLink* lnk, TYPE val){
   assert(dl);
   struct DLink* newlink = (struct DLink* )malloc(sizeof(struct DLink));
   newlink->value = val;
   newlink->prev = lnk->prev;
   newlink->next = lnk;
   lnk->prev->next = newlink;
   lnk->prev = newlink;
   dl->size++;
}

