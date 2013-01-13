#!/bin/bash

for f in texts/*
do
    ./speller $f | head -n -10 | tr [:upper:] [:lower:] | sort | uniq > results/$(basename $f)
    echo $f
done
