#!/bin/bash

#put in one directory with 'main.cpp' and your input in a file called 'input'
sed "s/.*ore robot\
[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\([[:digit:]]\+\)[^[:digit:]]*\
/{\1,\2,\3,\4,\5,\6},/;\
1 s/^/std::vector<input_t> input {/;\
$ s/,$/};/" input > input.inc
g++ -O2 part1.cpp
./a.out
g++ -O2 part2.cpp
./a.out
