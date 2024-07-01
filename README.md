## CEtherOps
The purpose of this repository is to implement EVM equivalent operations over 256 bit integers in C, so that it can be used in Stylus contracts. This project is a port of [uint256.go](https://github.com/holiman/uint256/), which is the integer library used by [go-ethereum](https://github.com/ethereum/go-ethereum).

#### The Opcodes
There are 25 opcodes for integer operations. General descriptions of all EVM opcodes can be seen at [evm.codes](https://evm.codes/) and in the Solidity docs for [Yul](https://docs.soliditylang.org/en/latest/yul.html#evm-dialect). You can see how they're implemented in [go-ethereum/core/vm/instructions.go](https://github.com/ethereum/go-ethereum/blob/master/core/vm/instructions.go#L30-L231).

**Supported Opcodes**
|     |     |     |     |     |
|-----|-----|-----|-----|-----|
| Add | Mul | Sub | Div | SDiv |
| Mod | SMod | AddMod | MulMod | Exp |
| SignExtend | Lt | Gt | Slt | Sgt |
| Eq | IsZero | And | Or | Xor |
| Not | Byte | Shl | Shr | Sar |
