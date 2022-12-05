#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


struct Element{
    int priority; /* the lower value the higher priority */
    char string[100];
};
#define TYPE struct Element
struct DynArr{
    TYPE *data; /* pointer to the data array */
    int size; /* number of elements in the array */
    int capacity; /* capacity of the array */
};
/* Percolate down a node of Heap
Input: heap -- pointer to the heap
index -- index of a node for percolating down
*/
void percolateDownHeap(struct DynArr *heap, int index) {
    assert(heap && index < heap->size);
    int higher;
    TYPE tmp;
    int maxIdx = heap->size;
    int leftIdx = index * 2 + 1; /* left child index */
    int rghtIdx = index * 2 + 2; /* right child index */
    while (leftIdx < heap->size){
        if (rghtIdx < maxIdx)
            higher = heap->data[leftIdx].priority < heap->data[rghtIdx].priority ?
            leftIdx : rghtIdx;
        else
            higher = leftIdx;
        if(heap->data[higher].priority < heap->data[index].priority){
            tmp = heap->data[higher];
            heap->data[higher] = heap->data[index];
            heap->data[index] = tmp;
            index = higher;
            leftIdx = index * 2 + 1;
            rghtIdx = index * 2 + 2;
        }
        else
            leftIdx = heap->size;
}
}
/* Remove from Heap elements with lower priority than a threshold
- Input: heap = pointer to a heap implemented as a dynamic array.
threshold = positive integer.
- Pre-conditions: heap was initialized well and exists in memory, but may be empty.
Also, heap correctly established the priority relationships among all of its elements.
- Constraints: time complexity <= O(n log n); no new data structures allowed,
no new memory locations can be allocated, except for a couple of integers
*/
void swapDynArr(DynArr *v, int i, int  j)
{
	TYPE  temp;
	
	assert(i < v->size);
	assert(j < v->size);
	
	temp = v->data[i];
	v->data[i] = v->data[j];
	v->data[j] = temp;
}
void _adjustHeap(DynArr *heap, int max, int pos)
{
  	/* FIXME */
	int left, right,small;
	left = 2*pos +1;
	right = 2*pos + 2;
	assert(max <= heap->size);
	if(right <= max){
		small = _smallerIndexHeap(heap,left,right);
		if(compare(heap->data[small],heap->data[pos])== -1){
			swapDynArr(heap,pos,small);
			_adjustHeap(heap,max,small);
		}
	}
	else if(left <= max){
		if(compare(heap->data[left],heap->data[pos]) == -1){
			swapDynArr(heap,pos,left);
			_adjustHeap(heap,max,left);
		}
	}


}
void removeThresholdHeap(struct DynArr *heap, int threshold){
    assert(heap && threshold > 0);
    /* FIX ME */
    int j = 0;
    while(j < heap->size){
        if(heap->data[j].priority < threshold){
            swapDynArr(heap,j,heap->size-1);
            _adjustHeap(heap,heap->size,j);
            heap->size--;
        }
        j++;
    }
}

int main(int argc, const char* argv[]){
    return 0;
}