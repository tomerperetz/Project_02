#! /usr/bin/env bash
./my_grep -v -i hump ./tests/tomer/input_07 | diff ./tests/tomer/out_07 -