/* CS261- HW1 - Program1.c*/
/* Name: Hyunjae Kim    
 * Date: 01/06/2021
 * Solution description: */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int foo(int* a, int* b, int c){   
    ++(*a);/* Increment a */   
    --(*b);/* Decrement  b */   
    c = (*a)-(*b);/* Assign a-b to c */  
    return c;/* Return c */
}


int main(){    
    int a;
    srand(time(NULL));
   /* Declare three integers x,y and z and initialize them randomly to values in [0,10] */   
    int x = rand()%11;
    int y = rand()%11;
    int z = rand()%11;
   
    /* Print the values of x, y and z */  
    printf("x before foo(): %d\n",x);
    printf("y before foo(): %d\n",y);
    printf("z berfore foo(): %d\n",z); 
    
    /* Call foo() appropriately, passing x,y,z as parameters */    
    foo(&x,&y,z);
    printf("\nCall foo()\n");
    
    /* Print the values of x, y and z */    
    printf("\nx after foo(): %d\n",x);
    printf("y after foo(): %d\n",y);
    printf("x after foo(): %d\n",z);
   
    /* Print the value returned by foo */
    printf("\n print foo(): %d\n",foo(&x,&y,z));

    /* Is the return value different than the value of z? No  
       Why? z is passed by value */ 

    return 0;
}
