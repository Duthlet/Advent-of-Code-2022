#!/bin/bash

#put in one directory with 'main.cpp' and your input in a file called 'input'
sed -e "s/\(.*\)/{\1},/;1 s/^/std::set<point> input {/;$ s/,$/};/" input > input.inc
g++ main.cpp
./a.out
