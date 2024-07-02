// SPDX-License-Identifier: MIT License
pragma solidity ^0.8.19;


interface Uint256 {
    // arithmetic
    function Add(uint x, uint y) external pure returns (uint z);
    function Mul(uint x, uint y) external pure returns (uint z);
    function Sub(uint x, uint y) external pure returns (uint z);
    function Div(uint x, uint y) external pure returns (uint z);
    function SDiv(uint x, uint y) external pure returns (uint z);
    function Mod(uint x, uint y) external pure returns (uint z);
    function SMod(uint x, uint y) external pure returns (uint z);
    function AddMod(uint x, uint y, uint m) external pure returns (uint);
    function MulMod(uint x, uint y, uint m) external pure returns (uint);
    function Exp(uint x, uint y) external pure returns (uint z);
    function SignExtend(uint x, uint y) external pure returns (uint z);

    // comparison
    function Lt(uint x, uint y) external pure returns (bool z);
    function Gt(uint x, uint y) external pure returns (bool z);
    function Slt(uint x, uint y) external pure returns (bool z);
    function Sgt(uint x, uint y) external pure returns (bool z);
    function Eq(uint x, uint y) external pure returns (bool z);
    function IsZero(uint x) external pure returns (bool z);

    // bitwise
    function And(uint x, uint y) external pure returns (uint z);
    function Or(uint x, uint y) external pure returns (uint z);
    function Xor(uint x, uint y) external pure returns (uint z);
    function Not(uint x) external pure returns (uint z);
    function Byte(uint x, uint y) external pure returns (uint z);
    function Shl(uint x, uint shift) external pure returns (uint z);
    function Shr(uint x, uint shift) external pure returns (uint z);
    function Sar(uint x, uint shift) external pure returns (uint z);
}

contract Uint256Test {
    Uint256 public stylusContract = Uint256(0x9bB4006025B0f8bE1B482835FCf43A457EFC945E);

    function test_values(uint256[] memory values, uint256 runners)
        public view returns (uint, uint, uint, uint, uint, uint, uint, uint)
    {
        for (uint i = 0; i < (values.length/3); i+=3) {
            uint256 result1;
            uint256 result2;
            uint256 x = values[i];
            uint256 y = values[i+1];
            uint256 z = values[i+2];

            if (runners > 0) {
                // Add
                result1 = stylusContract.Add(x, y);
                assembly {
                    result2 := add(x, y)
                }
                if (result1 != result2) return (0, 0, i, result1, result2, x, y, z);
            }

            if (runners > 1) {
                // Mul
                result1 = stylusContract.Mul(x, y);
                assembly {
                    result2 := mul(x, y)
                }
                if (result1 != result2) return (0, 1, i, result1, result2, x, y, z);
            }

            if (runners > 2) {
                // Sub
                result1 = stylusContract.Sub(x, y);
                assembly {
                    result2 := sub(x, y)
                }
                if (result1 != result2) return (0, 2, i, result1, result2, x, y, z);
            }

            if (runners > 3) {
                // Div
                result1 = stylusContract.Div(x, y);
                assembly {
                    result2 := div(x, y)
                }
                if (result1 != result2) return (0, 3, i, result1, result2, x, y, z);
            }

            if (runners > 4) {
                // SDiv
                result1 = stylusContract.SDiv(x, y);
                assembly {
                    result2 := sdiv(x, y)
                }
                if (result1 != result2) return (0, 4, i, result1, result2, x, y, z);
            }

            if (runners > 5) {
                // Mod
                result1 = stylusContract.Mod(x, y);
                assembly {
                    result2 := mod(x, y)
                }
                if (result1 != result2) return (0, 5, i, result1, result2, x, y, z);
            }

            if (runners > 6) {
                // SMod
                result1 = stylusContract.SMod(x, y);
                assembly {
                    result2 := smod(x, y)
                }
                if (result1 != result2) return (0, 6, i, result1, result2, x, y, z);
            }

            if (runners > 7) {
                // AddMod
                result1 = stylusContract.AddMod(x, y, z);
                assembly {
                    result2 := addmod(x, y, z)
                }
                if (result1 != result2) return (0, 7, i, result1, result2, x, y, z);
            }

            if (runners > 8) {
                // MulMod
                result1 = stylusContract.MulMod(x, y, z);
                assembly {
                    result2 := mulmod(x, y, z)
                }
                if (result1 != result2) return (0, 8, i, result1, result2, x, y, z);
            }

            if (runners > 9) {
                // Exp
                result1 = stylusContract.Exp(x, y);
                assembly {
                    result2 := exp(x, y)
                }
                if (result1 != result2) return (0, 9, i, result1, result2, x, y, z);
            }

            if (runners > 10) {
                // SignExtend
                result1 = stylusContract.SignExtend(x, y);
                assembly {
                    result2 := signextend(y, x)
                }
                if (result1 != result2) return (0, 10, i, result1, result2, x, y, z);
            }

            /*
               Comparisons
            */
            if (runners > 11) {
                // Lt
                result1 = stylusContract.Lt(x, y) ? 1 : 0;
                assembly {
                    result2 := lt(x, y)
                }
                if (result1 != result2) return (0, 11, i, result1, result2, x, y, z);
            }

            if (runners > 12) {
                // Gt
                result1 = stylusContract.Gt(x, y) ? 1 : 0;
                assembly {
                    result2 := gt(x, y)
                }
                if (result1 != result2) return (0, 12, i, result1, result2, x, y, z);
            }

            if (runners > 13) {
                // Slt
                result1 = stylusContract.Slt(x, y) ? 1 : 0;
                assembly {
                    result2 := slt(x, y)
                }
                if (result1 != result2) return (0, 13, i, result1, result2, x, y, z);
            }

            if (runners > 14) {
                // Sgt
                result1 = stylusContract.Sgt(x, y) ? 1 : 0;
                assembly {
                    result2 := sgt(x, y)
                }
                if (result1 != result2) return (0, 14, i, result1, result2, x, y, z);
            }

            if (runners > 15) {
                // Eq
                result1 = stylusContract.Eq(x, y) ? 1 : 0;
                assembly {
                    result2 := eq(x, y)
                }
                if (result1 != result2) return (0, 15, i, result1, result2, x, y, z);
            }

            if (runners > 16) {
                // IsZero
                result1 = stylusContract.IsZero(x) ? 1 : 0;
                assembly {
                    result2 := iszero(x)
                }
                if (result1 != result2) return (0, 16, i, result1, result2, x, y, z);
            }

            /*
                Bitwise
            */
            if (runners > 17) {
                // And
                result1 = stylusContract.And(x, y);
                assembly {
                    result2 := and(x, y)
                }
                if (result1 != result2) return (0, 17, i, result1, result2, x, y, z);
            }

            if (runners > 18) {
                // Or
                result1 = stylusContract.Or(x, y);
                assembly {
                    result2 := or(x, y)
                }
                if (result1 != result2) return (0, 18, i, result1, result2, x, y, z);
            }

            if (runners > 19) {
                // Xor
                result1 = stylusContract.Xor(x, y);
                assembly {
                    result2 := xor(x, y)
                }
                if (result1 != result2) return (0, 19, i, result1, result2, x, y, z);
            }

            if (runners > 20) {
                // Not
                result1 = stylusContract.Not(x);
                assembly {
                    result2 := not(x)
                }
                if (result1 != result2) return (0, 20, i, result1, result2, x, y, z);
            }

            if (runners > 21) {
                // Byte
                result1 = stylusContract.Byte(x, y);
                assembly {
                    result2 := byte(y, x)
                }
                if (result1 != result2) return (0, 21, i, result1, result2, x, y, z);
            }

            if (runners > 22) {
                // Shl
                result1 = stylusContract.Shl(x, y);
                assembly {
                    result2 := shl(y, x)
                }
                if (result1 != result2) return (0, 22, i, result1, result2, x, y, z);
            }

            if (runners > 23) {
                // Shr
                result1 = stylusContract.Shr(x, y);
                assembly {
                    result2 := shr(x, y)
                }
                if (result1 != result2) return (0, 22, i, result1, result2, x, y, z);
            }

            if (runners > 24) {
                // Sar
                result1 = stylusContract.Sar(x, y);
                assembly {
                    result2 := sar(y, x)
                }
                if (result1 != result2) return (0, 23, i, result1, result2, x, y, z);
            }
        }
        return (1, 0, 0, 0, 0, 0, 0, 0);
    }
}
