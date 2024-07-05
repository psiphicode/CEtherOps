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

    verbose_assert_eq(have, want, "Mul", "Should succeed");
}

void test_sub() {

}

void test_div() {

}

void test_sdiv() {

}

void test_mod() {

}

void test_smod() {

}

void test_add_mod() {

}

void test_mul_mod() {

}

void test__exp() {

}

void test_sign_extend() {

}

/*
    Comparison tests
    ---
    I handpicked most of the cases for the comparison tests.
*/
void test_lt() {

}

void test_gt() {

}

void test_slt() {

}

void test_sgt() {

}

void test_eq() {

}

void test_is_zero() {
    u256 x = {1, 0, 0, 0};
    bool want = false;

    bool have = is_zero(x);

    verbose_assert_bool(have, want, "IsZero", "Should be nonzero");

    x[0] = 0;
    want = true;
    have = is_zero(x);

    verbose_assert_bool(have, want, "IsZero", "Should be zero");
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
    char msg[32]; // expected behavior of test

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
}

void test_shr() {
    u256 x = {
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111,
        0b1110001111111111111111111111111111111111111111111111111111000111
    };
    u256 shift = {3, 0, 0, 0};
    // Note: shift left zero pads on left side of most significant word
    u256 want = {
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b1111110001111111111111111111111111111111111111111111111111111000,
        0b0001110001111111111111111111111111111111111111111111111111111000
    };

    u256 have;
    shr(have, x, shift);

    verbose_assert_eq(have, want, "Shr", "Should right shift by 3 bits");
}

void test_sar() {
    // There are several cases to test here! Need to implement more
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
        0b0001110001111111111111111111111111111111111111111111111111111000
    };

    u256 have;
    shr(have, x, shift);

    verbose_assert_eq(have, want, "Sar", "Should right shift by 3 bits");
}

int main() {
    // REFACTOR: Either a macro or a function pointer, print messages for pass
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

    printf("All tests passed.\n");
}
