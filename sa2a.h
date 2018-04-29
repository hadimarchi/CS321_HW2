// sa2a.h
// Glenn G. Chappell
// 7 Feb 2018
//
// For CS 321 Spring 2018
// A Computation to Delegate
// Used in Assignment 2, Exercise A
// There is no associated source file

#ifndef FILE_SA2A_H_INCLUDED
#define FILE_SA2A_H_INCLUDED

#include <cassert>
// For: assert


// f1
// Helper function for sa2a.
// Parameter k should be postive; level should be nonnegative.
inline
int f1(int k, int level)
{
    assert(k > 0);
    assert(level >= 0);

    int count = 0;
    while (k > 1)
    {
        if (k % 2)
            k = 3*k + 1;
        else
            k /= 2;

        int up;
        if (level == 0)
            up = 1;
        else
            up = 1+f1(k, level-1);
        count += up;
    }
    return count;
}


// rot12
// Left rotate of 12-bit value by given number of bits.
// Helper function for sa2a.
inline
int rot12(int val, int bits)
{
    assert(0 <= val && val <= 0xffff);
    assert(0 <= bits && bits < 12);

    return ((val << bits) & 0xfff) | (val >> (12-bits));
}


// hash12
// Simple 12-bit hash of given int.
// Helper function for sa2a.
inline
int hash12(int n)
{
    n &= 0xfff;
    int a = rot12(n, 2) + 0xa4e9;
    int b = rot12(n, 5) + 0x71f2;
    int c = rot12(n, 9) + 0xde35;
    return (a ^ b ^ c) & 0xfff;
}


// sa2a
// Computation to delegate.
inline
int sa2a(int n)
{
    int nn = hash12(n);
    if (nn == 0)
        nn = 0xbee;
    return f1(nn, 4);
}


#endif //#ifndef FILE_SA2A_H_INCLUDED

