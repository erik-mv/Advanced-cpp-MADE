#!/bin/bash

set -e

g++ -std=c++17 -I./ test/test.cpp -o function_test
./function_test

echo All tests passed!