/*    stackapp.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dynArray.h"

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
    param:      s pointer to a string 
    pre: s is not null
*/
char nextChar(char* s){
    assert(s != NULL);
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    
    if ( c == '\0' )
        return '\0';
    
    else 
        return c;
}

int is_pair(char ch1, char ch2){
    if(ch1 == '(' && ch2 == ')'){return 1;}
    else if(ch1 == '{' && ch2 == '}'){return 1;}
    else if(ch1 == '[' && ch2 == ']'){return 1;}
    else{return 0;}
}

/* Checks whether any occurrence of (, {, or [ are balanced    with the corresponding ), }, or ] respecting the LIFO principle
    arguments: s pointer to an input string 
    pre-condition: s is not null
    post: return 1 for balanced s or 0 for unbalanced s
*/
int isBalanced(char* s){
    assert(s != NULL);
    /*Use the following variables, do not change their names*/
    char ch;  
    
    /*stores the current character from the input string*/
    char ts;  
    
    /*stores the top element of the stack*/
    int b=1; 
    int check1, check2; 
   
    /*Boolean variable b=1 means balanced; b=0 means unbalanced string*/
    DynArr *stack;
    stack=newDynArr(100);
    /* initialize the stack with capacity = 100 */
    if (s && strlen(s)){
        while(1){ /*infinite loop that has to be stopped explicitly*/
            ch = nextChar(s); /*get the next character in the string*/                        
            /*stop the while loop when we reach the end of the string*/
            if(ch==0 || ch=='\0') break;                        
            /* FIXME: You will write this part of the function */
            else if(ch == '(' || ch == '{' || ch == '['){
                pushDynArr(stack,ch);
            }
            else if(ch == ')' || ch == '}' || ch == ']'){
                if(isEmptyDynArr(stack)) return 0;
                ts = topDynArr(stack);
                check1 = is_pair(ts,ch);
                if(check1){
                    b = 1;
                    popDynArr(stack);
                }
                else if(!check1){
                    b = 0;
                    if(isEmptyDynArr(stack)){
                        b = 0;
                    } 
                
            }
            /*else{continue;}*/
            }
        }
    }
    /* Free the memory allocated to the stack, and return b=1 or b=0 */
    /* FIXME: You will write this part of the function */
    check2 = isEmptyDynArr(stack);
    if(check2){
        b = 1;
        deleteDynArr(stack);
    }
    else if(!check2){
        b = 0;
        deleteDynArr(stack);
    }
    return b;
}

int main(int argc, char* argv[]){
    char* s=argv[1];
    /*char s[]="()+x+r*{{{((--{{[()[]]}}))}}}";*/
    int res;
    printf("Assignment 2\n");
    if(argc==2){
        res = isBalanced(s);
        if (res)
            printf("The string %s is balanced\n",s);
            
        else 
            printf("The string %s is not balanced\n",s);
        }
        
    else
        printf("Please enter a string to be evaluated.\n");
    
    return 0;
}