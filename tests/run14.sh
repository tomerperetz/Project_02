#! /usr/bin/env bash

cat ~nimrodav/grep_tests/in14 | ./my_grep -A 2 my_grep | diff ~nimrodav/grep_tests/out14 -

cat ~nimrodav/grep_tests/in14 | valgrind --quiet --leak-check=yes ./my_grep -A 2 my_grep | diff ~nimrodav/grep_tests/out14 -
