#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (struct hashLink**)malloc(sizeof(struct hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	int hash_index = 0;
	while(hash_index != ht->tableSize){
		
		if(ht->table[hash_index] != NULL){
			struct hashLink* previous = ht->table[hash_index];
			struct hashLink* current = ht->table[hash_index]->next;
			while(previous->next != NULL){
				previous->next = current->next;
				free(current->key);
				free(current);
				ht->count--;
				current = NULL;
				current = previous->next;
			}
			free(previous->key);
			free(ht->table[hash_index]);
		}

		hash_index++;
	}
	ht->count = 0;
	ht->tableSize = 0;
	free(ht->table);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	KeyType key = k;
	int hash = stringHash2(key);
	int hash_index = (int)(labs(hash)%ht->tableSize);
	float load = tableLoad(ht);
	int check = containsKey(ht,key);
	struct hashLink* current = ht->table[hash_index];
	if(check== 1){
		while(current != NULL){
			if(strcmp(key,current->key)==0){
				current->value += v;
			}
			current = current->next;
		}
		
		free(k);
	}
	if(ht->table[hash_index] == NULL || check == 0){
		struct hashLink* newlink = (struct hashLink*)malloc(sizeof(struct hashLink));
		newlink->value = v;
		newlink->key = k;
		newlink->next = ht->table[hash_index];
		ht->table[hash_index] = newlink;
		ht->count++;
	}

	
	if( load > 2.0){
		int old_size = ht->tableSize;
		struct hashLink** old_ht = ht->table;
		struct hashLink* current, *previous;
		int i;
		initMap(ht,2*old_size);
		for(i = 0;i < old_size;i++){
		current = old_ht[i];
		while(current != NULL){
			insertMap(ht,current->key,current->value);
			previous = current;
			current = current->next;
			free(previous);
		}
	}
	free(old_ht);
	}
	
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	int contain = containsKey(ht,k);
	int hash = stringHash2(k);
	int hash_index = (int)(labs(hash)% ht->tableSize);
	ValueType* val = &(ht->table[hash_index]->value);
	if(contain == 1){
		return val;
	}

	return NULL;
}

int containsKey (struct hashMap * ht, KeyType k){  
	/*write this*/
	int hash = stringHash2(k);
	int hash_index = (int)(labs(hash)%ht->tableSize);
	struct hashLink* current = ht->table[hash_index];
	
	while(current != NULL){
		if(strcmp(k,current->key) == 0){
			return 1;
		}

		current = current->next;
	}
	return 0;
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	int hash = stringHash2(k);
	int hash_index = (int)(labs(hash)%ht->tableSize);

	struct hashLink* previous = ht->table[hash_index];
	struct hashLink* current = ht->table[hash_index];

	while(current!= NULL){
		if(strcmp(k,current->key) == 0){
			if(current == ht->table[hash_index]){
				ht->table[hash_index] = current->next;
			}
			previous->next = current->next;
			free(current->key);
			free(current);
		}
		previous = current;
		current = current->next;
	}
	
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int num = 0;
	int hash_index = 0;
	for(hash_index = 0;hash_index < ht->tableSize;hash_index++){
		if(ht->table[hash_index] == NULL){
			num++;
		}
	}

	return num;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	int n = sizeMap(ht);
	int m = capacityMap(ht);

	return n/m;
}

