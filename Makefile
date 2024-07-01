STACK_SIZE=8192
CC=clang
LD=wasm-ld
CFLAGS=-I./include/ -Iinterface-gen/ --target=wasm32 -Os --no-standard-libraries -mbulk-memory -Wall -g
LDFLAGS=-O2 --no-entry --stack-first -z stack-size=$(STACK_SIZE) -Bstatic

OBJECTS=build/impl.o build/lib/bebi.o build/lib/helpers.o build/lib/uint256.o build/gen/Uint256_main.o

all: uint256.wasm

# STEP1 : compile solidity
# The output is used by cargo and can also be used by any web3 for ABI
# For interface_compile.json see: https://docs.soliditylang.org/en/v0.8.20/using-the-compiler.html#compiler-input-and-output-json-description
build/interface.json: interface_compile.json uint256.sol
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

# Step 3.2: build the reuqired library files
build/lib/%.o: ./src/%.c
	mkdir -p build/lib
	$(CC) $(CFLAGS) -c $< -o $@

# STEP 3.3: implement / build the functions creating the logic of the smart contract
build/%.o: %.c cargo-generate
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# Run all of the tests
testpy: test/test_c_and_go.py scripts/gen_test_cases.py test/uint256_test test/test_cases.go test/main.go
	python scripts/gen_test_cases.py 33
	gcc -I./include -Wall -g -o test/uint256_test test/uint256_test.c test/test_cases.c src/uint256.c test/helpers.c
	python test/test_c_and_go.py

# Step 4: link
build/uint256.wasm: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# Step 5: strip symbols (they won't help on-chain)
uint256.wasm: build/uint256.wasm
	wasm-strip -o $@ $<

clean:
	rm -rf interface-gen build uint256.wasm

.phony: all cargo-generate clean testpy
