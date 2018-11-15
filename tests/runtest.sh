#!/bin/bash

# Usage  : sh runtest.sh TEST_TYPE NODE TEST_NAME
# Example: sh runtest.sh integration node2 ir_test.c

# Enter correct test dir
cd $1

# Move old main.c out of the way
mkdir /tmp/byggerntest
mv ../../$2/src/main.c /tmp/byggerntest

# Replace main.c with test file
cp $3 ../../$2/src/main.c

# Enter node dir
cd ../../$2

# Make (requires sudo, test will prompt for password)
sudo make flash

# Move main file back and delete tmp dir
mv /tmp/byggerntest/main.c src
rm -rf /tmp/byggerntest
