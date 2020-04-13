#! /usr/bin/env tcsh

./my_grep -E "\[(1|)[0-9]\\\]" ~nimrodav/grep_tests/in17 | diff ~nimrodav/grep_tests/out17 -
valgrind --quiet --leak-check=yes ./my_grep -E "\[(1|)[0-9]\\\]" ~nimrodav/grep_tests/in17 | diff ~nimrodav/grep_tests/out17 -
