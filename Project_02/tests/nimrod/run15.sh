#! /usr/bin/env bash

./my_grep -E "(ab|a).(d|cd)[x-z]" ~nimrodav/grep_tests/in15 | diff ~nimrodav/grep_tests/out15 -
valgrind --quiet --leak-check=yes ./my_grep -E "(ab|a).(d|cd)[x-z]" ~nimrodav/grep_tests/in15 | diff ~nimrodav/grep_tests/out15 -
