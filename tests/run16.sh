#! /usr/bin/env bash

./my_grep -E "\[(1|)[0-9]\]" ~nimrodav/grep_tests/in16 | diff ~nimrodav/grep_tests/out16 -
valgrind --quiet --leak-check=yes ./my_grep -E "\[(1|)[0-9]\]" ~nimrodav/grep_tests/in16 | diff ~nimrodav/grep_tests/out16 -
