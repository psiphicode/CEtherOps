import subprocess


def fail_case(message):
    print("---    Failure")
    print(f"------ {message}")

def run_c_test():
    print("------ Running C code")
    c_result = subprocess.run('./test/uint256_test', capture_output=True)
    if c_result.returncode != 0:
        fail_case(f"There was an error when running the C code:")
        raise Exception(c_result.stderr)
    return c_result

def run_go_test():
    print("------ Running Go code")
    go_result = subprocess.run(['go', 'run', 'test/main.go',
                                'test/test_cases.go'],
                               capture_output=True)
    if go_result.returncode != 0:
        fail_case(f"There was an error when running the Go code:")
        raise Exception(go_result.stderr)
    return go_result


if __name__ == "__main__":
    print("--- Running C and Go tests in Python")

    c_result = run_c_test()
    go_result = run_go_test()

    if c_result.stdout == go_result.stdout:
        print("--- Success!")
    else:
        fail_case("The outputs of C and Go code were different!")
