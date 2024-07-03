#include <stylus_types.h>
#include <uint256.h>
#include <uint256/Uint256.h>


ArbResult inline nodata(ArbStatus status) {
    // return status with no data
    ArbResult res = {status, NULL, 0};
    return res;
}

ArbResult inline success(uint8_t const *retval) {
    // return success with a single word
    ArbResult res = {Success, retval , 32};
    return res;
}

ArbResult default_func(void *storage, uint8_t *input, size_t len, bebi32 value)
{
    // there is no fallback function
    return nodata(Failure);
}

void inline read1(uint8_t *input, u256 x) {
    // input is big endian, convert it to little endian
    for (int i = 0; i<4; i++) {
        __builtin_memcpy(x+i, input+(24-(i*sizeof(u64))), sizeof(u64));
        x[i] = __builtin_bswap64(x[i]);
    }
}

void inline read2(uint8_t *input, u256 x, u256 y) {
    // input is big endian, convert it to little endian
    for (int i = 0; i<4; i++) {
        __builtin_memcpy(x+i, input+(24-(i*sizeof(u64))), sizeof(u64));
        __builtin_memcpy(y+i, input+(56-(i*sizeof(u64))), sizeof(u64));
        x[i] = __builtin_bswap64(x[i]);
        y[i] = __builtin_bswap64(y[i]);
    }
}

void inline read3(uint8_t *input, u256 x, u256 y, u256 z) {
    // input is big endian, convert it to little endian
    for (int i = 0; i<4; i++) {
        __builtin_memcpy(x+i, input+(24-(i*sizeof(u64))), sizeof(u64));
        __builtin_memcpy(y+i, input+(56-(i*sizeof(u64))), sizeof(u64));
        __builtin_memcpy(z+i, input+(88-(i*sizeof(u64))), sizeof(u64));
        x[i] = __builtin_bswap64(x[i]);
        y[i] = __builtin_bswap64(y[i]);
        z[i] = __builtin_bswap64(z[i]);
    }
}

void inline write1(u256 buf_out, u256 result) {
    // result is little endian, convert it to big endian
    for (int i = 0; i < 4; i++) {
        buf_out[i] = __builtin_bswap64(result[3-i]);
    }
}

void inline swap_endian(u256 buf_out) {
    // swap from little endian <==> big endian or vice versa
    u64 temp;
    temp = __builtin_bswap64(buf_out[3]);
    buf_out[3] = __builtin_bswap64(buf_out[0]);
    buf_out[0] = temp;

    temp = __builtin_bswap64(buf_out[2]);
    buf_out[2] = __builtin_bswap64(buf_out[1]);
    buf_out[1] = temp;
}

/*
    Arithmetic
*/
ArbResult Add(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, y, buf_out;

    // big endian -> little endian
    read2(input, x, y);

    // perform operation
    add(result, x, y);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Mul(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, y, buf_out;

    // big endian -> little endian
    read2(input, x, y);

    // perform operation
    mul(result, x, y);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Sub(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, y, buf_out;

    // big endian -> little endian
    read2(input, x, y);

    // perform operation
    sub(result, x, y);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Div(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, y, buf_out;

    // big endian -> little endian
    read2(input, x, y);

    // perform operation
    div(result, x, y);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult SDiv(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, y, buf_out;

    // big endian -> little endian
    read2(input, x, y);

    // perform operation
    sdiv(result, x, y);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Mod(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    mod(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult SMod(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    smod(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult AddMod(uint8_t *input, size_t len) {
    // require input to be three evm words
    if (len != 96) {
        return nodata(Failure);
    }

    u256 result, x, y, m, buf_out;

    // big endian -> little endian
    read3(input, x, y, m);

    // perform operation
    add_mod(result, x, y, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult MulMod(uint8_t *input, size_t len) {
    // require input to be three evm words
    if (len != 96) {
        return nodata(Failure);
    }

    u256 result, x, y, m, buf_out;

    // big endian -> little endian
    read3(input, x, y, m);

    // perform operation
    mul_mod(result, x, y, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Exp(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    _exp(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}


ArbResult SignExtend(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    sign_extend(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

/*
    Comparison
*/
ArbResult Lt(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    bool r = lt(x, m);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Gt(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    bool r = gt(x, m);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Slt(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    bool r = slt(x, m);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Sgt(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    bool r = sgt(x, m);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Eq(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    bool r = eq(x, m);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult IsZero(uint8_t *input, size_t len) {
    // require input to be one evm word
    if (len != 32) {
        return nodata(Failure);
    }

    u256 result, x, buf_out;

    // big endian -> little endian
    read1(input, x);

    // perform operation
    bool r = is_zero(x);
    clear_words(&result[0], 4);
    result[0] = r;

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

/*
    Bitwise
*/
ArbResult And(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    and(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Or(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    or(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Xor(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    xor(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Not(uint8_t *input, size_t len) {
    // require input to be one evm word
    if (len != 32) {
        return nodata(Failure);
    }

    u256 result, x, buf_out;

    // big endian -> little endian
    read1(input, x);

    // perform operation
    not(result, x);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Byte(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    byte(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Shl(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    shl(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Shr(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    shr(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}

ArbResult Sar(uint8_t *input, size_t len) {
    // require input to be two evm words
    if (len != 64) {
        return nodata(Failure);
    }

    u256 result, x, m, buf_out;

    // big endian -> little endian
    read2(input, x, m);

    // perform operation
    sar(result, x, m);

    // convert result to big endian
    write1(buf_out, result);

    return success((uint8_t*)buf_out);
}