#! /usr/bin/env bash

./my_grep -x bla ~nimrodav/grep_tests/in10 | diff ~nimrodav/grep_tests/out10 -

valgrind --quiet --leak-check=yes ./my_grep -x bla ~nimrodav/grep_tests/in10 | diff ~nimrodav/grep_tests/out10 -
