#!/bin/bash
echo "====== STARTING INTEGRATION TESTS ======"
for f in $(find . -name '*.c'); do
    echo "Running $f"
    ./runtest.sh $f
    read -p "Press enter to continue to next test..."
done
echo "==== FINISHED ALL INTEGRATION TESTS ===="
