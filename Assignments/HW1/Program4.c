/* CS261- HW1 - Program4.c*/
/* Name: Hyunjae Kim
* Date: 
* Solution description: */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct student{
    char initials[2];
    int score;
};

void swap_student(struct student* a, struct student* b){
	struct student tmp;
	tmp = (*a);
   (*a) = (*b);
   (*b) = tmp;
}

void sort(struct student* students, int n){     
    int i,j;
    
	 //Sort n students based on their initials
    for(i  = 1;i < n; i++){
        for(j = 0;j < n-1;j++){
            if(students[j].initials[0] > students[j+1].initials[0]){
                swap_student(&students[j], &students[j+1]);
            }
            else if(students[j].initials[0] == students[j+1].initials[0]){
                if(students[j].initials[1] > students[j+1].initials[1]){
                    swap_student(&students[j], &students[j+1]);
                }
            }
        }
    }

}

int main(){    
    int i,j,l,k;
    /*Declare an integer n and assign it a value.*/    
    int n = 10;

    struct student* s_array;
    s_array = NULL;
    
    /*Allocate memory for n students using malloc.*/    
    s_array = (struct student*)malloc(n* sizeof(struct student));
	assert(s_array != NULL);

    /*Generate random IDs and scores for the n students, using rand().*/  
    srand(time(NULL)); 
    for(i = 0;i < n;i++){
        s_array[i].initials[0] = rand()%26 + 'A';
        s_array[i].initials[1] = rand()%26 + 'A';
        s_array[i].score = rand()%101;
    }
    
    /*Print the contents of the array of n students.*/ 
    if(n > 0) printf("\nUnsorted Students List\n");
    
    for(i = 0;i < n;i++){
        j = i+1;
        printf("%d. %s  %d\n",j, s_array[i].initials, s_array[i].score);
    }

    /*Pass this array along with n to the sort() function*/    
    sort(s_array, n);

    /*Print the contents of the array of n students.*/  
    if(n > 0) printf("\nSorted Students List\n");
    
    for(l = 0;l < n;l++){
        k = l+1;
        printf("%d. %s  %d\n", k, s_array[l].initials, s_array[l].score);
    }
 
	free(s_array);  
	 
    return 0;
}
