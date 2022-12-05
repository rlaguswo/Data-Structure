/* CS261- HW1 - Program3.c*/
/* Name: Hyunjae Kim
* Date: 01/07/2021
* Solution description: */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void sort(int* number, int n){      
    /*Sort the array of integeres of length n*/ 
    int i,j;
    int list;

    for(i = 1; i < n;i++){
        list = number[i];
        for(j = i-1; j >= 0 && list < number[j]; j--){
            number[j+1] = number[j];
        }
        number[j+1] = list;
    }
}

int main(){    
    /*Declare an integer n and assign it a value of 20.*/    
    int n = 20;
    int i,j;
    srand(time(NULL));

    /*Allocate memory for an array of n integers using malloc.*/  
    int *array = (int *)malloc(sizeof(int) * n);

    /*Fill this array with random numbers, using rand().*/   
    if(n > 0) printf("\nUnsorted Array\n");
    for(i = 0;i < n; i++){
        array[i] = rand();
    }
    
    /*Print the contents of the array.*/    
    for(i = 0;i < n;i++){
        j = i+1;
        printf("%d. %d\n",j,array[i]);
    }
    /*Pass this array along with n to the sort() function of part a.*/   
    sort(array, n);

    /*Print the contents of the array.*/      
    if(n > 0) printf("\nSorted Array\n");
    for(i = 0;i < n;i++){
        j = i+1;
        printf("%d. %d\n",j,array[i]);
    }  

    free(array);
    return 0;
}
