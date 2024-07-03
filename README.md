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

## Design Goals
The end goal of this project is to have an importable library in C Stylus contracts.
```c
#include <CEtherOps/uint256.h>
```


## Testing
The testing in this project is unconventional because I'm comparing the results of different implementations. The tests currently use randomly-generated integers. Passing tests only prove the correctness of subsets of all possible inputs and are not a guarantee of the safety of the code. The tests are currently lacking. The next iterations of testing will be more robust, probing for errors in edge cases. For example, in the `sar`, `shl`, etc. operations, the randomly generated integers will always be large enough to just set the result to zero. So I need to choose meaningful inputs to trigger different outcomes depending on the conditional branches of the operation.

#### C vs Go
I compare the C implementation directly to the Golang implementation by capturing the std output when executing the test binaries. See [run.py](./test/run.py) for the code. To put it simply, in both C and Go, we perform the same operations using the same integers, then write their elements to std out. The test is valid if the std output of the C implementation matches that of the Golang implementation. There's a risk of the operations being identical but the output being different, for example, if the programs write the result to std output with even a single deviation. However, if the output matches exactly, then that should be evidence of a passing test. In other words, there could be a false negative test, but I don't think there could be a false positive test.

Run the C/Go test:
```sh
make testpy
```

#### EVM vs Stylus
I had trouble setting up a local testing environment using foundry. It appears that when foundry does a fork of a contract, it locally caches the storage and bytecode of the contract, then tests run against the cached state and code. The only problem is that it uses the EVM to execute the forked bytecode, but Stylus contracts require the wasmer runtime. Therefore, the Solidity test contract is deployed on the Arbitrum Sepolia testnet. See [uint256.t.sol](./test/uint256.t.sol) for the code. I compare the way EVM handles big integers in Solidity to the Stylus contract.


To run the Solidity test, first install the npm dependencies:
```sh
npm install .
```
Then run the command:
```sh
make testsol
```
alternatively, run:
```sh
node test/uint256.t.js
```

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
cargo stylus deploy --wasm-file=build/uint256_stripped.wasm --private-key=$PRIVATE_KEY --endpoint=$ENDPOINT
```
alternatively, run:
```sh
bash scripts/deploy.sh
```

Note that there's no real point to deploying this contract as it's still actively being developed and this was just a proof of concept.
