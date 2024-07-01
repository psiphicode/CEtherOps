const fs = require("fs");
const ethers = require("ethers");
const crypto = require("crypto");


function randomBigInt() {
    let b = crypto.randomBytes(32);
    return BigInt('0x' + b.toString('hex'));
}

async function main() {
    const provider = new ethers.JsonRpcProvider("https://sepolia-rollup.arbitrum.io/rpc")
    const addr = "0xeb569e300d6cb584f688ea3464073baf5e051d71";
    const abi = JSON.parse(fs.readFileSync('build/interface.json')).contracts.uint256.Uint256.abi;
    const contract = new ethers.Contract(addr, abi, provider);

    for (let i = 0; i < 10; i++) {
        console.log("---------------------------------------- ", i);
        let m = randomBigInt();
        let x = randomBigInt();
        let y = randomBigInt();

        let x1 = x % m;
        let y1 = y % m;
        const js1 = (x1 + y1) % m;


        const x2 = await contract.Mod(x, m);
        const y2 = await contract.Mod(y, m);

        const sum = await contract.Add(x, y);
        const jssum = (x + y) & ((1n<<256n)-1n);

        const st1 = await contract.AddMod(x1, y1, m);
        const st2 = await contract.AddMod(x, y, m);


        if (sum != jssum) {
            console.log('not good add')
            console.log('js ', jssum)
            console.log('st ' , sum)
        }

        if (x2 != x1) {
            console.log('--- modx disc ---');
            console.log('js ' , x1);
            console.log('st ', x2);
        }

        if (y2 != y1) {
            console.log('--- mody disc ---');
            console.log('y  ', y);
            console.log('m  ', m);
            console.log('js ' , y1);
            console.log('st ', y2);
        }

        if (js1 != st1 || st2 != js1) {
            console.log('--- discrepancy ---');
            console.log('js ', js1);
            console.log('st ', st1);
            console.log('st2', st2);
            console.log('x  ', x);
            console.log('y  ', y);
            console.log('m  ', m);
        }

        const mulmodjs = (x * y) % m;
        const mulmodst = await contract.MulMod(x, y, m);

        if (mulmodjs != mulmodst) {
            console.log('--- discrepancy ---');
            console.log('js ', mulmodjs);
            console.log('st ', mulmodst);
            console.log('x  ', x);
            console.log('y  ', y);
            console.log('m  ', m);
        }
    }
}

main()
