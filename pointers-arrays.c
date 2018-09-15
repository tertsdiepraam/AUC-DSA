#include <string.h>
// in:  two int* variables, a and b.
// out: -
// side effect: the values that a and b point to are swapped.
void swap(int* a, int* b) {
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// in: an int* called a, pointing to the first of n ints.
// out: -
// side effect: the array is reversed:
//              a[0] is swapped with a[n-1],
//              a[1] is swapped with a[n-2],
//              ... and so on.
void reverse(int* a, int n) {
    for (int i=0; i<n/2; i++) {
        swap(&a[i], &a[n-i-1]);
    }
}

// in: an int* called a, pointing to the first of n ints
//     an int d satisfying 0 <= d < n.
// out: -
// side effect: all ints in a are shifted by d places, wrapping around so that
//              a[i] is moved to a[i+d] if i+d < n, and
//                            to a[i+d-n] otherwise.
// hint: you can program this from scratch, but this can actually also
//       be solved quite easily using just three calls to the function
//       "reverse".
void rotate(int *a, int n, int d) {
    reverse(a, n-d);
    reverse(a, n);
    reverse(a, d);
}

// in: a string of length >= 1 (terminated by a '\0' character)
// out: -
// side effect: the last character is removed from the string.
void chop(char* s) {
    s[strlen(s)-1] = '\0';
}

// in: an array of char*, the last of which equals NULL (to mark the end).
// out: the char* pointing to the longest string. (In case several strings
//      are longest, this function should return the first of those.)
char* find_longest(char** a) {
    int max = strlen(a[0]);
    int max_index = 0;
    int len;
    for (int i=1; a[i] != NULL; i++) {
        len = strlen(a[i]);
        if (len > max) {
            max = len;
            max_index = i;
        }
    }
    return a[max_index];
}