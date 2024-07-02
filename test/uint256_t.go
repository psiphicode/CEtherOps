package main

import (
	"fmt"
	"github.com/holiman/uint256"
)

func load_u256(u *uint256.Int, i int) {
	u.Set(test_cases_u256[i])
}

func print_uint(label string, x *uint256.Int) {
	fmt.Println(label+"[0]:", x[0])
	fmt.Println(label+"[1]:", x[1])
	fmt.Println(label+"[2]:", x[2])
	fmt.Println(label+"[3]:", x[3])
}

func tf(v bool) int {
	if v {
		return 1
	}
	return 0
}

func opSHL(res, x, y *uint256.Int) {
	if y.LtUint64(256) {
		res.Lsh(x, uint(y.Uint64()))
	} else {
		res.Clear()
	}
}

func opSHR(res, x, y *uint256.Int) {
	if y.LtUint64(256) {
		res.Rsh(x, uint(y.Uint64()))
	} else {
		res.Clear()
	}
}

func opSAR(res, value, shift *uint256.Int) {
	if shift.GtUint64(256) {
		if value.Sign() >= 0 {
			res.Clear()
		} else {
			res.SetAllOne()
		}
		return
	}
	n := uint(shift.Uint64())
	res.SRsh(value, n)
}

func test_run(i int, res, x, y, z *uint256.Int) {
    fmt.Println("----------------------------------------", i);

    // add
    res.Add(x, y);
    print_uint("add(x, y)", res);

    // mul
    res.Mul(x, y);
    print_uint("mul(x, y)", res);

    // sub
    res.Sub(x, y);
    print_uint("sub(x, y)", res);

    // div
    res.Div(x, y);
    print_uint("div(x, y)", res);

    // sdiv
    res.SDiv(x, y);
    print_uint("sdiv(x, y)", res);

    // mod
    res.Mod(x, y);
    print_uint("mod(x, y)", res);

    // smod
    res.SMod(x, y);
    print_uint("smod(x, y)", res);

    // add_mod
    res.AddMod(x, y, z);
    print_uint("add_mod(x, y, z)", res);

    // mul_mod
    res.MulMod(x, y, z);
    print_uint("mul_mod(x, y, z)", res);

    // _exp
    res.Exp(x, y);
    print_uint("_exp(x, y)", res);

    // sign_extend
    res.ExtendSign(x, y);
    print_uint("sign_extend(x, y)", res);

    // lt
    r := x.Lt(y);
    fmt.Println("lt(x, y):", tf(r));

    // gt
    r = x.Gt(y);
    fmt.Println("gt(x, y):", tf(r));

    // slt
    r = x.Slt(y);
    fmt.Println("slt(x, y):", tf(r));

    // sgt
    r = x.Sgt(y);
    fmt.Println("sgt(x, y):", tf(r));

    // eq
    r = x.Eq(y);
    fmt.Println("eq(x, y):", tf(r));

    // is_zero
    r = res.IsZero();
    fmt.Println("is_zero(x):", tf(r));

    // and
    res.And(x, y);
    print_uint("and(x, y)", res);

    // or
    res.Or(x, y);
    print_uint("or(x, y)", res);

    // xor
    res.Xor(x, y);
    print_uint("xor(x, y)", res);

    // not
    res.Not(x);
    print_uint("not(x)", res);

    byte_check := &uint256.Int{x[0], x[1], x[2], x[3]}
    // byte
    byte_check.Byte(y);
    print_uint("byte(x, y)", byte_check);

    // shl
    opSHL(res, x, y);
    print_uint("shl(x, y)", res);

    // shr
    opSHR(res, x, y);
    print_uint("shr(x, y)", res);

    // sar
    opSAR(res, x, y);
    print_uint("sar(x, y)", res);
}

func main() {
	var res *uint256.Int = &uint256.Int{}
	var x *uint256.Int = &uint256.Int{}
	var y *uint256.Int = &uint256.Int{}
	var z *uint256.Int = &uint256.Int{}

	for i:=0; i < len(test_cases_u256) - 3; i+= 3 {
		load_u256(x, i)
		load_u256(y, i+1)
		load_u256(z, i+2)
		test_run(i/3, res, x, y, z)
	}

    // sm := uint256.NewInt(1)
    // bi := uint256.NewInt(2)
    // sub := sm.Sub(sm, bi)
    // fmt.Println(sub.Dec())
}
