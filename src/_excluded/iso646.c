
/* iso646.h Tests

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <iso646.h>

#ifdef TEST

#include "_PDCLIB_test.h"

int main( void )
{
    int x;

    // and (&&) - Logical AND
    TESTEQUAL( 1, 1 and 1 );   // true && true -> 1
    TESTEQUAL( 0, 1 and 0 );   // true && false -> 0
    TESTEQUAL( 0, 0 and 0 );   // false && false -> 0

    // or (||) - Logical OR
    TESTEQUAL( 1, 1 or 0 );    // true || false -> 1
    TESTEQUAL( 0, 0 or 0 );    // false || false -> 0
    TESTEQUAL( 1, 1 or 1 );    // true || true -> 1

    // not (!) - Logical NOT
    TESTEQUAL( 0, not 1 );     // !true -> 0
    TESTEQUAL( 1, not 0 );     // !false -> 1

    // not_eq (!=) - Not Equal To
    TESTEQUAL( 0, 1 not_eq 1 ); // 1 != 1 -> 0
    TESTEQUAL( 1, 1 not_eq 0 ); // 1 != 0 -> 1

    // bitand (&) - Bitwise AND
    TESTEQUAL( 1, 3 bitand 1 ); // 0b11 & 0b01 -> 1
    TESTEQUAL( 2, 3 bitand 2 ); // 0b11 & 0b10 -> 2
    TESTEQUAL( 0, 3 bitand 4 ); // 0b11 & 0b100 -> 0

    // bitor (|) - Bitwise OR
    TESTEQUAL( 3, 3 bitor 1 );  // 0b11 | 0b01 -> 3
    TESTEQUAL( 7, 3 bitor 4 );  // 0b11 | 0b100 -> 7

    // xor (^) - Bitwise XOR
    TESTEQUAL( 2, 3 xor 1 );    // 0b11 ^ 0b01 -> 2
    TESTEQUAL( 1, 3 xor 2 );    // 0b11 ^ 0b10 -> 1
    TESTEQUAL( 7, 3 xor 4 );    // 0b11 ^ 0b100 -> 7

    // compl (~) - Bitwise NOT (assuming two's complement for 'int')
    TESTEQUAL( -1, compl 0 );   // ~0 -> -1
    TESTEQUAL( -2, compl 1 );   // ~1 -> -2

    // and_eq (&=) - Bitwise AND assignment
    x = 3;
    TESTEQUAL( 1, x and_eq 1 ); // x = 3 & 1; x is now 1
    x = 3;
    TESTEQUAL( 2, x and_eq 2 ); // x = 3 & 2; x is now 2
    x = 3;
    TESTEQUAL( 0, x and_eq 4 ); // x = 3 & 4; x is now 0

    // or_eq (|=) - Bitwise OR assignment
    x = 3;
    TESTEQUAL( 3, x or_eq 1 );  // x = 3 | 1; x is now 3
    x = 3;
    TESTEQUAL( 7, x or_eq 4 );  // x = 3 | 4; x is now 7

    // xor_eq (^=) - Bitwise XOR assignment
    x = 3;
    TESTEQUAL( 2, x xor_eq 1 ); // x = 3 ^ 1; x is now 2
    x = 3;
    TESTEQUAL( 7, x xor_eq 4 ); // x = 3 ^ 4; x is now 7

    return TEST_RESULTS;
}

#endif
