// In this assignment, you'll first get to answer a bunch of theoretical
// questions in the form of a computer program. (Please do not cheat by
// discussing with others. Remember that you can always resubmit your
// assignment if you made errors. Doing this the hard way will help prepare
// for the exams.)

// The theoretical questions all have a single integer number as answer, and
// can be answered by implementing the functions simply by "return <answer>;".
// None of these questions are judgment calls. Make sure that you know
// exactly why your answer is correct.

// Example question: what is 1+1?
// int q_demo();

// You would add to searchery.c:
// int q_demo() { return 2; }

// *** Question 1: ***
// Which of the following functions are in O(1)?
// (a) f(n) = 5           [Add 1 if this is in O(1)]
// (b) f(n) = log(n)      [Add 2 if this is in O(1)]
// (c) f(n) = 1 + 1/n     [Add 4 if this is in O(1)]
// (d) f(n) = sin(n)      [Add 8 if this is in O(1)]
// Example: if you believe that (b) and (c) are O(1), you should return 2+4 = 6.
int q_O1() {
    return 1+4+8;
}

// *** Question 2: ***
// Which of the following statements are true:
// (a) O(n(n+1)/2) = O(n^2)                               [Add  1 if true]
// (b) O(2^(3*n)) = O(2^n)                                [Add  2 if true]
// (c) O(1)+O(2)+...+O(n) = O(n^2)                        [Add  4 if true]
// (d) O(1)+O(2)+...+O(n) is ill defined                  [Add  8 if true]
// (e) If f(n) is a degree k polynomial, then f in O(n^k) [Add 16 if true]
int q_O2() {
    return 1+8+16;
}

// *** Question 3: ***
// We wish to modify the 'linear search' algorithm from the lecture so it
// counts the number of comparisons it performs.
// That means we really want to output two values: the index of the element
// that we found, and the number of comparisons performed.
// In C, we can't really output TWO values. So instead, we will add an
// additional INPUT: a pointer to an int called 'cmp'. The int that the pointer
// points to should be incremented by one for each comparison that the
// algorithm performs.

// in: a pointer a to an array of n integers,
//     the key that is searched for,
//     and a pointer cmp to a single int that counts the number of comparisons.
// side effect: the int that cmp points to has been incremented with the
//              number of comparisons that have been performed.
// out: the index of the key if it is found, or -1 if it is not found.
int linear_search_count(int* a, int n, int key, int* cmp) {
    for (int i=0; i<n; i++) {
        (*cmp)++;
        if (a[i] == key) {
            return i;
        }
    }
    return -1;
}

// *** Question 4: ***
// Binary search requires that we keep our array in sorted order, and we don't
// want to do that here. However imagine that some keys are searched *much*
// more often than other keys. In that case, we might speed up the search
// by moving keys that are searched for to the front of the array, so that they
// are found more quickly!
//
// First, write a helper function move_to_front that will percolate the item
// in the array with the given index to the front of the array.

// in: a pointer a to an array of at least k+1 integers,
//     the index k of the element to move to the front.
// side effect: the array is reshuffled so that the items at indices 0,1,...,k
//              now appear at indices 1,2,...,k,0 respectively.
void move_to_front(int* a, int k) {
    for (int i=0; i<k; i++) {
        int tmp = a[i];
        a[i] = a[k];
        a[k] = tmp;
    }
}


// *** Question 5: ***
// Adapt the function linear_search_count so that it always moves keys that
// are searched towards the front of the array. Using the test program you
// found with this exercise, measure the number of comparisons performed
// by the adaptive and the nonadaptive version of the search.

// in: a pointer a to an array of n integers,
//     the key that is searched for,
//     and a pointer cmp to a single int that counts the number of comparisons.
// side effects:
// - the int that cmp points to has been incremented with the
//   number of comparisons that have been performed.
// - if the key was found at an index k, it has been moved to the front of
//   the array, so that the items at indices 0,1,...,k now appear at indices
//   1,2,...,k,0 respectively.
// out: if the key was found, the index where it *currently* resides,
//      or -1 if it is not found.
int linear_search_adaptive(int* a, int n, int key, int* cmp) {
    int i = linear_search_count(a, n, key, cmp);
    if (i == -1) {
        return i;
    }
    move_to_front(a, i);
    return 0;
}