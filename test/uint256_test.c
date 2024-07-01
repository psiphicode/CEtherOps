#include <stdio.h>
#include <uint256.h>


void print_uint(const char *label, u256 x) {
    printf("%s[0]: %lu\n%s[1]: %lu\n%s[2]: %lu\n%s[3]: %lu\n",
           label, x[0], label, x[1], label, x[2], label, x[3]);
}

extern int num_u256;
extern u256 test_cases_u256[];

void load_u256(u256 u, int i) {
    copy_words(u, test_cases_u256[i], 4);
}

void test_run(int i, u256 res, u256 x, u256 y, u256 z) {
    printf("---------------------------------------- %i\n", i);

    // add
    add(res, x, y);
    print_uint("add(x, y)", res);

    // mul
    mul(res, x, y);
    print_uint("mul(x, y)", res);

    // sub
    sub(res, x, y);
    print_uint("sub(x, y)", res);

    // div
    div(res, x, y);
    print_uint("div(x, y)", res);

    // sdiv
    sdiv(res, x, y);
    print_uint("sdiv(x, y)", res);

    // mod
    mod(res, x, y);
    print_uint("mod(x, y)", res);

    // smod
    smod(res, x, y);
    print_uint("smod(x, y)", res);

    // add_mod
    add_mod(res, x, y, z);
    print_uint("add_mod(x, y, z)", res);

    // mul_mod
    mul_mod(res, x, y, z);
    print_uint("mul_mod(x, y, z)", res);

    // _exp
    _exp(res, x, y);
    print_uint("_exp(x, y)", res);

    // sign_extend
    sign_extend(res, x, y);
    print_uint("sign_extend(x, y)", res);

    bool r;

    // lt
    r = lt(x, y);
    printf("lt(x, y): %d\n", r);

    // gt
    r = gt(x, y);
    printf("gt(x, y): %d\n", r);

    // slt
    r = slt(x, y);
    printf("slt(x, y): %d\n", r);

    // sgt
    r = sgt(x, y);
    printf("sgt(x, y): %d\n", r);

    // eq
    r = eq(x, y);
    printf("eq(x, y): %d\n", r);

    // is_zero
    r = is_zero(x);
    printf("is_zero(x): %d\n", r);

    // and
    and(res, x, y);
    print_uint("and(x, y)", res);

    // or
    or(res, x, y);
    print_uint("or(x, y)", res);

    // xor
    xor(res, x, y);
    print_uint("xor(x, y)", res);

    // not
    not(res, x);
    print_uint("not(x)", res);

    // byte
    byte(res, x, y);
    print_uint("byte(x, y)", res);

    // shl
    shl(res, x, y);
    print_uint("shl(x, y)", res);

    // shr
    shr(res, x, y);
    print_uint("shr(x, y)", res);

    // sar
    // print_uint("x", x);
    // print_uint("y", y);
    sar(res, x, y);
    print_uint("sar(x, y)", res);
}

int main() {
    u256 res, x, y, z;

    for (int i = 0; i < (num_u256-3); i += 3) {
        load_u256(x, i);
        load_u256(y, i+1);
        load_u256(z, i+2);
        test_run(i/3, res, x, y, z);
    }

    // mul(res, x, y);
    // print_uint("mul(x, y)", res);
}