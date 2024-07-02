#include <helpers.h>

/*
    The 25 EVM Opcodes for uint256 operations.

    See: https://www.evm.codes/
*/

// arithmetic
void add(u256 res, u256 x, u256 y);
void mul(u256 res, u256 x, u256 y);
void sub(u256 res, u256 x, u256 y);
void div(u256 res, u256 x, u256 y);
void sdiv(u256 res, u256 x, u256 y);
void mod(u256 res, u256 x, u256 m);
void smod(u256 res, u256 x, u256 m);
void add_mod(u256 res, u256 x, u256 y, u256 m);
void mul_mod(u256 res, u256 x, u256 y, u256 m);
void _exp(u256 res, u256 x, u256 exponent);
void sign_extend(u256 res, u256 b, u256 x);

// comparison
bool lt(u256 x, u256 y);
bool gt(u256 x, u256 y);
bool slt(u256 x, u256 y);
bool sgt(u256 x, u256 y);
bool eq(u256 x, u256 y);
bool is_zero(u256 x);

// bitwise
void and(u256 res, u256 x, u256 y);
void or(u256 res, u256 x, u256 y);
void xor(u256 res, u256 x, u256 y);
void not(u256 res, u256 x);
void byte(u256 res, u256 x, u256 i);
void shl(u256 res, u256 x, u256 shift);
void shr(u256 res, u256 x, u256 shift);
void sar(u256 res, u256 x, u256 shift);
