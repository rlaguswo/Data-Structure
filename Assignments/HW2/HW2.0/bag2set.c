/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dynArray.h"

/*sort datas of the bag in ascending order*/
void sort(struct DynArr* da){
    int i,j;

	 /*complexity O(n*n)*/
    for(i = 1; i < da->size;i++){
        for(j = 0; j < da->size-1;j++){
            if(da->data[j] > da->data[j+1]){
                swapDynArr(da,j,j+1);
            }
        }
    }
}

/*Find how many unique values in bag*/
int uniquie(struct DynArr* da){
    int num = 0;
    int i;
    for(i = 0;i < da->size;i++){
        if((da->data[i] != da->data[i+1])){
            num++;
        }
    }

    return num;
}

/* Converts the input bag into a set using dynamic arrays 
    param:      da -- pointer to a bag 
    return value: void        
    result: after exiting the function da points to a set 
*/
void bag2set(struct DynArr *da){     
    /* FIX ME */
    
	/*First sort the bag in ascending order*/
	 sort(da);
	
	 int num = uniquie(da);
    int i = 0,j = 0;
   
    TYPE* old_data = da->data;

	 /*create new array*/
    initDynArr(da,2*num);
    da->size = num;
    
	 /*complexity O(n)*/
    while(j != num){
        if((old_data[i] != old_data[i+1])){
            da->data[j] = old_data[i];
            j++;
        }
        
        i++;
    }   

    free(old_data);
}

/* An example how to test your bag2set() */
int main(int argc, char* argv[]){
    int i;        
    struct DynArr da;  
    srand(time(NULL));
    /* bag */        
    initDynArr(&da, 100);        
    da.size = 11;        
    da.data[0] = 1.3;
    
    for (i=1;i<da.size-1;i++){    
        da.data[i] = 1.2; 
    }        

    da.data[da.size-1] = 1.4;        
    
    printf("Bag:\n\n");
    
    for (i=0;i<da.size;i++){          
        printf("%g  \n", da.data[i]);        
    }        
    printf("\n\n\n");        
    
    printf("Set:\n\n");        
    
    bag2set(&da);
    for (i=0;i<da.size;i++){          
        printf("%g ", da.data[i]);        
    }        
    
    printf("\n");

   freeDynArr(&da);
return 0;
}
