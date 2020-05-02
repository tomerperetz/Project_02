#! /usr/bin/env bash

valgrind --quiet --leak-check=yes ./my_grep -x bla ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out3 -
valgrind --quiet --leak-check=yes ./my_grep -E "(bla|bli)" ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out11 -
valgrind --quiet --leak-check=yes ./my_grep -E "(bla|li)" ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out11 -
valgrind --quiet --leak-check=yes ./my_grep -E "r(i|A).[y-z]\." ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out13 -
cat ~nimrodav/grep_tests/my_grep | valgrind --quiet --leak-check=yes ./my_grep my_grep | diff ~nimrodav/grep_tests/my_grep_out -
valgrind --quiet --leak-check=yes ./my_grep a ~nimrodav/grep_tests/emptyfile | diff ~nimrodav/grep_tests/emptyfile -
valgrind --quiet --leak-check=yes ./my_grep bla ~nimrodav/grep_tests/bla | diff ~nimrodav/grep_tests/bla -
valgrind --quiet --leak-check=yes ./my_grep bla ~nimrodav/grep_tests/3lines | diff ~nimrodav/grep_tests/out3 -
cat ~nimrodav/grep_tests/3lines | valgrind --quiet --leak-check=yes ./my_grep bla | diff ~nimrodav/grep_tests/out3 -
valgrind --quiet --leak-check=yes ./my_grep -n -i -E "o\.pdf" ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out5 -
valgrind --quiet --leak-check=yes ./my_grep -A 2 -n -i io ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out6 -
valgrind --quiet --leak-check=yes ./my_grep -b -i -E "o\.pdf" ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out7 -
valgrind --quiet --leak-check=yes ./my_grep -c -i -E "o\.pdf" ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out8 -
valgrind --quiet --leak-check=yes ./my_grep -v -i -E "o\.pdf" ~nimrodav/grep_tests/2013.html | diff ~nimrodav/grep_tests/out9 -
