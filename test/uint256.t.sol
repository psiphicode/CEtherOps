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
    Uint256 public stylusContract = Uint256(0x54FBcd29133d7C0aB47AA952348D8354232a5870);

    function test_values(uint256[] memory values, uint256 runners)
        public view returns (uint, uint, uint, uint, uint, uint, uint)
    {
        uint result1;
        uint result2;
        uint x;
        uint y;
        uint z;
        for (uint i = 0; i < (values.length/3); i+=3) {
            result1;
            result2;
            x = values[i];
            y = values[i+1];
            z = values[i+2];

            if ((runners & 1) > 0) {
                // Add
                result1 = stylusContract.Add(x, y);
                assembly {
                    result2 := add(x, y)
                }
                if (result1 != result2) return (0, 0, result1, result2, x, y, z);
            }

            if ((runners & 2) > 0) {
                // Mul
                result1 = stylusContract.Mul(x, y);
                assembly {
                    result2 := mul(x, y)
                }
                if (result1 != result2) return (0, 1, result1, result2, x, y, z);
            }

            if ((runners & 4) > 0) {
                // Sub
                result1 = stylusContract.Sub(x, y);
                assembly {
                    result2 := sub(x, y)
                }
                if (result1 != result2) return (0, 2, result1, result2, x, y, z);
            }

            if ((runners & 8) > 0) {
                // Div
                result1 = stylusContract.Div(x, y);
                assembly {
                    result2 := div(x, y)
                }
                if (result1 != result2) return (0, 3, result1, result2, x, y, z);
            }

            if ((runners & 16) > 0) {
                // SDiv
                result1 = stylusContract.SDiv(x, y);
                assembly {
                    result2 := sdiv(x, y)
                }
                if (result1 != result2) return (0, 4, result1, result2, x, y, z);
            }

            if ((runners & 32) > 0) {
                // Mod
                result1 = stylusContract.Mod(x, y);
                assembly {
                    result2 := mod(x, y)
                }
                if (result1 != result2) return (0, 5, result1, result2, x, y, z);
            }

            if ((runners & 64) > 0) {
                // SMod
                result1 = stylusContract.SMod(x, y);
                assembly {
                    result2 := smod(x, y)
                }
                if (result1 != result2) return (0, 6, result1, result2, x, y, z);
            }

            if ((runners & 128) > 0) {
                // AddMod
                result1 = stylusContract.AddMod(x, y, z);
                assembly {
                    result2 := addmod(x, y, z)
                }
                if (result1 != result2) return (0, 7, result1, result2, x, y, z);
            }

            if ((runners & 256) > 0) {
                // MulMod
                result1 = stylusContract.MulMod(x, y, z);
                assembly {
                    result2 := mulmod(x, y, z)
                }
                if (result1 != result2) return (0, 8, result1, result2, x, y, z);
            }

            if ((runners & 512) > 0) {
                // Exp
                result1 = stylusContract.Exp(x, y);
                assembly {
                    result2 := exp(x, y)
                }
                if (result1 != result2) return (0, 9, result1, result2, x, y, z);
            }

            if ((runners & 1024) > 0) {
                // SignExtend
                result1 = stylusContract.SignExtend(x, y);
                assembly {
                    result2 := signextend(y, x)
                }
                if (result1 != result2) return (0, 10, result1, result2, x, y, z);
            }

            /*
               Comparisons
            */
            if ((runners & 2048) > 0) {
                // Lt
                result1 = stylusContract.Lt(x, y) ? 1 : 0;
                assembly {
                    result2 := lt(x, y)
                }
                if (result1 != result2) return (0, 11, result1, result2, x, y, z);
            }

            if ((runners & 4096) > 0) {
                // Gt
                result1 = stylusContract.Gt(x, y) ? 1 : 0;
                assembly {
                    result2 := gt(x, y)
                }
                if (result1 != result2) return (0, 12, result1, result2, x, y, z);
            }

            if ((runners & 8192) > 0) {
                // Slt
                result1 = stylusContract.Slt(x, y) ? 1 : 0;
                assembly {
                    result2 := slt(x, y)
                }
                if (result1 != result2) return (0, 13, result1, result2, x, y, z);
            }

            if ((runners & 16384) > 0) {
                // Sgt
                result1 = stylusContract.Sgt(x, y) ? 1 : 0;
                assembly {
                    result2 := sgt(x, y)
                }
                if (result1 != result2) return (0, 14, result1, result2, x, y, z);
            }

            if ((runners & 32768) > 0) {
                // Eq
                result1 = stylusContract.Eq(x, y) ? 1 : 0;
                assembly {
                    result2 := eq(x, y)
                }
                if (result1 != result2) return (0, 15, result1, result2, x, y, z);
            }

            if ((runners & 65536) > 0) {
                // IsZero
                result1 = stylusContract.IsZero(x) ? 1 : 0;
                assembly {
                    result2 := iszero(x)
                }
                if (result1 != result2) return (0, 16, result1, result2, x, y, z);
            }

            /*
                Bitwise
            */
            if ((runners & 131072) > 0) {
                // And
                result1 = stylusContract.And(x, y);
                assembly {
                    result2 := and(x, y)
                }
                if (result1 != result2) return (0, 17, result1, result2, x, y, z);
            }

            if ((runners & 262144) > 0) {
                // Or
                result1 = stylusContract.Or(x, y);
                assembly {
                    result2 := or(x, y)
                }
                if (result1 != result2) return (0, 18, result1, result2, x, y, z);
            }

            if ((runners & 524288) > 0) {
                // Xor
                result1 = stylusContract.Xor(x, y);
                assembly {
                    result2 := xor(x, y)
                }
                if (result1 != result2) return (0, 19, result1, result2, x, y, z);
            }

            if ((runners & 1048576) > 0) {
                // Not
                result1 = stylusContract.Not(x);
                assembly {
                    result2 := not(x)
                }
                if (result1 != result2) return (0, 20, result1, result2, x, y, z);
            }

            if ((runners & 2097152) > 0) {
                // Byte
                result1 = stylusContract.Byte(x, y);
                assembly {
                    result2 := byte(y, x)
                }
                if (result1 != result2) return (0, 21, result1, result2, x, y, z);
            }

            if ((runners & 4194304) > 0) {
                // Shl
                result1 = stylusContract.Shl(x, y);
                assembly {
                    result2 := shl(y, x)
                }
                if (result1 != result2) return (0, 22, result1, result2, x, y, z);
            }

            if ((runners & 8388608) > 0) {
                // Shr
                result1 = stylusContract.Shr(x, y);
                assembly {
                    result2 := shr(y, x)
                }
                if (result1 != result2) return (0, 23, result1, result2, x, y, z);
            }

            if ((runners & 16777216) > 0) {
                // Sar
                result1 = stylusContract.Sar(x, y);
                assembly {
                    result2 := sar(y, x)
                }
                if (result1 != result2) return (0, 24, result1, result2, x, y, z);
            }
        }
        return (1, 0, 0, 0, 0, 0, 0);
    }
}
