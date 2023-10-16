#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;



void* heap_top(Heap* pq) {
  if (pq == NULL || pq->size == 0){
      return NULL;
  }
    
  return pq->heapArray[0].data;
}




void heap_push(Heap* pq, void* data, int priority) {
    if (pq == NULL) {
        exit(1);
    }
    
    //aumentar capacidad del arreglo si es necesario
    if (pq->size == pq->capac) {
        pq->capac = pq->capac * 2 + 1;
        pq->heapArray = (heapElem*)realloc(pq->heapArray, pq->capac * sizeof(heapElem));
        if (pq->heapArray == NULL) {
            exit(1);
        }
    }
    
    // Insertar el nuevo dato al final del arreglo
    int index = pq->size;
    pq->heapArray[index].data = data;
    pq->heapArray[index].priority = priority;
    pq->size++;

   
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (pq->heapArray[index].priority > pq->heapArray[parentIndex].priority) {
            heapElem temp = pq->heapArray[index];
            pq->heapArray[index] = pq->heapArray[parentIndex];
            pq->heapArray[parentIndex] = temp;
        } else {
            break;
        }
        index = parentIndex;
    }
}







void heap_pop(Heap* pq) {
    if (pq == NULL || pq->size == 0) {
        return;
    }
    
    pq->heapArray[0] = pq->heapArray[pq->size - 1];
    pq->size--;
    
    int index = 0;
    while (1) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;
        
        if (leftChild < pq->size && pq->heapArray[leftChild].priority > pq->heapArray[largest].priority) {
            largest = leftChild;
        }
        if (rightChild < pq->size && pq->heapArray[rightChild].priority > pq->heapArray[largest].priority) {
            largest = rightChild;
        }
        
        if (largest != index) {
            heapElem temp = pq->heapArray[index];
            pq->heapArray[index] = pq->heapArray[largest];
            pq->heapArray[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}



Heap* createHeap() {
    Heap* newHeap = (Heap*)malloc(sizeof(Heap));
    if (newHeap == NULL) {
        exit(1);
    }
    newHeap->heapArray = (heapElem*)malloc(3 * sizeof(heapElem));
    if (newHeap->heapArray == NULL) {
        free(newHeap);
        exit(1);
    }

    newHeap->size = 0;
    newHeap->capac = 3;

    return newHeap;
}
