#! /usr/bin/env bash

make all

grep "a" -x -v -i -A2 tests/tomer/input_01 > tests/tomer/out_01
grep "hump"   tests/tomer/input_02 > tests/tomer/out_02
grep "hump" -i -A0 tests/tomer/input_03 > tests/tomer/out_03
grep -i -n -v -c "hump" tests/tomer/input_04 > tests/tomer/out_04
grep -i -n -x "tomer" tests/tomer/input_05 > tests/tomer/out_05
grep -v -n "hump" tests/tomer/input_06 > tests/tomer/out_06
grep -v -i -n "hump" tests/tomer/input_07 > tests/tomer/out_07
grep "I" -n tests/tomer/input_08 > tests/tomer/out_08
grep "do" -n tests/tomer/input_09 > tests/tomer/out_09
grep -v -i -n "dance" tests/tomer/input_10 > tests/tomer/out_10
grep "do" -n tests/tomer/input_11 > tests/tomer/out_11
grep -i -n "ll" tests/tomer/input_12 > tests/tomer/out_12
grep -i "He" tests/tomer/input_13 > tests/tomer/out_13
grep "sound" tests/tomer/input_14 > tests/tomer/out_14
grep -i -A1 "He" tests/tomer/input_13 > tests/tomer/out_15
grep -i -b -A1 "He" tests/tomer/input_13 > tests/tomer/out_16
grep -i -n -A2 "He" tests/tomer/input_13 > tests/tomer/out_17
grep -i -n -b -A4 -v -x -c "He" tests/tomer/input_13 > tests/tomer/out_18
grep -i -A20 "He" tests/tomer/input_13 > tests/tomer/out_19


./my_grep a  -x -v -i -A2 ./tests/tomer/input_01 | diff ./tests/tomer/out_01 -
./my_grep hump  ./tests/tomer/input_02 | diff ./tests/tomer/out_02 -
./my_grep hump -i -A0 ./tests/tomer/input_03 | diff ./tests/tomer/out_03 -
./my_grep -n -i -v -c hump ./tests/tomer/input_04 | diff ./tests/tomer/out_04 - 
./my_grep -n -i -x tomer ./tests/tomer/input_05 | diff ./tests/tomer/out_05 - 
./my_grep -n -v hump ./tests/tomer/input_06 | diff ./tests/tomer/out_06 -
./my_grep -n -v -i hump ./tests/tomer/input_07 | diff ./tests/tomer/out_07 -
./my_grep -n "I" ./tests/tomer/input_08 | diff ./tests/tomer/out_08 -
./my_grep -n "do" ./tests/tomer/input_09 | diff ./tests/tomer/out_09 -
./my_grep -n -v -i "dance" ./tests/tomer/input_10 | diff ./tests/tomer/out_10 -
./my_grep -n "do" ./tests/tomer/input_11 | diff ./tests/tomer/out_11 -
./my_grep -n -i "ll" ./tests/tomer/input_12 | diff ./tests/tomer/out_12 -
./my_grep -i "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_13 -
./my_grep "sound" ./tests/tomer/input_14 | diff ./tests/tomer/out_14 -
./my_grep -i -A1 "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_15 -
./my_grep -i -b -A1 "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_16 -
./my_grep -i -n -A2 "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_17 -
./my_grep -i -n -b -A4 -v -x -c "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_18 -
./my_grep -i -A20 "He" ./tests/tomer/input_13 | diff ./tests/tomer/out_19 -