#! /usr/bin/env bash

./my_grep bla ~nimrodav/grep_tests/bla | diff ~nimrodav/grep_tests/bla -

valgrind --quiet --leak-check=yes ./my_grep bla ~nimrodav/grep_tests/bla | diff ~nimrodav/grep_tests/bla -

