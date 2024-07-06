#include <stdio.h>
#include <assert.h>
#include <uint256.h>

#define MAX_U64 0xffffffffffffffffULL


/*
    Test helper functions
*/
// Print each 64 bit word of the 256 integer. Zero index is least significant
void print_uint(const char *label, u256 x) {
    printf("%s[0]: %lu\n%s[1]: %lu\n%s[2]: %lu\n%s[3]: %lu\n",
           label, x[0], label, x[1], label, x[2], label, x[3]);
}

// Compare each word of two 256 bit integers
void assert_eq(u256 have, u256 want) {
    assert(have[0] == want[0]);
    assert(have[1] == want[1]);
    assert(have[2] == want[2]);
    assert(have[3] == want[3]);
}

// Check for eqality and print a friendly message then trigger assertion error
void verbose_assert_eq(u256 have, u256 want, char name[], char msg[]) {
    if ((have[0] != want[0]) || (have[1] != want[1])
     || (have[2] != want[2]) || (have[3] != want[3]))
    {
        printf("%s failed: %s\n", name, msg);
        print_uint("want", want);
        print_uint("have", have);
        assert_eq(have, want);
    } else {
        // success message?
        printf("%s succeeded: %s\n", name, msg);
    }
}

// Check a boolean and print a friendly message then trigger assertion error
void verbose_assert_bool(bool have, bool want, char name[], char msg[]) {
    if (have != want)
    {
        printf("%s failed: %s\n", name, msg);
        printf("want %s", want ? "true" : "false");
        printf("have %s", have ? "true" : "false");
        assert(have == want);
    } else {
        // success message?
        printf("%s succeeded: %s\n", name, msg);
    }
}

/*
    Arithmetic tests
    ---
    Many of these tests are generated using random values and running them
    through the Golang implementation of uint256. I tried to include "edge"
    cases where I could think of them, since any of the comprehensible
    arithmetic operations would only involve the least significant words, ie.
    2 * 2 = 4 only involves x[0] and y[0], which is not a good test, but if x
    is 188272676318726381273681726319 then its representation in four words
    won't be recognizable.
*/
void test_add() {
    /*
        Test that each addition carries into the next significant word
    */
    u256 x = {MAX_U64, 0, 0, 0};
    u256 y = {1, 0, 0, 0};
    u256 want = {0, 1, 0, 0};

    u256 have;
    add(have, x, y);

    verbose_assert_eq(have, want, "Add", "Should overflow/wrap correctly");

    x[1] = MAX_U64;
    want[1] = 0;
    want[2] = 1;
    add(have, x, y);

    verbose_assert_eq(have, want, "Add", "Should overflow/wrap correctly");

    x[2] = MAX_U64;
    want[2] = 0;
    want[3] = 1;
    add(have, x, y);

    verbose_assert_eq(have, want, "Add", "Should overflow/wrap correctly");

    x[3] = MAX_U64;
    want[3] = 0;
    add(have, x, y);

    verbose_assert_eq(have, want, "Add", "Should overflow/wrap correctly");
}

void test_mul() {
    u256 x = {2, 0, 0, 0};
    u256 y = {2, 0, 0, 0};
    u256 want = {4, 0, 0, 0};

    u256 have;
    add(have, x, y);

    verbose_assert_eq(have, want, "Mul", "Product should be correct");
}

void test_sub() {
    u256 x = {4, 0, 0, 0};
    u256 y = {2, 0, 0, 0};
    u256 want = {2, 0, 0, 0};

    u256 have;
    sub(have, x, y);

    verbose_assert_eq(have, want, "Sub", "Difference should be correct");
}

void test_div() {
    u256 x = {4, 0, 0, 0};
    u256 y = {2, 0, 0, 0};
    u256 want = {2, 0, 0, 0};

    u256 have;
    div(have, x, y);

    verbose_assert_eq(have, want, "Div", "Division should be correct");

    y[0] = 4;
    want[0] = 1;
    div(have, x, y);
    verbose_assert_eq(have, want, "Div", "A number divided by itself is one");
}

void test_sdiv() {
    u256 x = {10, 0, 0, 0};
    u256 y = {2, 0, 0, 0};
    u256 want = {5, 0, 0, 0};

    u256 have;
    sdiv(have, x, y);

    verbose_assert_eq(have, want, "SDiv", "Should succeed");
}

void test_mod() {
    u256 x = {7, 0, 0, 0};
    u256 m = {2, 0, 0, 0};
    u256 want = {7%2, 0, 0, 0};

    u256 have;
    mod(have, x, m);

    verbose_assert_eq(have, want, "Mod", "Should succeed");
}

void test_smod() {

}

void test_add_mod() {
    u256 x = {7, 0, 0, 0};
    u256 y = {10, 0, 0, 0};
    u256 m = {5, 0, 0, 0};
    u256 want = {17%5, 0, 0, 0};

    u256 have;
    add_mod(have, x, y, m);

    verbose_assert_eq(have, want, "AddMod", "Should succeed");
}

void test_mul_mod() {
    u256 x = {7, 0, 0, 0};
    u256 y = {10, 0, 0, 0};
    u256 m = {5, 0, 0, 0};
    u256 want = {70%5, 0, 0, 0};

    u256 have;
    mul_mod(have, x, y, m);

    verbose_assert_eq(have, want, "MulMod", "Should succeed");
}

void test__exp() {
    u256 x = {7, 0, 0, 0};
    u256 y = {3, 0, 0, 0};
    u256 want = {343, 0, 0, 0};

    u256 have;
    _exp(have, x, y);

    verbose_assert_eq(have, want, "Exp", "Should succeed");
}

void test_sign_extend() {

}

/*
    Comparison tests
    ---
    I handpicked most of the cases for the comparison tests.
*/
void test_lt() {
    u256 x = {1, 0, 0, 0};
    u256 y = {1, 0, 0, 0};
    bool want = false;

    bool have = lt(x, y);

    verbose_assert_bool(have, want, "Lt", "Should be false when equal");

    x[0] = 10;
    have = lt(x, y);

    verbose_assert_bool(have, want, "Lt", "Should be false when greater than");

    x[0] = 0;
    want = true;
    have = lt(x, y);

    verbose_assert_bool(have, want, "Lt", "Should be true when less than");

}

void test_gt() {
    u256 x = {1, 0, 0, 0};
    u256 y = {1, 0, 0, 0};
    bool want = false;

    bool have = gt(x, y);

    verbose_assert_bool(have, want, "Gt", "Should be false when equal");

    x[0] = 0;
    have = gt(x, y);

    verbose_assert_bool(have, want, "Gt", "Should be false when less than");

    x[0] = 2;
    want = true;
    have = gt(x, y);

    verbose_assert_bool(have, want, "Gt", "Should be true when greater than");
}

void test_slt() {
    u256 x = {MAX_U64, MAX_U64, MAX_U64, MAX_U64}; // x = -1
    u256 y = {1, 0, 0, 0};                         // y = 1
    bool want = true;

    bool have = slt(x, y);

    verbose_assert_bool(have, want, "Slt",
        "Negative number should be less than a positive number");

    y[0] = 0;                                      // y = 0
    have = slt(x, y);

    verbose_assert_bool(have, want, "Slt",
        "Negative number should be less than zero");

    copy_words(&y[0], &x[0], 4);                   // y = -1
    x[0] -=1;                                      // x = -2

    have = slt(x, y);
    verbose_assert_bool(have, want, "Slt",
        "More negative number should be less than less negative number");
}

void test_sgt() {
    u256 x = {1, 0, 0, 0};                         // x = 1
    u256 y = {MAX_U64, MAX_U64, MAX_U64, MAX_U64}; // y = -1
    bool want = true;

    bool have = sgt(x, y);

    verbose_assert_bool(have, want, "Sgt",
        "Positive number should be greater than a negative number");

    clear_words(&y[0], 4);                         // y = 0
    have = sgt(x, y);

    verbose_assert_bool(have, want, "Sgt",
        "Positive number should be greater than zero");

    copy_words(&y[0], &x[0], 4);                   // y = 1
    x[0] +=1;                                      // x = 2

    have = sgt(x, y);
    verbose_assert_bool(have, want, "Sgt",
        "More positive number should be greater than less positive number");
}

void test_eq() {
    u256 x = {1, 0, 0, 0};
    u256 y = {1, 0, 0, 0};
    bool want = true;

    bool have = eq(x, y);

    verbose_assert_bool(have, want, "Eq", "Should be true when equal");

    x[0] = 0;
    want = false;
    have = eq(x, y);

    verbose_assert_bool(have, want, "Eq", "Should be false when not equal");
}

void test_is_zero() {
    u256 x = {1, 0, 0, 0};
    bool want = false;

    bool have = is_zero(x);

    verbose_assert_bool(have, want, "IsZero", "Should be false when nonzero");

    x[0] = 0;
    want = true;
    have = is_zero(x);

    verbose_assert_bool(have, want, "IsZero", "Should be true when zero");
}

/*
    Bitwise tests
    ---
    For many of the bitwise operations tests, I arbitrarily chose the bits.
    Where applicable, I wrote the integers in binary notation so that the
    expected result is easy to understand from reading alone.
*/
void test_and() {
    u256 x = {
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111
    };
    u256 y = {
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111
    };
    u256 want = {
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111
    };

    u256 have;
    and(have, x, y);

    verbose_assert_eq(have, want, "And", "Should succeed");
}

void test_or() {
    u256 x = {
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111
    };
    u256 y = {
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111
    };
    u256 want = {
        0b1111111111111111111111111111111111111111111111111111111111111111,
        0b1111111111111111111111111111111111111111111111111111111111111111,
        0b1111111111111111111111111111111111111111111111111111111111111111,
        0b1111111111111111111111111111111111111111111111111111111111111111
    };

    u256 have;
    or(have, x, y);

    verbose_assert_eq(have, want, "Or", "Should succeed");
}

void test_xor() {
    u256 x = {
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111
    };
    u256 y = {
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111,
        0b1110000000000000000001111111111111111111111111111111111111111111
    };
    u256 want = {
        0b0001111111111111111110000000111111111111111111111111111111111000,
        0b0001111111111111111110000000111111111111111111111111111111111000,
        0b0001111111111111111110000000111111111111111111111111111111111000,
        0b0001111111111111111110000000111111111111111111111111111111111000
    };

    u256 have;
    xor(have, x, y);

    verbose_assert_eq(have, want, "Xor", "Should succeed");
}

void test_not() {
    u256 x = {
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111,
        0b1111111111111111111111111111000000000000000000000000000000000111
    };
    u256 want = {
        0b0000000000000000000000000000111111111111111111111111111111111000,
        0b0000000000000000000000000000111111111111111111111111111111111000,
        0b0000000000000000000000000000111111111111111111111111111111111000,
        0b0000000000000000000000000000111111111111111111111111111111111000
    };

    u256 have;
    not(have, x);

    verbose_assert_eq(have, want, "Not", "Should succeed");
}

void test_byte() {
    /*
        Check each index in this test. Note that `byte` indexes the byte as if
        the number was big-endian, even though we store them in little-endian
        order in the u256 type.
    */
    u256 x = {
        0x00000000000000ee, // use a diff byte for each u64 word
        0x00000000000000dd,
        0x00000000000000cc,
        0x00000000000000bb
    };
    u256 i = {32, 0, 0, 0}; // start above 31 because i[0] -= 1 in loop.
    u256 want = {
        0x00000000000000ee,
        0x0000000000000000,
        0x0000000000000000,
        0x0000000000000000
    };
    u256 have;    // result of operation
    char msg[32]; // test message depends on which byte is being checked

    // check each word
    for (int word = 0; word < 4; word++) {
        if (word == 1) {
            want[0] = 0x00000000000000dd;
        }
        if (word == 2) {
            want[0] = 0x00000000000000cc;
        }
        if (word == 3) {
            want[0] = 0x00000000000000bb;
        }

        // check each byte in each word
        for (int j = 0; j < 8; j++) {
            // first byte is already set in each word of x
            if (j > 0) {
                x[word] <<= 8;
            }
            i[0] -= 1;
            byte(have, x, i);
            sprintf(msg, "Should retrieve byte %lu", i[0]);
            verbose_assert_eq(have, want, "Byte", msg);
        }
    }
}

void test_shl() {
    u256 x = {
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111,
        0b1110000000000000000001111111000000000000000000000000000000000111
    };
    u256 shift = {3, 0, 0, 0};
    // Note: shift left zero pads on right side of least significant word
    u256 want = {
        0b0000000000000000001111111000000000000000000000000000000000111000,
        0b0000000000000000001111111000000000000000000000000000000000111111,
        0b0000000000000000001111111000000000000000000000000000000000111111,
        0b0000000000000000001111111000000000000000000000000000000000111111
    };

    u256 have;
    shl(have, x, shift);

    verbose_assert_eq(have, want, "Shl", "Should left shift by 3 bits");

    shift[0] = 256;
    clear_words(&want[0], 4);
    shl(have, x, shift);

    verbose_assert_eq(have, want, "Shl", "Maximum left shift should return 0");
}

void test_shr() {
    u256 x = {
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111
    };
    u256 shift = {3, 0, 0, 0};
    // Note: shift right zero pads on left side of most significant word
    u256 want = {
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b0001110001111111111111111111111111111111111111111111111111111000
    };

    u256 have;
    shr(have, x, shift);

    verbose_assert_eq(have, want, "Shr", "Should right shift by 3 bits");

    shift[0] = 256;
    clear_words(&want[0], 4);
    shr(have, x, shift);

    verbose_assert_eq(have, want, "Shr", "Maximum right shift should return 0");
}

void test_sar() {
    u256 x = {
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111
    };
    u256 shift = {3, 0, 0, 0};
    u256 want = {
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000
    };

    u256 have;
    sar(have, x, shift);

    verbose_assert_eq(have, want, "Sar",
        "Shift right for negative value should fill left with 1s");

    x[3] = 0b0110001111111111111111111111111111111111111111111111111111000111;
    want[3] =
        0b0000110001111111111111111111111111111111111111111111111111111000;

    sar(have, x, shift);

    verbose_assert_eq(have, want, "Sar",
        "Shift right for positive value should fill left with 0s");

    shift[0] = 256;
    clear_words(&want[0], 4);
    sar(have, x, shift);

    verbose_assert_eq(have, want, "Sar",
        "Maximum shift right for positive value should return all 0s");

    x[3] = 0b1000000000000000000000000000000000000000000000000000000000000000;
    want[0] = 0xffffffffffffffffULL;
    want[1] = 0xffffffffffffffffULL;
    want[2] = 0xffffffffffffffffULL;
    want[3] = 0xffffffffffffffffULL;
    sar(have, x, shift);

    verbose_assert_eq(have, want, "Sar",
        "Maximum shift right for negative value should return all 1s");
}

int main() {
    //////////////////////////// Arithmetic tests
    test_add();
    test_mul();
    test_sub();
    test_div();
    test_sdiv();
    test_mod();
    test_smod();
    test_add_mod();
    test_mul_mod();
    test__exp();
    test_sign_extend();

    //////////////////////////// Comparison tests
    test_lt();
    test_gt();
    test_slt();
    test_sgt();
    test_eq();
    test_is_zero();

    //////////////////////////// Bitwise tests
    test_and();
    test_or();
    test_xor();
    test_not();
    test_byte();
    test_shl();
    test_shr();
    test_sar();

    printf("All tests passed!\n");
}
