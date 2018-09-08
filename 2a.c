// max2
// inputs:  a, b: two integers
// returns: the maximum of a and b
int max2(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

#include <stdlib.c>
int max2(int a, int b) {
    return (a+b + abs(a-b)) / 2;
}

// max3
// inputs:  a, b, c: three integers
// returns: the maximum of a, b and c
int max3(int a, int b, int c) {
    return max2(a, max2(b, c));
}

// Contributor: Floris van den Ende
int max3(int a, int b, int c) {
    if (a>=b && a>c) {
        return a;
    } else if (b>a && b>c) {
        return b;
    } else {
        return c;
    }
}

// gcd
// inputs:  a, b: two positive integers
// returns: the greatest common divisor of a and b.
// note: the algorithm is described in the slides for lecture 1a.
// note: the remainder of a divided by b is obtained using a%b
int gcd(int a, int b) {
    int c;
    while (b != 0) {
        c = a%b;
        a = b;
        b = c;
    }
    return a;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a%b);
    }
}