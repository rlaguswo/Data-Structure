#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */
 
/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/
	int hash_index;
	struct hashMap* ht = NULL; 
	char* word = NULL;
	FILE* file;

	hash_index = 0;
	ht = (struct hashMap*)malloc(sizeof(struct hashMap));
	
	initMap(ht,100);

	
	file= fopen(argv[1],"r");
	while(feof(file) == 0){
		word = getWord(file);
		if(word != NULL){
			insertMap(ht,word,1);
		}
	}
	fclose(file);

	while(hash_index != ht->tableSize ){
		struct hashLink* current = ht->table[hash_index];
		while(current != NULL){
			printf("\n%s: %d\n",current->key,current->value);
			current = current->next;
		}

		hash_index++;
	}


	freeMap(ht);
	free(ht);


	
	return 0;
}




char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

