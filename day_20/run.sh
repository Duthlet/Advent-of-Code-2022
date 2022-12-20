#!/bin/bash

#put in one directory with 'main.cpp' and your input in a file called 'input'
sed -e "s/$/,/;1 s/^/std::vector<long long> input {/;$ s/,$/};/" input > input.inc
g++ -O2 main.cpp
./a.out
