#! /usr/bin/env bash

./my_grep a ./tests/emptyfile | diff ./tests/emptyfile -
