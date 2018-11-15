#!/bin/bash

# Usage  : sh TYPE/TEST
# Example: sh integration/ir_test.c

tempdir=$(( $RANDOM ))
# Move old main.c out of the way
mkdir /tmp/$tempdir
mv ../src/main.c /tmp/$tempdir

# Replace main.c with test file
cp $1 ../src/main.c

# Change dir to node root
cd ..

# Make (requires sudo, test will prompt for password)
sudo make flash

# Move main file back and delete tmp dir
mv /tmp/$tempdir/main.c src
rm -rf /tmp/$tempdir
