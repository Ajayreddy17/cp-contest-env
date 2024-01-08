#!/bin/bash

num=${1:-20}

for tc_num in $(seq 1 $num); do
    echo Running $tc_num
    ./gen.exe > in.txt
    ./sol.exe < in.txt > solout.txt
    ./naive.exe < in.txt > naiveout.txt

    if diff -b -Z -B "solout.txt" "naiveout.txt"; then
        echo Passed
    else
        echo failed
        ./output.exe 0
        exit
    fi
done
./output.exe 1

