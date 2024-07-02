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

async function main() {
    const provider = new ethers.JsonRpcProvider("https://sepolia-rollup.arbitrum.io/rpc")

    const addr = JSON.parse(fs.readFileSync('test_address.json')).address;
    console.log("address: ", addr);

    const abi = JSON.parse(fs.readFileSync('build/interface.json')).contracts.uint256_test.Uint256Test.abi;
    const contract = new ethers.Contract(addr, abi, provider);

    const values = [];
    for (let i = 0; i<333; i++) {
        values[i] = randomBigInt();
    }

    const test_result = await contract.test_values(values, 26);

    console.log(test_result);
    const [passing, opcode, loop_num, result1, result2, x, y, z] = test_result;
    if (passing) {
        console.log('Test passed!');
    } else {
        console.log("Test failed. Here's the data:");
        console.log(`Opcode: ${opcodes[opcode]}`);
        console.log(`x: ${values[loop_num]}`);
        console.log(`y: ${values[loop_num+1n]}`);
        console.log(`z: ${values[loop_num+2n]}`);
        console.log(`result1: ${result1}`);
        console.log(`result2: ${result2}`);
        console.log(`x: ${x}`);
        console.log(`y: ${y}`);
        console.log(`z: ${z}`);
    }

    // for (let i = 0; i < 10; i++) {
    //     console.log("---------------------------------------- ", i);
    //     let m = randomBigInt();
    //     let x = randomBigInt();
    //     let y = randomBigInt();
    //
    //     let x1 = x % m;
    //     let y1 = y % m;
    //     const js1 = (x1 + y1) % m;
    //
    //
    //     const x2 = await contract.Mod(x, m);
    //     const y2 = await contract.Mod(y, m);
    //
    //     const sum = await contract.Add(x, y);
    //     const jssum = (x + y) & ((1n<<256n)-1n);
    //
    //     const st1 = await contract.AddMod(x1, y1, m);
    //     const st2 = await contract.AddMod(x, y, m);
    //
    //
    //     if (sum != jssum) {
    //         console.log('not good add')
    //         console.log('js ', jssum)
    //         console.log('st ' , sum)
    //     }
    //
    //     if (x2 != x1) {
    //         console.log('--- modx disc ---');
    //         console.log('js ' , x1);
    //         console.log('st ', x2);
    //     }
    //
    //     if (y2 != y1) {
    //         console.log('--- mody disc ---');
    //         console.log('y  ', y);
    //         console.log('m  ', m);
    //         console.log('js ' , y1);
    //         console.log('st ', y2);
    //     }
    //
    //     if (js1 != st1 || st2 != js1) {
    //         console.log('--- discrepancy ---');
    //         console.log('js ', js1);
    //         console.log('st ', st1);
    //         console.log('st2', st2);
    //         console.log('x  ', x);
    //         console.log('y  ', y);
    //         console.log('m  ', m);
    //     }
    //
    //     const mulmodjs = (x * y) % m;
    //     const mulmodst = await contract.MulMod(x, y, m);
    //
    //     if (mulmodjs != mulmodst) {
    //         console.log('--- discrepancy ---');
    //         console.log('js ', mulmodjs);
    //         console.log('st ', mulmodst);
    //         console.log('x  ', x);
    //         console.log('y  ', y);
    //         console.log('m  ', m);
    //     }
    // }
}

function to_u256(num) {
    return num & MAX_UINT256;
}

function add(x, y) {
    return to_u256(x + y);
}

function mul(x, y) {
    return to_u256(x * y);
}

function sub(x, y) {
    return to_u256(x - y);
}

function div(x, y) {
    return to_u256(x / y);
}

function sdiv(x, y) {
    // fix
    return div(x, y);
}

function mod(x, m) {
    return to_u256(x % m);
}

function smod(x, m) {
    // fix
    return mod(x, m);
}

function addmod() {}

function mulmod() {}

function exp() {}

function signextend() {}

function lt() {}

function gt() {}

function slt() {}

function sgt() {}

function eq() {}

function is_zero() {}

function and() {}

function or() {}

function xor() {}

function not() {}

function byte() {}

function shl() {}

function shr() {}

function sar() {}

main()
