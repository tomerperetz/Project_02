#! /usr/bin/env bash

make all

grep "a" tests/tomer/input_01 > tests/tomer/out_01
grep "hump" tests/tomer/input_02 > tests/tomer/out_02
grep "hump" tests/tomer/input_03 > tests/tomer/out_03
grep -i "hump" tests/tomer/input_04 > tests/tomer/out_04
grep -i "tomer" tests/tomer/input_05 > tests/tomer/out_05
grep -v "hump" tests/tomer/input_06 > tests/tomer/out_06
grep -v -i "hump" tests/tomer/input_07 > tests/tomer/out_07
grep "I" tests/tomer/input_08 > tests/tomer/out_08
grep "do" tests/tomer/input_09 > tests/tomer/out_09
grep -v -i "dance" tests/tomer/input_10 > tests/tomer/out_10
grep "do" tests/tomer/input_11 > tests/tomer/out_11
grep -i "ll" tests/tomer/input_12 > tests/tomer/out_12
grep -i "He" tests/tomer/input_13 > tests/tomer/out_13
grep "sound" tests/tomer/input_14 > tests/tomer/out_14


./my_grep a ./tests/tomer/input_01 | diff ./tests/tomer/out_01 -
./my_grep hump ./tests/tomer/input_02 | diff ./tests/tomer/out_02 -
./my_grep hump ./tests/tomer/input_03 | diff ./tests/tomer/out_03 -
./my_grep -i hump ./tests/tomer/input_04 | diff ./tests/tomer/out_04 - 
./my_grep -i tomer ./tests/tomer/input_05 | diff ./tests/tomer/out_05 - 
./my_grep -v hump ./tests/tomer/input_06 | diff ./tests/tomer/out_06 -
./my_grep -v -i hump ./tests/tomer/input_07 | diff ./tests/tomer/out_07 -
./my_grep "I" ./tests/tomer/input_08 | diff ./tests/tomer/out_08 -
./my_grep "do" ./tests/tomer/input_09 | diff ./tests/tomer/out_09 -
./my_grep -v -i "dance" ./tests/tomer/input_10 | diff ./tests/tomer/out_10 -
./my_grep "do" ./tests/tomer/input_11 | diff ./tests/tomer/out_11 -
./my_grep -i "ll" ./tests/tomer/input_12 | diff ./tests/tomer/out_12 -
./my_grep -i "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_13 -
./my_grep "sound" ./tests/tomer/input_14 | diff ./tests/tomer/out_14 -