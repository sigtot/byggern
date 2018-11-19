#!/bin/bash

# Usage  : sh TYPE/TEST
# Example: sh integration/ir_test.c

testdir="$PWD"
tempdir=$(( $RANDOM ))
# Move old main.c out of the way
mkdir /tmp/$tempdir
mv ../src/main.c /tmp/$tempdir

# Move main file back and delete tmp dir
function finish {
    cd "$testdir/../src"
    mv /tmp/$tempdir/main.c .
    rm -rf /tmp/$tempdir
}

trap finish EXIT
# Replace main.c with test file
cp $1 ../src/main.c

# Change dir to node root
cd ..

# Make (requires sudo, test will prompt for password)
sudo make clean
sudo make flash
