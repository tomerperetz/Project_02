#! /usr/bin/env bash

./my_grep -E "(bla|bli)" ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out11 -

valgrind --quiet --leak-check=yes ./my_grep -E "(bla|bli)" ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out11 -
