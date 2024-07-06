STACK_SIZE=8192
CC=clang
LD=wasm-ld
CFLAGS=-I./include/ -Iinterface-gen/ --target=wasm32 -Os --no-standard-libraries -mbulk-memory -Wall -g
LDFLAGS=-O2 --no-entry --stack-first -z stack-size=$(STACK_SIZE) -Bstatic

OBJECTS=build/impl.o build/lib/bebi.o build/lib/helpers.o build/lib/uint256.o build/gen/Uint256_main.o

all: build/uint256_stripped.wasm

# STEP1 : compile solidity
# The output is used by cargo and can also be used by any web3 for ABI
# For interface_compile.json see: https://docs.soliditylang.org/en/v0.8.20/using-the-compiler.html#compiler-input-and-output-json-description
build/interface.json: interface_compile.json src/uint256.sol test/uint256.t.sol
	mkdir -p build
	cat $< | solc --standard-json --pretty-json > $@

# STEP 2 : generate headers and main function from the compiled solidity
cargo-generate: build/interface.json
	mkdir -p build
	cargo stylus cgen $< interface-gen

interface-gen/uint256/Uint256_main.c: cargo-generate

# Step 3.1: build the generated main file (Uint256_main.o)
build/gen/%.o: interface-gen/uint256/%.c
	mkdir -p build/gen/
	$(CC) $(CFLAGS) -c $< -o $@

# Step 3.2: build the required library files
build/lib/%.o: src/%.c
	mkdir -p build/lib
	$(CC) $(CFLAGS) -c $< -o $@

# STEP 3.3: implement / build the functions creating the logic of the smart contract
build/%.o: src/%.c cargo-generate
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Generate the test cases files
test/test_cases.go test/test_cases.c: scripts/gen_test_cases.py
	python scripts/gen_test_cases.py 33

# Run all of the tests
testpy: test/run.py scripts/gen_test_cases.py test/uint256.t.c test/test_cases.go test/uint256.t.go
	python scripts/gen_test_cases.py 33
	gcc -I./include -Wall -g -o test/ct_uint256 test/uint256.t.c test/test_cases.c src/uint256.c test/helpers.c
	python test/run.py

testsol: test/uint256.t.js
	node test/uint256.t.js

testc:
    gcc -I./include -Wall -g -o test/ct_uint256 test/uint256.tv2.c test/test_cases.c src/uint256.c test/helpers.c && ./test/ct_uint256

# Step 4: link
build/uint256.wasm: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# Step 5: strip symbols (they won't help on-chain)
build/uint256_stripped.wasm: build/uint256.wasm
	wasm-strip -o $@ $<

clean:
	rm -rf interface-gen build test/test_cases.c test/test_cases.go

.phony: all cargo-generate clean testpy testsol
