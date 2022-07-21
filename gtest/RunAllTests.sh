#!/bin/bash

# Get directory of this script
currentDir=$(dirname $(readlink -f $0))

# Run all tests and safe the results in a file
cd $currentDir/build/
./networktester --gtest_output=json:$currentDir/results.json
