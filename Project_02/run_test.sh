#! /usr/bin/env bash
./my_grep -A 13 -n -i bla text.txt
./my_grep -A13 bla
./my_grep -i 0123456789ABCDEFGHIJKLMN "OPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz[\]^_,{|}~:;<=>?@!""#$%&''()*+-./"