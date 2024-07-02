const fs = require("fs");
const ethers = require("ethers");
const crypto = require("crypto");


const MAX_UINT256 = (1n << 256n) - 1n;

function randomBigInt() {
    let b = crypto.randomBytes(32);
    return BigInt('0x' + b.toString('hex'));
}

const opcodes = [
    'Add', 'Mul', 'Sub', 'Div', 'SDiv', 'Mod', 'SMod', 'AddMod', 'MulMod', 'Exp',
    'SignExtend', 'Lt', 'Gt', 'Slt', 'Sgt', 'Eq', 'IsZero', 'And', 'Or', 'Xor',
    'Not', 'Byte', 'Shl', 'Shr', 'Sar'
];

const bitmasks = [];
for (let i = 0; i < 25; i++) {
    bitmasks[i] = 1n << BigInt(i);
}

// commenting out any of these values removes them from the test call
const opcodes_to_test = [
    'Add',
    'Mul',
    'Sub',
    'Div',
    'SDiv',
    'Mod',
    'SMod',
    'AddMod',
    'MulMod',
    'Exp',
    'SignExtend',
    'Lt',
    'Gt',
    'Slt',
    'Sgt',
    'Eq',
    'IsZero',
    'And',
    'Or',
    'Xor',
    'Not',
    'Byte',
    'Shl',
    'Shr',
    'Sar'
];

var tests_map = 0n;
for (let i = 0; i < opcodes_to_test.length; i++) {
    const bitmask_index = opcodes.indexOf(opcodes_to_test[i]);
    tests_map |= BigInt(bitmasks[bitmask_index]);
}

async function main() {
    const provider = new ethers.JsonRpcProvider("https://sepolia-rollup.arbitrum.io/rpc")

    const addr = JSON.parse(fs.readFileSync('test_address.json')).address;
    console.log("address: ", addr);

    const abi = JSON.parse(fs.readFileSync('build/interface.json')).contracts.uint256_test.Uint256Test.abi;
    const contract = new ethers.Contract(addr, abi, provider);

    const values = [];
    for (let i = 0; i<99; i++) {
        values[i] = randomBigInt();
    }

    const test_result = await contract.test_values(values, tests_map);

    const [passing, opcode, loop_num, result1, result2, x, y, z] = test_result;
    if (passing) {
        console.log('Test passed!');
    } else {
        console.log("Test failed. Here's the data:");
        console.log(`Opcode: ${opcodes[opcode]}`);
        console.log(`result1: ${result1}`);
        console.log(`result2: ${result2}`);
        console.log(`x: ${x}`);
        console.log(`y: ${y}`);
        console.log(`z: ${z}`);
    }
}


// function to_u256(num) {
//     return num & MAX_UINT256;
// }

// function add(x, y) {
//     return to_u256(x + y);
// }

// function mul(x, y) {
//     return to_u256(x * y);
// }

// function sub(x, y) {
//     return to_u256(x - y);
// }

// function div(x, y) {
//     return to_u256(x / y);
// }

// function sdiv(x, y) {
//     // fix
//     return div(x, y);
// }

// function mod(x, m) {
//     return to_u256(x % m);
// }

// function smod(x, m) {
//     // fix
//     return mod(x, m);
// }

// function addmod() {}

// function mulmod() {}

// function exp() {}

// function signextend() {}

// function lt() {}

// function gt() {}

// function slt() {}

// function sgt() {}

// function eq() {}

// function is_zero() {}

// function and() {}

// function or() {}

// function xor() {}

// function not() {}

// function byte() {}

// function shl() {}

// function shr() {}

// function sar() {}

main()
