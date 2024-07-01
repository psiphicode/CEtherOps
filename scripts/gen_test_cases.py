import sys
import random



C_TEMPLATE = """
#include "uint256.h"


int num_u256 = %s;
u256 test_cases_u256[] = {
%s};
"""

GO_TEMPLATE = """
package main

import "github.com/holiman/uint256"


var test_cases_u256 []*uint256.Int = []*uint256.Int{
%s}
"""


def rand_uint(bit_width):
    return int(random.random() * ((1<<bit_width)-1))

def rand_uint256():
    return [rand_uint(64) for _ in range(4)]

def gen_uints(num_vals):
    return [rand_uint256() for _ in range(num_vals)]

def format_c(uints):
    c_array = ""
    for uint in uints:
        c_array += "    {%sULL, %sULL, %sULL, %sULL},\n"%(uint[0], uint[1], uint[2], uint[3])
    return c_array

def format_go(uints):
    go_array = ""
    for uint in uints:
        go_array += "    &uint256.Int{%s, %s, %s, %s},\n"%(uint[0], uint[1], uint[2], uint[3])
    return go_array

if __name__ == '__main__':
    try:
        num_tests = int(sys.argv[1])
    except:
        print("usage: python gen_testcases.py num_tests")
        raise Exception("Invalid num_tests")

    uints = gen_uints(num_tests)

    c_array = format_c(uints)
    go_array = format_go(uints)

    c_test_cases = C_TEMPLATE % (num_tests, c_array)
    go_test_cases = GO_TEMPLATE % (go_array)

    with open('test/test_cases.c', 'w+') as f:
        f.write(c_test_cases)

    with open('test/test_cases.go', 'w+') as f:
        f.write(go_test_cases)


