/* ENTER YOUR FIRST AND LAST NAME: Hyunjae Kim     */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o program Group3.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: SIZE */
/* FOR EXAMPLE:  ./program 20 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)

struct Deque{
    TYPE *data;
    int size; /* number of elements in data */
    int capacity; /* memory capacity of deque */
    int front; /* index of the front element of deque  */
};

/* INTERFACE OF QUEUE ---------------------------*/
void addQueue(struct Deque *queue, TYPE val);

/* INTERFACE OF STACK ---------------------------*/
void pushStack(struct Deque *stack, TYPE val);
struct Deque * queue2stack(struct Deque *queue, struct Deque *stack);

/* INTERFACE OF DEQUE ---------------------------*/
void initDeque(struct Deque *dq, int cap);
void addFrontDeque(struct Deque *dq, TYPE val);
void addBackDeque(struct Deque *dq, TYPE val);
void printDeque(struct Deque *dq);
void _doubleCapacityDeque (struct Deque *dq);


/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque queue; /* variable  */
   struct Deque *stack = (struct Deque *) malloc(sizeof(struct Deque)); /*pointer to stack*/
   int i;
   TYPE val;
   int  capacity = 1;
   int  size = atoi(argv[1]);

   if(size < 0){
     printf("\nInvalid value for the size of Deque; size must be a nonnegative integer.\n");
     return 0;
   }

   initDeque(&queue, capacity); /*initialize and allocate memory to Queue*/

   /* Generate integers in [0,100] and add them to Queue */
   srand(time(NULL)); /*initialize the random generator*/

   for(i=0; i<size; i++){
      val = (TYPE) rand() % 101;
      addQueue(&queue, val); /*add val to Queue*/
   }

   printf("\nQueue after adding %d elements:\n", size);
   printDeque(&queue); /*print all elements of Queue from the front*/

   stack = queue2stack(&queue, stack); /*convert Queue into Stack*/

   printf("\nStack obtained from the above queue:\n");
   printDeque(stack); /*print all elements of Stack from the top*/
   free(stack);

   return 0;
}


/* ============ CODE FOR QUEUE ===============*/
/*----------------------------------------------*/
/* Adds a new element to a queue
  input arguments:
     queue -- pointer to a queue, implemented as a deque of a dynamic array
     val -- value of the data element to be added
*/
void addQueue(struct Deque *queue, TYPE val)
{
   /* FIX ME */
   addBackDeque(queue,val);
}

/*----------------------------------------------*/
/* Adds a new element to a stack
  input arguments:
     stack -- pointer to a stack, implemented as a deque of a dynamic array
     val -- value of the data element to be added
*/
void pushStack(struct Deque *stack, TYPE val)
{
   /* FIX ME */
   addBackDeque(stack,val);
}

/*----------------------------------------------*/
/* Converts a queue to a stack and frees memory block allocated to the queue
  input arguments:
     queue -- pointer to a queue, implemented as a deque of a dynamic array
     stack -- pointer to a stack, implemented as a deque of a dynamic array
  returns a pointer to a stack, implemented as a deque of a dynamic array
*/
struct Deque * queue2stack(struct Deque *queue, struct Deque *stack)
{
   assert(queue);
   assert(stack);
   assert(queue->size > 0);
   int di = 0;
   int i = 0;
   /* FIX ME */
   initDeque(stack, queue->capacity);
   for(i = queue->size-1;i >= 0;i--){
      di = (i + queue->front) % queue->capacity;
      pushStack(stack, queue->data[di]);
   }

   free(queue->data);
   queue->size = queue->capacity = 0;


   return stack;
}



/* ============ CODE FOR DEQUE ===============*/
/*----------------------------------------------*/
/* Initializes a deque
  input arguments:
  dq -- pointer to a deque implemented as a dynamic array
  cap -- capacity of memory block allocated to the deque
*/
void initDeque(struct Deque * dq, int cap) {
   assert (dq);
   dq->capacity = cap;
   dq->size = dq->front = 0;
   dq->data = (TYPE *) malloc(dq->capacity * sizeof(TYPE));
   assert (dq->data != 0);
}

/*----------------------------------------------*/
/* Prints out all elements of a deque starting from the front*/
/*  Input: dq -- pointer to a deque implemented as a dynamic array */
void printDeque(struct Deque * dq) {
   assert (dq);
   int i;
   for(i=0; i< dq->size; i++)
         printf("%d ", dq->data[(dq->front + i) % dq->capacity]);
   printf("\n");
}

/*----------------------------------------------*/
/* Doubles the memory capacity of a deque */
/*  Input: dq -- pointer to a deque implemented as a dynamic array */
void _doubleCapacityDeque (struct Deque *dq) {
  assert (dq);
  int j;
  TYPE * oldData = dq->data; /*memorize old data*/
  int oldFront = dq->front; /*memorize old index of the front end of deque*/
  int oldSize = dq->size; /*memorize old size*/
  int oldCapacity = dq->capacity; /*memorize old capacity*/
  initDeque(dq, 2 * oldCapacity); /*new memory allocation*/
  for (j = 0 ; j < oldSize; j++)  /* copy back old data */
      dq->data[j] = oldData[(oldFront++) % oldCapacity];
  free(oldData);
  dq->size = oldSize;
}

/*----------------------------------------------*/
/* Adds a new element to a deque at front
  input arguments:
     dq -- pointer to a deque implemented as a dynamic array
     val -- value of the data element to be added
*/
void addFrontDeque(struct Deque *dq, TYPE val) {
   assert(dq);
   if(dq->size >= dq->capacity){
      _doubleCapacityDeque(dq);
   }
   /* FIX ME */
   dq->front--;
   if(dq->front < 0){
      dq->front += dq->capacity;
   }
   dq->data[dq->front] = val;
   dq->size++;

}

/*----------------------------------------------*/
/* Adds a new element to a deque at back
  input arguments:
     dq -- pointer to a deque implemented as a dynamic array
     val -- value of the data element to be added
*/
void addBackDeque(struct Deque *dq, TYPE val) {
   assert(dq);
   if(dq->size >= dq->capacity){
      _doubleCapacityDeque(dq);
   }
   /* FIX ME */
   int back_index = (dq->front + dq->size) % dq->capacity;
   dq->data[back_index] = val;
   dq->size++;
}
