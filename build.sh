#!/usr/bin/env bash

# set the stack memory to unlimited
ulimit -s unlimited

# build the program
gcc GameOfLife.c -o GameOfLife -lraylib
