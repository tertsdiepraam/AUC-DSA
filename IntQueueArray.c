#include <stdlib.h>
// Your assignment is to develop an implementation of a Queue<int>,
// using EITHER an array data structure, OR a linked list data structure.

// You can freely borrow code from IntStackA.c and IntStackLL.c, which
// were developed during the lecture. However you'll have to think about
// how to adapt the code to make sure that it supports the operations
// specified below.
//
// In particular, items stored in the queue using "iq_enqueue" should
// come out in a first in, first out (FIFO) order.

// Define struct IntQueue in your answer.
typedef struct IntQueue* IntQueue;

struct IntQueue {
    int* values;
    int  head;
    int  size;
    int  alloc;
};

IntQueue iq_create();
void iq_destroy(IntQueue IQ);
void iq_enqueue(IntQueue IQ, int n);
int  iq_empty(IntQueue IQ);
int  iq_peek(IntQueue IQ);
void iq_dequeue(IntQueue IQ);

// out: an empty IntQueue.
IntQueue iq_create() {
    IntQueue IQ = (IntQueue) malloc(sizeof(struct IntQueue));
    IQ->values = (int*) malloc(100*sizeof(int));
    IQ->head  = 0;
    IQ->size  = 0;
    IQ->alloc = 100;
    return IQ;
}

// in: an IntQueue IQ.
// side effect: free all the memory that's associated with IQ.
void iq_destroy(IntQueue IQ) {
    free(IQ->values);
    free(IQ);
}

// in: an IntQueue IQ and a number n to add to the queue.
// side effect: n is stored in the queue datastructure.
void iq_enqueue(IntQueue IQ, int n) {
    // Reallocation if necessary
    if (IQ->size == IQ->alloc) {
        int* new = (int*) malloc(2*IQ->alloc*sizeof(int));
        for (int i=0; i<IQ->size; i++) {
            new[i] = IQ->values[(IQ->head + i) % IQ->alloc];
        }
        IQ->values = new;
        IQ->head = 0;
        IQ->alloc = 2*IQ->alloc;
    }

    // Put the value in the queue
    IQ->values[(IQ->head + IQ->size) % IQ->alloc] = n;
    IQ->size++;
}

// in: an IntQueue IQ
// out: 1 if the queue is empty, and 0 if it's not.
int iq_empty(IntQueue IQ) {
    return !IQ->size;
}

// in: an IntQueue IQ
// out: the oldest, first inserted value that's still in the queue.
int iq_peek(IntQueue IQ) {
    return IQ->values[IQ->head];
}

// in: an IntQueue IQ
// side effect: the oldest, first inserted item is removed from the queue.
void iq_dequeue(IntQueue IQ) {
    IQ->head = (IQ->head + 1) % IQ->alloc;
    IQ->size--;
}
