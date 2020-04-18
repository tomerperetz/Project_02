#! /usr/bin/env bash

cat ./tests/3lines | ./my_grep bla | diff ./tests/out3 -
