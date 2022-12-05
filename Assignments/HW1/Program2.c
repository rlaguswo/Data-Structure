/* CS261- HW1 - Program2.c*/
/* Name: Hyunjae Kim    
 * Date: 01/06/2021 
 * Solution description: */
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
struct student{
    char initials[2];
    int score;
};

struct student* allocate(){     
    /*Allocate memory for ten students*/     
    struct student* Students = NULL;
    Students = (struct student*)malloc(sizeof(struct student) * 10);
    
    /*return the pointer*/
    return Students;
}

void generate(struct student* students){     
    /*Generate random initials and scores for ten students.
    The two initial letters must be capital and must be between A and Z. 
    The scores must be between 0 and 100*/
    int i;
    srand(time(NULL));
    for(i = 0; i < 10; i++){
        students[i].initials[0] = rand()%26+'A';
        students[i].initials[1] = rand()%26+'A';
        students[i].score = rand()%101;
    }
}

void output(struct student* students){     
    int i,j;
    /*Output information about the ten students in the format:              
    1. Initials  Score              
    2. Initials  Score              
    ...              
    10. Initials Score*/
    for(i=0;i < 10;i++){
        j = i+1;
        printf("%d. %s %d\n",j, students[i].initials, students[i].score);
    }
}

void summary(struct student* students){     
    int i;
    int min = students[0].score;
    int max = students[0].score;
    float sum = 0, average = 0;
    /*Compute and print the minimum, maximum and average scores of the ten students*/
    for(i = 0; i < 10; i++){
        if(min > students[i].score){
            min = students[i].score;
        }

        if(max < students[i].score){
            max = students[i].score;
        }

        sum += students[i].score;
    }
    average = sum/10;
    printf("Minimum: %d Maximum: %d Average: %.2f\n", min,max,average);
}

void deallocate(struct student* stud){     
    /*Deallocate memory from stud*/
    free(stud);

}

int main(){    
    struct student* stud = NULL;    
    /*call allocate*/
    stud = allocate();

    /*call generate*/
    generate(stud);
    
    /*call output*/ 
    output(stud);
    
    /*call summary*/ 
    summary(stud);

    /*call deallocate*/
    deallocate(stud);
    return 0;
}