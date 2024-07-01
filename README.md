## CEtherOps
The purpose of this repository is to implement EVM equivalent operations over 256 bit integers in C, so that it can be used in Stylus contracts. This project is a port of [uint256.go](https://github.com/holiman/uint256/), which is the integer library used by [go-ethereum](https://github.com/ethereum/go-ethereum).

#### The Opcodes
There are 25 opcodes for integer operations. General descriptions of all EVM opcodes can be seen at [evm.codes](https://evm.codes/) and in the Solidity docs for [Yul](https://docs.soliditylang.org/en/latest/yul.html#evm-dialect). You can see how they're implemented in [go-ethereum/core/vm/instructions.go](https://github.com/ethereum/go-ethereum/blob/master/core/vm/instructions.go#L30-L231) and [uint256/uint256.go](https://github.com/holiman/uint256/blob/master/uint256.go).

**Supported Opcodes**
|     |     |     |     |     |
|-----|-----|-----|-----|-----|
| Add | Mul | Sub | Div | SDiv |
| Mod | SMod | AddMod | MulMod | Exp |
| SignExtend | Lt | Gt | Slt | Sgt |
| Eq | IsZero | And | Or | Xor |
| Not | Byte | Shl | Shr | Sar |

## Testing
The testing in this project is unconventional because I'm comparing the results of different implementations.
- I compare the C implementation directly to the Golang implementation.
    - Use Python to capture std output of the compiled C to the std output of the compiled Go code.
    - These tests must get the same results for each Opcode invocation, then they must write the results to std output identically.
    - I'm sure it's better to write each test's results to JSON and then compare them, but I did this as a quick first pass.
- TODO: I compare the way JavaScript handles big integers to the Stylus contract directly.
    - Use JS to compute the integer operations, then compare to the results of calling the functions on the Sepolia testnet using ethers.
- TODO: I compare the way EVM handles big integers in Solidity to the Stylus contract.
    - Use Solidity/Yul contract to compute the opcode results then compare to the results of a cross-contract call to the Stylus contract.

The tests use randomly-generated integers. Passing tests only prove the correctness of subsets of all possible inputs and are not a guarantee of the safety of the code.

Run the Python test:
```sh
make testpy
```

#### TODO
- Write the JS tests
- Write the Solidity tests
- Update the C/Go tests to write the results into JSON

## Build & Deploy
To build the Stylus contract, run:
```sh
make
```
To deploy it, you need a testnet account with testnet ETH. Set the following environment variables:
```text
PRIVATE_KEY=0x...
ENDPOINT=https://sepolia-rollup.arbitrum.io/rpc
```
Then run the command:
```sh
cargo stylus deploy --wasm-file=uint256.wasm --private-key=$PRIVATE_KEY --endpoint=$ENDPOINT
```
Note that there's no real point to deploying this contract as it's still actively being developed and this was just a proof of concept.